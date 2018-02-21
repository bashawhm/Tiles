#ifndef _MENU_H_
#define _MENU_H_
#include "stage.h"
#include "SDL2/SDL_image.h"

// typedef struct Menu {
	
	
// } Menu;

void initMenu(Stage *stage, i32 height, i32 width){
	if (stage -> needsUpdate){
		SDL_Rect menuFrame;
		menuFrame.x = 0;
		menuFrame.y = 0;
		menuFrame.w = width;
		menuFrame.h = height;

		SDL_Surface *background = IMG_Load("assets/menu.png");
		SDL_Texture *tex = SDL_CreateTextureFromSurface(stage -> renderer, background);
		SDL_FreeSurface(background);
		// SDL_RenderClear(stage -> renderer);
		SDL_RenderCopy(stage -> renderer, tex, NULL, &menuFrame);
		
		
		SDL_Surface *exitSur = IMG_Load("assets/exit.png");
		SDL_Texture *exitTex = SDL_CreateTextureFromSurface(stage -> renderer, exitSur);
		SDL_FreeSurface(exitSur);


		SDL_Rect exitButton;
		exitButton.x = (width / 2) - 22;
		exitButton.y = (height / 2) + (height / 4);
		exitButton.w = 50;
		exitButton.h = 20;
		SDL_SetRenderDrawColor(stage -> renderer, 200, 0, 0, 255);
		// SDL_RenderFillRect(stage -> renderer, &exitButton);
		SDL_RenderCopy(stage -> renderer, exitTex, NULL, &exitButton);
		
		SDL_DestroyTexture(tex);
		SDL_DestroyTexture(exitTex);
		
		
	}
}

#endif