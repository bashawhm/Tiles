#include "stage.h"
#include "type.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

void renderLegend(Stage *);


void initTiles(Stage *stage) {
	for (i32 i = 0; i < TILENUM; ++i){
		for (i32 j = 0; j < TILENUM; ++j){
			stage -> game -> tiles[i][j].type = Normal;
		}
	}
	for (i32 i = 0; i < TILENUM; ++i){
		for (i32 j = 0; j < TILENUM; ++j){
			stage -> game -> tiles[i][j].tile.x = ((WINWIDTH / TILENUM) * i);
			stage -> game -> tiles[i][j].tile.y = ((WINHEIGHT / TILENUM) * j);
			stage -> game -> tiles[i][j].tile.w = (WINWIDTH / TILENUM);
			stage -> game -> tiles[i][j].tile.h = (WINHEIGHT / TILENUM);
		}
	}
}

void renderGame(Stage *stage){
	if (stage -> needsUpdate){
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

		SDL_Surface *dTileSur = IMG_Load("assets/darkTile.png");
		SDL_Texture *dTileTex = SDL_CreateTextureFromSurface(stage -> renderer, dTileSur);
		SDL_FreeSurface(dTileSur);

		for (i32 i = 0; i < TILENUM; ++i){
			for (i32 j = 0; j < TILENUM; ++j){
				if ((stage -> game -> tiles[i][j].type) == Normal){
					SDL_RenderCopy(stage -> renderer, tileTex, NULL, &(stage -> game -> tiles[i][j].tile));
				} else if ((stage -> game -> tiles[i][j].type) == Dark) {
					SDL_RenderCopy(stage -> renderer, dTileTex, NULL, &(stage -> game -> tiles[i][j].tile));
				}
			}
		}
		renderLegend(stage);
		SDL_RenderPresent(stage -> renderer);
		stage -> needsUpdate = false;
	}
}

void renderLegend(Stage *stage){
	if (stage -> needsUpdate){
		//Render Legend
		SDL_Surface *legSur = IMG_Load("assets/legend.png");
		SDL_Texture *legTex = SDL_CreateTextureFromSurface(stage -> renderer, legSur);
		SDL_FreeSurface(legSur);

		SDL_Rect legend;
		legend.x = 0;
		legend.y = WINHEIGHT - (2 * WINHEIGHT / TILENUM);
		legend.w = WINWIDTH;
		legend.h = (2 * WINHEIGHT / TILENUM);
		SDL_RenderCopy(stage -> renderer, legTex, NULL, &legend);

		//Render Bulldozer
		SDL_Surface *bullSur = IMG_Load("assets/bulldozer.png");
		SDL_Texture *bullTex = SDL_CreateTextureFromSurface(stage -> renderer, bullSur);
		SDL_FreeSurface(bullSur);

		SDL_Rect bullButton;
		bullButton.x = (WINWIDTH - (WINWIDTH / TILENUM));
		bullButton.y = (WINHEIGHT - 2 * (WINHEIGHT / TILENUM));
		bullButton.w = (WINWIDTH / TILENUM);
		bullButton.h = (WINHEIGHT / TILENUM);
		SDL_RenderCopy(stage -> renderer, bullTex, NULL, &bullButton);


	}
}

