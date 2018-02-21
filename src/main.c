#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "SDL2/SDL.h"

#include "menu.h"
#include "event.h"
#include "stage.h"

#define WINHIGHT 480
#define WINWIDTH 640



int main(){
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window * window = SDL_CreateWindow("Tiles", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINWIDTH, WINHIGHT, SDL_WINDOW_SHOWN);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

	
	Stage *stage = newGame(window, renderer, MenuMode, WINHIGHT, WINWIDTH);
	initMenu(stage, WINHIGHT, WINWIDTH);
	// SDL_Delay(5000);

	//Main Event Loop
	while (stage -> alive){
		if (stage -> needsUpdate){
			SDL_RenderPresent(stage -> renderer);
			stage -> needsUpdate = false;
		}

		switch (stage -> currState){
		case MenuMode: {
			menuEvents(stage);
			break;
		}
		case GameMode: {
			gameEvents(stage);
			break;
		}
		}
		

	}
	

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	return 0;
}

