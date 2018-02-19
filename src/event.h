#ifndef _EVENT_H_
#define _EVENT_H_
#include "stage.h"
#include "type.h"
#include "SDL2/SDL.h"


void startMenuInput(Stage *stage){
	SDL_Event event;
	while (SDL_PollEvent(&event)){
		switch (event.type) {
		case SDL_KEYDOWN: {
			switch (event.key.keysym.sym){
			case SDLK_ESCAPE: {
				stage -> alive = false;
				break;
			}
			
			}
			break;
		}
		case SDL_QUIT: {
			stage -> alive = false;
		}


		}
	}


}


void startGameInput(Stage *stage){



}


#endif