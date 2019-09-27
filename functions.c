#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include <unistd.h>
#include <windows.h>
#include "A&H_Chess.h"
//player 1 small letters, the upper part, black
//player -1 capital letters, the lower part, white
char board[8][8];
char deadWhite[16]={' '},deadBlack[16]={' '};
int nBlack=0,nWhite=0;
char virtBoard[8][8];
int x_1, y_1, x_2, y_2,player=1;
int blackKing[2]={0,4},whiteKing[2]={7,4};
int undoFlag=0,counter=0,undoNum=0;
char player1[13],player2[13],prom;
int bk,wk,r1,r2,r3,r4,cas;
bk=0;wk=0;r1=0;r2=0;r3=0;r4=0;cas=0;

void SetColorAndBackground(int ForgC, int BackC){
     WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
     return;
}
void initialScreen(){
int i=0;
printf("        CCCCCCCCCCCChhhhhhh\n");
printf("     CCC::::::::::::h:::::h\n");
printf("   CC:::::::::::::::h:::::h\n");
printf("  C:::::CCCCCCCC::::h:::::h\n");
printf(" C:::::C       CCCCCCh::::h hhhhh          eeeeeeeeeeee       ssssssssss      ssssssssss\n");
printf("C:::::C              h::::hh:::::hhh     ee::::::::::::ee   ss::::::::::s   ss::::::::::s\n");
printf("C:::::C              h::::::::::::::hh  e::::::eeeee:::::ess:::::::::::::sss:::::::::::::s\n");
printf("C:::::C              h:::::::hhh::::::he::::::e     e:::::s::::::ssss:::::s::::::ssss:::::s\n");
printf("C:::::C              h::::::h   h::::::e:::::::eeeee::::::es:::::s  ssssss s:::::s  ssssss\n");
printf("C:::::C              h:::::h     h:::::e:::::::::::::::::e   s::::::s        s::::::s\n");
printf("C:::::C              h:::::h     h:::::e::::::eeeeeeeeeee       s::::::s        s::::::s\n");
printf(" C:::::C       CCCCCCh:::::h     h:::::e:::::::e          ssssss   s:::::sssssss   s:::::s\n");
printf("  C:::::CCCCCCCC::::Ch:::::h     h:::::e::::::::e         s:::::ssss::::::s:::::ssss::::::s\n");
printf("   CC:::::::::::::::Ch:::::h     h:::::he::::::::eeeeeeee s::::::::::::::ss::::::::::::::s\n ");
printf("     CCC::::::::::::Ch:::::h     h:::::h ee:::::::::::::e  s:::::::::::ss  s:::::::::::ss\n  ");
printf("        CCCCCCCCCCCCChhhhhhh     hhhhhhh   eeeeeeeeeeeeee   sssssssssss     sssssssssss\n    ");
printf("                                         Hossam ElDin ElKordi©Ahmed Yasser Ahmed (c) \n    ");
printf("\n\n\n");
printf("\nEnter Player 1 Name:");
fgets(player1,12,stdin);
printf("Enter Player 2 Name:");
fgets(player2,12,stdin);
printf("\n\n\npress any key to continue..........");
getchar();
while(player1[i]!='\0'){if(player1[i]=='\n')player1[i]=' ';i++;}
i=0;
while(player2[i]!='\0'){if(player2[i]=='\n')player2[i]=' ';i++;}
}

void initialPlaces(){
    int i,j;
for(i=0;i<8;i++){
    for(j=0;j<8;j++){
        if(i==6){board[i][j]='P';}
        else if(i==1){board[i][j]='p';}
        else if(i==7){
            switch(j){
            case 0:;
            case 7:board[i][j]='R';break;
            case 6:;
            case 1:board[i][j]='N';break;
            case 2:;
            case 5:board[i][j]='B';break;
            case 3:board[i][j]='Q';break;
            case 4:board[i][j]='K';break;
            }
        }
        else if(i==0){
            switch(j){
            case 0:;
            case 7:board[i][j]='r';break;
            case 6:;
            case 1:board[i][j]='n';break;
            case 2:;
            case 5:board[i][j]='b';break;
            case 3:board[i][j]='q';break;
            case 4:board[i][j]='k';break;
            }
        }
        else {board[i][j]=' ';}
    }

}
for(i=0;i<16;i++){deadWhite[i]=' ';deadBlack[i]=' ';}

}

void boardPrinter(){
system("cls");
int i,j,flag=0;
if (player==1){printf("\t\t\t\t%s's turn\n",player1);}
if (player==-1){printf("\t\t\t\t%s's turn\n",player2);}
printf("\n\n\n\n\n");
printf("                         ");
printf("   ");
for(i=-1;i<9;i++){
    for(j=-1;j<9;j++){if(i==8&&j==-1){printf("   ");}
        if (i<0||i>7){
            if(j>=0&&j<8){printf(" %c ",65+j);}
        }
        else if(j>=0&&j<8){if((flag+i)%2==0){
                if(islower((int)board[i][j])){SetColorAndBackground(0, 22);printf(" %c ",board[i][j]);flag++;}else{
                    SetColorAndBackground(15, 22);printf(" %c ",board[i][j]);flag++;
                }}
        else if ((flag+i)%2==1){if(islower((int)board[i][j])){SetColorAndBackground(0, 84);printf(" %c ",board[i][j]);flag++;}else{
                    SetColorAndBackground(15, 84);printf(" %c ",board[i][j]);flag++;
                }}
        }
        else {SetColorAndBackground(15, 0);;printf(" %d ",i+1);}
    }
printf("\n");
printf("                         ");
}
printf("dead White pieces: ");
printf("\n");
printf("                         ");
for(i=0;i<nWhite;i++){printf("%c ",deadWhite[i]);}
printf("\n");
printf("                         ");
printf("dead Black pieces: ");
printf("\n");
printf("                         ");
for(i=0;i<nBlack;i++){printf("%c ",deadBlack[i]);}
printf("\n");
printf("                         ");
}

void saveFileCreator(){
FILE* file = fopen("file.txt", "w");
fclose(file);
}

void stepAdder(){
char temp[3];
int i,j;
if(undoFlag==1){
 FILE* file = fopen("file.txt", "w");
 FILE* filetemp = fopen("filetemp.txt", "r");
 char line[256];
while (fgets(line, sizeof(line), filetemp)) {
    fprintf(file,line);
    }
fclose(file);
fclose(filetemp);
undoFlag=0;
}
FILE* file = fopen("file.txt", "a");
temp[1]='\n';temp[2]='\0';
for(i=0;i<8;i++){
    for(j=0;j<8;j++){
        temp[0]=board[i][j];
        fprintf(file,temp);
    }
}
for(i=0;i<16;i++){
    temp[0]=deadWhite[i];
    fprintf(file,temp);
}
temp[0]=nWhite+'0';
fprintf(file,temp);
for(i=0;i<16;i++){
    temp[0]=deadBlack[i];
    fprintf(file,temp);
}
temp[0]=nBlack+'0';
fprintf(file,temp);
fclose(file);
undoNum=0;
}

void gameSaver(){
char temp[3];
int i,j;
FILE* file = fopen("load.txt", "w");
temp[1]='\n';temp[2]='\0';
for(i=0;i<8;i++){
    for(j=0;j<8;j++){
        temp[0]=board[i][j];
        fprintf(file,temp);
    }
}
for(i=0;i<16;i++){
    temp[0]=deadWhite[i];
    fprintf(file,temp);
}
temp[0]=nWhite+'0';
fprintf(file,temp);
for(i=0;i<16;i++){
    temp[0]=deadBlack[i];
    fprintf(file,temp);
}
temp[0]=nBlack+'0';
fprintf(file,temp);
temp[0]=player+'1';
fprintf(file,temp);
fclose(file);

}

void stepUndoer(int step){//where the initial setup is step zero
int i=0,j=0,z=0,k=0;
FILE *file = fopen("file.txt", "r");
FILE *filetemp = fopen("filetemp.txt", "w");
char line[256];
while (fgets(line, sizeof(line), file)) {
    z++;
    fprintf(filetemp,line);
    if(z>(98*step)){
        if(j==8){j=0;i++;}
        if(i<8){
        board[i][j]=line[0];
        j++;
        }
        else if(k<16)
        {deadWhite[k]=line[0];k++;}
        else if(k==16){nWhite=line[0]-'0';k++;}
        else if(k<33){deadBlack[k-17]=line[0];k++;}
        else if(k==33){nBlack=line[0]-'0';break;}

    }}
fclose(file);
fclose(filetemp);
undoFlag=1;
for(i=0;i<8;i++){
    for(j=0;j<8;j++){
        if(board[i][j]=='k'){blackKing[0]=i;blackKing[1]=j;}
        if(board[i][j]=='K'){whiteKing[0]=i;whiteKing[1]=j;}
    }
}
}

void boardCopier(){
int i,j;
for(i=0;i<8;i++){
    for(j=0;j<8;j++){
        virtBoard[i][j]=board[i][j];
    }
}
}

