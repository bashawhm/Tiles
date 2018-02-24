#include <stdio.h>
#include "stage.h"
#include "type.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"


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
			if ((mouseX > (stage -> screenWidth / 2) - EXITBUTTONXOFFSET) && (mouseX < (stage -> screenWidth / 2) - EXITBUTTONXOFFSET + 100) && (mouseY > (stage -> screenHeight / 2) + (stage -> screenHeight / 4)) && (mouseY < (stage -> screenHeight / 2) + (stage -> screenHeight / 4) + EXITBUTTONXOFFSET)){
				stage -> alive = false;
			}
			//New Game Button
			if ((mouseX > ((stage -> screenWidth / 2) - NEWGAMEBUTTONXOFFSET)) && (mouseX < ((stage -> screenWidth / 2) - NEWGAMEBUTTONXOFFSET + 200)) && (mouseY > ((stage -> screenHeight / 2) - (stage -> screenHeight / 6))) && (mouseY < (stage -> screenHeight / 2) - (stage -> screenHeight / 6) + 40)){
				//Spawn new Game
				initTiles(stage);
				stage -> needsUpdate = true;
				stage -> currState = GameMode;
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
	SDL_Event event;
	while (SDL_PollEvent(&event)){
		switch (event.type) {
		case SDL_KEYDOWN: {
			switch (event.key.keysym.sym){
			case SDLK_ESCAPE: {
				//Go back to main menu
				stage -> currState = MenuMode;
				stage -> needsUpdate = true;
				break;
			}

			}
			break;
		}
		case SDL_MOUSEBUTTONDOWN: {
			i32 mouseX;
			i32 mouseY;
			SDL_GetMouseState(&mouseX, &mouseY);
			//This is messy sorry. Haven't /yet/ figured out a clean way to fix it.
			//Bulldozer button
			if (mouseX > (WINWIDTH - (WINWIDTH / TILENUM)) && (mouseX < (WINWIDTH - (WINWIDTH / TILENUM) + (WINWIDTH / TILENUM))) && (mouseY > (WINHEIGHT - 2 * (WINHEIGHT / TILENUM))) && (mouseY < (WINHEIGHT - 2 * (WINHEIGHT / TILENUM) + (WINHEIGHT / TILENUM)))) {
				if (stage -> stagedEvent == None){
					stage -> stagedEvent = Bulldozer;
				// Else if required for when there are more than two states of stagedEvent
				} else if (stage -> stagedEvent == Bulldozer) {
					stage -> stagedEvent = None;
				}
			}

			i32 tileX = (mouseX / (stage -> screenWidth / TILENUM));
			i32 tileY = (mouseY / (stage -> screenHeight / TILENUM));
			// printf("tileX: %d  |  tileY %d\n", tileX, tileY);
			if (stage -> stagedEvent == Bulldozer){
				stage -> game -> tiles[tileX][tileY].type = Normal;
			// Else if required for when there are more than two states of stagedEvent
			} else if (stage -> stagedEvent == None) {
				stage -> game -> tiles[tileX][tileY].type = Dark;
			}
			stage -> needsUpdate = true;
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

