#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "pixel.h"

const size_t update_rate = 120;
const float  pulse_freq_hz = 0.25f;

int main( int argc, char** argv )
{

    int fd = pixel_init( argv[1] );

    // output = A * sin( F*t );
    const float PI = 3.14159265;
    const size_t usleep_time = 1e6/update_rate;
    const float offset = 0.025f;

    struct pixel p = { UINT16_MAX, 0, 0 };

    float time = 0;
    while(1)
    {
        //offset sin by one and divide by 2 - so the sine is 0-1;
        float amp = ( ( cos( 2.0f * PI * pulse_freq_hz * time ) + 1.0f + offset ) / (2+offset) );


        struct pixel ptmp = { amp * p.R,  amp * p.G,  amp * p.B };
        pixel_sendcolor( fd, &ptmp, 1 );

        usleep( usleep_time );
        time += 1.0f/update_rate;
        time = fmod ( time , 1.0f/pulse_freq_hz  );
    }

    return 0;
}

