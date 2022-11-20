#include <iostream>
#include "windows.h"
#include <chrono>
#include <thread>
#include <string>
#include <vector>
#include <ctime>
#include <fstream>
#include <cstdlib>

using namespace std;

ofstream file;

BOOL scpt(int x,int y){
	COORD c;
	c.X=x;
	c.Y=y;
	return SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}


void rect(int x,int yy,int w,int h,string c){
	string cc="";
	for(int i=0;i<w;i++){
		cc+=c;
	}
	for(int y=0;y<h;y++){
		scpt(x,yy+y);
		cout << cc;
	}
}

void grass(int x,int y,int w,int h){
	rect(x,y,w/2,h,",.");
}

struct grassPatch{
	int x;
	int y;
	int w=0;
	int h=0;
};
int x=10;
int y=10;
bool touching(int xx,int yy,int w,int h){
	return (x>=xx && x<=xx+w && y>=yy && y<=yy+h);
}

void house(int x,int y){
	scpt(x,y+0);
	cout << "   /\\";
	scpt(x,y+1);
	cout << "  /  \\";
	scpt(x,y+2);
	cout << " /    \\";
	scpt(x,y+3);
	cout << " | [] |";
	scpt(x,y+4);
	cout << " |____|";
}

void battle(){
	int ph=100;
	int eh=100;
	string move;
	int em;
	rect(0,0,120,30," ");
	while(ph > 0 && eh > 0){
		em=rand()%2;
		scpt(5,2);
		cout << "   ";
		cout << ph;
		scpt(110,2);
		
		scpt(110,2);
		cout << "   ";
		scpt(110,2);
		cout << eh;
		scpt(5,4);
		cout << "attack";
		scpt(5,6);
		cout << "heal";
		cin >> move;
		if(move=="attack"){
			eh-=10+(rand()%10-5);
		}
		if(move=="heal"){
			ph+=10+(rand()%10-5);
		}
		switch(em){
			case 0:
				eh+=10+(rand()%10-5);
			break;
			case 1:
				ph-=10+(rand()%10-5);
			break;
			
		}
	}
	rect(0,0,120,30," ");
}

int count=0;
vector<grassPatch> gps={};
int main(){
	srand(time(0));
	gps.push_back(grassPatch());
	gps[0].x=0;
	gps[0].y=5;
	gps[0].w=120;
	gps[0].h=24;
	while(true){
		for(int i=0;i<gps.size();i++){
			grass(
			gps[i].x,
			gps[i].y,
			gps[i].w,
			gps[i].h);
		}
		house(60,15);
		
		if(GetAsyncKeyState(VK_RIGHT) < 0){
			x++;
			for(int i=0;i<gps.size();i++){
			if(touching(gps[i].x,
			gps[i].y,
			gps[i].w,
			gps[i].h)
			&&
			rand()%100<5
			){
				battle();
			}
		}
		}
		if(GetAsyncKeyState(VK_LEFT) < 0){
			x--;
			for(int i=0;i<gps.size();i++){
			if(touching(gps[i].x,
			gps[i].y,
			gps[i].w,
			gps[i].h)
			&&
			rand()%100<5
			){
				battle();
			}
		}
		}
		if(GetAsyncKeyState(VK_DOWN) < 0){
			y++;
			for(int i=0;i<gps.size();i++){
			if(touching(gps[i].x,
			gps[i].y,
			gps[i].w,
			gps[i].h)
			&&
			rand()%100<5
			){
				battle();
			}
		}
		}
		if(GetAsyncKeyState(VK_UP) < 0){
			y--;
			for(int i=0;i<gps.size();i++){
			if(touching(gps[i].x,
			gps[i].y,
			gps[i].w,
			gps[i].h)
			&&
			rand()%100<5
			){
				battle();
			}
		}
		}
		
		scpt(x,y);
		cout << ":)";
		for(int j=0;j<8000;j++){
			scpt(0,0);
		}
		cout << count;
	}
}
