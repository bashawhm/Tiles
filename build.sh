gcc -O3 -march=native -Wall `sdl2-config --cflags` `sdl2-config --libs` -lSDL2_image -lSDL2_mixer  -std=c99 src/main.c -o tiles
