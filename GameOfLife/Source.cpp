#include "Header.h"

#define FULL_CLEAR 

void main() {
	InitMap();
	int i, j;
	bool res = true;
	COORD tmp;

#ifndef FULL_CLEAR
	for (i = 0; i < Xmax; i += 1) {
		for (j = 0; j < Ymax; j += 1) {
			if (map[i][j]) printf("%c", -37);
			else printf("%c", -80);
		}
		printf("\n");
	}
#endif 
	while (true) {	
#ifdef FULL_CLEAR
		for (i = 0; i < Xmax; i += 1) {
			for (j = 0; j < Ymax; j += 1) {
				if (map[i][j]) printf("%c", -37);
				else printf("%c", -80);
			}
			printf("\n");
	}
#endif // FULL_CLEAR
		for (i = 0; i < Xmax; i += 1) {
			for (j = 0; j < Ymax; j += 1)
				if (map[i][j]) {
					tmp.X = i; tmp.Y = j;
					Alive.push_back(tmp);
				}
		}
		//update alive->dead cells
		for (i = 0; i < Alive.size(); i += 1) {
			IsDie(Alive[i].X, Alive[i].Y, res);
			nextStepAlive.push_back(res);
			//map[Alive[i].X][Alive[i].Y] = res;
		}
		IsCreate();
		//update dead->alive
		for (i = 0; i < BecomeAlive.size(); i += 1) {
			map[BecomeAlive[i].X][BecomeAlive[i].Y] = true;
#ifndef FULL_CLEAR
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), BecomeAlive[i]);
			if (map[BecomeAlive[i].X][BecomeAlive[i].Y]) printf("%c", -37);
			else printf("%c", -80);
#endif 
		}

		for (i = 0; i < Alive.size(); i += 1) {
			map[Alive[i].X][Alive[i].Y] = nextStepAlive[i];
#ifndef FULL_CLEAR
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Alive[i]);
			if (map[Alive[i].X][Alive[i].Y]) printf("%c", -37);
			else printf("%c", -80);
#endif 
		}

		Alive.clear(); BecomeAlive.clear(); nextStepAlive.clear();
		Sleep(1000);
#ifdef FULL_CLEAR
		system("cls");
#endif // FULL_CLEAR
	}
}