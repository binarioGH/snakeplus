#include <stdio.h>
#include <windows.h>
#include <conio.h>
void gotoxy(int x, int y);
void hideCursor(void);
void drawBorders(void);
class Food{
private:
	int x=0, y = 0;
public:
	Food(void);
	int X(void){return x;}
	int Y(void){return y;}
	void reload(void);
};
Food::Food(void){
	Food::reload();
}
void Food::reload(){
	gotoxy(x,y);printf(" ");
	x = rand()%75+5;
	y = rand()%17+5;
	gotoxy(x,y);printf("*");
}
class Snake{
private:
	int x, y;
	int xDirection=-1, yDirection=0;
	void draw(void);
	void collition(void);
public:
	Snake(int _x, int _y){x=_x;y=_y;}
	void move(void);
	int X(void){return x;}
	int Y(void){return y;}
	bool alive = true;
};
void Snake::move(void){
	Snake::draw();
	x+=xDirection;
	y+=yDirection;
	if(kbhit()){
		char key = getch();
		switch(key){
			case 'w':xDirection = 0;yDirection = -1;break;
			case 's':xDirection=0;yDirection = 1;break;
			case 'a':xDirection=-1;yDirection =0;break;
			case 'd':xDirection=1;yDirection=0;break;
		}
	}
	Snake::collition();
	return;
}
void Snake::draw(void){
	gotoxy(x,y);printf(" ");
	gotoxy(x+xDirection,y+yDirection);printf("%c",223);
	return;
}
void Snake::collition(void){
	if(x<=3 || x>= 77){
		alive = false;
	}
	if(y<=4 || y>= 23){
		alive = false;
	}
	return;
}
int main(){
	system("cls");
	hideCursor();
	drawBorders();
	Snake s (40,11);
	Food p;
	int score = 00;
	gotoxy(35, 2);printf("Puntos:  %i", score);
	while(s.alive){
		if(p.X() == s.X() && p.Y() == s.Y()){
			score += 1;
			gotoxy(35,2);printf("                   ");
			gotoxy(35,2);printf("Puntos:  %i", score);
			p.reload();
		}
		s.move();
		Sleep(100);
	}
	return 0;
}

void gotoxy(int x, int y){
	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwpos;
	dwpos.X = x;
	dwpos.Y = y;
	SetConsoleCursorPosition(hCon, dwpos);
	return;
}
void hideCursor(void){
	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 0;
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(hCon, &cci);
	return;
}
void drawBorders(void){
	int x,  y=3;
	for(x=2;x<78;x++){
		gotoxy(x,y);printf("%c",205);
		gotoxy(x,y+20);printf("%c", 205);
	}
	x = 2;
	for(y;y<23;y++){
		gotoxy(x,y);printf("%c",186);
		gotoxy(x+76,y);printf("%c", 186);
	}
	gotoxy(2,3);printf("%c",201);
	gotoxy(2,23);printf("%c", 200);
	gotoxy(78,3);printf("%c", 187);
	gotoxy(78, 23);printf("%c", 188);
	return;   
}