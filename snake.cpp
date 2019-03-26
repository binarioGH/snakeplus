#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <list>
using namespace std;
// int lastX, latY;
// int getLatX(void){return x;}
// int getLastY(void){return y;}
#define W 119
#define S 115
#define A 97
#define D 100

void gotoxy(int x, int y);
void hidecursor(void);
void drawBorders(int bx, int by);

class Food{
private:
	int x,y;
public:
	Food(int xx, int yy){reload(xx,yy);}
	void reload(int _x, int _y){
		x = _x;
		y = _y;
		gotoxy(x,y);printf("*");
	}
	int X(void){return x;}
	int Y(void){return y;}
};

class Body{
private:
	int x, y;
	int dx, dy;
public:
	Body(int _x, int _y){
		x = _x;
		y = _y;
	}
	~Body(void){}
	int X(void){return x;}
	int Y(void){return y;}
	int lastX, lastY;
	int getLastX(void){return lastX;}
	int getLastY(void){return lastY;}
	void move(int gotoX, int gotoY);
};
void Body::move(int gotoX, int gotoY){
	lastX = x;
	lastY = y;
	gotoxy(x,y);printf(" ");
	x = gotoX;
	y = gotoY;
	gotoxy(x,y);printf("%c", 254);
	return;
}
class Head{
private:
	int x, y;
	int dx=-1, dy=0;
	int face = 17;
	void collition(void);
	
public:
	Head(int _x, int _y){
		x = _x;
		y = _y;
	}
	~Head(void){}
	void keyMove(void);
	void move(int key);
	bool death = false;
	int X(void){return x;}
	int Y(void){return y;}
	list<Body*> tail;
	list<Body*>::iterator tailIterator;
};

void Head::move(int key){
	gotoxy(x,y);printf(" ");
	int lastX = x, lastY = y;
	for(tailIterator=tail.begin();tailIterator != tail.end();tailIterator ++){
		(*tailIterator)->move(lastX, lastY);
		lastX = (*tailIterator)->getLastX();
		lastY = (*tailIterator)->getLastY();
	}	
	switch(key){
		case W:dx=0;dy=-1;face=30;break;
		case S:dx=0;dy=1;face=31;break;
		case A:dx=-1;dy=0;face=17;break;
		case D:dx=1;dy=0;face=16;break;
		break;
	}
	x += dx;
	y += dy; 
	
	Head::collition();
	gotoxy(x,y);printf("%c",face);
	return;
}
void Head::keyMove(void){
	char key = '?';
	if(kbhit()){
		key = getch();
	}
	Head::move(key);
	return;
}

void Head::collition(void){
	if(x<=2 || x>=78 || y <= 2 || y >= 22){
		death = true;
		return;
	}
	for(tailIterator=tail.begin();tailIterator != tail.end();tailIterator++){
		if((*tailIterator)->X() == x && (*tailIterator)->Y() == y){
			death = true;
			return;
		}
	}
	return;
}

int main(int nArgs, char* argv[]){
	system("cls");
	hidecursor();
	drawBorders(219, 219);
	Head snake (40,12);
	Food points (rand()%75+4, rand()%17+4);
	while(!snake.death){
		snake.keyMove();
		if((snake.X() == points.X()) && (snake.Y() == points.Y())){
			points.reload(rand()%75+4, rand()%17+4);
			snake.tail.push_back(new Body(0,0));
		}
		Sleep(100);
	}

	return 0;
}

void gotoxy(int x, int y){
	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	SetConsoleCursorPosition(hCon, dwPos);
	return;
}

void hidecursor(void){
	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 0;
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(hCon, &cci);
	return;
}

void drawBorders(int bx, int by){
	int x=2, y=2;
	for(x;x<=78;x++){
		y=2;
		gotoxy(x,y);printf("%c", bx);
		y=22;
		gotoxy(x,y);printf("%c", bx);
	}
	for(y=2;y<=22;y++){
		x=2;
		gotoxy(x,y);printf("%c", by);
		x=78;
		gotoxy(x,y);printf("%c", by);
	}
	return;
}