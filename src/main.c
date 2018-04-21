#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include "stage.h"
#include "type.h"

// void *econHandler(void *stuff);


int main(){
	initGraphics();

	Stage *stage = newStage(MenuMode, WINHEIGHT, WINWIDTH);
	initTiles(stage);

	//Main Event Loop
	while (stage -> alive){
		stage -> current = time(NULL);
		
		switch (stage -> currState){
		case GameMode: {
			if ((stage -> current - stage -> start) % 30 == 0){
				updateEcon(stage);
			}
			renderGame(stage);
			gameEvents(stage);
			break;
		}
		default: {
			renderMenu(stage);
			menuEvents(stage);
			break;
		}
		}
		//~60Hz
		usleep(16667);
	}
	destroyStage(stage);

	return 0;
}
