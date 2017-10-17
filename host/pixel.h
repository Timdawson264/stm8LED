#pragma once

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

struct pixel{
        uint16_t R;
        uint16_t G;
        uint16_t B;
};

void pixel_sendcolor( int fd, struct pixel* p, size_t n )
{
        ssize_t r = write(fd, (void*)p, 6*n);
        if( r == -1 ) abort();
}

int pixel_init( char* serial )
{

    int fd = open( serial, O_WRONLY);
    if( fd == -1)
    {
        printf( "Failed to open file: %s\n", serial );
        return -1;
    }

    //Set Baud Rate
    struct termios2 tio;
    ioctl(fd, TCGETS2, &tio);
    tio.c_cflag &= ~CBAUD;
    tio.c_cflag |= BOTHER;
    tio.c_ispeed = 1000000;
    tio.c_ospeed = 1000000;
    ioctl(fd, TCSETS2, &tio);

    struct pixel p1 = {UINT16_MAX>>2,0,0};
    struct pixel p2 = {0,UINT16_MAX>>2,0};
    struct pixel p3 = {0,0,UINT16_MAX>>2};

    pixel_sendcolor( fd, &p1, 1 );
    usleep( 1e6 / 4 );
    pixel_sendcolor( fd, &p2, 1 );
    usleep( 1e6/ 4 );
    pixel_sendcolor( fd, &p3, 1 );
    usleep( 1e6/ 4 );

    return fd;
}

