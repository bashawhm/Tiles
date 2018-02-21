#include "stage.h"
#include "type.h"
#include "SDL2/SDL_image.h"


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
		
		//Load texture for new game button
		SDL_Surface *newGameSur = IMG_Load("assets/newGame.png");
		SDL_Texture *newGameTex = SDL_CreateTextureFromSurface(stage -> renderer, newGameSur);
		SDL_FreeSurface(newGameSur);


		//Create rectangle for exit button
		SDL_Rect exitButton;
		exitButton.x = (width / 2) - EXITBUTTONXOFFSET;
		exitButton.y = (height / 2) + (height / 4);
		exitButton.w = 100;
		exitButton.h = 40;
		SDL_RenderCopy(stage -> renderer, exitTex, NULL, &exitButton);

		//New game button
		SDL_Rect newGameButton;
		newGameButton.x = (width / 2) - NEWGAMEBUTTONXOFFSET;
		newGameButton.y = (height / 2) - (height / 6);
		newGameButton.w = 200;
		newGameButton.h = 40;
		SDL_RenderCopy(stage -> renderer, newGameTex, NULL, &newGameButton);
		
		SDL_DestroyTexture(tex);
		SDL_DestroyTexture(exitTex);
		
		stage -> needsUpdate = false;
		SDL_RenderPresent(stage -> renderer);
	}
}
