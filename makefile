#-I/usr/local/include -L/usr/local/lib
program:ex.o
	g++ `pkg-config --cflags gtk+-3.0` ex.cpp common.h common.cpp common_platform.h common_platform.cpp `pkg-config --libs gtk+-3.0` -lSDL2 -lSDL2_mixer -I/usr/local/include -L/usr/local/lib -lfmod 
ex.o:
	g++ -c ex.cpp