int checkChecker(int a,int x_checked,int y_checked){//returns 0 when there is a checkmate in (x_checked,y_checked), a==1 checks in the regular board  a==2 checks in the virtual board
int i=1;
if(a==1){
if (player==1){
    //pawn
    if((board[y_checked+1][x_checked+1]=='P'&&x_checked+1<8&&y_checked+1<8)||(board[y_checked+1][x_checked-1]=='P'&&y_checked+1<8&&x_checked-1>=0)){return 0;}
     //queen diagonally and bishop
    while(x_checked+i<8&&y_checked+i<8){
        if(board[y_checked+i][x_checked+i]=='B'||board[y_checked+i][x_checked+i]=='Q'){return 0;}
        if(board[y_checked+i][x_checked+i]!=' '){break;}
        i++;
    }
    i=1;
    while(x_checked-i>=0&&y_checked+i<8){
        if(board[y_checked+i][x_checked-i]=='B'||board[y_checked+i][x_checked-i]=='Q'){return 0;}
        if(board[y_checked+i][x_checked-i]!=' '){break;}
        i++;
    }
    i=1;
     while(x_checked-i>=0&&y_checked-i>=0){
        if(board[y_checked-i][x_checked-i]=='B'||board[y_checked-i][x_checked-i]=='Q'){return 0;}
        if(board[y_checked-i][x_checked-i]!=' '){break;}
        i++;
    }i=1;
    while(x_checked+i<8&&y_checked-i>=0){
        if(board[y_checked-i][x_checked+i]=='B'||board[y_checked-i][x_checked+i]=='Q'){return 0;}
        if(board[y_checked-i][x_checked+i]!=' '){break;}
        i++;
    }
    i=1;
    //queen horizontally and vertically and rooks
    while(x_checked+i<8){
        if(board[y_checked][x_checked+i]=='R'||board[y_checked][x_checked+i]=='Q'){return 0;}
        if(board[y_checked][x_checked+i]!=' '){break;}
        i++;
    }
    i=1;
    while(x_checked-i>=0){
        if(board[y_checked][x_checked-i]=='R'||board[y_checked][x_checked-i]=='Q'){return 0;}
        if(board[y_checked][x_checked-i]!=' '){break;}
        i++;
    }
    i=1;
    while(y_checked+i<8){
        if(board[y_checked+i][x_checked]=='R'||board[y_checked+i][x_checked]=='Q'){return 0;}
        if(board[y_checked+i][x_checked]!=' '){break;}
        i++;
    }
    i=1;
    while(y_checked-i<=0){
        if(board[y_checked-i][x_checked]=='R'||board[y_checked-i][x_checked]=='Q'){return 0;}
        if(board[y_checked-i][x_checked]!=' '){break;}
        i++;
    }

    i=1;
    //knight
    if(x_checked+1<8&&y_checked+2<8&&board[y_checked+2][x_checked+1]=='N'){return 0;}
    if(x_checked-1>=0&&y_checked+2<8&&board[y_checked+2][x_checked-1]=='N'){return 0;}
    if(x_checked+1<8&&y_checked-2>=0&&board[y_checked-2][x_checked+1]=='N'){return 0;}
    if(x_checked-1>=0&&y_checked-2>=0&&board[y_checked-2][x_checked-1]=='N'){return 0;}
    if(x_checked+2<8&&y_checked+1<8&&board[y_checked+1][x_checked+2]=='N'){return 0;}
    if(x_checked-2>=0&&y_checked+1<8&&board[y_checked+1][x_checked-2]=='N'){return 0;}
    if(x_checked-2>=0&&y_checked-1>=0&&board[y_checked-1][x_checked-2]=='N'){return 0;}
    if(x_checked+2<8&&y_checked-1>=0&&board[y_checked-1][x_checked+2]=='N'){return 0;}
}

if (player==-1){i=-1;
    //pawn
    if(board[y_checked-1][x_checked-1]=='p'||board[y_checked-1][x_checked+1]=='p'){return 0;}

 //queen diagonally and bishop
    while(x_checked+i>=0&&y_checked+i>=0){
        if(board[y_checked+i][x_checked+i]=='b'||board[y_checked+i][x_checked+i]=='q'){return 0;}
        if(board[y_checked+i][x_checked+i]!=' '){break;}
        i--;
    }
    i=-1;
    while(x_checked-i<8&&y_checked+i>=0){
        if(board[y_checked+i][x_checked-i]=='b'||board[y_checked+i][x_checked-i]=='q'){return 0;}
        if(board[y_checked+i][x_checked-i]!=' '){break;}
        i--;
    }
    i=-1;
     while(x_checked-i<8&&y_checked-i<8){
        if(board[y_checked-i][x_checked-i]=='b'||board[y_checked-i][x_checked-i]=='q'){return 0;}
        if(board[y_checked-i][x_checked-i]!=' '){break;}
        i--;
    }i=-1;
    while(x_checked+i>=0&&y_checked-i<8){
        if(board[y_checked-i][x_checked+i]=='b'||board[y_checked-i][x_checked+i]=='q'){return 0;}
        if(board[y_checked-i][x_checked+i]!=' '){break;}
        i--;
    }
    i=-1;
    //queen horizontally and vertically and rooks
    while(x_checked+i>=0){
        if(board[y_checked][x_checked+i]=='r'||board[y_checked][x_checked+i]=='q'){return 0;}
        if(board[y_checked][x_checked+i]!=' '){break;}
        i--;
    }
    i=-1;
    while(x_checked-i<8){
        if(board[y_checked][x_checked-i]=='r'||board[y_checked][x_checked-i]=='q'){return 0;}
        if(board[y_checked][x_checked-i]!=' '){break;}
        i--;
    }
    i=-1;
    while(y_checked+i>=0){
        if(board[y_checked+i][x_checked]=='r'||board[y_checked+i][x_checked]=='q'){return 0;}
        if(board[y_checked+i][x_checked]!=' '){break;}
        i--;
    }
    i=-1;
    while(y_checked-i>8){
        if(board[y_checked-i][x_checked]=='r'||board[y_checked-i][x_checked]=='q'){return 0;}
        if(board[y_checked-i][x_checked]!=' '){break;}
        i--;
    }

    i=1;
    //knight
    if(x_checked+1<8&&y_checked+2<8&&board[y_checked+2][x_checked+1]=='n'){return 0;}
    if(x_checked-1>=0&&y_checked+2<8&&board[y_checked+2][x_checked-1]=='n'){return 0;}
    if(x_checked+1<8&&y_checked-2>=0&&board[y_checked-2][x_checked+1]=='n'){return 0;}
    if(x_checked-1>=0&&y_checked-2>=0&&board[y_checked-2][x_checked-1]=='n'){return 0;}
    if(x_checked+2<8&&y_checked+1<8&&board[y_checked+1][x_checked+2]=='n'){return 0;}
    if(x_checked-2>=0&&y_checked+1<8&&board[y_checked+1][x_checked-2]=='n'){return 0;}
    if(x_checked-2>=0&&y_checked-1>=0&&board[y_checked-1][x_checked-2]=='n'){return 0;}
    if(x_checked+2<8&&y_checked-1>=0&&board[y_checked-1][x_checked+2]=='n'){return 0;}
}
return 1;

}
if(a==2){
if (player==1){
    //pawn
    if(virtBoard[y_checked+1][x_checked+1]=='P'||virtBoard[y_checked+1][x_checked-1]=='P'){return 0;}
    //queen diagonally and bishop
    while(x_checked+i<8&&y_checked+i<8){
        if(virtBoard[y_checked+i][x_checked+i]=='B'||virtBoard[y_checked+i][x_checked+i]=='Q'){return 0;}
        if(virtBoard[y_checked+i][x_checked+i]!=' '){break;}
        i++;
    }
    i=1;
    while(x_checked-i>=0&&y_checked+i<8){
        if(virtBoard[y_checked+i][x_checked-i]=='B'||virtBoard[y_checked+i][x_checked-i]=='Q'){return 0;}
        if(virtBoard[y_checked+i][x_checked-i]!=' '){break;}
        i++;
    }
    i=1;
     while(x_checked-i>=0&&y_checked-i>=0){
        if(virtBoard[y_checked-i][x_checked-i]=='B'||virtBoard[y_checked-i][x_checked-i]=='Q'){return 0;}
        if(virtBoard[y_checked-i][x_checked-i]!=' '){break;}
        i++;
    }i=1;
    while(x_checked+i<8&&y_checked-i>=0){
        if(virtBoard[y_checked-i][x_checked+i]=='B'||virtBoard[y_checked-i][x_checked+i]=='Q'){return 0;}
        if(virtBoard[y_checked-i][x_checked+i]!=' '){break;}
        i++;
    }
    i=1;
    //queen horizontally and vertically and rooks
    while(x_checked+i<8){
        if(virtBoard[y_checked][x_checked+i]=='R'||virtBoard[y_checked][x_checked+i]=='Q'){return 0;}
        if(virtBoard[y_checked][x_checked+i]!=' '){break;}
        i++;
    }
    i=1;
    while(x_checked-i>=0){
        if(virtBoard[y_checked][x_checked-i]=='R'||virtBoard[y_checked][x_checked-i]=='Q'){return 0;}
        if(virtBoard[y_checked][x_checked-i]!=' '){break;}
        i++;
    }
    i=1;
    while(y_checked+i<8){
        if(virtBoard[y_checked+i][x_checked]=='R'||virtBoard[y_checked+i][x_checked]=='Q'){return 0;}
        if(virtBoard[y_checked+i][x_checked]!=' '){break;}
        i++;
    }
    i=1;
    while(y_checked-i<=0){
        if(virtBoard[y_checked-i][x_checked]=='R'||virtBoard[y_checked-i][x_checked]=='Q'){return 0;}
        if(virtBoard[y_checked-i][x_checked]!=' '){break;}
        i++;
    }

    i=1;
    //knight
    if(x_checked+1<8&&y_checked+2<8&&virtBoard[y_checked+2][x_checked+1]=='N'){return 0;}
    if(x_checked-1>=0&&y_checked+2<8&&virtBoard[y_checked+2][x_checked-1]=='N'){return 0;}
    if(x_checked+1<8&&y_checked-2>=0&&virtBoard[y_checked-2][x_checked+1]=='N'){return 0;}
    if(x_checked-1>=0&&y_checked-2>=0&&virtBoard[y_checked-2][x_checked-1]=='N'){return 0;}
    if(x_checked+2<8&&y_checked+1<8&&virtBoard[y_checked+1][x_checked+2]=='N'){return 0;}
    if(x_checked-2>=0&&y_checked+1<8&&virtBoard[y_checked+1][x_checked-2]=='N'){return 0;}
    if(x_checked-2>=0&&y_checked-1>=0&&virtBoard[y_checked-1][x_checked-2]=='N'){return 0;}
    if(x_checked+2<8&&y_checked-1>=0&&virtBoard[y_checked-1][x_checked+2]=='N'){return 0;}
}

if (player==-1){i=-1;
    //pawn
    if(virtBoard[y_checked-1][x_checked-1]=='p'||virtBoard[y_checked-1][x_checked+1]=='p'){return 0;}

    //queen diagonally and bishop
    while(x_checked+i>=0&&y_checked+i>=0){
        if(virtBoard[y_checked+i][x_checked+i]=='b'||virtBoard[y_checked+i][x_checked+i]=='q'){return 0;}
        if(virtBoard[y_checked+i][x_checked+i]!=' '){break;}
        i--;
    }
    i=-1;
    while(x_checked-i<8&&y_checked+i>=0){
        if(virtBoard[y_checked+i][x_checked-i]=='b'||virtBoard[y_checked+i][x_checked-i]=='q'){return 0;}
        if(virtBoard[y_checked+i][x_checked-i]!=' '){break;}
        i--;
    }
    i=-1;
     while(x_checked-i<8&&y_checked-i<8){
        if(virtBoard[y_checked-i][x_checked-i]=='b'||virtBoard[y_checked-i][x_checked-i]=='q'){return 0;}
        if(virtBoard[y_checked-i][x_checked-i]!=' '){break;}
        i--;
    }
    i=-1;
    while(x_checked+i>=0&&y_checked-i<8){
        if(virtBoard[y_checked-i][x_checked+i]=='b'||virtBoard[y_checked-i][x_checked+i]=='q'){return 0;}
        if(virtBoard[y_checked-i][x_checked+i]!=' '){break;}
        i--;
    }
    i=-1;
    //queen horizontally and vertically and rooks
    while(x_checked+i>=0){
        if(virtBoard[y_checked][x_checked+i]=='r'||virtBoard[y_checked][x_checked+i]=='q'){return 0;}
        if(virtBoard[y_checked][x_checked+i]!=' '){break;}
        i--;
    }
    i=-1;
    while(x_checked-i<8){
        if(virtBoard[y_checked][x_checked-i]=='r'||virtBoard[y_checked][x_checked-i]=='q'){return 0;}
        if(virtBoard[y_checked][x_checked-i]!=' '){break;}
        i--;
    }
    i=-1;
    while(y_checked+i>=0){
        if(virtBoard[y_checked+i][x_checked]=='r'||virtBoard[y_checked+i][x_checked]=='q'){return 0;}
        if(virtBoard[y_checked+i][x_checked]!=' '){break;}
        i--;
    }
    i=-1;
    while(y_checked-i<8){
        if(virtBoard[y_checked-i][x_checked]=='r'||virtBoard[y_checked-i][x_checked]=='q'){return 0;}
        if(virtBoard[y_checked-i][x_checked]!=' '){break;}
        i--;
    }

    i=1;
    //knight
    if(x_checked+1<8&&y_checked+2<8&&virtBoard[y_checked+2][x_checked+1]=='n'){return 0;}
    if(x_checked-1>=0&&y_checked+2<8&&virtBoard[y_checked+2][x_checked-1]=='n'){return 0;}
    if(x_checked+1<8&&y_checked-2>=0&&virtBoard[y_checked-2][x_checked+1]=='n'){return 0;}
    if(x_checked-1>=0&&y_checked-2>=0&&virtBoard[y_checked-2][x_checked-1]=='n'){return 0;}
    if(x_checked+2<8&&y_checked+1<8&&virtBoard[y_checked+1][x_checked+2]=='n'){return 0;}
    if(x_checked-2>=0&&y_checked+1<8&&virtBoard[y_checked+1][x_checked-2]=='n'){return 0;}
    if(x_checked-2>=0&&y_checked-1>=0&&virtBoard[y_checked-1][x_checked-2]=='n'){return 0;}
    if(x_checked+2<8&&y_checked-1>=0&&virtBoard[y_checked-1][x_checked+2]=='n'){return 0;}
}
return 1;
}
}

