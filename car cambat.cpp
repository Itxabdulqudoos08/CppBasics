#include<iostream>
#include<conio.h>
#include<dos.h> 
#include <windows.h>
#include <time.h>

#define SCREEN_WIDTH 92
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70

using namespace std; 
 
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

int enemyY[3];
int enemyX[3];
int enemyFlag[3];

char car[4][4] = { ' ','#','#',' ', 
					'#','#','#','#', 
					' ','#','#',' ',
					'#','#','#','#' }; 
					
int carPos = WIN_WIDTH/2;
int score = 0; 

void gotoxy(int x, int y){
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}
void setcursor(bool visible ,DWORD size) {
	if(size == 0)
		size = 20;
			
   CONSOLE_CURSOR_INFO lpCursor;	
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console,&lpCursor);
}


	
void drawBorder(){  
	for(int i=0; i<SCREEN_HEIGHT; i++){
		for(int j=0; j<17; j++){
			gotoxy(0+j,i); cout<<"_";
			gotoxy(WIN_WIDTH-j,i); cout<<"_";
		}
	} 
	for(int i=0; i<SCREEN_HEIGHT; i++){
		gotoxy(SCREEN_WIDTH,i); cout<<"*";
	} 
}
void genEnemy(int ind){
	enemyX[ind] = 17 + rand()%(33);  
}
void drawEnemy(int ind){
	if( enemyFlag[ind] == true ){
		gotoxy(enemyX[ind], enemyY[ind]);   cout<<"++++";  
		gotoxy(enemyX[ind], enemyY[ind]+1); cout<<" ++ "; 
		gotoxy(enemyX[ind], enemyY[ind]+2); cout<<"++++"; 
		gotoxy(enemyX[ind], enemyY[ind]+3); cout<<" ++ ";  
	} 
}
void eraseEnemy(int ind){
	if( enemyFlag[ind] == true ){
		gotoxy(enemyX[ind], enemyY[ind]); cout<<"    ";  
		gotoxy(enemyX[ind], enemyY[ind]+1); cout<<"    "; 
		gotoxy(enemyX[ind], enemyY[ind]+2); cout<<"    "; 
		gotoxy(enemyX[ind], enemyY[ind]+3); cout<<"    "; 
	} 
} 
void resetEnemy(int ind){  
	eraseEnemy(ind);
	enemyY[ind]=1;       
	genEnemy(ind);
}

void drawCar(){                  
	for(int i=0; i<4; i++){         
		for(int j=0; j<4; j++){
		gotoxy(j+carPos, i+22); cout<<car[i][j];
		}
	}
}
void eraseCar(){ 					
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			gotoxy(j+carPos, i+22); cout<<" ";
		}
	}
}
 
int collision(){
	if( enemyY[0]+4 >= 23 ){					
		if( enemyX[0] + 4 - carPos >= 0 && enemyX[0] + 4 - carPos <= 9 ){
			return 1;					
		}
	}
	return 0;					
} 

void updateScore(){
	gotoxy(WIN_WIDTH + 5, 5);cout<<"Total Score: "<<score<<endl;}

void gameover(){
	system("cls");
	system("color 56");
	cout<<endl;
	cout<<"\t\t################################"<<endl;
	cout<<"\t\t#  **************************  #"<<endl;
	cout<<"\t\t#  *       ~Game Over~      *  #"<<endl;
	cout<<"\t\t#  *                        *  #"<<endl;
	cout<<"\t\t#  *       ~TRY AGIN~       *  #"<<endl;
	cout<<"\t\t#  **************************  #"<<endl;
    cout<<"\t\t################################"<<endl;
	cout<<"\t\tPRESS ANY  KEY TO GO BACK TO MENU:"<<endl;
	cout<<"\t\t***********THANK YOU************"<<endl<<endl;
	gotoxy(20,12);cout<<"~Your Total Score~ :"<<score;
    
	
	
	getch();
}

void instructions(){
	system("cls");
	system("color 76");
	gotoxy(10,5);cout<<" *************************************************"<<endl;
	gotoxy(10,6);cout<<" |               *INSTRUCTIONS*                  |";
    gotoxy(10,7);cout<<" |               --------------                  |";
    gotoxy(10,8);cout<<" |    ~ Avoid Cars by moving left or right~      |";
	gotoxy(10,9);cout<<" |          ~Press 'A' to move left~             |";
	gotoxy(10,10);cout<<" |          ~Press 'D' to move right~            |";
	gotoxy(10,11);cout<<" |          ~Press 'escape' to exit~             |";
    gotoxy(10,12);cout<<" |     ~Press any key to go back to menu~        |";
	gotoxy(10,13);cout<<" *************************************************"<<endl;
	getch();
}

void play()
{
    system("color 30");
	carPos =  WIN_WIDTH/2;
	score = 0;
	enemyFlag[0] = 1;          
	enemyFlag[1] = 0;             
	enemyY[0] = enemyY[1] = 1;         
	  
	system("cls"); 
	drawBorder();                
	updateScore();    
    genEnemy(0);
	genEnemy(1);
	
	
	gotoxy(18, 5);cout<<"~Press any key to start~";
	getch();
	gotoxy(18, 5);cout<<"                        ";
	
	while(1)
	{
		if(kbhit())
		{
			char ch = getch();
			if( ch=='A' || ch=='a' )
			{
				if( carPos > 18 )
					carPos -= 2;
			}
			if( ch=='D' || ch=='d' )
			{
				if( carPos < 48 )
					carPos += 2;
			} 
			if(ch==27)
			
			{
				break;
			}
		} 
		
		drawCar(); 
		drawEnemy(0); 
		drawEnemy(1); 
		if( collision() == 1){
			gameover();
		
			return;
		} 
		Sleep(50);
		eraseCar();
		eraseEnemy(0);
		eraseEnemy(1);   
		
		if( enemyY[0] == 10 )
			if( enemyFlag[1] == 0 )
				enemyFlag[1] = 1;		
		
		if( enemyFlag[0] == 1 )
			enemyY[0] += 1;
		
		if( enemyFlag[1] == 1 )
			enemyY[1] += 1;
		 
		if( enemyY[0] > SCREEN_HEIGHT-4 )
		{
			resetEnemy(0);
			score++;
			updateScore();
		}
		if( enemyY[1] > SCREEN_HEIGHT-4 )
		{
			resetEnemy(1);
			score++;
			updateScore();
		}
	}
}

int main()
{
	setcursor(0,0); 
	srand((unsigned)time(NULL)); 
	 
	do{
		
		system("cls");
		system("color ");
		gotoxy(10,5); cout<<"\t\t ######################### ";
		gotoxy(10,6); cout<<"\t\t #********CAR GAME*******# ";
		gotoxy(10,7);cout<<"\t\t #########################";
		gotoxy(10,9); cout<<"\t\t1. ~START GAME~";
		gotoxy(10,10);cout<<"\t\t2. ~INSTRUCTIONS~";	 
		gotoxy(10,11); cout<<"\t\t3. QUItT !";
		gotoxy(10,13); cout<<"\t\t~SELECT OPTION~: ";
		char op = getche();
	
		if( op=='1') play();
		else if( op=='2') instructions();
		else if( op=='3') exit(0);
		
	}while (1);
	
	return 0;
	
	
}
