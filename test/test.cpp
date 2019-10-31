// test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

//�������ع�꺯��
void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor;    
	cursor.bVisible = FALSE;    
	cursor.dwSize = sizeof(cursor);    
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);    
	SetConsoleCursorInfo(handle, &cursor);
}


//��Ϸ����
//1.ʵ�����������ƶ�
//2.�Զ�������
//3.ײǽײ�Լ�����
//4.��ӡ�÷�

//�����ͼ��С
#define MAP_WIDTH 60
#define MAP_HEIGHT 20
//�����ߺ����ڵ�Ľṹ��
typedef struct Position{
	int x;
	int y;
}Position;

typedef struct Snack{
	int size;  
	Position pos[MAP_WIDTH*MAP_HEIGHT]; //�ܴ�С
}Sanck;

//�����ߵ�ȫ�ֱ���
Snack g_snack; 
//����ʳ��
Position g_food;
//�������
int score;

//���ַ�
void DrawChar(int x,int y,char ch){
	COORD pos;
	pos.X=x;
	pos.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
	putchar(ch);
}

//�õ��ַ�
char GetChar(int x,int y){
	COORD pos;
	pos.X=x;
	pos.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
	return getchar();
}

//��ʼ��̰���� 
void InitSnack(){
	g_snack.size=3;
	g_snack.pos[0].x =MAP_WIDTH/2;
	g_snack.pos[0].y =MAP_HEIGHT/2;
	g_snack.pos[1].x =MAP_WIDTH/2-1;
	g_snack.pos[1].y =MAP_HEIGHT/2;
	g_snack.pos[2].x =MAP_WIDTH/2-2;
	g_snack.pos[2].y =MAP_HEIGHT/2;
}

//����̰����
void DrawSnack(){
	for(int i =0;i<g_snack.size;i++){
		if(i==0){
			DrawChar(g_snack.pos[i].x,g_snack.pos[i].y,'*');
			}else{
				DrawChar(g_snack.pos[i].x,g_snack.pos[i].y,'#');
			}
	}
}

//���Ƶ�ͼ
void InitMap(){
	int i,j;
	for(i=0;i<=MAP_HEIGHT;i++){
		for(j=0;j<=MAP_WIDTH;j++){
			if(j==MAP_WIDTH){
				//�ұ߿�
				printf("|\n");
			}else if(i==MAP_HEIGHT){
				//�ױ߿�
				printf("_"); 
			}
			else{
				printf(" ");
			}
		}
	}		
}

//��ʼ��ʳ��
void InitFood(){
	int w=0;
	srand( (unsigned)time(NULL) );
	g_food.x = rand() %MAP_WIDTH;
	g_food.y =rand() % MAP_HEIGHT;
	while(w==0){ //��֤ʳ�ﲻ��������
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

//�ð����������ƶ�wsad
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
	//�����һ��λ����ʧ�������Ļ�в������ߵ�'#'�� 
	DrawChar(g_snack.pos[g_snack.size-1].x,g_snack.pos[g_snack.size-1].y,' ');
	//�޸�����λ��  
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

//�Զ���
void EatFood(){
	if(g_snack.pos[0].x==g_food.x && g_snack.pos[0].y==g_food.y){    
		g_snack.size++; //�߳������� β�ڵ� ��ʳ������һ��
		g_snack.pos[g_snack.size-1].x = g_food.x;
		g_snack.pos[g_snack.size-1].y = g_food.y;
		InitFood(); //����ʳ��
		score++;
	} 
}

//�ж���Ϸ�Ƿ����
int GameOver(){
	//ײ�Լ�
	for(int i =1 ; i<g_snack.size-1 ; i++){
		if(g_snack.pos[0].x==g_snack.pos[i].x && g_snack.pos[0].y==g_snack.pos[i].y){
		return 1;
		}
	}
	//ײǽ
	if(g_snack.pos[0].x>=MAP_WIDTH || g_snack.pos[0].y >=MAP_HEIGHT){ 
		return 1;	
	}else {
		return 0;
	}
}

//������Ļ
void UpdateScreen(){
	//��̰����
	DrawSnack();
	//����ʳ��
	EatFood();
}

/*********************************************************************************************/

void Init(){
	
	InitMap();
	InitSnack();
	InitFood();
}

void GameLoop(){
	int key=0;
	score=0;
	while(1){
		HideCursor();		
		//��ⰴ������
		if(_kbhit()){
			key = _getch();
		}
		if(key=='q'|| key=='Q'){
			return;
		}
		//�ƶ�̰����
		SanckMove(key);
		//�ж��Ƿ���Ϸ����
		int x = GameOver();
		if(x==1){
			return;
		}
		//������Ļ
		UpdateScreen();
		Sleep(100);
	}
}

void Score(){
	COORD pos;
	pos.X=0;
	pos.Y=MAP_HEIGHT+1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
	printf("��Ϸ�������ܵ÷�=%d\n",score);
}
/**********************************************************************************************/
int main(int argc, char* argv[])
{
	Init();
	GameLoop(); 
	Score();  

	return 0;

}

