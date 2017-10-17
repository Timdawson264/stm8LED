CC=clang-3.8
CXX=clang++-3.8
CFLAGS=-ggdb -lm -O3
CXXFLAGS=-ggdb -O0 -Irtaudio -lm  -lfftw3f -Lrtaudio -lrtaudio -rpath rtaudio/

all: rainbow pulse music

% : %.c pixel.h
	$(CC) $(CFLAGS) $< -o $@

% : %.cc pixel.h
	$(CXX) $< $(CXXFLAGS) -o $@
