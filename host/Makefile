CC=gcc
CXX=g++
CFLAGS=-ggdb -lm -O0
CXXFLAGS=-ggdb -O0 -lfftw3f -Lrtaudio -lrtaudio -lm

all: rainbow pulse music

% : %.c pixel.h
	$(CC) $(CFLAGS) $< -o $@

% : %.cc pixel.h
	$(CXX) $< $(CXXFLAGS) -o $@
