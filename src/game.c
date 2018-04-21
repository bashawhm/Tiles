#include "stage.h"
#include "type.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

void renderLegend(Stage *);

void initTex(Stage *stage){

	SDL_Surface *backSur = IMG_Load("assets/menu.png");
	stage -> game -> background = SDL_CreateTextureFromSurface(stage -> renderer, backSur);
	SDL_FreeSurface(backSur);

	SDL_Surface *tileSur = IMG_Load("assets/tile.png");
	stage -> game -> tileTex = SDL_CreateTextureFromSurface(stage -> renderer, tileSur);
	SDL_FreeSurface(tileSur);

	SDL_Surface *dTileSur = IMG_Load("assets/darkTile.png");
	stage -> game -> dTileTex = SDL_CreateTextureFromSurface(stage -> renderer, dTileSur);
	SDL_FreeSurface(dTileSur);

	SDL_Surface *houseSur = IMG_Load("assets/house.png");
	stage -> game -> houseTex = SDL_CreateTextureFromSurface(stage -> renderer, houseSur);
	SDL_FreeSurface(houseSur);

	//Legend Stuff
	SDL_Surface *legSur = IMG_Load("assets/legend.png");
	stage -> game -> legTex = SDL_CreateTextureFromSurface(stage -> renderer, legSur);
	SDL_FreeSurface(legSur);

	stage -> game -> bullSur = IMG_Load("assets/bulldozer.png");
	stage -> game -> bullSurDark = IMG_Load("assets/bulldozerDark.png");

	stage -> game -> resSur = IMG_Load("assets/houseButton.png");
	stage -> game -> resSurDark = IMG_Load("assets/houseButtonDark.png");

	stage -> game -> font = TTF_OpenFont("assets/Lato.ttf", 200);
}


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
	SDL_Rect gameFrame;
	gameFrame.x = 0;
	gameFrame.y = 0;
	gameFrame.w = stage -> screenWidth;
	gameFrame.h = stage -> screenHeight;

	//Load texture into gameFrame
	SDL_RenderCopy(stage -> renderer, stage -> game -> background, NULL, &gameFrame);

	for (i32 i = 0; i < TILENUM; ++i){
		for (i32 j = 0; j < TILENUM; ++j){
			if ((stage -> game -> tiles[i][j].type) == Normal){
				SDL_RenderCopy(stage -> renderer, stage -> game -> tileTex, NULL, &(stage -> game -> tiles[i][j].tile));
			} else if ((stage -> game -> tiles[i][j].type) == Dark) {
				SDL_RenderCopy(stage -> renderer, stage -> game -> dTileTex, NULL, &(stage -> game -> tiles[i][j].tile));
			} else if ((stage -> game -> tiles[i][j].type) == Residential) {
				SDL_RenderCopy(stage -> renderer, stage -> game -> houseTex, NULL, &(stage -> game -> tiles[i][j].tile));
			}
		}
	}
	renderLegend(stage);
	SDL_RenderPresent(stage -> renderer);
	stage -> needsUpdate = false;
	
}

void renderLegend(Stage *stage){
	
	SDL_Rect legend;
	legend.x = 0;
	legend.y = stage -> screenHeight - (2 * (stage -> screenHeight / TILENUM));
	legend.w = stage -> screenWidth;
	legend.h = (2 * (stage -> screenHeight / TILENUM));
	SDL_RenderCopy(stage -> renderer, stage -> game -> legTex, NULL, &legend);

	/*
	SDL_Surface *resSur = NULL;
	if (stage -> stagedEvent != House) {
		resSur = IMG_Load("assets/houseButton.png");
	} else if (stage -> stagedEvent == House) {
		resSur = IMG_Load("assets/houseButtonDark.png");
	}
	*/
	
	SDL_Color fontColor = {255, 255, 255, 255};

	char timeVal[100]; 
	if ((stage -> current - stage -> start) % 60 > 9){
		sprintf(timeVal, "%ld:%ld", ((stage -> current - stage -> start) / 60) % 24, (stage -> current - stage -> start) % 60);
	} else {
		sprintf(timeVal, "%ld:0%ld", ((stage -> current - stage -> start) / 60) % 24, (stage -> current - stage -> start) % 60);
	}

	SDL_Surface *timeSur = TTF_RenderText_Solid(stage -> game -> font, timeVal, fontColor);
	SDL_Texture *timeTex = SDL_CreateTextureFromSurface(stage -> renderer, timeSur);
	SDL_FreeSurface(timeSur);

	char bankVal[100];
	sprintf(bankVal, "$%d", getTotalMoney(stage));

	SDL_Surface *bankSur = TTF_RenderText_Solid(stage -> game -> font, bankVal, fontColor);
	SDL_Texture *bankTex = SDL_CreateTextureFromSurface(stage -> renderer, bankSur);
	SDL_FreeSurface(bankSur);


	SDL_Texture *bullTex = NULL;
	if (stage -> stagedEvent != Bulldozer){
		bullTex = SDL_CreateTextureFromSurface(stage -> renderer, stage -> game -> bullSur);
	} else {
		bullTex = SDL_CreateTextureFromSurface(stage -> renderer, stage -> game -> bullSurDark);
	}

	SDL_Texture *houseTex = NULL;
	if (stage -> stagedEvent != House){
		houseTex = SDL_CreateTextureFromSurface(stage -> renderer, stage -> game -> resSur);
	} else {
		houseTex = SDL_CreateTextureFromSurface(stage -> renderer, stage -> game -> resSurDark);
	}


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

	SDL_Rect timeBox;
	timeBox.x = (stage -> screenWidth - (stage -> screenWidth / TILENUM));
	timeBox.y = (stage -> screenHeight - (stage -> screenHeight / TILENUM));
	timeBox.w = (stage -> screenWidth / TILENUM);
	timeBox.h = (stage -> screenHeight / TILENUM);
	SDL_RenderCopy(stage -> renderer, timeTex, NULL, &timeBox);

	SDL_DestroyTexture(timeTex);
	SDL_DestroyTexture(bankTex);
	SDL_DestroyTexture(bullTex);
	SDL_DestroyTexture(houseTex);
	

}

