#include "pixel.h"

#include <cmath>
#include <RtAudio.h>
#include <fftw3.h>
#include <cstring>
#include <algorithm>

typedef struct {
    double r;       // a fraction between 0 and 1
    double g;       // a fraction between 0 and 1
    double b;       // a fraction between 0 and 1
} rgb;

typedef struct {
    double h;       // angle in degrees
    double s;       // a fraction between 0 and 1
    double v;       // a fraction between 0 and 1
} hsv;

rgb hsv2rgb(hsv in)
{
    double      hh, p, q, t, ff;
    long        i;
    rgb         out;

    if(in.s <= 0.0) {       // < is bogus, just shuts up warnings
        out.r = in.v;
        out.g = in.v;
        out.b = in.v;
        return out;
    }
    hh = in.h;
    if(hh >= 360.0) hh = 0.0;
    hh /= 60.0;
    i = (long)hh;
    ff = hh - i;
    p = in.v * (1.0 - in.s);
    q = in.v * (1.0 - (in.s * ff));
    t = in.v * (1.0 - (in.s * (1.0 - ff)));

    switch(i) {
        case 0:
            out.r = in.v;
            out.g = t;
            out.b = p;
            break;
        case 1:
            out.r = q;
            out.g = in.v;
            out.b = p;
            break;
        case 2:
            out.r = p;
            out.g = in.v;
            out.b = t;
            break;

        case 3:
            out.r = p;
            out.g = q;
            out.b = in.v;
            break;
        case 4:
            out.r = t;
            out.g = p;
            out.b = in.v;
            break;
        case 5:
        default:
            out.r = in.v;
            out.g = p;
            out.b = q;
            break;
    }
    return out;
}

struct context
{
    size_t n;
    float* in_buffer;
    fftwf_complex* out_buffer;
    float* processed;
    fftwf_plan plan;
    pixel pix;
    int pix_fd;
    float all_time_max;
    float h_offset; //Running offset of colour - just to change the colour up
    float h_offset_step;
};


int record( void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
            double streamTime, RtAudioStreamStatus status, void *userData )
{
    context* ctx = (context*)userData;
    const size_t fft_size = ctx->n;
    const size_t fft_half = ctx->n / 2;
    const size_t new_data_count = nBufferFrames;
    const float* inputBuffer_f = (float*) inputBuffer;

    if ( status )
        std::cout << "Stream overflow detected!" << std::endl;
    // Do something with the data in the "inputBuffer" buffer.
//     std::cout << "Record: " << nBufferFrames << std::endl;

    if( new_data_count > fft_size )
    {
        std::cerr << "To many samples in record callback" << std::endl;
        abort();
    }

    size_t in_buffer_off = (fft_size - new_data_count);

    //shift FFT input down and append new data to end.
    std::memcpy( ctx->in_buffer, ctx->in_buffer+new_data_count, in_buffer_off*sizeof(float) );

    //add new data and hann window it.
    for (size_t i = 0; i < new_data_count; i++)
    {
        double multiplier = 0.5 * ( 1 - cos(2*M_PI*i/fft_size) );
        ctx->in_buffer[i+in_buffer_off] = multiplier * inputBuffer_f[i];
    }

    //DO FFT
    fftwf_execute( ctx->plan );

    for(size_t i=0; i<fft_half; i++)
    {
        ctx->out_buffer[i][0] *= 2.0/fft_size;
        ctx->out_buffer[i][1] *= 2.0/fft_size;
        ctx->processed[i] = powf(ctx->out_buffer[i][0], 2) + powf(ctx->out_buffer[i][1], 2); // C^2 = A^2 + B^2
        ctx->processed[i] = sqrt( std::abs( ctx->processed[i] ) ) ; // C = sqrt( C^2 )
    }

    float* max_e = std::max_element( ctx->processed, ctx->processed+fft_half );

    //Track the Dynamic range
    ctx->all_time_max = std::max( ctx->all_time_max, *max_e ); //max this the new max if it wins

    //Normalize
    *max_e = *max_e/ctx->all_time_max;

    size_t max_idx = ( uintptr_t(max_e) - uintptr_t(ctx->processed) ) / sizeof(float);


    //TODO: Maybe a running average would look better - stop jaring colour changes
    float h = ( (float)max_idx/fft_half ) * 360.0; //degrees 0-360
    h = fmod( h+ctx->h_offset, 360.0 ); //offset H so the colour is always different
    ctx->h_offset = fmod( ctx->h_offset + ctx->h_offset_step, 360.0 );  //slowly change the colour over time.

    float v = *max_e;

    std::cout << "MAX_n:\t" << max_idx << "\tMAX_v:\t" << v << "\tH:\t" << h << std::endl;

    float gamma = 2.2f;

    hsv in = { h , 1, v };
    rgb out = hsv2rgb( in );
    //inline gamma correction
    pixel p = { pow(out.r,gamma)*UINT16_MAX, pow(out.g,gamma)*UINT16_MAX, pow(out.b,gamma)*UINT16_MAX };
    ctx->pix = p;

    pixel_sendcolor( ctx->pix_fd, &ctx->pix, 1 );

    return 0;
}



int main( int argc, char** argv )
{

    int fd = pixel_init( argv[1] );
    if( fd == -1 ) return 1;

    context ctx = {0};
    ctx.pix_fd = fd;
    RtAudio adc(RtAudio::LINUX_PULSE);

    if ( adc.getDeviceCount() < 1 ) {
        std::cout << "\nNo audio devices found!\n";
        exit( 2 );
    }
    else
    {
        size_t count = adc.getDeviceCount() ;
        std::cerr << "N Devices: " << count << std::endl;
        for( size_t i=0; i<count; i++ )
        {
            RtAudio::DeviceInfo info = adc.getDeviceInfo( i );
            std::cerr << "Device: " << i << " Name: " << info.name << std::endl;
        }

    }

    RtAudio::StreamParameters parameters;
    parameters.deviceId = adc.getDefaultInputDevice();
    parameters.nChannels = 1;
    parameters.firstChannel = 0;
    unsigned int sampleRate = 8000;
    size_t update_rate = 60; //LED update rate
    unsigned int bufferFrames = sampleRate / update_rate;

    //Rotate the colour wheel every 5 minutes
    ctx.h_offset_step = 360.0f / (float)(update_rate * 60 * 5 );


    ctx.n = 512 ;
    ctx.in_buffer = (float*) malloc( sizeof(float) * ctx.n );
    ctx.out_buffer = (fftwf_complex*) fftwf_malloc(sizeof(fftwf_complex) * ctx.n);
    ctx.processed = (float*) malloc( sizeof(float) * ctx.n / 2 );

    ctx.plan = fftwf_plan_dft_r2c_1d( ctx.n, ctx.in_buffer, ctx.out_buffer, FFTW_MEASURE );

    std::cerr << "FFT SIZE: " << ctx.n << std::endl;
    try {
        adc.openStream( NULL, &parameters, RTAUDIO_FLOAT32,
                        sampleRate, &bufferFrames, &record, &ctx );
        adc.startStream();
    }
    catch ( RtAudioError& e ) {
        e.printMessage();
        exit( 0 );
    }

    char input;
    std::cout << "\nRecording ... press <enter> to quit.\n";
    std::cin.get( input );

    try {
        // Stop the stream
        adc.stopStream();
    }
    catch (RtAudioError& e) {
        e.printMessage();
    }
    if ( adc.isStreamOpen() ) adc.closeStream();
    return 0;

	return 0;
}
