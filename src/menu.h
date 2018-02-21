#ifndef _MENU_H_
#define _MENU_H_
#include "stage.h"
#include "type.h"
#include "SDL2/SDL_image.h"


// typedef struct MainMenu {
		
// } MainMenu;

void renderMenu(Stage *stage){
	if (stage -> needsUpdate) {
		i32 height = stage -> screenHeight;
		i32 width = stage -> screenWidth;
		//Create the main menu UI frame
		SDL_Rect menuFrame;
		menuFrame.x = 0;
		menuFrame.y = 0;
		menuFrame.w = width;
		menuFrame.h = height;
		//Load the image onto main UI frame
		SDL_Surface *background = IMG_Load("assets/menu.png");
		SDL_Texture *tex = SDL_CreateTextureFromSurface(stage -> renderer, background);
		SDL_FreeSurface(background);
		// SDL_RenderClear(stage -> renderer);
		SDL_RenderCopy(stage -> renderer, tex, NULL, &menuFrame);
		
		
		//Load texture for exit button
		SDL_Surface *exitSur = IMG_Load("assets/exit.png");
		SDL_Texture *exitTex = SDL_CreateTextureFromSurface(stage -> renderer, exitSur);
		SDL_FreeSurface(exitSur);


		//Create rectangle for exit button
		SDL_Rect exitButton;
		exitButton.x = (width / 2) - BUTTONXOFFSET;
		exitButton.y = (height / 2) + (height / 4);
		exitButton.w = 100;
		exitButton.h = 40;
		SDL_RenderCopy(stage -> renderer, exitTex, NULL, &exitButton);
		
		SDL_DestroyTexture(tex);
		SDL_DestroyTexture(exitTex);
		
		stage -> needsUpdate = false;
		SDL_RenderPresent(stage -> renderer);
	}
}

#endif