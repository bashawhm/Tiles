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

	u8 alive;
	State currState;
} Stage;


Stage * newGame(SDL_Window *win, SDL_Renderer *ren, u8 alive, State newState){
	Stage *newStage = (Stage *)malloc(sizeof(Stage));
	newStage -> window = win;
	newStage -> renderer = ren;
	newStage -> alive = alive;
	newStage -> currState = newState;
	return newStage;
}

#endif