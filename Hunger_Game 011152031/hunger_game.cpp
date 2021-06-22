#include "iGraphics.h"
#include <string.h>
#include <stdio.h>
//#include <stdlib.h>
#define speed 4
double Gspeed = 0.5;
int Food_for_X_axis[6][17]={0}, Food_for_Y_axis_up[6][17]={0}, Food_for_Y_axis_down[6][17]={0}, Food_for_Y_axis_middle[6][17]={0};
int Score = 0;
int hungry_x, hungry_y;
char hungry_img_link[100];
bool Block(double x, double y);
double Ghost[3] = { 8, 8, 2 };//ghost 1
double Ghost2[3] = { 8, 572, 4 };//ghost 2
double Ghost3[3] = { 236, 380, 2 };//ghost 3
double Ghost4[3] = { 612, 156, 3 };//ghost 4
bool play=true;
bool play_load=true;
int load=(int)time(NULL);
double load_count=0;

int menu = 5, pause = 1;			// when menu = 1  ---- shows menu

double GetMove(double x, double y){
	srand(time(NULL));
	int s;
	if (x == 8 && y == 572)
	{
		s = rand() % 2;
		if (s == 0)
			return 2;
		else if (s == 1)
			return 4;
	}
	else if (x == 8 && y == 8){
		s = rand() % 2;
		if (s == 0)
			return 3;
		else if (s == 1)
			return 2;
	}
	else if (x == 612 && y == 572){

		s = rand() % 2;
		if (s == 0)
			return 1;
		else if (s == 1)
			return 4;
	}
	else if (x == 612 && y == 8)
	{

		s = rand() % 2;
		if (s == 0)
			return 3;
		else if (s == 1)
			return 1;
	}
	else if (x == 612 && y > 20 && y < 550){
		s = rand() % 3;
		if (s == 0)
			return 4;
		else if (s == 1)
			return 3;
		else if (s == 2)
			return 1;
	}
	else if ((x > 10 && x < 610 && y >= 8 && y < 68) || (x > 20 && x < 600 && y >= 200 && y < 288) || (x > 20 && x < 600 && y >= 424 && y < 488)){
		s = rand() % 3;
		if (s == 0)
			return 3;
		else if (s == 1)
			return 1;
		else if (s == 2)
			return 2;
	}
	else if ((x > 10 && x < 610 && y >= 508 && y <= 572) || (x > 20 && x < 600 && y >= 300 && y <= 380) || (x > 20 && x < 600 && y >= 64 && y <= 156)){
		s = rand() % 3;
		if (s == 0)
			return 1;
		else if (s == 1)
			return 2;
		else if (s == 2)
			return 4;
	}
	else if (x == 8 && y > 20 && y < 550){
		s = rand() % 3;
		if (s == 0)
			return 2;
		else if (s == 1)
			return 4;
		else if (s == 2)
			return 3;
	}
	return 0;
}
double GetGhostXY_X(int id){
	if (id == 0)
		return 8;
	else if (id == 1)
		return 236;
	else if (id == 2)
		return 384;
	else if (id == 3)
		return 612;
}

double GetGhostXY_Y(int id){
	if (id == 0)
		return 8;
	else if (id == 1)
		return 156;
	else if (id == 2)
		return 204;
	else if (id == 3)
		return 380;
	else if (id == 4)
		return 428;
	else if (id == 5)
		return 572;
}

//This function is for rotating image.
void hungry_img(char link[100]){
	hungry_img_link[0] = '\0';
	strcpy_s(hungry_img_link, link);
}//line 20-50 for X axis food
/*
This function will return in which Coordinate along X-axis food will be put

*/
int getFood1X(int id){
	int k = 25;
	for (int i = 0; i < id; i++){
		k += 38;
	}
	return k;
}
/*
This function will return Coordinate of Y-axis
*/
int getFood1Y(int id){
	if (id == 0)
		return 588;
	else if (id == 1)
		return 440;
	else if (id == 2)
		return 395;
	else if (id == 3)
		return 218;
	else if (id == 4)
		return 172;
	else if (id == 5)
		return 22;

}

