#pragma once
#include "type.h"
#include "SDL2/SDL.h"

typedef enum State{
	MenuMode,
	GameMode,
} State;


typedef struct Stage {
	SDL_Window * window;
	SDL_Renderer * renderer;
	
	i32 screenWidth;
	i32 screenHeight;

	State currState;
	bool alive;
	bool needsUpdate;
	char _unused[2];
	
} Stage;


static inline Stage * newGame(SDL_Window *win, SDL_Renderer *ren, State newState, i32 height, i32 width){
	Stage *newStage = (Stage *)malloc(sizeof(Stage));
	newStage -> window = win;
	newStage -> renderer = ren;
	newStage -> alive = true;
	newStage -> currState = newState;
	newStage -> screenWidth = width;
	newStage -> screenHeight = height;
	newStage -> needsUpdate = true;
	return newStage;
}

