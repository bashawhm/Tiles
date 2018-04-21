#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "type.h"
#include "stage.h"



void updateEcon(Stage *stage){
	i64 moneyToAdd = 0;
	for (i32 i = 0; i < TILENUM; ++i){
		for (i32 j = 0; j < TILENUM; ++j){
			if (stage -> game -> tiles[i][j].type == Residential){
				moneyToAdd += (RESTAXBASE * stage -> game -> econ -> resTaxRate);
			}
		}
	}
	stage -> game -> econ -> money += moneyToAdd;
	stage -> needsUpdate = true;
}

i64 getTotalMoney(Stage *stage){
	// return 0;
	return stage -> game -> econ -> money;
}

