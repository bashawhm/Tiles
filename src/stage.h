#pragma once
#include "type.h"
#include "SDL2/SDL.h"

typedef enum State{
	MenuMode,
	GameMode,
} State;

typedef enum Type {
	normal,
	dark,
} Type;

typedef struct Tile {
	SDL_Rect tile;
	Type type;
} Tile;

typedef struct Game {
	Tile tiles[16][16];

} Game;

typedef struct Stage {
	SDL_Window * window;
	SDL_Renderer * renderer;
	Game *game;
	
	i32 screenWidth;
	i32 screenHeight;

	State currState;
	bool alive;
	bool needsUpdate;
	char _unused[2];
	
} Stage;


static inline Stage * newGame(SDL_Window *win, SDL_Renderer *ren, State newState, i32 height, i32 width){
	Stage *newStage = (Stage *)malloc(sizeof(Stage));
	Game *game = (Game *)malloc(sizeof(Game));
	newStage -> window = win;
	newStage -> renderer = ren;
	newStage -> game = game;
	newStage -> alive = true;
	newStage -> currState = newState;
	newStage -> screenWidth = width;
	newStage -> screenHeight = height;
	newStage -> needsUpdate = true;
	return newStage;
}

