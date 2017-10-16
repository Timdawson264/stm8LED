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

struct pixle{
	uint16_t R;
	uint16_t G;
	uint16_t B;
};

void sendcolor( int fd, struct pixle* p, size_t n )
{
	ssize_t r = write(fd, (void*)p, 6*n);
	if( r == -1 ) abort();
}

void HSVtoRGB(float h, float s, float v, struct pixle* out) 
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
	//TODO: Set baud rate and calculate max number of updates/s with said baudrate and number of pixels
	int fd = open( argv[1], O_WRONLY);
	if( fd == -1)
	{
		printf( "Failed to open file: %s\n", argv[1] ); 
		exit(1);
	}

	//Set Baud Rate
	struct termios2 tio;
	ioctl(fd, TCGETS2, &tio);
	tio.c_cflag &= ~CBAUD;
	tio.c_cflag |= BOTHER;
	tio.c_ispeed = 1000000;
	tio.c_ospeed = 1000000;
	ioctl(fd, TCSETS2, &tio);


	struct pixle p1 = {UINT16_MAX,0,0};
	struct pixle p2 = {0,UINT16_MAX,0};
	struct pixle p3 = {0,0,UINT16_MAX};

	sendcolor( fd, &p1, 1 ); 
	sleep(1);
	sendcolor( fd, &p2, 1 ); 
	sleep(1);
	sendcolor( fd, &p3, 1 ); 
	sleep(1);

	double  h = 0;
	double step = 0.00005;
	size_t sleep_len = ( 60*1000000 ) / ( 1.0f / step ) ;
	printf( "Sleep size: %zu us\n", sleep_len ); 
	struct pixle p = {0,0,0};
	while(1)
	{
		HSVtoRGB( h, 1, 0.01f, &p);
		//printf( "H: %f, R: %hu, G: %hu, B: %hu\n", h, p.R, p.G, p.B );
		sendcolor( fd, &p, 1 );
		usleep( sleep_len );

		h = fmod( (h+step), 1.0f );
	}


	return 0;
}
