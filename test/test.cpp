// test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

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
//定义分数
int score;

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
				printf("-"); 
			}
			else{
				printf(" ");
			}
		}
	}	
	printf("\n");
	printf("提示: w:上  s:下 a:左  d:右  \n");
}

//初始化食物
void InitFood(){
	int w=0;
	int m=0,n=0,t=0;
	srand( (unsigned)time(NULL) );
	g_food.x = rand() %MAP_WIDTH;
	g_food.y =rand() % MAP_HEIGHT;
	while(w==0){ //保证食物不会在蛇上
		for(int i =0;i<g_snack.size;i++){
			if(g_food.x==g_snack.pos[i].x && g_food.y==g_snack.pos[i].y){ 
			/*g_food.x = rand() % MAP_WIDTH;
			g_food.y = rand() % MAP_HEIGHT;*/
				//重新生成
				g_food.x=m;
				g_food.y=n;
				if(n==t && m<60){
				m++;	
				}else{
					n++;
					t++;
					m=0;
				  }
				if(n>=20){
					break;
				  }
		}else{
			w=1;
			break;
		}
	 }
 }	
	DrawChar(g_food.x,g_food.y,'#');
}

//用按键控制蛇移动wsad
void SanckMove(int key){
	int delta_x = 0;
	int delta_y = 0;
	if(key=='W'|| key=='w'){
		delta_x = 0;
		delta_y = -1;
	}else if(key=='S'|| key=='s'){
		delta_x = 0;
		delta_y = 1;
	}else if(key=='A'|| key=='a'){
		delta_x = -1;
		delta_y = 0;
	}else if(key=='D'|| key=='d'){
		delta_x = 1;
		delta_y = 0;
	}else{
		return;
	}
	//让最后一个位置消失（清除屏幕中不属于蛇的'#'） 
	DrawChar(g_snack.pos[g_snack.size-1].x,g_snack.pos[g_snack.size-1].y,' ');
	//修改数组位置  
	for(int i=g_snack.size-1;i>0;i--){
			g_snack.pos[i].x =g_snack.pos[i-1].x;
			g_snack.pos[i].y =g_snack.pos[i-1].y;
	}
			g_snack.pos[0].x +=delta_x;
			g_snack.pos[0].y +=delta_y;
	if(key=='E'|| key=='e'){
		delta_x = 0;
		delta_y = 0;
	}
}


//吃东西
void EatFood(){
	if(g_snack.pos[0].x==g_food.x && g_snack.pos[0].y==g_food.y){    
		g_snack.size++; //蛇长度增加 尾节点 跟食物坐标一样
		g_snack.pos[g_snack.size-1].x = g_food.x;
		g_snack.pos[g_snack.size-1].y = g_food.y;
		InitFood(); //更新食物
		score++;
	} 
}

//判断游戏是否结束
int GameOver(){
	//撞自己
	for(int i = 1; i<g_snack.size-1 ; i++){
		if(g_snack.pos[0].x==g_snack.pos[i].x && g_snack.pos[0].y==g_snack.pos[i].y){
		return 1;
		}
	}
	//撞墙
	if(g_snack.pos[0].x>MAP_WIDTH || g_snack.pos[0].y >=MAP_HEIGHT || g_snack.pos[0].x<0 || g_snack.pos[0].y <0  ){      
		return 1;	
	}else {
		return 0;
	}
}

//判断是否回头
int IsBack(int key ,int last_key){
	if(last_key=='w' || last_key=='W'){
		if(key=='s' || key=='S'){return 1;}
	}
	if(last_key=='s' || last_key=='S'){
		if(key=='w' || key=='W'){return 1;}
	}
	if(last_key=='d' || last_key=='D'){
		if(key=='a' || key=='A'){return 1;}
	}
	if(last_key=='a' || last_key=='A'){
		if(key=='d' || key=='D'){return 1;}
	}
	return 0;
}

//更新屏幕
void UpdateScreen(){
	//画贪吃蛇
	DrawSnack();
	//更新食物
	EatFood();
}


/*********************************************************************************************/

void Init(){
	
	InitMap();
	InitSnack();
	InitFood();
}

void GameLoop(){
	int key=0,last_key=0;
	score=0;
	while(1){
		HideCursor();		
		//检测按键输入  
		if(_kbhit()){
			key = _getch();
			if(IsBack(key,last_key)==1){ 
				key = last_key;
				continue;
			}
			last_key = key;
		}
		if(key=='q'|| key=='Q'){
			return;
		}
		//移动贪吃蛇
		SanckMove(key);
		//判断是否游戏结束
		int x = GameOver();
		if(x==1){
			return;
		}
		//更新屏幕
		UpdateScreen();
		Sleep(100);
	}
}

void Score(){
	system("cls");
	printf("游戏结束，总得分=%d\n",score);
}
/**********************************************************************************************/
int main(int argc, char* argv[])
{
	
	Init();
	GameLoop(); 
	Score();	
	return 0;

}

