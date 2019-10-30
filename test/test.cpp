// test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <stdlib.h>
#include <time.h>

//定义隐藏光标函数
void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor;    
	cursor.bVisible = FALSE;    
	cursor.dwSize = sizeof(cursor);    
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);    
	SetConsoleCursorInfo(handle, &cursor);
}


//游戏功能
//1.实现上下左右移动
//2.吃东西长大
//3.撞墙撞自己死亡
//4.打印得分

//定义地图大小
#define MAP_WIDTH 60
#define MAP_HEIGHT 20
//定义蛇和所在点的结构体
typedef struct Position{
	int x;
	int y;
}Position;

typedef struct Snack{
	int size;  
	Position pos[MAP_WIDTH*MAP_HEIGHT]; //总大小
}Sanck;

//定义蛇的全局变量
Snack g_snack; 
//定义食物
Position g_food;

//画字符
void DrawChar(int x,int y,char ch){
	COORD pos;
	pos.X=x;
	pos.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
	putchar(ch);
}

//初始化贪吃蛇 
void InitSnack(){
	g_snack.size=3;
	g_snack.pos[0].x =MAP_WIDTH/2;
	g_snack.pos[0].y =MAP_HEIGHT/2;
	g_snack.pos[1].x =MAP_WIDTH/2-1;
	g_snack.pos[1].y =MAP_HEIGHT/2;
	g_snack.pos[2].x =MAP_WIDTH/2-2;
	g_snack.pos[2].y =MAP_HEIGHT/2;
}

//绘制贪吃蛇
void DrawSnack(){
	for(int i =0;i<g_snack.size;i++){
		if(i==0){
			DrawChar(g_snack.pos[i].x,g_snack.pos[i].y,'*');
			}else{
				DrawChar(g_snack.pos[i].x,g_snack.pos[i].y,'#');
			}
	}
}

//绘制地图
void InitMap(){
	int i,j;
	for(i=0;i<=MAP_HEIGHT;i++){
		for(j=0;j<=MAP_WIDTH;j++){
			if(j==MAP_WIDTH){
				//右边框
				printf("|\n");
			}else if(i==MAP_HEIGHT){
				//底边框
				printf("_"); 
			}
			else{
				printf(" ");
			}
		}
	}		
}

//初始化食物
void InitFood(){
	int w=0;
	srand( (unsigned)time(NULL) );
	g_food.x = rand() %MAP_WIDTH;
	g_food.y =rand() % MAP_HEIGHT;
	while(w==0){ //保证食物不会在蛇上
		for(int i =0;i<g_snack.size;i++){
		if(g_food.x==g_snack.pos[i].x && g_food.y==g_snack.pos[i].y){
			g_food.x = rand() %MAP_WIDTH;
			g_food.y =rand() % MAP_HEIGHT;
		}else{
			w=1;
			break;
		}
	 }
 }
	
	DrawChar(g_food.x,g_food.y,'#');
}

//更新屏幕
void UpdateScreen(){
	//画贪吃蛇
	DrawSnack();

}

/*****************************************************************************/

void Init(){
	//绘制地图
	InitMap();
	//初始化贪吃蛇
	InitSnack();
	//初始化食物
	InitFood();
}

void GameLoop(){
	while(1){
		HideCursor();
		UpdateScreen();
		Sleep(100);
	}
}

void Score(){

}

int main(int argc, char* argv[])
{
	Init();//初始化

	GameLoop(); //游戏主循环

	Score();  //打印得分

	return 0;

}

