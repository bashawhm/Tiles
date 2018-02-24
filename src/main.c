#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include "stage.h"
#include "type.h"

int main(){
	initGraphics();

	Stage *stage = newStage(MenuMode, WINHEIGHT, WINWIDTH);
	initTiles(stage);
	renderMenu(stage);

	//Main Event Loop
	while (stage -> alive){
		switch (stage -> currState){
		case MenuMode: {
			renderMenu(stage);
			menuEvents(stage);
			break;
		}
		case GameMode: {
			renderGame(stage);
			gameEvents(stage);
			break;
		}
		}
		//~60Hz
		usleep(16667);
	}
	
	destroyStage(stage);

	return 0;
}
