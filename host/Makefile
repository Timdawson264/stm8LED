CC=clang-3.8
CXX=clang++-3.8
CFLAGS=-lm -O3
CXXFLAGS=-O3 -lm -lrtaudio -lfftw3f

all: rainbow pulse music

% : %.c pixel.h
	$(CC) $(CFLAGS) $< -o $@

% : %.cc pixel.h
	$(CXX) $(CXXFLAGS) $< -o $@