int check_allMoves(){
    boardCopier();
    virtBoard[y_2][x_2] = virtBoard[y_1][x_1];
    virtBoard[y_1][x_1] = ' ';
    if (player==1){
        if(!checkChecker(2,blackKing[1],blackKing[0])){
            return 0;
        }
    }
    if (player==-1){
        if(!checkChecker(2,whiteKing[1],whiteKing[0])){
            return 0;
        }
    }
    return 1;
}

void gameRestorer(){
int i=0,j=0,k=0;
FILE *file = fopen("load.txt", "a");
fclose(file);
file = fopen("load.txt", "r");
char line[256];
while (fgets(line, sizeof(line), file)){k++;}
if(k<10){printf("\n\t\t\tNo Previously Saved Game\n\t\t\t"); }

else{k=0;fclose(file);file = fopen("load.txt", "r");
while (fgets(line, sizeof(line), file)) {

        if(i<8){
        board[i][j]=line[0];
        j++;
        if(j==8){j=0;i++;}
        }
        else if(k<16)
        {deadWhite[k]=line[0];k++;}
        else if(k==16){nWhite=line[0]-'0';k++;}
        else if(k<33){deadBlack[k-17]=line[0];k++;}
        else if(k==33){nBlack=line[0]-'0';k++;}
        else if(k==34){player=line[0]-'1';break;}
    }saveFileCreator();stepAdder();boardPrinter();
    printf("Loaded Successfully\n\t\t\t");}
fclose(file);

}

int bishop (){
    if (abs(x_2-x_1)!=abs(y_2-y_1)){
        return 0;
    }
    if ((x_2-x_1)>0 && (y_2-y_1)>0){
        for (int i=1; i<abs(x_2-x_1); i++){
            if (board[y_1+i][x_1+i]!=' '){
                return 0;
            }
        }
    }
    if ((x_2-x_1)<0 && (y_2-y_1)<0){
        for (int i=1; i<abs(x_2-x_1); i++){
            if (board[y_1-i][x_1-i]!=' '){
                return 0;
            }
        }
    }
    if ((x_2-x_1)>0 && (y_2-y_1)<0){
        for (int i=1; i<abs(x_2-x_1); i++){
            if (board[y_1-i][x_1+i]!=' '){
                return 0;
            }
        }
    }
    if ((x_2-x_1)<0 && (y_2-y_1)>0){
        for (int i=1; i<abs(x_2-x_1); i++){
            if (board[y_1+i][x_1-i]!=' '){
                return 0;
            }
        }
    }
    if (!check_allMoves()){return 0;}
}

int rook (){
    if (abs(x_2-x_1)==0 && abs(y_2-y_1)==0){
        return 0;}

     if (abs(x_2-x_1)!=0 && abs(y_2-y_1)!=0){
        return 0;}

    if ((y_2-y_1)==0 && (x_2-x_1)>0){
           for (int i=1; i<abs(x_2-x_1); i++){
               if (board[y_1][x_1+i]!=' '){
                    return 0;
               }
           }}

    if ((y_2-y_1)==0 && (x_2-x_1)<0){
            for (int i=1; i<abs(x_2-x_1); i++){
                if (board[y_1][x_1-i]!=' '){
                    return 0;
                }
            }
    }
    if ((x_2-x_1)==0 && (y_2-y_1)>0){
            for (int i=1; i<abs(y_2-y_1); i++){
                if (board[y_1+i][x_1]!=' '){
                    return 0;
                }
            }
    }
    if ((x_2-x_1)==0 && (y_2-y_1)<0){
            for (int i=1; i<abs(y_2-y_1); i++){
                if (board[y_1-i][x_1]!=' '){
                    return 0;
                }
            }
    }
    if (!check_allMoves()){return 0;}
    if (player==1){
        if (x_1==0&&y_1==0&&board[0][0]=='r'){r1++;}
        if (x_1==7&&y_1==0&&board[0][7]=='r'){r2++;}
    }
    if (player==-1){
        if (x_1==0&&y_1==7&&board[7][0]=='R'){r3++;}
        if (x_1==7&&y_1==7&&board[7][7]=='R'){r4++;}
    }
    return 1;
}

