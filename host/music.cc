#include "pixel.h"

#include <cmath>
#include <RtAudio.h>
#include <fftw3.h>
#include <cstring>
#include <algorithm>

void HSVtoRGB(float h, float s, float v, struct pixel* out)
{
    double r, g, b, f, p, q, t;
    size_t i;
    i = floor(h * 6);
    f = h * 6 - i;
    p = v * (1 - s);
    q = v * (1 - f * s);
    t = v * (1 - (1 - f) * s);

    switch (i % 6) {
        case 0: r = v, g = t, b = p; break;
        case 1: r = q, g = v, b = p; break;
        case 2: r = p, g = v, b = t; break;
        case 3: r = p, g = q, b = v; break;
        case 4: r = t, g = p, b = v; break;
        case 5: r = v, g = p, b = q; break;
    }

	out->R = r*UINT16_MAX;
	out->G = g*UINT16_MAX;
	out->B = b*UINT16_MAX;
}


struct context
{
    size_t n;
    float* in_buffer;
    float* out_buffer;
    fftwf_plan plan;
};


int record( void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
            double streamTime, RtAudioStreamStatus status, void *userData )
{
    context* ctx = (context*)userData;

    if ( status )
        std::cout << "Stream overflow detected!" << std::endl;
    // Do something with the data in the "inputBuffer" buffer.
//     std::cout << "Record: " << nBufferFrames << std::endl;

    if( nBufferFrames > ctx->n )
    {
        std::cerr << "To many samples in record callback" << std::endl;
        abort();
    }

    std::memcpy( (void*)ctx->in_buffer, inputBuffer, sizeof(float)*nBufferFrames );

    //DO FFT
    fftwf_execute( ctx->plan );

    float* maxe = std::max_element( ctx->in_buffer, ctx->in_buffer+ctx->n );


    return 0;
}



int main( int argc, char** argv )
{

    int fd = pixel_init( argv[1] );
    if( fd == -1 ) return 1;

    pixel p = {0};
    pixel_sendcolor( fd, &p, 1 );

    RtAudio adc;
    if ( adc.getDeviceCount() < 1 ) {
        std::cout << "\nNo audio devices found!\n";
        exit( 2 );
    }

    RtAudio::StreamParameters parameters;
    parameters.deviceId = adc.getDefaultInputDevice();
    parameters.nChannels = 1;
    parameters.firstChannel = 0;
    unsigned int sampleRate = 44100;
    unsigned int bufferFrames = 1024; // 256 sample frames

    context ctx;
    ctx.n = bufferFrames;
    ctx.in_buffer = (float*) malloc( sizeof(float) * bufferFrames );
    ctx.out_buffer = (float*) malloc( sizeof(float) * bufferFrames );
    ctx.plan = fftwf_plan_r2r_1d( bufferFrames, ctx.in_buffer, ctx.out_buffer, FFTW_DHT, FFTW_MEASURE );

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