//line........................
/*
This function will return in which Coordinate along X-axis(up) food will be put

*/
int getFood2X_up(int id){
	if (id == 0)
		return 25;
	else if (id == 1)
		return 253;
	else if (id == 2)
		return 405;
	else if (id == 3)
		return 633;

}
/*
This function will return Coordinate of Y-axis(up)
*/
int getFood2Y_up(int id){
	int k = 475;
	for (int i = 0; i < id; i++){
		k += 38;
	}
	return k;

}
//line........................
/*
This function will return in which Coordinate along X-axis(down) food will be put

*/
int getFood2X_down(int id){
	if (id == 0)
		return 25;
	else if (id == 1)
		return 253;
	else if (id == 2)
		return 405;
	else if (id == 3)
		return 633;

}
/*
This function will return Coordinate of Y-axis(down)
*/
int getFood2Y_down(int id){
	int k = 57;
	for (int i = 0; i < id; i++){
		k += 38;
	}
	return k;

}

//line........................
/*
This function will return in which Coordinate along X-axis(middle) food will be put

*/
int getFood2X_middle(int id){
	if (id == 0)
		return 25;
	else if (id == 1)
		return 253;
	else if (id == 2)
		return 405;
	else if (id == 3)
		return 633;

}
/*
This function will return Coordinate of Y-axis(middle)
*/
int getFood2Y_middle(int id){
	int k = 250;
	for (int i = 0; i < id; i++){
		k += 38;
	}
	return k;

}
/*
function iDraw() is called again and again by the system.
*/

void Draw_Ghost(){
	if (pause == 1){
		if (Ghost[2] == 1){
			if (Ghost[0] > 8)
				Ghost[0] -= Gspeed;
		}
		else if (Ghost[2] == 2){
			if (Ghost[0] < 616)
				Ghost[0] += Gspeed;
		}
		else if (Ghost[2] == 3){
			if (Ghost[1] < 572)
				Ghost[1] += Gspeed;
		}
		else if (Ghost[2] == 4){
			if (Ghost[1] > 8)
				Ghost[1] -= Gspeed;
		}

		//
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (Ghost[0] == GetGhostXY_X(j) && Ghost[1] == GetGhostXY_Y(i)){
					Ghost[2] = GetMove(GetGhostXY_X(j), GetGhostXY_Y(i));
					//printf("%lf\n",Ghost[2]);
				}
			}
		}
	}
	iShowBMP(Ghost[0], Ghost[1], "ghost_1.bmp");
}


void Draw_Ghost2(){
	if (pause == 1){
		if (Ghost2[2] == 1){
			if (Ghost2[0] > 8)
				Ghost2[0] -= Gspeed;
		}
		else if (Ghost2[2] == 2){
			if (Ghost2[0] < 616)
				Ghost2[0] += Gspeed;
		}
		else if (Ghost2[2] == 3){
			if (Ghost2[1] < 572)
				Ghost2[1] += Gspeed;
		}
		else if (Ghost2[2] == 4){
			if (Ghost2[1] > 8)
				Ghost2[1] -= Gspeed;
		}

		//
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (Ghost2[0] == GetGhostXY_X(j) && Ghost2[1] == GetGhostXY_Y(i)){
					Ghost2[2] = GetMove(GetGhostXY_X(j), GetGhostXY_Y(i));
					//printf("%lf\n", Ghost2[2]);
				}
			}
		}
	}
	iShowBMP(Ghost2[0], Ghost2[1], "ghost_2.bmp");
}


void Draw_Ghost3(){
	if (pause == 1){
		if (Ghost3[2] == 1){
			if (Ghost3[0] > 8)
				Ghost3[0] -= Gspeed;
		}
		else if (Ghost3[2] == 2){
			if (Ghost3[0] < 616)
				Ghost3[0] += Gspeed;
		}
		else if (Ghost3[2] == 3){
			if (Ghost3[1] < 572)
				Ghost3[1] += Gspeed;
		}
		else if (Ghost3[2] == 4){
			if (Ghost3[1] > 8)
				Ghost3[1] -= Gspeed;
		}

		//
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (Ghost3[0] == GetGhostXY_X(j) && Ghost3[1] == GetGhostXY_Y(i)){
					Ghost3[2] = GetMove(GetGhostXY_X(j), GetGhostXY_Y(i));
					//printf("%lf\n", Ghost3[2]);
				}
			}
		}
	}
	iShowBMP(Ghost3[0], Ghost3[1], "ghost_3.bmp");
}

