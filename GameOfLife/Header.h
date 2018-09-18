#include <vector>
#include <Windows.h>

const int Xmax = 50;
const int Ymax = 50;
bool map[Xmax][Ymax];

void InitMap() {
	for (int i = 0; i < Xmax; i += 1) {
		for (int j = 0; j < Ymax; j += 1) {
			map[i][j] = false;
		}
	}
	/*Set your figure in this plase*/
	//Glaider
	map[3][1] = true;
	map[3][2] = true;
	map[3][3] = true;
	map[2][3] = true;
	map[1][2] = true;
}

//all alive cells
std::vector<COORD> Alive;
std::vector<bool> nextStepAlive;
//become alives
std::vector<COORD> BecomeAlive;

//near alive
void HowManyNear(int y,int x, int &count, bool needed) {
	count = 0;
	if (x > -1 && x < Xmax && y > -1 && y < Ymax) 
		if (map[y][x] == needed)
		if (x == 0) {
			if (y == 0) {
				if (map[0][1])count++;
				if (map[1][1])count++;
				if (map[1][0])count++;
			}
			else {
				if (y == Ymax - 1) {
					if (map[Ymax - 1][1])count++;
					if (map[Ymax - 2][1])count++;
					if (map[Ymax - 2][0])count++;
				}
				else {
					if (map[y - 1][0])count++;
					if (map[y - 1][1])count++;
					if (map[y][1])count++;
					if (map[y + 1][1])count++;
					if (map[y + 1][0])count++;
				}
			}
		}
		else {
			if (x < Xmax - 1) {
				if (y == 0) {
					if (map[0][x - 1])count++;
					if (map[1][x - 1])count++;
					if (map[1][x])count++;
					if (map[1][x + 1])count++;
					if (map[0][x + 1])count++;
				}
				else {
					if (y == Ymax - 1) {
						if (map[Ymax - 1][x - 1])count++;
						if (map[Ymax - 2][x - 1])count++;
						if (map[Ymax - 2][x])count++;
						if (map[Ymax - 2][x + 1])count++;
						if (map[Ymax - 1][x + 1])count++;
					}
					else {
						if (map[y - 1][x - 1])count++;
						if (map[y][x - 1])count++;
						if (map[y + 1][x - 1])count++;
						if (map[y - 1][x])count++;
						if (map[y + 1][x])count++;
						if (map[y - 1][x + 1])count++;
						if (map[y][x + 1])count++;
						if (map[y + 1][x + 1])count++;
					}
				}
			}
			else {
				if (y == 0) {
					if (map[0][Xmax - 2])count++;
					if (map[1][Xmax - 2])count++;
					if (map[1][Xmax - 1])count++;
				}
				else {
					if (y == Ymax - 1) {
						if (map[Ymax - 1][Xmax - 2])count++;
						if (map[Ymax - 2][Xmax - 2])count++;
						if (map[Ymax - 2][Xmax - 1])count++;
					}
					else {
						if (map[y - 1][Xmax - 1])count++;
						if (map[y - 1][Xmax - 2])count++;
						if (map[y][Xmax - 2])count++;
						if (map[y + 1][Xmax - 2])count++;
						if (map[y + 1][Xmax - 1])count++;
					}
				}
			}
		}
}

//true - alive, flase - die
int IsDie(int x, int y, bool &result) {
	if ((x > -1 && x < Xmax) && (y > -1 && y < Ymax)) {
		int count = 0;
		HowManyNear(x, y, count, true);
		if (count > 1 && count < 4) result = true;
		else result = false;
		return 1;
	}
	else return -1;
}

int IsCreate() {
	if (!Alive.empty()) {
		int count = 0, i, m;
		COORD t;
		for (i = 0; i < Alive.size(); i += 1) {			
			HowManyNear(Alive[i].X-1, Alive[i].Y-1, count,false);
			if(count==3){t.X=Alive[i].X-1; t.Y=Alive[i].Y-1; BecomeAlive.push_back(t);}
			HowManyNear(Alive[i].X-1, Alive[i].Y,   count,false);
			if(count==3){t.X=Alive[i].X-1; t.Y=Alive[i].Y  ; BecomeAlive.push_back(t);}
			HowManyNear(Alive[i].X-1, Alive[i].Y+1, count,false);
			if(count==3){t.X=Alive[i].X-1; t.Y=Alive[i].Y+1; BecomeAlive.push_back(t);}
			HowManyNear(Alive[i].X,   Alive[i].Y-1, count,false);
			if(count==3){t.X=Alive[i].X  ; t.Y=Alive[i].Y-1; BecomeAlive.push_back(t);}
			HowManyNear(Alive[i].X,   Alive[i].Y+1, count,false);
			if(count==3){t.X=Alive[i].X  ; t.Y=Alive[i].Y+1; BecomeAlive.push_back(t);}
			HowManyNear(Alive[i].X+1, Alive[i].Y-1, count,false);
			if(count==3){t.X=Alive[i].X+1; t.Y=Alive[i].Y-1; BecomeAlive.push_back(t);}
			HowManyNear(Alive[i].X+1, Alive[i].Y,   count,false);
			if(count==3){t.X=Alive[i].X+1; t.Y=Alive[i].Y  ; BecomeAlive.push_back(t);}
			HowManyNear(Alive[i].X+1, Alive[i].Y+1, count,false);
			if(count==3){t.X=Alive[i].X+1; t.Y=Alive[i].Y+1; BecomeAlive.push_back(t);}
		}
	}
	else return -1;
}