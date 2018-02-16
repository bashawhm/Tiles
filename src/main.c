#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "stage.h"

int main(){
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window * window = SDL_CreateWindow("Tiles", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);


/*
	SDL_Surface *png = IMG_Load("assets/something.png");
	SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, png);
	SDL_FreeSurface(png);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, tex, NULL, NULL);
	SDL_RenderPresent(renderer);
	SDL_Delay(5000);
	

	SDL_DestroyTexture(tex);
*/
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	return 0;
}