int knight (){
    if (abs(x_2-x_1)>2 || abs(y_2-y_1)>2){
        return 0;
    }
    if ((abs(x_2-x_1)==2 && abs(y_2-y_1)!=1) || (abs(y_2-y_1)==2 && abs(x_2-x_1)!=1)){
        return 0;
    }
    if ((abs(x_2-x_1)==1 && abs(y_2-y_1)!=2) || (abs(y_2-y_1)==1 && abs(x_2-x_1)!=2)){
        return 0;
    }
    if (!check_allMoves()){return 0;}
    return 1;
}

int queen (){
    if (abs(x_2-x_1)>1 && abs(y_2-y_1)!=abs(x_2-x_1)&&(y_2-y_1)!=0){
        return 0;
    }
    if (abs(y_2-y_1)>1 && abs(x_2-x_1)!=abs(y_2-y_1)&&(x_2-x_1)!=0){
        return 0;
    }
    if ((y_2-y_1)==0 && (x_2-x_1)>0){
            for (int i=1; i<abs(x_2-x_1); i++){
                if (board[y_1][x_1+i]!=' '){
                    return 0;
                }
            }
    }
    if ((y_2-y_1)==0 && (x_2-x_1)<0){
            for (int i=1; i<abs(x_2-x_1); i++){
                if (board[y_1][x_1-i]!=' '){
                    return 0;
                }
            }
    }
    if ((x_2-x_1)==0 && (y_2-y_1)>0){
            for (int i=1; i<abs(y_2-y_1); i++){
                if (board[y_1+i][x_1]!=' '){
                    return 0;
                }
            }
    }
    if ((x_2-x_1)==0 && (y_2-y_1)<0){
            for (int i=1; i<abs(y_2-y_1); i++){
                if (board[y_1-i][x_1]!=' '){
                    return 0;
                }
            }
    }
    if ((x_2-x_1)>0 && (y_2-y_1)>0){
        for (int i=1; i<abs(x_2-x_1); i++){
            if (board[y_1+i][x_1+i]!=' '){
                return 0;
            }
        }
    }
    if ((x_2-x_1)<0 && (y_2-y_1)<0){
        for (int i=1; i<abs(x_2-x_1); i++){
            if (board[y_1-i][x_1-i]!=' '){
                return 0;
            }
        }
    }
    if ((x_2-x_1)>0 && (y_2-y_1)<0){
        for (int i=1; i<abs(x_2-x_1); i++){
            if (board[y_1-i][x_1+i]!=' '){
                return 0;
            }
        }
    }
    if ((x_2-x_1)<0 && (y_2-y_1)>0){
        for (int i=1; i<abs(x_2-x_1); i++){
            if (board[y_1+i][x_1-i]!=' '){
                return 0;
            }
        }
    }
    if (!check_allMoves()){return 0;}
    return 1;
}

int pawn (){
    if ((y_2-y_1)<0 && player==1){
        return 0;
    }
    if ((y_2-y_1)>0 && player==-1){
        return 0;
    }
    if (y_1==1 && player==1){
        if (abs(y_2-y_1)>2){
            return 0;
        }
    }
    if (y_1==6 && player==-1){
        if (abs(y_2-y_1)>2){
            return 0;
        }
    }
    if (y_1!=1 && y_1!=6){
        if (abs(y_2-y_1)!=1){
            return 0;
        }
    }
    if(abs(y_2-y_1)==0){return 0;}
    if ((x_2-x_1)==0){
      if (board[y_2][x_2]!=' '){
          return 0;
      }
    }

   if(abs(x_2-x_1)>1){return 0;}
   if(abs(x_2-x_1)==1&&board[y_2][x_2]==' '){return 0;}
   if (!check_allMoves()){return 0;}
   if ((board[y_1][x_1]=='P'&&y_2==0) || (board[y_1][x_1]=='p'&&y_2==7)){
        board[y_1][x_1] = prom;

   }

   return 1;
}

int king(){
if (abs(x_2-x_1)==2&&abs(y_2-y_1)==0){
    if (player==1){
        if (bk!=0){return 0;}
        if ((x_2-x_1)>0){
            if (board[0][5]!=' '||board[0][6]!=' '||r2!=0){return 0;}
            else{if(!checkChecker(1,x_2,y_2)){return 0;}cas=2;blackKing[0]=y_2;blackKing[1]=x_2;return 1;}
        }
        if ((x_2-x_1)<0){
            if (board[0][1]!=' '||board[0][2]!=' '||board[0][3]!=' '||r1!=0){return 0;}
            else{if(!checkChecker(1,x_2,y_2)){return 0;}cas=1;blackKing[0]=y_2;blackKing[1]=x_2;return 1;}
        }
    }
    if (player==-1){
        if (wk!=0||board[7][4]!='K'){return 0;}
        if ((x_2-x_1)>0){
            if (board[7][5]!=' '||board[7][6]!=' '||r4!=0){return 0;}
            else{if(!checkChecker(1,x_2,y_2)){return 0;}cas=4;whiteKing[0]=y_2;whiteKing[1]=x_2;return 1;}
        }
        if ((x_2-x_1)<0){
            if (board[7][1]!= ' '||board[7][2]!=' '||board[7][3]!=' '||r3!=0){return 0;}
            else{if(!checkChecker(1,x_2,y_2)){return 0;}cas=3;whiteKing[0]=y_2;whiteKing[1]=x_2;return 1;}
        }
    }
}
if(abs(x_2-x_1)>1||abs(y_2-y_1)>1){return 0;}
if(!checkChecker(1,x_2,y_2)){return 0;}
if (player==1){blackKing[0]=y_2;blackKing[1]=x_2;bk++;}
if (player==-1){whiteKing[0]=y_2;whiteKing[1]=x_2;wk++;}
return 1;
}

int validate_move (char move[]){//player 1 lowercase(small) player -1 uppercase(capital)
    if (strlen(move)>6){
        return 0;
    }
    if (islower((int)move[0])){
        if (strlen(move)>2){
            return 0;
        }else{
            return 1;
        }
    }
    if (move[0]<'A' || move[0]>'H'){
        return 0;
    }
    if (move[2]<'A' || move[2]>'H'){
        return 0;
    }
    if (move[1]<'1' || move[1]>'8'){
        return 0;
    }
    if (move[3]<'1' || move[3]>'8'){
        return 0;
    }
    x_1 = move[0]-65;
    y_1 = move[1]-'1';
    x_2 = move[2]-65;
    y_2 = move[3]-'1';
    if (board[y_1][x_1]==' '){
        return 0;
    }
    if (x_1>8||x_1<0||x_2>8||x_1<0||y_1>8||y_1<0||y_2>8||y_2<0){
        return 0;
    }
    if (((board[y_1][x_1]>='A'&& board[y_1][x_1]<='Z')&&player==1) ||((board[y_1][x_1]>='a'&&board[y_1][x_1]<='z')&&player==-1)){
        return 0;
    }
    if (((board[y_2][x_2]>='A'&&board[y_2][x_2]<='Z')&&player==-1) ||((board[y_2][x_2]>='a'&&board[y_2][x_2]<='z')&&player==1)){
        return 0;
    }
    if((board[y_1][x_1]=='p'&&y_1==6)||(board[y_1][x_1]=='P'&&y_1==1)){
        if (move[4]!='q' && move[4]!='Q' && move[4]!='b' && move[4]!='B' && move[4]!='r' && move[4]!='R' && move[4]!='n' && move[4]!='N'){
           return 0;
        }
        if(y_1==1 && islower((int)move[4]) || y_1==6 && isupper((int)move[4])){
            return 0;
        }else{
            prom = move[4];
        }
    }
    return 1;
}