void Draw_Ghost4(){
	if (pause == 1){
		if (Ghost4[2] == 1){
			if (Ghost4[0] > 8)
				Ghost4[0] -= Gspeed;
		}
		else if (Ghost4[2] == 2){
			if (Ghost4[0] < 616)
				Ghost4[0] += Gspeed;
		}
		else if (Ghost4[2] == 3){
			if (Ghost4[1] < 572)
				Ghost4[1] += Gspeed;
		}
		else if (Ghost4[2] == 4){
			if (Ghost4[1] > 8)
				Ghost4[1] -= Gspeed;
		}

		//
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (Ghost4[0] == GetGhostXY_X(j) && Ghost4[1] == GetGhostXY_Y(i)){
					Ghost4[2] = GetMove(GetGhostXY_X(j), GetGhostXY_Y(i));
					//printf("%lf\n", Ghost4[2]);
				}
			}
		}

	}
	iShowBMP(Ghost4[0], Ghost4[1], "ghost_4.bmp");
}
//This function  will return ghost and hunger touched each other or not
bool isHeat(double x, double y, double x1, double y1){
	if (x <= x1 && x1 <= x + 32 && y <= y1 && y1 <= y + 32)
		return true;
	else if (x1 <= x && x <= x1 + 32 && y1 <= y && y <= y1 + 32)
		return true;
	else
		return false;
}

//This function will game over if ghost and hunger touched each other.
void Hunger_Heat_Ghost(){
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (isHeat(hungry_x, hungry_y, Ghost[0], Ghost[1]) || isHeat(hungry_x, hungry_y, Ghost2[0], Ghost2[1]) || isHeat(hungry_x, hungry_y, Ghost3[0], Ghost3[1]) || isHeat(hungry_x, hungry_y, Ghost4[0], Ghost4[1])){
				menu = 3;
				PlaySound("hit.wav", NULL, SND_ASYNC | SND_FILENAME);

			}
		}
	}
}


