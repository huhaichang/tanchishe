// test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <stdlib.h>
#include <time.h>

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

//���ַ�
void DrawChar(int x,int y,char ch){
	COORD pos;
	pos.X=x;
	pos.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
	putchar(ch);
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

//������Ļ
void UpdateScreen(){
	//��̰����
	DrawSnack();

}

/*****************************************************************************/

void Init(){
	//���Ƶ�ͼ
	InitMap();
	//��ʼ��̰����
	InitSnack();
	//��ʼ��ʳ��
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
	Init();//��ʼ��

	GameLoop(); //��Ϸ��ѭ��

	Score();  //��ӡ�÷�

	return 0;

}