int staleChecker(){//returns 0 when there is a stale, returns 1 when there isn't
int ky,kx,ky1,kx1,i,j,k;
if(player==1){
    ky=blackKing[0];kx=blackKing[1];
    boardCopier();
    //king
    ky1=ky+1;kx1=kx;
    if(ky1>=0&&ky1<8&&kx1>=0&&kx1<8){
        if(virtBoard[ky1][kx1]>='A' && virtBoard[ky1][kx1]<='Z'){
            virtBoard[ky][kx]=' ';
            if(checkChecker(2,kx1,ky1)){return 1;}
        }
        if((virtBoard[ky1][kx1]==' ')){
            virtBoard[ky][kx]=' ';
            if(checkChecker(2,kx1,ky1)){return 1;}
           }

    }
    boardCopier();
    ky1=ky-1;kx1=kx+1;
    if(ky1>=0&&ky1<8&&kx1>=0&&kx1<8){
        if(virtBoard[ky1][kx1]>='A' && virtBoard[ky1][kx1]<='Z'){
            virtBoard[ky][kx]=' ';
            if(checkChecker(2,kx1,ky1)){return 1;}
        }
        if((virtBoard[ky1][kx1]==' ')){
            virtBoard[ky][kx]=' ';
            if(checkChecker(2,kx1,ky1)){return 1;}
           }

    }
    boardCopier();
    ky1=ky+1;kx1=kx+1;
    if(ky1>=0&&ky1<8&&kx1>=0&&kx1<8){
        if(virtBoard[ky1][kx1]>='A' && virtBoard[ky1][kx1]<='Z'){
            virtBoard[ky][kx]=' ';
            if(checkChecker(2,kx1,ky1)){return 1;}
        }
        if((virtBoard[ky1][kx1]==' ')){
            virtBoard[ky][kx]=' ';
            if(checkChecker(2,kx1,ky1)){return 1;}
           }

    }
    boardCopier();
    ky1=ky-1;kx1=kx-1;
    if(ky1>=0&&ky1<8&&kx1>=0&&kx1<8){
        if(virtBoard[ky1][kx1]>='A' && virtBoard[ky1][kx1]<='Z'){
            virtBoard[ky][kx]=' ';
            if(checkChecker(2,kx1,ky1)){return 1;}
        }
        if(virtBoard[ky1][kx1]==' '){
            virtBoard[ky][kx]=' ';
            if(checkChecker(2,kx1,ky1)){return 1;}
           }

    }

    boardCopier();
    ky1=ky;kx1=kx+1;
    if(ky1>=0&&ky1<8&&kx1>=0&&kx1<8){
        if(virtBoard[ky1][kx1]>='A' && virtBoard[ky1][kx1]<='Z'){
            virtBoard[ky][kx]=' ';
            if(checkChecker(2,kx1,ky1)){return 1;}
        }
        if(virtBoard[ky1][kx1]==' '){
            virtBoard[ky][kx]=' ';
            if(checkChecker(2,kx1,ky1)){return 1;}
           }

    }

    boardCopier();
    ky1=ky+1;kx1=kx-1;
    if(ky1>=0&&ky1<8&&kx1>=0&&kx1<8){
        if(virtBoard[ky1][kx1]>='A' && virtBoard[ky1][kx1]<='Z'){
            virtBoard[ky][kx]=' ';
            if(checkChecker(2,kx1,ky1)){return 1;}
        }
        if(virtBoard[ky1][kx1]==' '){
            virtBoard[ky][kx]=' ';
            if(checkChecker(2,kx1,ky1)){return 1;}
           }

    }
    boardCopier();
    ky1=ky;kx1=kx-1;
    if(ky1>=0&&ky1<8&&kx1>=0&&kx1<8){
        if(virtBoard[ky1][kx1]>='A' && virtBoard[ky1][kx1]<='Z'){
            virtBoard[ky][kx]=' ';
            if(checkChecker(2,kx1,ky1)){return 1;}
        }
        if(virtBoard[ky1][kx1]==' '){
            virtBoard[ky][kx]=' ';
            if(checkChecker(2,kx1,ky1)){return 1;}
           }

    }
    boardCopier();
    ky1=ky-1;kx1=kx;
    if(ky1>=0&&ky1<8&&kx1>=0&&kx1<8){
        if(virtBoard[ky1][kx1]>='A' && virtBoard[ky1][kx1]<='Z'){
            virtBoard[ky][kx]=' ';
            if(!checkChecker(2,kx1,ky1)){return 1;}
        }
        if(virtBoard[ky1][kx1]==' '){
            virtBoard[ky][kx]=' ';
            if(checkChecker(2,kx1,ky1)){return 1;}
           }

    }
for(i=0;i<8;i++){
    for(j=0;j<8;j++){boardCopier();
      switch(virtBoard[i][j]){
      case 'p':if(i+1<8){if(virtBoard[i+1][j]==' '){
                    if(i!=1){virtBoard[i+1][j]='p';virtBoard[i][j]=' ';if(checkChecker(2,kx,ky)){return 1;}}
                    else{virtBoard[i+1][j]='p';virtBoard[i][j]=' ';if(checkChecker(2,kx,ky)){return 1;}
                   if(i+1<8){ if(virtBoard[i+2][j]==' '){ virtBoard[i+2][j]='p';virtBoard[i=1][j]=' ';if(checkChecker(2,kx,ky)){return 1;}}}}}
                }boardCopier();
                 if(i+1<8&&j+1<8){if(virtBoard[i+1][j+1]>='A'&&virtBoard[i+1][j+1]<='Z'){
                       virtBoard[i+1][j+1]='p';virtBoard[i][j]=' ';
                        if(checkChecker(2,kx,ky)){return 1;}
                }}
                boardCopier();
                 if(i+1<8&&j-1>=0){if(virtBoard[i+1][j-1]>='A'&&virtBoard[i+1][j-1]<='Z'){
                        virtBoard[i+1][j-1]='p';virtBoard[i][j]=' ';
                        if(checkChecker(2,kx,ky)){return 1;}
                }};break;

      case 'b':k=1;boardCopier();
                while((i+k)<8&&(j+k)<8&&(virtBoard[i+k-1][j+k-1]==' '||virtBoard[i+k-1][j+k-1]=='b')){
                 if(virtBoard[i+k][j+k]==' '||(virtBoard[i+k][j+k]>='A'&&virtBoard[i+k][j+k]<='Z')){
                        virtBoard[i+k][j+k]='b';virtBoard[i][j]=' ';if(checkChecker(2,kx,ky)){return 1;}}
                 boardCopier();k++;
                }
                k=1;
                while((i-k)>=0&&(j+k)<8&&(virtBoard[i-k+1][j+k-1]==' '||virtBoard[i-k+1][j+k-1]=='b')){
                 if(virtBoard[i-k][j+k]==' '||(virtBoard[i-k][j+k]>='A'&&virtBoard[i-k][j+k]<='Z')){
                        virtBoard[i-k][j+k]='b';virtBoard[i][j]=' ';if(checkChecker(2,kx,ky)){return 1;}}
                 boardCopier();k++;
                }
                k=1;
                while((i-k)>=0&&(j-k)>=0&&(virtBoard[i-k+1][j-k+1]==' '||virtBoard[i-k+1][j-k+1]=='b')){
                 if(virtBoard[i-k][j-k]==' '||(virtBoard[i-k][j-k]>='A'&&virtBoard[i-k][j-k]<='Z')){
                        virtBoard[i-k][j-k]='b';virtBoard[i][j]=' ';if(checkChecker(2,kx,ky)){return 1;}}
                 boardCopier();k++;
                }
                k=1;
                 while((i+k)<8&&(j-k)>=0&&(virtBoard[i+k-1][j-k+1]==' '||virtBoard[i+k-1][j-k+1]=='b')){
                 if(virtBoard[i+k][j-k]==' '||(virtBoard[i+k][j-k]>='A'&&virtBoard[i+k][j-k]<='Z')){
                        virtBoard[i+k][j-k]='b';virtBoard[i][j]=' ';if(checkChecker(2,kx,ky)){return 1;}}
                 boardCopier();k++;
                }
                break;
    case 'n':boardCopier;
            if((i+1>=0&&i+1<8&&j+2>=0&&j+2<8)&&(virtBoard[i+1][j+2]==' '||(virtBoard[i+1][j+2]>='A'&&virtBoard[i+1][j+2]<='Z'))){
                virtBoard[i][j]=' ';virtBoard[i+1][j+2]='n';if(checkChecker(2,kx,ky)){return 1;}}
            boardCopier;
            if((i+1>=0&&i+1<8&&j-2>=0&&j-2<8)&&(virtBoard[i+1][j-2]==' '||(virtBoard[i+1][j-2]>='A'&&virtBoard[i+1][j-2]<='Z'))){
                virtBoard[i][j]=' ';virtBoard[i+1][j-2]='n';if(checkChecker(2,kx,ky)){return 1;}}
            boardCopier;
            if((i-1>=0&&i-1<8&&j+2>=0&&j+2<8)&&(virtBoard[i-1][j+2]==' '||(virtBoard[i-1][j+2]>='A'&&virtBoard[i-1][j+2]<='Z'))){
                virtBoard[i][j]=' ';virtBoard[i-1][j+2]='n';if(checkChecker(2,kx,ky)){return 1;}}
            boardCopier;
            if((i-1>=0&&i-1<8&&j-2>=0&&j-2<8)&&(virtBoard[i-1][j-2]==' '||(virtBoard[i-1][j-2]>='A'&&virtBoard[i-1][j-2]<='Z'))){
                virtBoard[i][j]=' ';virtBoard[i-1][j-2]='n';if(checkChecker(2,kx,ky)){return 1;}}
            boardCopier;
            if((i+2>=0&&i+2<8&&j+1>=0&&j+1<8)&&(virtBoard[i+2][j+1]==' '||(virtBoard[i+2][j+1]>='A'&&virtBoard[i+2][j+1]<='Z'))){
                virtBoard[i][j]=' ';virtBoard[i+2][j+1]='n';if(checkChecker(2,kx,ky)){return 1;}}
            boardCopier;
            if((i-2>=0&&i-2<8&&j+1>=0&&j+1<8)&&(virtBoard[i-2][j+1]==' '||(virtBoard[i-2][j+1]>='A'&&virtBoard[i-2][j+1]<='Z'))){
                virtBoard[i][j]=' ';virtBoard[i-2][j+1]='n';if(checkChecker(2,kx,ky)){return 1;}}
            boardCopier;
            if((i+2>=0&&i+2<8&&j-1>=0&&j-1<8)&&(virtBoard[i+2][j-1]==' '||(virtBoard[i+2][j-1]>='A'&&virtBoard[i+2][j-1]<='Z'))){
                virtBoard[i][j]=' ';virtBoard[i+2][j-1]='n';if(checkChecker(2,kx,ky)){return 1;}}
            boardCopier;
            if((i-2>=0&&i-2<8&&j+1>=0&&j+1<8)&&(virtBoard[i-2][j+1]==' '||(virtBoard[i-2][j+1]>='A'&&virtBoard[i-2][j+1]<='Z'))){
                virtBoard[i][j]=' ';virtBoard[i-2][j+1]='n';if(checkChecker(2,kx,ky)){return 1;}}
                ;break;
    case'r':boardCopier;
            k=1;
            while(i+k>=0&&i+k<8&&(virtBoard[i+k][j]==' '||(virtBoard[i+k][j]>='A'&&virtBoard[i+k][j]<='Z'))&&
            (virtBoard[i+k-1][j]==' '||virtBoard[i+k-1][j]=='r')){
                virtBoard[i][j]=' ';virtBoard[i+k][j]='r';if(checkChecker(2,kx,ky)){return 1;}
                k++;}
           boardCopier;
            k=1;
            while(i-k>=0&&i+k<8&&(virtBoard[i-k][j]==' '||(virtBoard[i-k][j]>='A'&&virtBoard[i-k][j]<='Z'))&&
            (virtBoard[i-k+1][j]==' '||virtBoard[i-k+1][j]=='r')){
                virtBoard[i][j]=' ';virtBoard[i-k][j]='r';if(checkChecker(2,kx,ky)){return 1;}
                k++;}
            boardCopier;
            k=1;
            while(j+k>=0&&j+k<8&&(virtBoard[i][j+k]==' '||(virtBoard[i][j+k]>='A'&&virtBoard[i][j+k]<='Z'))&&
            (virtBoard[i][j+k-1]==' '||virtBoard[i][j+k-1]=='r')){
                virtBoard[i][j]=' ';virtBoard[i][j+k]='r';if(checkChecker(2,kx,ky)){return 1;}
                k++;}
              boardCopier;
            k=1;
            while(j-k>=0&&j-k<8&&(virtBoard[i][j-k]==' '||(virtBoard[i][j-k]>='A'&&virtBoard[i][j-k]<='Z'))&&
            (virtBoard[i][j-k+1]==' '||virtBoard[i][j-k+1]=='r')){
                virtBoard[i][j]=' ';virtBoard[i][j-k]='r';if(checkChecker(2,kx,ky)){return 1;}
                k++;};
            break;

    case 'q':boardCopier;
             k=1;
            while(i+k>=0&&i+k<8&&(virtBoard[i+k][j]==' '||(virtBoard[i+k][j]>='A'&&virtBoard[i+k][j]<='Z'))&&
            (virtBoard[i+k-1][j]==' '||virtBoard[i+k-1][j]=='q')){
                virtBoard[i][j]=' ';virtBoard[i+k][j]='q';if(checkChecker(2,kx,ky)){return 1;}
                k++;}
           boardCopier;
            k=1;
            while(i-k>=0&&i+k<8&&(virtBoard[i-k][j]==' '||(virtBoard[i-k][j]>='A'&&virtBoard[i-k][j]<='Z'))&&
            (virtBoard[i-k+1][j]==' '||virtBoard[i-k+1][j]=='q')){
                virtBoard[i][j]=' ';virtBoard[i-k][j]='q';if(checkChecker(2,kx,ky)){return 1;}
                k++;}
            boardCopier;
            k=1;
            while(j+k>=0&&j+k<8&&(virtBoard[i][j+k]==' '||(virtBoard[i][j+k]>='A'&&virtBoard[i][j+k]<='Z'))&&
            (virtBoard[i][j+k-1]==' '||virtBoard[i][j+k-1]=='q')){
                virtBoard[i][j]=' ';virtBoard[i][j+k]='q';if(checkChecker(2,kx,ky)){return 1;}
                k++;}
              boardCopier;
            k=1;
            while(j-k>=0&&j-k<8&&(virtBoard[i][j-k]==' '||(virtBoard[i][j-k]>='A'&&virtBoard[i][j-k]<='Z'))&&
            (virtBoard[i][j-k+1]==' '||virtBoard[i][j-k+1]=='q')){
                virtBoard[i][j]=' ';virtBoard[i][j-k]='q';if(checkChecker(2,kx,ky)){return 1;}
                k++;};
            k=1;boardCopier();
                while((i+k)<8&&(j+k)<8&&(virtBoard[i+k-1][j+k-1]==' '||virtBoard[i+k-1][j+k-1]=='q')){
                 if(virtBoard[i+k][j+k]==' '||(virtBoard[i+k][j+k]>='A'&&virtBoard[i+k][j+k]<='Z')){
                        virtBoard[i+k][j+k]='q';virtBoard[i][j]=' ';if(checkChecker(2,kx,ky)){return 1;}}
                 boardCopier();k++;
                }
                k=1;
                while((i-k)>=0&&(j+k)<8&&(virtBoard[i-k+1][j+k-1]==' '||virtBoard[i-k+1][j+k-1]=='q')){
                 if(virtBoard[i-k][j+k]==' '||(virtBoard[i-k][j+k]>='A'&&virtBoard[i-k][j+k]<='Z')){
                        virtBoard[i-k][j+k]='q';virtBoard[i][j]=' ';if(checkChecker(2,kx,ky)){return 1;}}
                 boardCopier();k++;
                }
                k=1;
                while((i-k)>=0&&(j-k)>=0&&(virtBoard[i-k+1][j-k+1]==' '||virtBoard[i-k+1][j-k+1]=='q')){
                 if(virtBoard[i-k][j-k]==' '||(virtBoard[i-k][j-k]>='A'&&virtBoard[i-k][j-k]<='Z')){
                        virtBoard[i-k][j-k]='q';virtBoard[i][j]=' ';if(checkChecker(2,kx,ky)){return 1;}}
                 boardCopier();k++;
                }
                k=1;
                 while((i+k)<8&&(j-k)>=0&&(virtBoard[i+k-1][j-k+1]==' '||virtBoard[i+k-1][j-k+1]=='q')){
                 if(virtBoard[i+k][j-k]==' '||(virtBoard[i+k][j-k]>='A'&&virtBoard[i+k][j-k]<='Z')){
                        virtBoard[i+k][j-k]='q';virtBoard[i][j]=' ';if(checkChecker(2,kx,ky)){return 1;}}
                 boardCopier();k++;
                }
                break;






      }//switch


    }//el for el tania
}//el for el oula


}//player 1

if(player==-1){
    ky=whiteKing[0];kx=whiteKing[1];
    boardCopier();
    //king
    ky1=ky+1;kx1=kx;
    if(ky1>=0&&ky1<8&&kx1>=0&&kx1<8){
        if(virtBoard[ky1][kx1]>='a' && virtBoard[ky1][kx1]<='z'){
            virtBoard[ky][kx]=' ';
            virtBoard[ky1][kx1]='K';
            if(checkChecker(2,kx1,ky1)){return 1;}
        }
        if(virtBoard[ky1][kx1]==' '){
            virtBoard[ky][kx]=' ';
            virtBoard[ky1][kx1]='K';
            if(checkChecker(2,kx1,ky1)){return 1;}
           }

    }
    boardCopier();
    ky1=ky-1;kx1=kx+1;
    if(ky1>=0&&ky1<8&&kx1>=0&&kx1<8){
        if(virtBoard[ky1][kx1]>='a' && virtBoard[ky1][kx1]<='z'){
            virtBoard[ky][kx]=' ';
            virtBoard[ky1][kx1]='K';
            if(checkChecker(2,kx1,ky1)){return 1;}
        }
        if(virtBoard[ky1][kx1]==' '){
            virtBoard[ky][kx]=' ';
            virtBoard[ky1][kx1]='K';
            if(checkChecker(2,kx1,ky1)){return 1;}
           }

    }
    boardCopier();
    ky1=ky+1;kx1=kx+1;
    if(ky1>=0&&ky1<8&&kx1>=0&&kx1<8){
        if(virtBoard[ky1][kx1]>='a' && virtBoard[ky1][kx1]<='z'){
            virtBoard[ky][kx]=' ';
            virtBoard[ky1][kx1]='K';
            if(checkChecker(2,kx1,ky1)){return 1;}
        }
        if(virtBoard[ky1][kx1]==' '){
            virtBoard[ky][kx]=' ';
            virtBoard[ky1][kx1]='K';
            if(checkChecker(2,kx1,ky1)){return 1;}
           }

    }
    boardCopier();
    ky1=ky-1;kx1=kx-1;
    if(ky1>=0&&ky1<8&&kx1>=0&&kx1<8){
        if(virtBoard[ky1][kx1]>='a' && virtBoard[ky1][kx1]<='z'){
            virtBoard[ky][kx]=' ';
            virtBoard[ky1][kx1]='K';
            if(checkChecker(2,kx1,ky1)){return 1;}
        }
        if(virtBoard[ky1][kx1]==' '){
            virtBoard[ky][kx]=' ';
            virtBoard[ky1][kx1]='K';
            if(checkChecker(2,kx1,ky1)){return 1;}
           }

    }

    boardCopier();
    ky1=ky;kx1=kx+1;
    if(ky1>=0&&ky1<8&&kx1>=0&&kx1<8){
        if(virtBoard[ky1][kx1]>='a' && virtBoard[ky1][kx1]<='z'){
            virtBoard[ky][kx]=' ';
            virtBoard[ky1][kx1]='K';
            if(checkChecker(2,kx1,ky1)){return 1;}
        }
        if(virtBoard[ky1][kx1]==' '){
            virtBoard[ky][kx]=' ';
            virtBoard[ky1][kx1]='K';
            if(checkChecker(2,kx1,ky1)){return 1;}
           }

    }

    boardCopier();
    ky1=ky+1;kx1=kx-1;
    if(ky1>=0&&ky1<8&&kx1>=0&&kx1<8){
        if(virtBoard[ky1][kx1]>='a' && virtBoard[ky1][kx1]<='z'){
            virtBoard[ky][kx]=' ';
            virtBoard[ky1][kx1]='K';
            if(checkChecker(2,kx1,ky1)){return 1;}
        }
        if(virtBoard[ky1][kx1]==' '){
            virtBoard[ky][kx]=' ';
            virtBoard[ky1][kx1]='K';
            if(checkChecker(2,kx1,ky1)){return 1;}
           }

    }
    boardCopier();
    ky1=ky;kx1=kx-1;
    if(ky1>=0&&ky1<8&&kx1>=0&&kx1<8){
        if(virtBoard[ky1][kx1]>='a' && virtBoard[ky1][kx1]<='z'){
            virtBoard[ky][kx]=' ';
            virtBoard[ky1][kx1]='K';
            if(checkChecker(2,kx1,ky1)){return 1;}
        }
        if(virtBoard[ky1][kx1]==' '){
            virtBoard[ky][kx]=' ';
            virtBoard[ky1][kx1]='K';
            if(checkChecker(2,kx1,ky1)){return 1;}
           }

    }
    boardCopier();
    ky1=ky-1;kx1=kx;
    if(ky1>=0&&ky1<8&&kx1>=0&&kx1<8){
        if(virtBoard[ky1][kx1]>='a' && virtBoard[ky1][kx1]<='z'){
            virtBoard[ky][kx]=' ';
            virtBoard[ky1][kx1]='K';
            if(checkChecker(2,kx1,ky1)){return 1;}
        }
        if(virtBoard[ky1][kx1]==' '){
            virtBoard[ky][kx]=' ';
            virtBoard[ky1][kx1]='K';
            if(checkChecker(2,kx1,ky1)){return 1;}
           }

    }

    for(i=0;i<8;i++){
    for(j=0;j<8;j++){boardCopier();
      switch(virtBoard[i][j]){
      case 'P':if(i-1>=0){if(virtBoard[i-1][j]==' '){
                    if(i!=6){virtBoard[i-1][j]='P';virtBoard[i][j]=' ';if(checkChecker(2,kx,ky)){return 1;}}
                    else{virtBoard[i-1][j]='P';virtBoard[i][j]=' ';if(checkChecker(2,kx,ky)){return 1;}
                     if(i-2>=0){if(virtBoard[i-2][j]==' '){virtBoard[i-2][j]='p';virtBoard[i][j]=' ';if(checkChecker(2,kx,ky)){return 1;}}}}
                }}boardCopier();
                if(virtBoard[i-1][j+1]>='a'&&virtBoard[i+1][j+1]<='z'){
                        virtBoard[i+1][j+1]='P';virtBoard[i][j]=' ';
                        if(checkChecker(2,kx,ky)){return 1;}
                }
                boardCopier();
                if(i-1>=0&&j-1>=0){if(virtBoard[i-1][j-1]>='a'&&virtBoard[i+1][j-1]<='z'){
                        virtBoard[i-1][j-1]='p';virtBoard[i][j]=' ';
                        if(checkChecker(2,kx,ky)){return 1;}
               } };break;

      case 'B':k=1;boardCopier();
                while((i+k)<8&&(j+k)<8&&(virtBoard[i+k-1][j+k-1]==' '||virtBoard[i+k-1][j+k-1]=='B')){
                 if(virtBoard[i+k][j+k]==' '||(virtBoard[i+k][j+k]>='a'&&virtBoard[i+k][j+k]<='z')){
                        virtBoard[i+k][j+k]='B';virtBoard[i][j]=' ';if(checkChecker(2,kx,ky)){return 1;}}
                 boardCopier();k++;
                }
                k=1;
                while((i-k)>=0&&(j+k)<8&&(virtBoard[i-k+1][j+k-1]==' '||virtBoard[i-k+1][j+k-1]=='B')){
                 if(virtBoard[i-k][j+k]==' '||(virtBoard[i-k][j+k]>='a'&&virtBoard[i-k][j+k]<='z')){
                        virtBoard[i-k][j+k]='B';virtBoard[i][j]=' ';if(checkChecker(2,kx,ky)){return 1;}}
                 boardCopier();k++;
                }
                k=1;
                while((i-k)>=0&&(j-k)>=0&&(virtBoard[i-k+1][j-k+1]==' '||virtBoard[i-k+1][j-k+1]=='B')){
                 if(virtBoard[i-k][j-k]==' '||(virtBoard[i-k][j-k]>='a'&&virtBoard[i-k][j-k]<='z')){
                        virtBoard[i-k][j-k]='B';virtBoard[i][j]=' ';if(checkChecker(2,kx,ky)){return 1;}}
                 boardCopier();k++;
                }
                k=1;
                 while((i+k)<8&&(j-k)>=0&&(virtBoard[i+k-1][j-k+1]==' '||virtBoard[i+k-1][j-k+1]=='B')){
                 if(virtBoard[i+k][j-k]==' '||(virtBoard[i+k][j-k]>='a'&&virtBoard[i+k][j-k]<='z')){
                        virtBoard[i+k][j-k]='B';virtBoard[i][j]=' ';if(checkChecker(2,kx,ky)){return 1;}}
                 boardCopier();k++;
                }
                break;
    case 'N':boardCopier;
            if((i+1>=0&&i+1<8&&j+2>=0&&j+2<8)&&(virtBoard[i+1][j+2]==' '||(virtBoard[i+1][j+2]>='a'&&virtBoard[i+1][j+2]<='z'))){
                virtBoard[i][j]=' ';virtBoard[i+1][j+2]='N';if(checkChecker(2,kx,ky)){return 1;}}
            boardCopier;
            if((i+1>=0&&i+1<8&&j-2>=0&&j-2<8)&&(virtBoard[i+1][j-2]==' '||(virtBoard[i+1][j-2]>='a'&&virtBoard[i+1][j-2]<='z'))){
                virtBoard[i][j]=' ';virtBoard[i+1][j-2]='N';if(checkChecker(2,kx,ky)){return 1;}}
            boardCopier;
            if((i-1>=0&&i-1<8&&j+2>=0&&j+2<8)&&(virtBoard[i-1][j+2]==' '||(virtBoard[i-1][j+2]>='a'&&virtBoard[i-1][j+2]<='z'))){
                virtBoard[i][j]=' ';virtBoard[i-1][j+2]='N';if(checkChecker(2,kx,ky)){return 1;}}
            boardCopier;
            if((i-1>=0&&i-1<8&&j-2>=0&&j-2<8)&&(virtBoard[i-1][j-2]==' '||(virtBoard[i-1][j-2]>='a'&&virtBoard[i-1][j-2]<='z'))){
                virtBoard[i][j]=' ';virtBoard[i-1][j-2]='N';if(checkChecker(2,kx,ky)){return 1;}}
            boardCopier;
            if((i+2>=0&&i+2<8&&j+1>=0&&j+1<8)&&(virtBoard[i+2][j+1]==' '||(virtBoard[i+2][j+1]>='a'&&virtBoard[i+2][j+1]<='z'))){
                virtBoard[i][j]=' ';virtBoard[i+2][j+1]='N';if(checkChecker(2,kx,ky)){return 1;}}
            boardCopier;
            if((i-2>=0&&i-2<8&&j+1>=0&&j+1<8)&&(virtBoard[i-2][j+1]==' '||(virtBoard[i-2][j+1]>='a'&&virtBoard[i-2][j+1]<='z'))){
                virtBoard[i][j]=' ';virtBoard[i-2][j+1]='N';if(checkChecker(2,kx,ky)){return 1;}}
            boardCopier;
            if((i+2>=0&&i+2<8&&j-1>=0&&j-1<8)&&(virtBoard[i+2][j-1]==' '||(virtBoard[i+2][j-1]>='a'&&virtBoard[i+2][j-1]<='z'))){
                virtBoard[i][j]=' ';virtBoard[i+2][j-1]='N';if(checkChecker(2,kx,ky)){return 1;}}
            boardCopier;
            if((i-2>=0&&i-2<8&&j+1>=0&&j+1<8)&&(virtBoard[i-2][j+1]==' '||(virtBoard[i-2][j+1]>='a'&&virtBoard[i-2][j+1]<='z'))){
                virtBoard[i][j]=' ';virtBoard[i-2][j+1]='N';if(checkChecker(2,kx,ky)){return 1;}}
                ;break;
    case'R':boardCopier;
            k=1;
            while((i+k>=0&&i+k<8)&&(virtBoard[i+k][j]==' '||(virtBoard[i+k][j]>='a'&&virtBoard[i+k][j]<='z'))&&
            (virtBoard[i+k-1][j]==' '||virtBoard[i+k-1][j]=='R')){
                virtBoard[i][j]=' ';virtBoard[i+k][j]='R';if(checkChecker(2,kx,ky)){return 1;}
                k++;}
           boardCopier;
            k=1;
            while(i-k>=0&&i+k<8&&(virtBoard[i-k][j]==' '||(virtBoard[i-k][j]>='a'&&virtBoard[i-k][j]<='z'))&&
            (virtBoard[i-k+1][j]==' '||virtBoard[i-k+1][j]=='R')){
                virtBoard[i][j]=' ';virtBoard[i-k][j]='R';if(checkChecker(2,kx,ky)){return 1;}
                k++;}
            boardCopier;
            k=1;
            while(j+k>=0&&j+k<8&&(virtBoard[i][j+k]==' '||(virtBoard[i][j+k]>='a'&&virtBoard[i][j+k]<='z'))&&
            (virtBoard[i][j+k-1]==' '||virtBoard[i][j+k-1]=='R')){
                virtBoard[i][j]=' ';virtBoard[i][j+k]='R';if(checkChecker(2,kx,ky)){return 1;}
                k++;}
              boardCopier;
            k=1;
            while(j-k>=0&&j-k<8&&(virtBoard[i][j-k]==' '||(virtBoard[i][j-k]>='a'&&virtBoard[i][j-k]<='z'))&&
            (virtBoard[i][j-k+1]==' '||virtBoard[i][j-k+1]=='R')){
                virtBoard[i][j]=' ';virtBoard[i][j-k]='R';if(checkChecker(2,kx,ky)){return 1;}
                k++;};
            break;

    case 'Q':boardCopier;
             k=1;
            while(i+k>=0&&i+k<8&&(virtBoard[i+k][j]==' '||(virtBoard[i+k][j]>='a'&&virtBoard[i+k][j]<='z'))&&
            (virtBoard[i+k-1][j]==' '||virtBoard[i+k-1][j]=='Q')){
                virtBoard[i][j]=' ';virtBoard[i+k][j]='Q';if(checkChecker(2,kx,ky)){return 1;}
                k++;}
           boardCopier;
            k=1;
            while(i-k>=0&&i+k<8&&(virtBoard[i-k][j]==' '||(virtBoard[i-k][j]>='a'&&virtBoard[i-k][j]<='z'))&&
            (virtBoard[i-k+1][j]==' '||virtBoard[i-k+1][j]=='Q')){
                virtBoard[i][j]=' ';virtBoard[i-k][j]='Q';if(checkChecker(2,kx,ky)){return 1;}
                k++;}
            boardCopier;
            k=1;
            while(j+k>=0&&j+k<8&&(virtBoard[i][j+k]==' '||(virtBoard[i][j+k]>='a'&&virtBoard[i][j+k]<='z'))&&
            (virtBoard[i][j+k-1]==' '||virtBoard[i][j+k-1]=='Q')){
                virtBoard[i][j]=' ';virtBoard[i][j+k]='Q';if(checkChecker(2,kx,ky)){return 1;}
                k++;}
              boardCopier;
            k=1;
            while(j-k>=0&&j-k<8&&(virtBoard[i][j-k]==' '||(virtBoard[i][j-k]>='a'&&virtBoard[i][j-k]<='z'))&&
            (virtBoard[i][j-k+1]==' '||virtBoard[i][j-k+1]=='Q')){
                virtBoard[i][j]=' ';virtBoard[i][j-k]='Q';if(checkChecker(2,kx,ky)){return 1;}
                k++;};
            k=1;boardCopier();
                while((i+k)<8&&(j+k)<8&&(virtBoard[i+k-1][j+k-1]==' '||virtBoard[i+k-1][j+k-1]=='Q')){
                 if(virtBoard[i+k][j+k]==' '||(virtBoard[i+k][j+k]>='a'&&virtBoard[i+k][j+k]<='z')){
                        virtBoard[i+k][j+k]='Q';virtBoard[i][j]=' ';if(checkChecker(2,kx,ky)){return 1;}}
                 boardCopier();k++;
                }
                k=1;
                while((i-k)>=0&&(j+k)<8&&(virtBoard[i-k+1][j+k-1]==' '||virtBoard[i-k+1][j+k-1]=='Q')){
                 if(virtBoard[i-k][j+k]==' '||(virtBoard[i-k][j+k]>='a'&&virtBoard[i-k][j+k]<='z')){
                        virtBoard[i-k][j+k]='Q';virtBoard[i][j]=' ';if(checkChecker(2,kx,ky)){return 1;}}
                 boardCopier();k++;
                }
                k=1;
                while((i-k)>=0&&(j-k)>=0&&(virtBoard[i-k+1][j-k+1]==' '||virtBoard[i-k+1][j-k+1]=='Q')){
                 if(virtBoard[i-k][j-k]==' '||(virtBoard[i-k][j-k]>='a'&&virtBoard[i-k][j-k]<='z')){
                        virtBoard[i-k][j-k]='Q';virtBoard[i][j]=' ';if(checkChecker(2,kx,ky)){return 1;}}
                 boardCopier();k++;
                }
                k=1;
                 while((i+k)<8&&(j-k)>=0&&(virtBoard[i+k-1][j-k+1]==' '||virtBoard[i+k-1][j-k+1]=='Q')){
                 if(virtBoard[i+k][j-k]==' '||(virtBoard[i+k][j-k]>='a'&&virtBoard[i+k][j-k]<='z')){
                        virtBoard[i+k][j-k]='Q';virtBoard[i][j]=' ';if(checkChecker(2,kx,ky)){return 1;}}
                 boardCopier();k++;
                }
                break;






      }//switch


    }//el for el tania
}//el for el oula

}//player -1

return 0;

}