void iDraw()
{
	iClear();
	
	
	if(menu==5){
		if((int)time(NULL)-load<5)
		{
		iSetColor(255,255,255);
		iText(275,350,"Loading...",GLUT_BITMAP_TIMES_ROMAN_24);
		iSetColor(6,166,14);
		iFilledRectangle(0,300,load_count+=.2,20);
		iSetColor(0,0,0);
		iFilledRectangle(0,300,100,20);
		iFilledRectangle(556,300,100,20);

		
	    }
		else{
			menu=1;
		}
		 
	}
	
	else if (menu == 1)
	{
		iShowBMP(0, 0, "menu.bmp");
		iFilledRectangle(0,0,10,10);
		if(play_load)
		 {
		 PlaySound("starting.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
		 play_load =false;
		 }
	}
	else if (menu == 2)
	{

		

		//for score board
		iSetColor(255, 255, 128);
		iFilledRectangle(0, 610, 834, 704);

		//for border
		iSetColor(128, 64, 64);
		iFilledRectangle(0, 0, 834, 610);

		//game field
		iShowBMP(6, 6, "game_field.bmp");

		//image of hungry
		iShowBMP(hungry_x, hungry_y, hungry_img_link);

		//to calculate coordinate of X and Y 
		printf("X= %d ... Y = %d\n", hungry_x, hungry_y);

		iSetColor(175, 213,47);
		//to eat food along x-axis
		for (int l = 0; l < 6; l++){
			for (int k = 0; k < 17; k++){
				if (Food_for_X_axis[l][k] == 1)
					iFilledCircle(getFood1X(k), getFood1Y(l), 8, 32);
			}
		}
		//to eat food along y-axis(up)
		for (int i = 0; i < 4; i++){
			for (int j = 0; j < 3; j++){
				if (Food_for_Y_axis_up[i][j] == 1)
					iFilledCircle(getFood2X_up(i), getFood2Y_up(j), 8, 32);
			}
		}
		//to eat food along y-axis(down)
		for (int i = 0; i < 4; i++){
			for (int j = 0; j < 3; j++){
				if (Food_for_Y_axis_down[i][j] == 1)
					iFilledCircle(getFood2X_down(i), getFood2Y_down(j), 8, 32);
			}
		}
		//to draw food along y-axis(middle)
		for (int i = 0; i < 4; i++){
			for (int j = 0; j < 4; j++){
				if (Food_for_Y_axis_middle[i][j] == 1)
					iFilledCircle(getFood2X_middle(i), getFood2Y_middle(j), 8, 32);
			}
		}
		//to eat food along x-axis
		for (int l = 0; l < 6; l++){
			for (int k = 0; k < 17; k++){
				if (Food_for_X_axis[l][k] == 1)
				{
					if (hungry_y < getFood1Y(l) + 8 && hungry_y > getFood1Y(l) - 42 && hungry_x < getFood1X(k) + 8 && hungry_x > getFood1X(k) - 42)
					{
						Food_for_X_axis[l][k] = 0;
						Score += 5;
						PlaySound("eat.wav", NULL, SND_ASYNC | SND_FILENAME);
					}
				}
				
				
			}
			/*if(Score==710){
				menu=4;
			}*/	
		}
		//to eat food along y-axis(up)
		for (int i = 0; i < 4; i++){
			for (int j = 0; j < 3; j++){
				if (Food_for_Y_axis_up[i][j] == 1)
					if (getFood2X_up(i) + 8 >= hungry_x && hungry_x + 42 >= getFood2X_up(i) && getFood2Y_up(j) + 8 >= hungry_y && getFood2Y_up(j) <= hungry_y + 42){
						Food_for_Y_axis_up[i][j] = 0;
						Score += 5;
						PlaySound("eat.wav", NULL, SND_ASYNC | SND_FILENAME);
					}
			}
			
			}
		/*if(Score==710){
				menu=4;
		}*/

		//to eat food along y-axis(down)
		for (int i = 0; i < 4; i++){
			for (int j = 0; j < 3; j++){
				if (Food_for_Y_axis_down[i][j] == 1)
					if (getFood2X_down(i) + 8 >= hungry_x && hungry_x + 42 >= getFood2X_down(i) && getFood2Y_down(j) + 8 >= hungry_y && getFood2Y_down(j) <= hungry_y + 42){
						Food_for_Y_axis_down[i][j] = 0;
						Score += 5;
						PlaySound("eat.wav", NULL, SND_ASYNC | SND_FILENAME);
					}
			}
			
			}
			

		//to eat food along y-axis(middle)
		for (int i = 0; i < 4; i++){
			for (int j = 0; j < 4; j++){
				if (Food_for_Y_axis_middle[i][j] == 1)
					if (getFood2X_middle(i) + 8 >= hungry_x && hungry_x + 42 >= getFood2X_middle(i) && getFood2Y_middle(j) + 8 >= hungry_y && getFood2Y_middle(j) <= hungry_y + 42)
					{
						Food_for_Y_axis_middle[i][j] = 0;
						Score += 5;
						PlaySound("eat.wav", NULL, SND_ASYNC | SND_FILENAME);

					}
			}
		
		}
	/*	int count=0;
		for (int l = 0; l < 6; l++)
	    {
			for (int k = 0; k < 17; k++)
			{
				if(Food_for_X_axis[l][k] == 0){
					count++;
				}
				if(Food_for_Y_axis_up[l][k]==0){
					count++;
				}
				if(Food_for_Y_axis_down[l][k]==0){
					count++;
				}
				if(Food_for_Y_axis_middle[l][k]==0){
					count++;
				}
				
			
			}
		
	    }*/
		//printf("%d\n",count);
		//if(count==408){//300
		//	menu=4;
		//}
		if(Score==710){
				menu=4;
		}

		//to show score in screen 
		iSetColor(64, 128, 128);
		iText(8, 618, "Score :", GLUT_BITMAP_HELVETICA_18);
		char ScoreString[10];
		itoa(Score, ScoreString, 10);
		iText(70, 617, ScoreString, GLUT_BITMAP_HELVETICA_18);
		int ax = Score;
		//printf("%d", ax);
		iText(250, 650, "Hunger Game", GLUT_BITMAP_TIMES_ROMAN_24);//for game name
		
		Draw_Ghost3();
		Draw_Ghost();
		Draw_Ghost4();
		Draw_Ghost2();
		Hunger_Heat_Ghost();//This function to hit hunger by ghost
	}
	 
	 else if (menu == 3)						// game over
	{

		iShowBMP(0, 0, "gameover.bmp");
		iSetColor(255, 255, 255);
		iText(225, 140, "PRESS 'Q' to Exit", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(240, 300, "Your Score :", GLUT_BITMAP_TIMES_ROMAN_24);
		char ScoreString[5];
		itoa(Score, ScoreString, 10);
		iText(370, 300, ScoreString, GLUT_BITMAP_TIMES_ROMAN_24);
		//int ax = Score;
	}
	 else if(menu==4)
	 {
         iShowBMP(0,0, "winer.bmp");
		 if(play)
		 {
		 PlaySound("winer.wav", NULL, SND_ASYNC | SND_FILENAME);
		 play =false;
		 }

	 }
	 
}

bool Block(double x, double y)
{
	if (x < 8 || y < 8 || x > 616 || y > 572)//for whole boundary
		return false;
	else if (12 < x && x < 236 && 8 < y && y < 152)//under-left-
		return false;
	else if ((388 < x && x < 612) && (8 < y && y < 152))//under-right-
		return false;
	else if ((388 < x && x < 612) && (428 < y && y < 572))//upper-right
		return false;
	else if ((12 < x && x < 236) && (428 < y && y < 572))//upper-left
		return false;
	else if ((240 < x && x < 384) && (8 < y && y < 152))//under-middle
		return false;
	else if ((240 < x && x < 384) && (428 < y && y < 572))//upper-middle
		return false;
	else if ((12 < x && x < 236) && (204 < y && y < 376))//middle-left
		return false;
	else if ((388 < x && x < 612) && (204 < y && y < 376))//middle-right
		return false;
	else if ((12 < x && x < 612) && (156 < y && y < 200))//lower-straightline
		return false;
	else if ((12 < x && x < 612) && (380 < y && y < 424))//upper-straightline
		return false;
	else if ((240 < x && x < 384) && (204 < y && y < 344))//centre-[]
		return false;
	else if ((316 < x && x < 384) && (343 < y && y < 376))//centre-[]||
		return false;
	else if ((240 < x && x < 308) && (343 < y && y < 376))//centre-||[]
		return false;
	else
		return true;
}


/*;/."//??????????????????/'/
f.unction iMouseMove() is called when the user presses and drags the mouse./////./llll;./.l......;//./.
(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
	//place your codes here
}

/*
function iMouse() is called when the user presses/releases the mouse.
(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
	if (menu == 1){
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{

			//============= play ======================
			if (mx >= 247 && mx <= 407 && my >= 301 && my <= 389){
				menu = 2;
				PlaySound(NULL, NULL, 0);
			}
			//============= play ======================


			// ======== quit ===========
			if (mx >= 243 && mx <= 409 && my >= 105 && my <= 196){
				exit(0);
			}
			// ======== quit ===========
		}
	}
}

/*
function iKeyboard() is called whenever the user hits a key in keyboard.
key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{
	if (key == 'p' || key == 'P')
	{
		pause = 0;
		/*iSetColor(255, 255, 128);
		iText(312, 344, "Hunger Game", GLUT_BITMAP_TIMES_ROMAN_24);*/
	}
	if (key == 'r' || key == 'R')
	{
		pause = 1;
	}


	if (key == 'q' || key == 'Q')
	{
		exit(0);
	}


}

