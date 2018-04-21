#include "stage.h"
#include "type.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

void renderLegend(Stage *);


void initTiles(Stage *stage) {
	for (i32 i = 0; i < TILENUM; ++i){
		for (i32 j = 0; j < TILENUM; ++j){
			stage -> game -> tiles[i][j].type = Normal;
		}
	}
	for (i32 i = 0; i < TILENUM; ++i){
		for (i32 j = 0; j < TILENUM; ++j){
			stage -> game -> tiles[i][j].tile.x = ((stage -> screenWidth / TILENUM) * i);
			stage -> game -> tiles[i][j].tile.y = ((stage -> screenHeight / TILENUM) * j);
			stage -> game -> tiles[i][j].tile.w = (stage -> screenWidth / TILENUM);
			stage -> game -> tiles[i][j].tile.h = (stage -> screenHeight / TILENUM);
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

		SDL_Surface *houseSur = IMG_Load("assets/house.png");
		SDL_Texture *houseTex = SDL_CreateTextureFromSurface(stage -> renderer, houseSur);
		SDL_FreeSurface(houseSur);


		for (i32 i = 0; i < TILENUM; ++i){
			for (i32 j = 0; j < TILENUM; ++j){
				if ((stage -> game -> tiles[i][j].type) == Normal){
					SDL_RenderCopy(stage -> renderer, tileTex, NULL, &(stage -> game -> tiles[i][j].tile));
				} else if ((stage -> game -> tiles[i][j].type) == Dark) {
					SDL_RenderCopy(stage -> renderer, dTileTex, NULL, &(stage -> game -> tiles[i][j].tile));
				} else if ((stage -> game -> tiles[i][j].type) == Residential) {
					SDL_RenderCopy(stage -> renderer, houseTex, NULL, &(stage -> game -> tiles[i][j].tile));
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
		legend.y = stage -> screenHeight - (2 * (stage -> screenHeight / TILENUM));
		legend.w = stage -> screenWidth;
		legend.h = (2 * (stage -> screenHeight / TILENUM));
		SDL_RenderCopy(stage -> renderer, legTex, NULL, &legend);

		//Render Bulldozer
		SDL_Surface *bullSur = NULL;
		if (stage -> stagedEvent != Bulldozer) {
			bullSur = IMG_Load("assets/bulldozer.png");
		} else if (stage -> stagedEvent == Bulldozer) {
			bullSur = IMG_Load("assets/bulldozerDark.png");
		}
		SDL_Surface *resSur = NULL;
		if (stage -> stagedEvent != House) {
			resSur = IMG_Load("assets/houseButton.png");
		} else if (stage -> stagedEvent == House) {
			resSur = IMG_Load("assets/houseButtonDark.png");
		}
		TTF_Font *bankFont = TTF_OpenFont("assets/Lato.ttf", 200);
		SDL_Color fontColor = {255, 255, 255, 255};


		char bankVal[100];
		sprintf(bankVal, "$%d", getTotalMoney(stage));

		SDL_Surface *bankSur = TTF_RenderText_Solid(bankFont, bankVal, fontColor);
		SDL_Texture *bankTex = SDL_CreateTextureFromSurface(stage -> renderer, bankSur);
		SDL_FreeSurface(bankSur);

		SDL_Texture *bullTex = SDL_CreateTextureFromSurface(stage -> renderer, bullSur);
		SDL_FreeSurface(bullSur);

		SDL_Texture *houseTex = SDL_CreateTextureFromSurface(stage -> renderer, resSur);
		SDL_FreeSurface(resSur);

		SDL_Rect bullButton;
		bullButton.x = (stage -> screenWidth - (stage -> screenWidth / TILENUM));
		bullButton.y = (stage -> screenHeight - 2 * (stage -> screenHeight / TILENUM));
		bullButton.w = (stage -> screenWidth / TILENUM);
		bullButton.h = (stage -> screenHeight / TILENUM);
		SDL_RenderCopy(stage -> renderer, bullTex, NULL, &bullButton);

		SDL_Rect resButton;
		resButton.x = ((2 * (stage -> screenWidth / TILENUM)));
		resButton.y = (stage -> screenHeight - 2 * (stage -> screenHeight / TILENUM));
		resButton.w = (stage -> screenWidth / TILENUM);
		resButton.h = (stage -> screenHeight / TILENUM);
		SDL_RenderCopy(stage -> renderer, houseTex, NULL, &resButton);


		SDL_Rect bankBox;
		bankBox.x = 0;
		bankBox.y = (stage -> screenHeight - (stage -> screenHeight / TILENUM));
		bankBox.w = 2 * (stage -> screenWidth / TILENUM);
		bankBox.h = (stage -> screenHeight / TILENUM);
		SDL_RenderCopy(stage -> renderer, bankTex, NULL, &bankBox);

	}
}

