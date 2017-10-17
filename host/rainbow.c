#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <sys/ioctl.h>

#include <asm-generic/termbits.h>

#include "pixel.h"

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

int main( int argc, char** argv )
{

    int fd = pixel_init( argv[1] );


	double  h = 0;
	double step = 0.00005;
	size_t sleep_len = ( 60*1000000 ) / ( 1.0f / step ) ;
	printf( "Sleep size: %zu us\n", sleep_len );
    struct pixel p = {0,0,0};
	while(1)
	{
		HSVtoRGB( h, 1, 0.5f, &p);
		//printf( "H: %f, R: %hu, G: %hu, B: %hu\n", h, p.R, p.G, p.B );
        pixel_sendcolor( fd, &p, 1 );
		usleep( sleep_len );

		h = fmod( (h+step), 1.0f );
	}


	return 0;
}
