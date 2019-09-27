#ifndef A&H_CHESS_H_INCLUDED
#define A&H_CHESS_H_INCLUDED

//player 1 small letters, the upper part, black
//player -1 capital letters, the lower part, white

void SetColorAndBackground(int ForgC, int BackC);
void initialScreen();
void initialPlaces();
void boardPrinter();
void saveFileCreator();
void stepAdder();
void gameSaver();
void stepUndoer(int step);
void boardCopier();
int checkChecker(int a,int x_checked,int y_checked);
int check_allMoves();
void gameRestorer();
int bishop ();
int rook ();
int knight ();
int queen ();
int pawn ();
int king();
int validate_move (char move[]);
int staleChecker();
void swap();
int typeDetector();
int flowHandler();
void inputTaker();


#endif // A&H_CHESS_H_INCLUDED

