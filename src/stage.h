#ifndef _STAGE_H_
#define _STAGE_H_
#include "type.h"


typedef enum State{
	Menu,
	Game,
} State;


typedef struct Stage {
	SDL_Window * window;
	SDL_Renderer * renderer;
	bool needsUpdate;


	bool alive;
	State currState;
} Stage;


Stage * newGame(SDL_Window *win, SDL_Renderer *ren, State newState){
	Stage *newStage = (Stage *)malloc(sizeof(Stage));
	newStage -> window = win;
	newStage -> renderer = ren;
	newStage -> alive = true;
	newStage -> currState = newState;
	newStage -> needsUpdate = true;
	return newStage;
}

#endif