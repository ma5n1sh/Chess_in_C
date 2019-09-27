#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include <unistd.h>
#include <windows.h>
#include "A&H_Chess.h"


//player 1 small letters, the upper part, black
//player -1 capital letters, the lower part, white

int main(){
int s,s1=0;
initialScreen();
initialPlaces();
boardPrinter();
saveFileCreator();
stepAdder();
s=flowHandler();
while(s==1){
inputTaker();
s=flowHandler();
}
if(s==2){printf("\n\t\t\t\tSTALEMATE\a");}
if(s==0){printf("\n\t\t\t\tCHECKMATE\a");}
printf("\n\n\npress any key to continue..........");
getchar();
return 0;
}
