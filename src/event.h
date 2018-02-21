#ifndef _EVENT_H_
#define _EVENT_H_
#include "stage.h"
#include "type.h"
#include "SDL2/SDL.h"


void menuEvents(Stage *stage){
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
		case SDL_MOUSEBUTTONDOWN: {
			i32 mouseX;
			i32 mouseY;
			SDL_GetMouseState(&mouseX, &mouseY);
			//Am personally sorry for this if statement. Havent yet implenmented some form of map to check against so here we are.
			//Will change to be tolorable later.
			//Exit Button
			if ((mouseX > (stage -> screenWidth / 2) - BUTTONXOFFSET) && (mouseX < (stage -> screenWidth / 2) - BUTTONXOFFSET + 100) && (mouseY > (stage -> screenHeight / 2) + (stage -> screenHeight / 4)) && (mouseY < (stage -> screenHeight / 2) + (stage -> screenHeight / 4) + BUTTONXOFFSET)){
				stage -> alive = false;
			}


			break;
		}
		case SDL_WINDOWEVENT_RESIZED: {
			//resize code goes here!
			break;
		}
		case SDL_QUIT: {
			stage -> alive = false;
			break;
		}


		}
	}


}


void gameEvents(Stage *stage){



}


#endif