#pragma once
#include "type.h"
#include "SDL2/SDL.h"

typedef enum State{
	MenuMode,
	EscMenuMode,
	GameMode,
} State;

typedef enum TileType {
	Normal,
	Dark,
	Residential,
} TileType;

typedef enum StagedEvent {
	None,
	Bulldozer,
} StagedEvent;

typedef struct Tile {
	SDL_Rect tile;
	TileType type;
} Tile;

typedef struct Game {
	Tile tiles[TILENUM][TILENUM];

} Game;

typedef struct Stage {
	SDL_Window * window;
	SDL_Renderer * renderer;
	Game *game;
	
	i32 screenWidth;
	i32 screenHeight;

	State currState;
	StagedEvent stagedEvent;
	bool alive;
	bool needsUpdate;
	char _unused[2];
	
} Stage;


static inline Stage * newStage(State newState, i32 height, i32 width){
	Stage *newStage = (Stage *)malloc(sizeof(Stage));
	Game *game = (Game *)malloc(sizeof(Game));
	newStage -> window = SDL_CreateWindow("Tiles", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINWIDTH, WINHEIGHT, SDL_WINDOW_SHOWN);
	newStage -> renderer = SDL_CreateRenderer(newStage -> window, -1, SDL_RENDERER_PRESENTVSYNC);
	newStage -> game = game;
	newStage -> alive = true;
	newStage -> currState = newState;
	newStage -> stagedEvent = None;
	newStage -> screenWidth = width;
	newStage -> screenHeight = height;
	newStage -> needsUpdate = true;
	return newStage;
}

static inline void destroyStage(Stage * stage){
	SDL_DestroyWindow(stage -> window);
	SDL_DestroyRenderer(stage -> renderer);
	free(stage -> game);
	free(stage);
	SDL_Quit();
}

static inline void initGraphics(void){
	SDL_Init(SDL_INIT_VIDEO);
}