void swap(){
if (cas!=0){
if (cas==1){board[0][2]='k';board[0][4]=' ';board[0][0]=' ';board[0][3]='r';}
if (cas==3){board[7][2]='K';board[7][4]=' ';board[7][0]=' ';board[7][3]='R';}
if (cas==2){board[0][6]='k';board[0][4]=' ';board[0][7]=' ';board[0][5]='r';}
if (cas==4){board[7][6]='K';board[7][4]=' ';board[7][7]=' ';board[7][5]='R';}
cas=0;return;}
if(board[y_2][x_2]==' '){
        board[y_2][x_2]=board[y_1][x_1];
        board[y_1][x_1]=' ';}
else if(board[y_2][x_2]>='A'&&board[y_2][x_2]<='Z'){
        deadWhite[nWhite]=board[y_2][x_2];
        nWhite++;
        board[y_2][x_2]=board[y_1][x_1];
        board[y_1][x_1]=' ';}
else {  deadBlack[nBlack]=board[y_2][x_2];
        nBlack++;
        board[y_2][x_2]=board[y_1][x_1];
        board[y_1][x_1]=' ';}
}

int typeDetector(){
switch (board[y_1][x_1]){
case 'p':;
case 'P':return pawn();break;
case 'r':;
case 'R':return rook();break;
case 'B':;
case 'b':return bishop();break;
case 'q':;
case 'Q':return queen();break;
case 'N':;
case 'n':return knight();break;
case 'k':;
case 'K':return king();break;

}
}

