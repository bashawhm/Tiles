#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "SDL2/SDL.h"

#include "stage.h"
#include "type.h"

int main(){
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window * window = SDL_CreateWindow("Tiles", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINWIDTH, WINHEIGHT, SDL_WINDOW_SHOWN);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

	
	Stage *stage = newGame(window, renderer, MenuMode, WINHEIGHT, WINWIDTH);
	initTiles(stage);
	renderMenu(stage);

	//Main Event Loop
	while (stage -> alive){
		switch (stage -> currState){
		case MenuMode: {
			renderMenu(stage);
			menuEvents(stage);
			break;
		}
		case GameMode: {
			renderGame(stage);
			gameEvents(stage);
			break;
		}
		}
		
		SDL_Delay(100);
	}
	

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	return 0;
}
