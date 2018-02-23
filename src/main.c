#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
		
		usleep(16666.7);
	}
	
	destroyStage(stage);

	return 0;
}
