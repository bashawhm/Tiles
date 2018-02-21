#include "stage.h"
#include "type.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"


void initTiles(Stage *stage) {
	for (i32 i = 0; i < 16; ++i){
		for (i32 j = 0; j < 16; ++j){
			stage -> game -> tiles[i][j].x = ((WINWIDTH / 16) * i);
			stage -> game -> tiles[i][j].y = ((WINHEIGHT / 16) * j);
			stage -> game -> tiles[i][j].w = (WINWIDTH / 16);
			stage -> game -> tiles[i][j].h = (WINHEIGHT / 16);
		}
	}
}

void renderGame(Stage *stage){
	if (stage -> needsUpdate){
		stage -> needsUpdate = false;
		SDL_Rect gameFrame;
		gameFrame.x = 0;
		gameFrame.y = 0;
		gameFrame.w = stage -> screenWidth;
		gameFrame.h = stage -> screenHeight;


		//Load some surface
		SDL_Surface *background = IMG_Load("assets/menu.png");
		SDL_Texture *tex = SDL_CreateTextureFromSurface(stage -> renderer, background);
		SDL_FreeSurface(background);
		//Load texture into gameFrame
		SDL_RenderCopy(stage -> renderer, tex, NULL, &gameFrame);

		SDL_Surface *tileSur = IMG_Load("assets/tile.png");
		SDL_Texture *tileTex = SDL_CreateTextureFromSurface(stage -> renderer, tileSur);
		SDL_FreeSurface(tileSur);

		for (i32 i = 0; i < 16; ++i){
			for (i32 j = 0; j < 16; ++j){
				SDL_RenderCopy(stage -> renderer, tileTex, NULL, &(stage -> game -> tiles[i][j]));
			}
		}

		SDL_RenderPresent(stage -> renderer);
	}
}