int flowHandler(){//returns 0 in case of checkmate, 1 in regular cases , 2 in case of stale mate;
if(counter>0){
        if(player==1){
            if (!checkChecker(1,blackKing[1],blackKing[0])&&staleChecker())
                {printf("Check\n\t\t\t\a");return 1;}
            else if(!checkChecker(1,blackKing[1],blackKing[0])&&!staleChecker())
                {printf("\n\t\t\t\tYou Lost");return 0;}
            else if(checkChecker(1,blackKing[1],blackKing[0])&&!staleChecker()){printf("\n\t\t\t\tDraw");return 2;}
            else{return 1;}


        }
         if(player==-1){
            if (!checkChecker(1,whiteKing[1],whiteKing[0])&&staleChecker())
                {printf("Check\n\t\t\t\a");return 1;}
            else if(!checkChecker(1,whiteKing[1],whiteKing[0])&&!staleChecker())
                {printf("\n\t\t\t\tYou Lost");return 0;}
             else if(checkChecker(1,whiteKing[1],whiteKing[0])&&!staleChecker()){printf("\n\t\t\t\tDraw");return 2;}
            else{return 1;}


        }
}
else return 1;
}

void inputTaker(){//returns 1 if the input is correct and 0 if the input is not correct
int s=1;
while(s){
char move[256];
fgets(move,255,stdin);
if(move[0]=='u'&& counter>0){
if(!validate_move(move)){s=1;printf("\t\t\tInvalid Input\n\t\t\t");}
counter--;
stepUndoer(counter);
player=-player;
boardPrinter();
int f=flowHandler();
s=0;
undoNum++;
}

else if(move[0]=='u'&& counter<=0){
if(!validate_move(move)){s=1;printf("\t\t\tInvalid Input\n\t\t\t");}
printf("\t\t\tInvalid Input Cannot Undo Further \n\t\t\t");}

else if(move[0]=='r'&&undoNum>0){
if(!validate_move(move)){s=1;printf("\t\t\tInvalid Input\n\t\t\t");}
counter++;
stepUndoer(counter);
player=-player;
boardPrinter();
undoFlag=0;
s=0;
undoNum--;
}
else if(move[0]=='r'&&undoNum<=0){if(!validate_move(move)){s=1;printf("\t\t\tInvalid Input\n\t\t\t");}
printf("\t\t\tInvalid Input cannot redo a step that was not done\n\t\t\t");

}
else if(move[0]=='s'){if(!validate_move(move)){s=1;printf("\t\t\tInvalid Input\n\t\t\t");}else{
gameSaver();printf("\t\t\tSaved Successfully\n\t\t\t");s=0;
}}
else if(move[0]=='l'){if(!validate_move(move)){s=1;printf("\t\t\tInvalid Input\n\t\t\t");}else{
gameRestorer();s=0;
}}

else if(!validate_move(move)||!typeDetector()){s=1;printf("\t\t\tInvalid Input\n\t\t\t");}
else{
swap();
player=-player;
boardPrinter();
counter++;
stepAdder();


s=0;

}
}
}