/*
function iSpecialKeyboard() is called whenver user hits special keys like-
function keys, home, end, pg up, pg down, arraows etc. you have to use
appropriate constants to detect them. A list is:
GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyboard(unsigned char key)
{
	printf("X= %d Y= %d\n",hungry_x,hungry_y);
	
	if (pause == 1){
		if (key == GLUT_KEY_END)
		{
			exit(0);
		}
		else if (key == GLUT_KEY_LEFT)
		{
			if (Block(hungry_x - speed, hungry_y))
				hungry_x -= speed;
			hungry_img("hungry_left.bmp");

		}
		else if (key == GLUT_KEY_RIGHT)
		{
			if (Block(hungry_x + speed, hungry_y))
				hungry_x += speed;
			hungry_img("hungry_right.bmp");

		}
		else if (key == GLUT_KEY_UP)
		{
			if (Block(hungry_x, hungry_y + speed))
				hungry_y += speed;
			hungry_img("hungry_up.bmp");

		}
		else if (key == GLUT_KEY_DOWN)
		{
			if (Block(hungry_x, hungry_y - speed))
				hungry_y -= speed;
			hungry_img("hungry_down.bmp");

		}
	}
}



int main()
{
	hungry_img("hungry_right.bmp");//func calling for image
	hungry_x = 312;
	hungry_y = 344;


	for (int l = 0; l < 6; l++)
	{
		for (int k = 0; k < 17; k++)
		{
			Food_for_X_axis[l][k] = 1;
			
		}
		
	}
	
	//
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			Food_for_Y_axis_up[i][j] = 1;
		}
	}

	//
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			Food_for_Y_axis_down[i][j] = 1;
		}
	}
	//
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			Food_for_Y_axis_middle[i][j] = 1;
		}
	}
	iInitialize(656, 675, "Hunger Game");
	//place your own initialization codes here.
	return 0;
}