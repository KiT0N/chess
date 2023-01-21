#include<iostream>
#include<windows.h>
#include<conio.h>
using namespace std;
enum pieceName {BLANK = 0, PAWN = 1, KNIGHT = 2, BISHOP = 3, ROOK = 4, QUEEN = 5, KING = 7};
void gotoxy(int x, int y);
void set_data_highlight (int xx, int yy, int pp, bool uh);
void check_and_unhighlight();
bool end_game_or_not ();
void tell_about_check(int,int);
struct dataHighlight {
	int x_coordinate;
	int y_coordinate;
	int kept_piece;
	bool unhighlight_it;
};
//Plansza
class CChessBoard {
      public:
             bool change;

             CChessBoard(){
                  change=0;
             }

             void greenStep(){
                  HANDLE hConsole;
                  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                  SetConsoleTextAttribute(hConsole, 2);
                  for (int i=0; i<5; i++) {
                      cout<<"\xB0";
                  }
             }

             void grayStep(){
                  HANDLE hConsole;
                  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                  SetConsoleTextAttribute(hConsole, 8);
                  for (int i=0; i<5; i++) {
                      cout<<"\xDB";
                  }
             }

             void printRowGreen() {
                  for (int i=0; i<4; i++) {
                      greenStep();
                      grayStep();
                  }
             }

             void printRowGray() {
                  for (int i=0; i<4; i++) {
                      grayStep();
                      greenStep();
                  }
             }

             void printBoard () {
                  change=0;
                  cout<<"\t\t";
                  for (int i=0; i<8; i++) {
                      if(change==0) {
                           printRowGreen(); cout<<"\n"; cout<<"\t\t";
                           printRowGreen(); cout<<"\n"; cout<<"\t\t";
                           printRowGreen(); cout<<"\n"; cout<<"\t\t";
                           change=1;
                      }
                      else {
                           printRowGray(); cout<<"\n"; cout<<"\t\t";
                           printRowGray(); cout<<"\n"; cout<<"\t\t";
                           printRowGray(); cout<<"\n"; cout<<"\t\t";
                           change=0;
                      }
                  }
             }

             void PrintX_Label(){
                  HANDLE hConsole;
                  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                  SetConsoleTextAttribute(hConsole, 12);
                  int cnt = 1;
                  for(int i=18;i<58;i+=5){
                      gotoxy(i,24);
                      cout<<cnt;
                      cnt++;
                  }
             }

             void PrintY_Label(){
                  HANDLE hConsole;
                  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                  SetConsoleTextAttribute(hConsole, 12);
                  int cnt = 1;
                  for(int i=22;i>=1;i-=3){
                      gotoxy(15,i);
                      cout<<cnt;
                      cnt++;
                  }
             }

             void MoveTo(int numx,int numy){
                  HANDLE hConsole;
                  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                  SetConsoleTextAttribute(hConsole, 2);
                  int X = (numx * 5)+16-3;
                  int Y = 24-(numy * 3)+1;
                  gotoxy(X,Y);
             }

             void Move(char chx,char chy){
                  HANDLE hConsole;
                  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                  SetConsoleTextAttribute(hConsole, 12);
                  int numx = chx - '0'; int numy = chy - '0';
                  int X = (numx * 5)+16-3;
                  int Y = 24-(numy * 3)+1;
                  gotoxy(X,Y);
                  cout<<"\xDB";
             }

             void MoveInt(int numx,int numy, int color){
                  HANDLE hConsole;
                  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                  SetConsoleTextAttribute(hConsole, color);
                  int X = (numx * 5)+16-3;
                  int Y = 24-(numy * 3)+1;
                  gotoxy(X,Y);
                  cout<<"\xDB";
             }
};

class CPiece {
      public:

             bool is_empty;
             bool is_highlight;
             int which_piece;
             bool kill_him;
             int square_x, square_y;

             CPiece () {
                  square_x = 0;
                  square_y = 0;
                  is_empty = 1;
                  is_highlight = 0;
                  which_piece = BLANK;
                  kill_him = 0;
             }

             void setSquare (int sx, int sy, bool isEmp, bool isHigh, int which, bool kill) {
                  square_x = sx;
                  square_y = sy;
                  is_empty = isEmp;
                  is_highlight = isHigh;
                  which_piece = which;
                  kill_him = kill;
             }

             bool selectPiece () {
                  if (is_empty == 0) {
                      return 1;
                  }
                  else return 0;
             }

             bool selectNewPosition () {
                  if (is_highlight == 1) {
                      return 1;
                  }
                  else return 0;
             }

             void printBlank (int cx, int cy) {
                  if ( cx%2==0 && cy%2==0 ) {
                       HANDLE hConsole;
                       hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                       SetConsoleTextAttribute(hConsole, 8);
                       int X = (cx * 5)+16-3;
                       int Y = 24-(cy * 3)+1;
                       gotoxy(X,Y);
                       cout<<"\xDB\xDB";
                  }
                  else if ( cx%2!=0 && cy%2!=0 ) {
                       HANDLE hConsole;
                       hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                       SetConsoleTextAttribute(hConsole, 8);
                       int X = (cx * 5)+16-3;
                       int Y = 24-(cy * 3)+1;
                       gotoxy(X,Y);
                       cout<<"\xDB\xDB";
                  }
                  else if ( cx%2!=0 && cy%2==0 ) {
                       HANDLE hConsole;
                       hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                       SetConsoleTextAttribute(hConsole, 2);
                       int X = (cx * 5)+16-3;
                       int Y = 24-(cy * 3)+1;
                       gotoxy(X,Y);
                       cout<<"\xB0\xB0";
                  }
                  else if ( cx%2==0 && cy%2!=0 ) {
                       HANDLE hConsole;
                       hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                       SetConsoleTextAttribute(hConsole, 2);
                       int X = (cx * 5)+16-3;
                       int Y = 24-(cy * 3)+1;
                       gotoxy(X,Y);
                       cout<<"\xB0\xB0";
                  }
             }

             void printPiece (int cx, int cy, int color, int pieceNum) {
                  HANDLE hConsole;
                  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                  SetConsoleTextAttribute(hConsole, color);
                  int X = (cx * 5)+16-3;
                  int Y = 24-(cy * 3)+1;
                  gotoxy(X,Y);
                  if (pieceNum == PAWN ) {
                      cout<<"\xDB";
                  }
                  else if (pieceNum == ROOK ) {
                      cout<<"[]";
                  }
                  else if (pieceNum == KNIGHT ) {
                      cout<<"\x15";
                  }
                  else if (pieceNum == BISHOP ) {
                      cout<<"\x0F";
                  }
                  else if (pieceNum == QUEEN ) {
                      cout<<"\x03";
                  }
                  else if (pieceNum == KING ) {
                      cout<<"\x05";
                  }
             }

			 void pinkHighlightStep(int cx, int cy, int pieceNum);
			 void highlightPiece (int cx, int cy, int thisPiece);
			 void unhighlightStep(int cx, int cy);
};

CPiece gameSquares[9][9];

struct dataHighlight data[9][9];
//Ustawianie figur
class CGamePlay {
      public:

             CChessBoard board;

             void settingGameBoard () {
                  board.printBoard();
                  board.PrintX_Label();
                  board.PrintY_Label();

                  //Pionki dla pierwszego gracza
                  for (int i=1; i<9; i++) {
                      gameSquares[i][2].printPiece(i,2,10,PAWN);
                      gameSquares[i][2].setSquare(i,2,0,0,PAWN,0);
                  }
                  //Wieża dla pierwszego gracza
                  gameSquares[1][1].printPiece(1,1,10,ROOK);
                  gameSquares[1][1].setSquare(1,1,0,0,ROOK,0);
                  gameSquares[8][1].printPiece(8,1,10,ROOK);
                  gameSquares[8][1].setSquare(8,1,0,0,ROOK,0);
                  //Koń dla pierwszego gracza
                  gameSquares[2][1].printPiece(2,1,10,KNIGHT);
                  gameSquares[2][1].setSquare(2,1,0,0,KNIGHT,0);
                  gameSquares[7][1].printPiece(7,1,10,KNIGHT);
                  gameSquares[7][1].setSquare(7,1,0,0,KNIGHT,0);
                  //Goniec dla drugiego gracza
                  gameSquares[3][1].printPiece(3,1,10,BISHOP);
                  gameSquares[3][1].setSquare(3,1,0,0,BISHOP,0);
                  gameSquares[6][1].printPiece(6,1,10,BISHOP);
                  gameSquares[6][1].setSquare(6,1,0,0,BISHOP,0);
                  //Król i królowa dla pierwszego gracza
                  gameSquares[5][1].printPiece(5,1,10,KING);
                  gameSquares[5][1].setSquare(5,1,0,0,KING,0);
                  gameSquares[4][1].printPiece(4,1,10,QUEEN);
                  gameSquares[4][1].setSquare(4,1,0,0,QUEEN,0);
                  //Pionki drugiego gracza
                  //Pionki dla drugiego gracza
                  for (int i=1; i<9; i++) {
                      gameSquares[i][7].printPiece(i,7,15,PAWN);
                      gameSquares[i][7].setSquare(i,7,0,0,PAWN,1);
                  }
                  //Wieża dla drugiego gracza
                  gameSquares[1][8].printPiece(1,8,15,ROOK);
                  gameSquares[1][8].setSquare(1,8,0,0,ROOK,1);
                  gameSquares[8][8].printPiece(8,8,15,ROOK);
                  gameSquares[8][8].setSquare(8,8,0,0,ROOK,1);
                  //Koń dla drugiego gracza
                  gameSquares[2][8].printPiece(2,8,15,KNIGHT);
                  gameSquares[2][8].setSquare(2,8,0,0,KNIGHT,1);
                  gameSquares[7][8].printPiece(7,8,15,KNIGHT);
                  gameSquares[7][8].setSquare(7,8,0,0,KNIGHT,1);
                  //Goniec dla drugiego gracza
                  gameSquares[3][8].printPiece(3,8,15,BISHOP);
                  gameSquares[3][8].setSquare(3,8,0,0,BISHOP,1);
                  gameSquares[6][8].printPiece(6,8,15,BISHOP);
                  gameSquares[6][8].setSquare(6,8,0,0,BISHOP,1);
                  //Król i królowa dla drugiego gracza
                  gameSquares[4][8].printPiece(4,8,15,KING);
                  gameSquares[4][8].setSquare(4,8,0,0,KING,1);
                  gameSquares[5][8].printPiece(5,8,15,QUEEN);
                  gameSquares[5][8].setSquare(5,8,0,0,QUEEN,1);
             }

             void removePiece (int cx, int cy) {
                  gameSquares[cx][cy].setSquare(cx,cy,1,0,0,0);
                  gameSquares[cx][cy].printBlank(cx,cy);
             }
};
//Główna funkcja
int main () {
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CGamePlay game1;
    game1.settingGameBoard();
    SetConsoleTextAttribute(hConsole, 7);
    char chx; char chy;
    int coord_x, coord_y, X, Y;
	int pieceColor;
	bool whose_turn = 0;
	gotoxy(0,10);
	cout<<"Gracz 1!";
    while(true){
SELECT_PIECE:
		   gotoxy(0,26);
           SetConsoleTextAttribute(hConsole, 7);
           cout<<"Wybierz pozycje (w formacie XY,np 62): ";
           gotoxy(42,26);
           chx = getche(); chy = getche();

           coord_x = chx - '0'; coord_y = chy - '0';
		   if (gameSquares[coord_x][coord_y].kill_him != whose_turn ) { goto WRONG_PIECE; }
		   else {
				if ( gameSquares[coord_x][coord_y].selectPiece() ) {
				    gameSquares[coord_x][coord_y].highlightPiece(coord_x,coord_y,gameSquares[coord_x][coord_y].which_piece);
NEW_MOVE:
					if (gameSquares[coord_x][coord_y].kill_him == 1) { pieceColor = 15; }
					else { pieceColor = 10; }
					gotoxy(0,25);
				    SetConsoleTextAttribute(hConsole, 14);
				    cout<<"Gdzie przesunac? (Nowa pozycja):  ";
				    gotoxy(33,25);

					chx = getche(); chy = getche();
				    X = chx - '0';
				    Y = chy - '0';
					if (X==0 && Y==0) {
						check_and_unhighlight();
						gameSquares[coord_x][coord_y].printPiece(coord_x,coord_y,pieceColor,gameSquares[coord_x][coord_y].which_piece);
						whose_turn = gameSquares[coord_x][coord_y].kill_him;
						goto SELECT_PIECE;
					}
				    if (gameSquares[X][Y].is_highlight==1) {
						check_and_unhighlight();
						game1.removePiece(X,Y);
						if (gameSquares[coord_x][coord_y].which_piece == PAWN && gameSquares[coord_x][coord_y].kill_him == 0 && Y==8) {
							if (X==1 || X==8 ) { gameSquares[coord_x][coord_y].which_piece = ROOK; }
							else if (X==2 || X==7) { gameSquares[coord_x][coord_y].which_piece = KNIGHT; }
							else if (X==3 || X==6) { gameSquares[coord_x][coord_y].which_piece = BISHOP; }
							else if (X==4 || X==5) { gameSquares[coord_x][coord_y].which_piece = QUEEN; }
						}
						if (gameSquares[coord_x][coord_y].which_piece == PAWN && gameSquares[coord_x][coord_y].kill_him == 1 && Y==1) {
							if (X==1 || X==8) { gameSquares[coord_x][coord_y].which_piece = ROOK; }
							else if (X==2 || X==7) { gameSquares[coord_x][coord_y].which_piece = KNIGHT; }
							else if (X==3 || X==6) { gameSquares[coord_x][coord_y].which_piece = BISHOP; }
							else if (X==4 || X==5) { gameSquares[coord_x][coord_y].which_piece = QUEEN; }
						}
						gameSquares[coord_x][coord_y].printPiece(X,Y,pieceColor,gameSquares[coord_x][coord_y].which_piece);
						gameSquares[X][Y].setSquare(X,Y,0,0,gameSquares[coord_x][coord_y].which_piece,gameSquares[coord_x][coord_y].kill_him);
						game1.removePiece(coord_x,coord_y);
						data[X][Y].unhighlight_it = 0;
						gotoxy(5,15);
						SetConsoleTextAttribute(hConsole, 0);
						cout<<"      ";
						tell_about_check(X,Y);
				    }
					else {
						gotoxy(0,27);
						SetConsoleTextAttribute(hConsole, 12);
						cout<<"Invalid Move!";
						goto NEW_MOVE;
					}
					if (whose_turn == 0) {
						whose_turn = 1;
						gotoxy(0,10);
						cout<<"Gracz 1!";
					}
					else {
						whose_turn = 0;
						gotoxy(0,10);
						cout<<"Gracz 2!";
					}
					gotoxy(0,27);
					SetConsoleTextAttribute(hConsole, 0);
					cout<<"                       ";
				}
				else {
WRONG_PIECE:
					gotoxy(0,27);
					SetConsoleTextAttribute(hConsole, 12);
					cout<<"Wrong Piece Selected!";
				}
		   }
		   if ( end_game_or_not() ) { break; }
		   if (whose_turn == 0) {
				   SetConsoleTextAttribute(hConsole, 10);
				   gotoxy(0,10);
				   cout<<"Gracz 1!";
			}
			else {
				   SetConsoleTextAttribute(hConsole, 15);
				   gotoxy(0,10);
				   cout<<"Gracz 2!";
			}
    }
    gotoxy(0,25);
	cout<<"GKoniec gry!";
    system("Pause");
}

void gotoxy(int x, int y)
{
     HANDLE hConsoleOutput;
     COORD dwCursorPosition;
     cout.flush();
     dwCursorPosition.X = x;
     dwCursorPosition.Y = y;
     hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
     SetConsoleCursorPosition(hConsoleOutput,dwCursorPosition);
}

void set_data_highlight (int xx, int yy, int pp, bool uh) {
	data[xx][yy].x_coordinate = xx;
	data[xx][yy].y_coordinate = yy;
	data[xx][yy].kept_piece = pp;
	data[xx][yy].unhighlight_it = uh;
}
//Sprawdzanie i wyłączenie podświetlenia
void check_and_unhighlight() {
	for (int i=1; i<9; i++) {
		for (int j=1; j<9; j++) {
			if (data[i][j].unhighlight_it == 1) {
				gameSquares[i][j].unhighlightStep(i,j);
				data[i][j].unhighlight_it = 0;
			}
		}
	}
}
//Sprawdzic czy gra jest skonczona
bool end_game_or_not () {
	int num=0;
	for (int i=1; i<9; i++) {
		for (int j=1; j<9; j++) {
			if (gameSquares[i][j].which_piece == KING) {
				num++;
			}
		}
	}
	if (num == 2) {
		return 0;
	}
	else return 1;
}

void CPiece::highlightPiece (int cx, int cy, int thisPiece) {
	//Pionek movemant
	if (thisPiece == PAWN) {
		if (gameSquares[cx][cy].kill_him == 0) {
			if (cy == 2) {                  //Jeśli to pierwszy ruch pionka
				printPiece(cx,cy,14,PAWN);
			    for (int i=cy, j=0; j<2; i++, j++) {
					if (gameSquares[cx][i+1].is_empty==0 && gameSquares[cx][i+1].kill_him==0) { break; }
					else if (gameSquares[cx][i+1].is_empty==0 && gameSquares[cx][i+1].kill_him==1) { break; }
					else {
						pinkHighlightStep(cx,i,PAWN);
						gameSquares[cx][i+1].setSquare(cx,i,1,1,BLANK,0);
						set_data_highlight(cx,i+1,BLANK,1);
					}
				}
				if (gameSquares[cx+1][cy+1].is_empty==0 && gameSquares[cx+1][cy+1].kill_him==1) {
					pinkHighlightStep(cx+1,cy,gameSquares[cx+1][cy+1].which_piece);
					gameSquares[cx+1][cy+1].setSquare(cx+1,cy+1,0,1,gameSquares[cx+1][cy+1].which_piece,1);
					set_data_highlight(cx+1,cy+1,gameSquares[cx+1][cy+1].which_piece,1);
					gameSquares[cx+1][cy+1].printPiece(cx+1,cy+1,11,gameSquares[cx+1][cy+1].which_piece);
					//Powiedz o szachu(cx+1,cy+1);
				}
				if (gameSquares[cx-1][cy+1].is_empty==0 && gameSquares[cx-1][cy+1].kill_him==1) {
					pinkHighlightStep(cx-1,cy,gameSquares[cx-1][cy+1].which_piece);
					gameSquares[cx-1][cy+1].setSquare(cx-1,cy+1,0,1,gameSquares[cx-1][cy+1].which_piece,1);
					set_data_highlight(cx-1,cy+1,gameSquares[cx-1][cy+1].which_piece,1);
					gameSquares[cx-1][cy+1].printPiece(cx-1,cy+1,11,gameSquares[cx-1][cy+1].which_piece);
					//Powiedz o szachu(cx+1,cy+1);
				}
			}
			else {				//Nie pierwszy ruch
				printPiece(cx,cy,14,PAWN);
				if (gameSquares[cx][cy+1].is_empty==0 && gameSquares[cx][cy+1].kill_him==0) { }
				else if (gameSquares[cx][cy+1].is_empty==0 && gameSquares[cx][cy+1].kill_him==1) { }
				else {
					pinkHighlightStep(cx,cy,BLANK);
					gameSquares[cx][cy+1].setSquare(cx,cy+1,1,1,BLANK,0);
					set_data_highlight(cx,cy+1,BLANK,1);
				}
				if (gameSquares[cx+1][cy+1].is_empty==0 && gameSquares[cx+1][cy+1].kill_him==1) {
					pinkHighlightStep(cx+1,cy,gameSquares[cx+1][cy+1].which_piece);
					gameSquares[cx+1][cy+1].setSquare(cx+1,cy+1,0,1,gameSquares[cx+1][cy+1].which_piece,1);
					set_data_highlight(cx+1,cy+1,gameSquares[cx+1][cy+1].which_piece,1);
					gameSquares[cx+1][cy+1].printPiece(cx+1,cy+1,11,gameSquares[cx+1][cy+1].which_piece);
				}
				if (gameSquares[cx-1][cy+1].is_empty==0 && gameSquares[cx-1][cy+1].kill_him==1) {
					pinkHighlightStep(cx-1,cy,gameSquares[cx-1][cy+1].which_piece);
					gameSquares[cx-1][cy+1].setSquare(cx-1,cy+1,0,1,gameSquares[cx-1][cy+1].which_piece,1);
					set_data_highlight(cx-1,cy+1,gameSquares[cx-1][cy+1].which_piece,1);
					gameSquares[cx-1][cy+1].printPiece(cx-1,cy+1,11,gameSquares[cx-1][cy+1].which_piece);
				}
			}
		}

		else {	//Dla drugiego gracza
			if (cy == 7) {                  //Jeśli jest to pierwszy jego rych
				printPiece(cx,cy,14,PAWN);
			    for (int i=cy-1, j=0; j<2; i--, j++) {
					if (gameSquares[cx][i].is_empty==0 && gameSquares[cx][i].kill_him==0) { break; }
					else if (gameSquares[cx][i].is_empty==0 && gameSquares[cx][i].kill_him==1) { break; }
					else {
						pinkHighlightStep(cx,i-1,PAWN);
						gameSquares[cx][i].setSquare(cx,i,1,1,BLANK,0);
						set_data_highlight(cx,i,BLANK,1);
					}
				}
				if (gameSquares[cx+1][cy-1].is_empty==0 && gameSquares[cx+1][cy-1].kill_him==0 && cx!=8) {
					pinkHighlightStep(cx+1,cy-2,gameSquares[cx+1][cy-1].which_piece);
					gameSquares[cx+1][cy-1].setSquare(cx+1,cy-1,0,1,gameSquares[cx+1][cy-1].which_piece,0);
					set_data_highlight(cx+1,cy-1,gameSquares[cx+1][cy-1].which_piece,1);
					gameSquares[cx+1][cy-1].printPiece(cx+1,cy-1,11,gameSquares[cx+1][cy-1].which_piece);
				}
				if (gameSquares[cx-1][cy-1].is_empty==0 && gameSquares[cx-1][cy-1].kill_him==0 && cx!=1) {
					pinkHighlightStep(cx-1,cy-2,gameSquares[cx-1][cy-1].which_piece);
					gameSquares[cx-1][cy-1].setSquare(cx-1,cy-1,0,1,gameSquares[cx-1][cy-1].which_piece,0);
					set_data_highlight(cx-1,cy-1,gameSquares[cx-1][cy-1].which_piece,1);
					gameSquares[cx-1][cy-1].printPiece(cx-1,cy-1,11,gameSquares[cx-1][cy-1].which_piece);
				}
			}
			else {
				printPiece(cx,cy,14,PAWN);
				if (gameSquares[cx][cy-1].is_empty==0 && gameSquares[cx][cy-1].kill_him==1) { }
				if (gameSquares[cx][cy-1].is_empty==0 && gameSquares[cx][cy-1].kill_him==0) { }
				else {
					pinkHighlightStep(cx,cy-2,PAWN);
					gameSquares[cx][cy-1].setSquare(cx,cy-1,1,1,BLANK,0);
					set_data_highlight(cx,cy-1,BLANK,1);
				}
				if (gameSquares[cx+1][cy-1].is_empty==0 && gameSquares[cx+1][cy-1].kill_him==0 && cx!=8) {
					pinkHighlightStep(cx+1,cy-2,gameSquares[cx+1][cy-1].which_piece);
					gameSquares[cx+1][cy-1].setSquare(cx+1,cy-1,0,1,gameSquares[cx+1][cy-1].which_piece,gameSquares[cx+1][cy-1].kill_him);
					set_data_highlight(cx+1,cy-1,gameSquares[cx+1][cy-1].which_piece,1);
					gameSquares[cx+1][cy-1].printPiece(cx+1,cy-1,11,gameSquares[cx+1][cy-1].which_piece);
				}
				if (gameSquares[cx-1][cy-1].is_empty==0 && gameSquares[cx-1][cy-1].kill_him==0 && cx!=1) {
					pinkHighlightStep(cx-1,cy-2,gameSquares[cx-1][cy-1].which_piece);
					gameSquares[cx-1][cy-1].setSquare(cx-1,cy-1,0,1,gameSquares[cx-1][cy-1].which_piece,gameSquares[cx+1][cy-1].kill_him);
					set_data_highlight(cx-1,cy-1,gameSquares[cx-1][cy-1].which_piece,1);
					gameSquares[cx-1][cy-1].printPiece(cx-1,cy-1,11,gameSquares[cx-1][cy-1].which_piece);
				}
			}
		}
	}
	//Koń movemant
    else if (thisPiece == KNIGHT) {
		if (gameSquares[cx][cy].kill_him == 0) {
		    printPiece(cx,cy,14,KNIGHT);
			int temp_x; int temp_y;
			//Pierwszy ruch (X-1,Y+2)
			temp_x = cx - 1;
			temp_y = cy + 1;
			if (temp_x < 1 || temp_x > 8 || temp_y < 0 || temp_y >= 8) { }
			else {
				if (gameSquares[temp_x][temp_y+1].is_empty==0 && gameSquares[temp_x][temp_y+1].kill_him==0) { }
				else if (gameSquares[temp_x][temp_y+1].is_empty==0 && gameSquares[temp_x][temp_y+1].kill_him==1) {
					pinkHighlightStep(temp_x,temp_y,gameSquares[temp_x][temp_y+1].which_piece);
					gameSquares[temp_x][temp_y+1].setSquare(temp_x,temp_y+1,0,1,gameSquares[temp_x][temp_y+1].which_piece,1);
					set_data_highlight(temp_x,temp_y+1,gameSquares[temp_x][temp_y+1].which_piece,1);
					gameSquares[temp_x][temp_y+1].printPiece(temp_x,temp_y+1,11,gameSquares[temp_x][temp_y+1].which_piece);
				}
				else  {
					pinkHighlightStep(temp_x,temp_y,BLANK);
					gameSquares[temp_x][temp_y+1].setSquare(temp_x,temp_y+1,1,1,BLANK,0);
					set_data_highlight(temp_x,temp_y+1,BLANK,1);
				}
			}
			//Drugi ruch(X-1,Y-2)
			temp_x = cx - 1;
			temp_y = cy - 3;
			if (temp_x < 1 || temp_x > 8 || temp_y < 0 || temp_y >= 8) { }
			else {
				if (gameSquares[temp_x][temp_y+1].is_empty==0 && gameSquares[temp_x][temp_y+1].kill_him==0 ) { }
				else if (gameSquares[temp_x][temp_y+1].is_empty==0 && gameSquares[temp_x][temp_y+1].kill_him==1) {
					pinkHighlightStep(temp_x,temp_y,gameSquares[temp_x][temp_y+1].which_piece);
					gameSquares[temp_x][temp_y+1].setSquare(temp_x,temp_y+1,0,1,gameSquares[temp_x][temp_y+1].which_piece,1);
					set_data_highlight(temp_x,temp_y+1,gameSquares[temp_x][temp_y+1].which_piece,1);
					gameSquares[temp_x][temp_y+1].printPiece(temp_x,temp_y+1,11,gameSquares[temp_x][temp_y+1].which_piece);
				}
				else  {
					pinkHighlightStep(temp_x,temp_y,BLANK);
					gameSquares[temp_x][temp_y+1].setSquare(temp_x,temp_y+1,1,1,BLANK,0);
					set_data_highlight(temp_x,temp_y+1,BLANK,1);
				}
			}
			//Trzeci ruch (X+1,Y+2)
			temp_x = cx + 1;
			temp_y = cy + 1;
			if (temp_x < 1 || temp_x > 8 || temp_y < 0 || temp_y >= 8) { }
			else {
				if (gameSquares[temp_x][temp_y+1].is_empty==0 && gameSquares[temp_x][temp_y+1].kill_him==0) { }
				else if (gameSquares[temp_x][temp_y+1].is_empty==0 && gameSquares[temp_x][temp_y+1].kill_him==1) {
					pinkHighlightStep(temp_x,temp_y,gameSquares[temp_x][temp_y+1].which_piece);
					gameSquares[temp_x][temp_y+1].setSquare(temp_x,temp_y+1,0,1,gameSquares[temp_x][temp_y+1].which_piece,1);
					set_data_highlight(temp_x,temp_y+1,gameSquares[temp_x][temp_y+1].which_piece,1);
					gameSquares[temp_x][temp_y+1].printPiece(temp_x,temp_y+1,11,gameSquares[temp_x][temp_y+1].which_piece);
				}
				else  {
					pinkHighlightStep(temp_x,temp_y,BLANK);
					gameSquares[temp_x][temp_y+1].setSquare(temp_x,temp_y+1,1,1,BLANK,0);
					set_data_highlight(temp_x,temp_y+1,BLANK,1);
				}
			}
			//Czwarty ruch (X+1,Y-2)
			temp_x = cx + 1;
			temp_y = cy - 3;
			if (temp_x < 1 || temp_x > 8 || temp_y < 0 || temp_y >= 8) { }
			else {
				if (gameSquares[temp_x][temp_y+1].is_empty==0 && gameSquares[temp_x][temp_y+1].kill_him==0) { }
				else if (gameSquares[temp_x][temp_y+1].is_empty==0 && gameSquares[temp_x][temp_y+1].kill_him==1) {
					pinkHighlightStep(temp_x,temp_y,gameSquares[temp_x][temp_y+1].which_piece);
					gameSquares[temp_x][temp_y+1].setSquare(temp_x,temp_y+1,0,1,gameSquares[temp_x][temp_y+1].which_piece,1);
					set_data_highlight(temp_x,temp_y+1,gameSquares[temp_x][temp_y+1].which_piece,1);
					gameSquares[temp_x][temp_y+1].printPiece(temp_x,temp_y+1,11,gameSquares[temp_x][temp_y+1].which_piece);
				}
				else  {
					pinkHighlightStep(temp_x,temp_y,BLANK);
					gameSquares[temp_x][temp_y+1].setSquare(temp_x,temp_y+1,1,1,BLANK,0);
					set_data_highlight(temp_x,temp_y+1,BLANK,1);
				}
			}
			//Piąty ruch (X-2,Y-1)
			temp_x = cx - 2;
			temp_y = cy - 2;
			if (temp_x < 1 || temp_x > 8 || temp_y < 0 || temp_y >= 8) { }
			else {
				if (gameSquares[temp_x][temp_y+1].is_empty==0 && gameSquares[temp_x][temp_y+1].kill_him==0) { }
				else if (gameSquares[temp_x][temp_y+1].is_empty==0 && gameSquares[temp_x][temp_y+1].kill_him==1) {
					pinkHighlightStep(temp_x,temp_y,gameSquares[temp_x][temp_y+1].which_piece);
					gameSquares[temp_x][temp_y+1].setSquare(temp_x,temp_y+1,0,1,gameSquares[temp_x][temp_y+1].which_piece,1);
					set_data_highlight(temp_x,temp_y+1,gameSquares[temp_x][temp_y+1].which_piece,1);
					gameSquares[temp_x][temp_y+1].printPiece(temp_x,temp_y+1,11,gameSquares[temp_x][temp_y+1].which_piece);
				}
				else  {
					pinkHighlightStep(temp_x,temp_y,BLANK);
					gameSquares[temp_x][temp_y+1].setSquare(temp_x,temp_y+1,1,1,BLANK,0);
					set_data_highlight(temp_x,temp_y+1,BLANK,1);
				}
			}
			//Szósty ruch (X-2,Y+1)
			temp_x = cx - 2;
			temp_y = cy + 0;
			if (temp_x < 1 || temp_x > 8 || temp_y < 0 || temp_y >= 8) { }
			else {
				if (gameSquares[temp_x][temp_y+1].is_empty==0 && gameSquares[temp_x][temp_y+1].kill_him==0) { }
				else if (gameSquares[temp_x][temp_y+1].is_empty==0 && gameSquares[temp_x][temp_y+1].kill_him==1) {
					pinkHighlightStep(temp_x,temp_y,gameSquares[temp_x][temp_y+1].which_piece);
					gameSquares[temp_x][temp_y+1].setSquare(temp_x,temp_y+1,0,1,gameSquares[temp_x][temp_y+1].which_piece,1);
					set_data_highlight(temp_x,temp_y+1,gameSquares[temp_x][temp_y+1].which_piece,1);
					gameSquares[temp_x][temp_y+1].printPiece(temp_x,temp_y+1,11,gameSquares[temp_x][temp_y+1].which_piece);
				}
				else  {
					pinkHighlightStep(temp_x,temp_y,BLANK);
					gameSquares[temp_x][temp_y+1].setSquare(temp_x,temp_y+1,1,1,BLANK,0);
					set_data_highlight(temp_x,temp_y+1,BLANK,1);
				}
			}
			//Śiódmy ruch (X+2,Y-1)
			temp_x = cx + 2;
			temp_y = cy - 2;
			if (temp_x < 1 || temp_x > 8 || temp_y < 0 || temp_y >= 8) { }
			else {
				if (gameSquares[temp_x][temp_y+1].is_empty==0 && gameSquares[temp_x][temp_y+1].kill_him==0) { }
				else if (gameSquares[temp_x][temp_y+1].is_empty==0 && gameSquares[temp_x][temp_y+1].kill_him==1) {
					pinkHighlightStep(temp_x,temp_y,gameSquares[temp_x][temp_y+1].which_piece);
					gameSquares[temp_x][temp_y+1].setSquare(temp_x,temp_y+1,0,1,gameSquares[temp_x][temp_y+1].which_piece,1);
					set_data_highlight(temp_x,temp_y+1,gameSquares[temp_x][temp_y+1].which_piece,1);
					gameSquares[temp_x][temp_y+1].printPiece(temp_x,temp_y+1,11,gameSquares[temp_x][temp_y+1].which_piece);
				}
				else  {
					pinkHighlightStep(temp_x,temp_y,BLANK);
					gameSquares[temp_x][temp_y+1].setSquare(temp_x,temp_y+1,1,1,BLANK,0);
					set_data_highlight(temp_x,temp_y+1,BLANK,1);
				}
			}
			//Ósmy ruch (X+2,Y+1)
			temp_x = cx + 2;
			temp_y = cy + 0;
			if (temp_x < 1 || temp_x > 8 || temp_y < 0 || temp_y >= 8) { }
			else {
				if (gameSquares[temp_x][temp_y+1].is_empty==0 && gameSquares[temp_x][temp_y+1].kill_him==0) { }
				else if (gameSquares[temp_x][temp_y+1].is_empty==0 && gameSquares[temp_x][temp_y+1].kill_him==1) {
					pinkHighlightStep(temp_x,temp_y,gameSquares[temp_x][temp_y+1].which_piece);
					gameSquares[temp_x][temp_y+1].setSquare(temp_x,temp_y+1,0,1,gameSquares[temp_x][temp_y+1].which_piece,1);
					set_data_highlight(temp_x,temp_y+1,gameSquares[temp_x][temp_y+1].which_piece,1);
					gameSquares[temp_x][temp_y+1].printPiece(temp_x,temp_y+1,11,gameSquares[temp_x][temp_y+1].which_piece);
				}
				else  {
					pinkHighlightStep(temp_x,temp_y,BLANK);
					gameSquares[temp_x][temp_y+1].setSquare(temp_x,temp_y+1,1,1,BLANK,0);
					set_data_highlight(temp_x,temp_y+1,BLANK,1);
				}
			}
		}
		else  {
		    printPiece(cx,cy,14,KNIGHT);
			int temp_x; int temp_y;
			//Pierwszy ruch (X-1,Y+2)
			temp_x = cx - 1;
			temp_y = cy + 1;
			if (temp_x < 1 || temp_x > 8 || temp_y < 0 || temp_y >= 8) { }
			else {
				if (gameSquares[temp_x][temp_y+1].is_empty==0 && gameSquares[temp_x][temp_y+1].kill_him==1) { }
				else if (gameSquares[temp_x][temp_y+1].is_empty==0 && gameSquares[temp_x][temp_y+1].kill_him==0) {
					pinkHighlightStep(temp_x,temp_y,gameSquares[temp_x][temp_y+1].which_piece);
					gameSquares[temp_x][temp_y+1].setSquare(temp_x,temp_y+1,0,1,gameSquares[temp_x][temp_y+1].which_piece,gameSquares[temp_x][temp_y+1].kill_him);
					set_data_highlight(temp_x,temp_y+1,gameSquares[temp_x][temp_y+1].which_piece,1);
					gameSquares[temp_x][temp_y+1].printPiece(temp_x,temp_y+1,11,gameSquares[temp_x][temp_y+1].which_piece);
				}
				else  {
					pinkHighlightStep(temp_x,temp_y,BLANK);
					gameSquares[temp_x][temp_y+1].setSquare(temp_x,temp_y+1,1,1,BLANK,0);
					set_data_highlight(temp_x,temp_y+1,BLANK,1);
				}
			}
			//Drugi ruch (X-1,Y-2)
			temp_x = cx - 1;
			temp_y = cy - 3;
			if (temp_x < 1 || temp_x > 8 || temp_y < 0 || temp_y >= 8) { }
			else {
				if (gameSquares[temp_x][temp_y+1].is_empty==0 && gameSquares[temp_x][temp_y+1].kill_him==1 ) { }
				else if (gameSquares[temp_x][temp_y+1].is_empty==0 && gameSquares[temp_x][temp_y+1].kill_him==0) {
					pinkHighlightStep(temp_x,temp_y,gameSquares[temp_x][temp_y+1].which_piece);
					gameSquares[temp_x][temp_y+1].setSquare(temp_x,temp_y+1,0,1,gameSquares[temp_x][temp_y+1].which_piece,gameSquares[temp_x][temp_y+1].kill_him);
					set_data_highlight(temp_x,temp_y+1,gameSquares[temp_x][temp_y+1].which_piece,1);
					gameSquares[temp_x][temp_y+1].printPiece(temp_x,temp_y+1,11,gameSquares[temp_x][temp_y+1].which_piece);
				}
				else  {
					pinkHighlightStep(temp_x,temp_y,BLANK);
					gameSquares[temp_x][temp_y+1].setSquare(temp_x,temp_y+1,1,1,BLANK,0);
					set_data_highlight(temp_x,temp_y+1,BLANK,1);
				}
			}
			//Trzeci ruch(X+1,Y+2)
			temp_x = cx + 1;
			temp_y = cy + 1;
			if (temp_x < 1 || temp_x > 8 || temp_y < 0 || temp_y >= 8) { }
			else {
				if (gameSquares[temp_x][temp_y+1].is_empty==0 && gameSquares[temp_x][temp_y+1].kill_him==1) { }
				else if (gameSquares[temp_x][temp_y+1].is_empty==0 && gameSquares[temp_x][temp_y+1].kill_him==0) {
					pinkHighlightStep(temp_x,temp_y,gameSquares[temp_x][temp_y+1].which_piece);
					gameSquares[temp_x][temp_y+1].setSquare(temp_x,temp_y+1,0,1,gameSquares[temp_x][temp_y+1].which_piece,gameSquares[temp_x][temp_y+1].kill_him);
					set_data_highlight(temp_x,temp_y+1,gameSquares[temp_x][temp_y+1].which_piece,1);
					gameSquares[temp_x][temp_y+1].printPiece(temp_x,temp_y+1,11,gameSquares[temp_x][temp_y+1].which_piece);
				}
				else  {
					pinkHighlightStep(temp_x,temp_y,BLANK);
					gameSquares[temp_x][temp_y+1].setSquare(temp_x,temp_y+1,1,1,BLANK,0);
					set_data_highlight(temp_x,temp_y+1,BLANK,1);
				}
			}
			//Czwarty ruch (X+1,Y-2)
			temp_x = cx + 1;
			temp_y = cy - 3;
			if (temp_x < 1 || temp_x > 8 || temp_y < 0 || temp_y >= 8) { }
			else {
				if (gameSquares[temp_x][temp_y+1].is_empty==0 && gameSquares[temp_x][temp_y+1].kill_him==1) { }
				else if (gameSquares[temp_x][temp_y+1].is_empty==0 && gameSquares[temp_x][temp_y+1].kill_him==0) {
					pinkHighlightStep(temp_x,temp_y,gameSquares[temp_x][temp_y+1].which_piece);
					gameSquares[temp_x][temp_y+1].setSquare(temp_x,temp_y+1,0,1,gameSquares[temp_x][temp_y+1].which_piece,gameSquares[temp_x][temp_y+1].kill_him);
					set_data_highlight(temp_x,temp_y+1,gameSquares[temp_x][temp_y+1].which_piece,1);
					gameSquares[temp_x][temp_y+1].printPiece(temp_x,temp_y+1,11,gameSquares[temp_x][temp_y+1].which_piece);
				}
				else  {
					pinkHighlightStep(temp_x,temp_y,BLANK);
					gameSquares[temp_x][temp_y+1].setSquare(temp_x,temp_y+1,1,1,BLANK,0);
					set_data_highlight(temp_x,temp_y+1,BLANK,1);
				}
			}
			//Piąty ruch (X-2,Y-1)
			temp_x = cx - 2;
			temp_y = cy - 2;
			if (temp_x < 1 || temp_x > 8 || temp_y < 0 || temp_y >= 8) { }
			else {
				if (gameSquares[temp_x][temp_y+1].is_empty==0 && gameSquares[temp_x][temp_y+1].kill_him==1) { }
				else if (gameSquares[temp_x][temp_y+1].is_empty==0 && gameSquares[temp_x][temp_y+1].kill_him==0) {
					pinkHighlightStep(temp_x,temp_y,gameSquares[temp_x][temp_y+1].which_piece);
					gameSquares[temp_x][temp_y+1].setSquare(temp_x,temp_y+1,0,1,gameSquares[temp_x][temp_y+1].which_piece,gameSquares[temp_x][temp_y+1].kill_him);
					set_data_highlight(temp_x,temp_y+1,gameSquares[temp_x][temp_y+1].which_piece,1);
					gameSquares[temp_x][temp_y+1].printPiece(temp_x,temp_y+1,11,gameSquares[temp_x][temp_y+1].which_piece);
				}
				else  {
					pinkHighlightStep(temp_x,temp_y,BLANK);
					gameSquares[temp_x][temp_y+1].setSquare(temp_x,temp_y+1,1,1,BLANK,0);
					set_data_highlight(temp_x,temp_y+1,BLANK,1);
				}
			}
			//Szósty ruch (X-2,Y+1)
			temp_x = cx - 2;
			temp_y = cy + 0;
			if (temp_x < 1 || temp_x > 8 || temp_y < 0 || temp_y >= 8) { }
			else {
				if (gameSquares[temp_x][temp_y+1].is_empty==0 && gameSquares[temp_x][temp_y+1].kill_him==1) { }
				else if (gameSquares[temp_x][temp_y+1].is_empty==0 && gameSquares[temp_x][temp_y+1].kill_him==0) {
					pinkHighlightStep(temp_x,temp_y,gameSquares[temp_x][temp_y+1].which_piece);
					gameSquares[temp_x][temp_y+1].setSquare(temp_x,temp_y+1,0,1,gameSquares[temp_x][temp_y+1].which_piece,gameSquares[temp_x][temp_y+1].kill_him);
					set_data_highlight(temp_x,temp_y+1,gameSquares[temp_x][temp_y+1].which_piece,1);
					gameSquares[temp_x][temp_y+1].printPiece(temp_x,temp_y+1,11,gameSquares[temp_x][temp_y+1].which_piece);
				}
				else  {
					pinkHighlightStep(temp_x,temp_y,BLANK);
					gameSquares[temp_x][temp_y+1].setSquare(temp_x,temp_y+1,1,1,BLANK,0);
					set_data_highlight(temp_x,temp_y+1,BLANK,1);
				}
			}
			//Śiódmy ruch (X+2,Y-1)
			temp_x = cx + 2;
			temp_y = cy - 2;
			if (temp_x < 1 || temp_x > 8 || temp_y < 0 || temp_y >= 8) { }
			else {
				if (gameSquares[temp_x][temp_y+1].is_empty==0 && gameSquares[temp_x][temp_y+1].kill_him==1) { }
				else if (gameSquares[temp_x][temp_y+1].is_empty==0 && gameSquares[temp_x][temp_y+1].kill_him==0) {
					pinkHighlightStep(temp_x,temp_y,gameSquares[temp_x][temp_y+1].which_piece);
					gameSquares[temp_x][temp_y+1].setSquare(temp_x,temp_y+1,0,1,gameSquares[temp_x][temp_y+1].which_piece,gameSquares[temp_x][temp_y+1].kill_him);
					set_data_highlight(temp_x,temp_y+1,gameSquares[temp_x][temp_y+1].which_piece,1);
					gameSquares[temp_x][temp_y+1].printPiece(temp_x,temp_y+1,11,gameSquares[temp_x][temp_y+1].which_piece);
				}
				else  {
					pinkHighlightStep(temp_x,temp_y,BLANK);
					gameSquares[temp_x][temp_y+1].setSquare(temp_x,temp_y+1,1,1,BLANK,0);
					set_data_highlight(temp_x,temp_y+1,BLANK,1);
				}
			}
			//Ósmy ruch (X+2,Y+1)
			temp_x = cx + 2;
			temp_y = cy + 0;
			if (temp_x < 1 || temp_x > 8 || temp_y < 0 || temp_y >= 8) { }
			else {
				if (gameSquares[temp_x][temp_y+1].is_empty==0 && gameSquares[temp_x][temp_y+1].kill_him==1) { }
				else if (gameSquares[temp_x][temp_y+1].is_empty==0 && gameSquares[temp_x][temp_y+1].kill_him==0) {
					pinkHighlightStep(temp_x,temp_y,gameSquares[temp_x][temp_y+1].which_piece);
					gameSquares[temp_x][temp_y+1].setSquare(temp_x,temp_y+1,0,1,gameSquares[temp_x][temp_y+1].which_piece,gameSquares[temp_x][temp_y+1].kill_him);
					set_data_highlight(temp_x,temp_y+1,gameSquares[temp_x][temp_y+1].which_piece,1);
					gameSquares[temp_x][temp_y+1].printPiece(temp_x,temp_y+1,11,gameSquares[temp_x][temp_y+1].which_piece);
				}
				else  {
					pinkHighlightStep(temp_x,temp_y,BLANK);
					gameSquares[temp_x][temp_y+1].setSquare(temp_x,temp_y+1,1,1,BLANK,0);
					set_data_highlight(temp_x,temp_y+1,BLANK,1);
				}
			}
		}
	}
	//Goniec movemant
    else if (thisPiece == BISHOP) {
		if (gameSquares[cx][cy].kill_him == 0) {
		    printPiece(cx,cy,14,BISHOP);
			int temp_x, temp_y;

			temp_x = cx; temp_y = cy;
			if (temp_x >= 8 || temp_y >= 8) { }
			else {
				for (int i=cx+1, j=cy; ; i++, j++) {
					if (i > 8 || j >= 8) { break; }
					if (gameSquares[i][j+1].is_empty==0 && gameSquares[i][j+1].kill_him==0) { break; }
					if (gameSquares[i][j+1].is_empty==0 && gameSquares[i][j+1].kill_him==1) {
						pinkHighlightStep(i,j,gameSquares[i][j+1].which_piece);
						gameSquares[i][j+1].setSquare(i,j+1,0,1,gameSquares[i][j+1].which_piece,gameSquares[i][j+1].kill_him);
						set_data_highlight(i,j+1,gameSquares[i][j+1].which_piece,1);
						gameSquares[i][j+1].printPiece(i,j+1,11,gameSquares[i][j+1].which_piece);
						break;
					}
					pinkHighlightStep(i,j,BLANK);
					gameSquares[i][j+1].setSquare(i,j+1,1,1,BLANK,0);
					set_data_highlight(i,j+1,BLANK,1);
				}
			}

			if (temp_x < 1 || temp_y >= 8) { }
			else {
				for (int i=cx-1, j=cy;  ; i--, j++) {
					if (i < 1 || j > 7) { break; }
					if (gameSquares[i][j+1].is_empty==0 && gameSquares[i][j+1].kill_him==0) { break; }
					if (gameSquares[i][j+1].is_empty==0 && gameSquares[i][j+1].kill_him==1) {
						pinkHighlightStep(i,j,gameSquares[i][j+1].which_piece);
						gameSquares[i][j+1].setSquare(i,j+1,0,1,gameSquares[i][j+1].which_piece,gameSquares[i][j+1].kill_him);
						set_data_highlight(i,j+1,gameSquares[i][j+1].which_piece,1);
						gameSquares[i][j+1].printPiece(i,j+1,11,gameSquares[i][j+1].which_piece);
						break;
					}
					pinkHighlightStep(i,j,BLANK);
					gameSquares[i][j+1].setSquare(i,j+1,1,1,BLANK,0);
					set_data_highlight(i,j+1,BLANK,1);
				}
			}

			if (temp_x < 1 || temp_y < 1) { }
			else {
				for (int i=cx-1, j=cy-2;  ; i--, j--) {
					if (i <= 0 || j < 0) { break; }
					if (gameSquares[i][j+1].is_empty==0 && gameSquares[i][j+1].kill_him==0) { break; }
					if (gameSquares[i][j+1].is_empty==0 && gameSquares[i][j+1].kill_him==1) {
						pinkHighlightStep(i,j,gameSquares[i][j+1].which_piece);
						gameSquares[i][j+1].setSquare(i,j+1,0,1,gameSquares[i][j+1].which_piece,gameSquares[i][j+1].kill_him);
						set_data_highlight(i,j+1,gameSquares[i][j+1].which_piece,1);
						gameSquares[i][j+1].printPiece(i,j+1,11,gameSquares[i][j+1].which_piece);
						break;
					}
					pinkHighlightStep(i,j,BLANK);
					gameSquares[i][j+1].setSquare(i,j+1,1,1,BLANK,0);
					set_data_highlight(i,j+1,BLANK,1);
				}
			}

			if (temp_x >= 8 || temp_y < 1) { }
			else {
				for (int i=cx+1, j=cy-2;  ; i++, j--) {
					if (i > 8 || j < 0) { break; }
					if (gameSquares[i][j+1].is_empty==0 && gameSquares[i][j+1].kill_him==0) { break; }
					if (gameSquares[i][j+1].is_empty==0 && gameSquares[i][j+1].kill_him==1) {
						pinkHighlightStep(i,j,gameSquares[i][j+1].which_piece);
						gameSquares[i][j+1].setSquare(i,j+1,0,1,gameSquares[i][j+1].which_piece,gameSquares[i][j+1].kill_him);
						set_data_highlight(i,j+1,gameSquares[i][j+1].which_piece,1);
						gameSquares[i][j+1].printPiece(i,j+1,11,gameSquares[i][j+1].which_piece);
						break;
					}
					pinkHighlightStep(i,j,BLANK);
					gameSquares[i][j+1].setSquare(i,j+1,1,1,BLANK,0);
					set_data_highlight(i,j+1,BLANK,1);
				}
			}
		}
		else  {
		    printPiece(cx,cy,14,BISHOP);
			int temp_x, temp_y;

			temp_x = cx; temp_y = cy;
			if (temp_x >= 8 || temp_y >= 8) { }
			else {
				for (int i=cx+1, j=cy; ; i++, j++) {
					if (i > 8 || j >= 8) { break; }
					if (gameSquares[i][j+1].is_empty==0 && gameSquares[i][j+1].kill_him==1) { break; }
					if (gameSquares[i][j+1].is_empty==0 && gameSquares[i][j+1].kill_him==0) {
						pinkHighlightStep(i,j,gameSquares[i][j+1].which_piece);
						gameSquares[i][j+1].setSquare(i,j+1,0,1,gameSquares[i][j+1].which_piece,gameSquares[i][j+1].kill_him);
						set_data_highlight(i,j+1,gameSquares[i][j+1].which_piece,1);
						gameSquares[i][j+1].printPiece(i,j+1,11,gameSquares[i][j+1].which_piece);
						break;
					}
					pinkHighlightStep(i,j,BLANK);
					gameSquares[i][j+1].setSquare(i,j+1,1,1,BLANK,0);
					set_data_highlight(i,j+1,BLANK,1);
				}
			}

			if (temp_x < 1 || temp_y >= 8) { }
			else {
				for (int i=cx-1, j=cy;  ; i--, j++) {
					if (i < 1 || j > 7) { break; }
					if (gameSquares[i][j+1].is_empty==0 && gameSquares[i][j+1].kill_him==1) { break; }
					if (gameSquares[i][j+1].is_empty==0 && gameSquares[i][j+1].kill_him==0) {
						pinkHighlightStep(i,j,gameSquares[i][j+1].which_piece);
						gameSquares[i][j+1].setSquare(i,j+1,0,1,gameSquares[i][j+1].which_piece,gameSquares[i][j+1].kill_him);
						set_data_highlight(i,j+1,gameSquares[i][j+1].which_piece,1);
						gameSquares[i][j+1].printPiece(i,j+1,11,gameSquares[i][j+1].which_piece);
						break;
					}
					pinkHighlightStep(i,j,BLANK);
					gameSquares[i][j+1].setSquare(i,j+1,1,1,BLANK,0);
					set_data_highlight(i,j+1,BLANK,1);
				}
			}

			if (temp_x < 1 || temp_y < 1) { }
			else {
				for (int i=cx-1, j=cy-2;  ; i--, j--) {
					if (i <= 0 || j < 0) { break; }
					if (gameSquares[i][j+1].is_empty==0 && gameSquares[i][j+1].kill_him==1) { break; }
					if (gameSquares[i][j+1].is_empty==0 && gameSquares[i][j+1].kill_him==0) {
						pinkHighlightStep(i,j,gameSquares[i][j+1].which_piece);
						gameSquares[i][j+1].setSquare(i,j+1,0,1,gameSquares[i][j+1].which_piece,gameSquares[i][j+1].kill_him);
						set_data_highlight(i,j+1,gameSquares[i][j+1].which_piece,1);
						gameSquares[i][j+1].printPiece(i,j+1,11,gameSquares[i][j+1].which_piece);
						break;
					}
					pinkHighlightStep(i,j,BLANK);
					gameSquares[i][j+1].setSquare(i,j+1,1,1,BLANK,0);
					set_data_highlight(i,j+1,BLANK,1);
				}
			}

			if (temp_x >= 8 || temp_y < 1) { }
			else {
				for (int i=cx+1, j=cy-2; ; i++, j--) {
					if (i > 8 || j < 0) { break; }
					if (gameSquares[i][j+1].is_empty==0 && gameSquares[i][j+1].kill_him==1) { break; }
					if (gameSquares[i][j+1].is_empty==0 && gameSquares[i][j+1].kill_him==0) {
						pinkHighlightStep(i,j,gameSquares[i][j+1].which_piece);
						gameSquares[i][j+1].setSquare(i,j+1,0,1,gameSquares[i][j+1].which_piece,gameSquares[i][j+1].kill_him);
						set_data_highlight(i,j+1,gameSquares[i][j+1].which_piece,1);
						gameSquares[i][j+1].printPiece(i,j+1,11,gameSquares[i][j+1].which_piece);
						break;
					}
					pinkHighlightStep(i,j,BLANK);
					gameSquares[i][j+1].setSquare(i,j+1,1,1,BLANK,0);
					set_data_highlight(i,j+1,BLANK,1);
				}
			}
		}
	}
	//Wieża movemant
    else if (thisPiece == ROOK)
	{
		if (gameSquares[cx][cy].kill_him == 0) {
			printPiece(cx,cy,14,ROOK);
			int temp_x, temp_y;

			temp_x = cx; temp_y = cy-1;
			if ( temp_x >= 8 ) { }
			else {
				for (int i=cx+1;  ; i++) {
					if (i > 8) { break; }
					if (gameSquares[i][temp_y+1].is_empty==0 && gameSquares[i][temp_y+1].kill_him==0) { break; }
					if (gameSquares[i][temp_y+1].is_empty==0 && gameSquares[i][temp_y+1].kill_him==1) {
						pinkHighlightStep(i,temp_y,gameSquares[i][temp_y+1].which_piece);
						gameSquares[i][temp_y+1].setSquare(i,temp_y+1,0,1,gameSquares[i][temp_y+1].which_piece,gameSquares[i][temp_y+1].kill_him);
						set_data_highlight(i,temp_y+1,gameSquares[i][temp_y+1].which_piece,1);
						gameSquares[i][temp_y+1].printPiece(i,temp_y+1,11,gameSquares[i][temp_y+1].which_piece);
						break;
					}
					pinkHighlightStep(i,temp_y,BLANK);
					gameSquares[i][temp_y+1].setSquare(i,temp_y+1,1,1,BLANK,0);
					set_data_highlight(i,temp_y+1,BLANK,1);
				}
			}

			temp_x = cx; temp_y = cy-1;
			if ( temp_x < 1 ) { }
			else {
				for (int i=cx-1; ; i--) {
					if (i < 1) { break; }
					if (gameSquares[i][temp_y+1].is_empty==0 && gameSquares[i][temp_y+1].kill_him==0) { break; }
					if (gameSquares[i][temp_y+1].is_empty==0 && gameSquares[i][temp_y+1].kill_him==1) {
						pinkHighlightStep(i,temp_y,gameSquares[i][temp_y+1].which_piece);
						gameSquares[i][temp_y+1].setSquare(i,temp_y+1,0,1,gameSquares[i][temp_y+1].which_piece,gameSquares[i][temp_y+1].kill_him);
						set_data_highlight(i,temp_y+1,gameSquares[i][temp_y+1].which_piece,1);
						gameSquares[i][temp_y+1].printPiece(i,temp_y+1,11,gameSquares[i][temp_y+1].which_piece);
						break;
					}
					pinkHighlightStep(i,temp_y,BLANK);
					gameSquares[i][temp_y+1].setSquare(i,temp_y+1,1,1,BLANK,0);
					set_data_highlight(i,temp_y+1,BLANK,1);
				}
			}

			temp_x = cx; temp_y = cy;
			if ( temp_y >= 8 ) { }
			else {
				for (int i=cy; ; i++) {
					if (i >= 8) { break; }
					if (gameSquares[temp_x][i+1].is_empty==0 && gameSquares[temp_x][i+1].kill_him==0) { break; }
					if (gameSquares[temp_x][i+1].is_empty==0 && gameSquares[temp_x][i+1].kill_him==1) {
						pinkHighlightStep(temp_x,i,gameSquares[temp_x][i+1].which_piece);
						gameSquares[temp_x][i+1].setSquare(temp_x,i+1,0,1,gameSquares[temp_x][i+1].which_piece,gameSquares[temp_x][i+1].kill_him);
						set_data_highlight(temp_x,i+1,gameSquares[temp_x][i+1].which_piece,1);
						gameSquares[temp_x][i+1].printPiece(temp_x,i+1,11,gameSquares[temp_x][i+1].which_piece);
						break;
					}
					pinkHighlightStep(temp_x,i,BLANK);
					gameSquares[temp_x][i+1].setSquare(temp_x,i+1,1,1,BLANK,0);
					set_data_highlight(temp_x,i+1,BLANK,1);
				}
			}

			temp_x = cx; temp_y = cy;
			if ( temp_y < 0 ) { }
			else {
				for (int i=cy-2; ; i--) {
					if (i < 0) { break; }
					if (gameSquares[temp_x][i+1].is_empty==0 && gameSquares[temp_x][i+1].kill_him==0) { break; }
					if (gameSquares[temp_x][i+1].is_empty==0 && gameSquares[temp_x][i+1].kill_him==1) {
						pinkHighlightStep(temp_x,i,gameSquares[temp_x][i+1].which_piece);
						gameSquares[temp_x][i+1].setSquare(temp_x,i+1,0,1,gameSquares[temp_x][i+1].which_piece,gameSquares[temp_x][i+1].kill_him);
						set_data_highlight(temp_x,i+1,gameSquares[temp_x][i+1].which_piece,1);
						gameSquares[temp_x][i+1].printPiece(temp_x,i+1,11,gameSquares[temp_x][i+1].which_piece);
						break;
					}
					pinkHighlightStep(temp_x,i,BLANK);
					gameSquares[temp_x][i+1].setSquare(temp_x,i+1,1,1,BLANK,0);
					set_data_highlight(temp_x,i+1,BLANK,1);
				}
			}
		}
	else  {
			printPiece(cx,cy,14,ROOK);
			int temp_x, temp_y;

			temp_x = cx; temp_y = cy-1;
			if ( temp_x >= 8 ) { }
			else {
				for (int i=cx+1;  ; i++) {
					if (i > 8) { break; }
					if (gameSquares[i][temp_y+1].is_empty==0 && gameSquares[i][temp_y+1].kill_him==1) { break; }
					if (gameSquares[i][temp_y+1].is_empty==0 && gameSquares[i][temp_y+1].kill_him==0) {
						pinkHighlightStep(i,temp_y,gameSquares[i][temp_y+1].which_piece);
						gameSquares[i][temp_y+1].setSquare(i,temp_y+1,0,1,gameSquares[i][temp_y+1].which_piece,gameSquares[i][temp_y+1].kill_him);
						set_data_highlight(i,temp_y+1,gameSquares[i][temp_y+1].which_piece,1);
						gameSquares[i][temp_y+1].printPiece(i,temp_y+1,11,gameSquares[i][temp_y+1].which_piece);
						break;
					}
					pinkHighlightStep(i,temp_y,BLANK);
					gameSquares[i][temp_y+1].setSquare(i,temp_y+1,1,1,BLANK,0);
					set_data_highlight(i,temp_y+1,BLANK,1);
				}
			}

			temp_x = cx; temp_y = cy-1;
			if ( temp_x < 1 ) { }
			else {
				for (int i=cx-1;  ; i--) {
					if (i < 1) { break; }
					if (gameSquares[i][temp_y+1].is_empty==0 && gameSquares[i][temp_y+1].kill_him==1) { break; }
					if (gameSquares[i][temp_y+1].is_empty==0 && gameSquares[i][temp_y+1].kill_him==0) {
						pinkHighlightStep(i,temp_y,gameSquares[i][temp_y+1].which_piece);
						gameSquares[i][temp_y+1].setSquare(i,temp_y+1,0,1,gameSquares[i][temp_y+1].which_piece,gameSquares[i][temp_y+1].kill_him);
						set_data_highlight(i,temp_y+1,gameSquares[i][temp_y+1].which_piece,1);
						gameSquares[i][temp_y+1].printPiece(i,temp_y+1,11,gameSquares[i][temp_y+1].which_piece);
						break;
					}
					pinkHighlightStep(i,temp_y,BLANK);
					gameSquares[i][temp_y+1].setSquare(i,temp_y+1,1,1,BLANK,0);
					set_data_highlight(i,temp_y+1,BLANK,1);
				}
			}

			temp_x = cx; temp_y = cy;
			if ( temp_y >= 8 ) { }
			else {
				for (int i=cy; ; i++) {
					if (i >= 8) { break; }
					if (gameSquares[temp_x][i+1].is_empty==0 && gameSquares[temp_x][i+1].kill_him==1) { break; }
					if (gameSquares[temp_x][i+1].is_empty==0 && gameSquares[temp_x][i+1].kill_him==0) {
						pinkHighlightStep(temp_x,i,gameSquares[temp_x][i+1].which_piece);
						gameSquares[temp_x][i+1].setSquare(temp_x,i+1,0,1,gameSquares[temp_x][i+1].which_piece,gameSquares[temp_x][i+1].kill_him);
						set_data_highlight(temp_x,i+1,gameSquares[temp_x][i+1].which_piece,1);
						gameSquares[temp_x][i+1].printPiece(temp_x,i+1,11,gameSquares[temp_x][i+1].which_piece);
						break;
					}
					pinkHighlightStep(temp_x,i,BLANK);
					gameSquares[temp_x][i+1].setSquare(temp_x,i+1,1,1,BLANK,0);
					set_data_highlight(temp_x,i+1,BLANK,1);
				}
			}

			temp_x = cx; temp_y = cy;
			if ( temp_y < 0 ) { }
			else {
				for (int i=cy-2; ; i--) {
					if (i < 0) { break; }
					if (gameSquares[temp_x][i+1].is_empty==0 && gameSquares[temp_x][i+1].kill_him==1) { break; }
					if (gameSquares[temp_x][i+1].is_empty==0 && gameSquares[temp_x][i+1].kill_him==0) {
						pinkHighlightStep(temp_x,i,gameSquares[temp_x][i+1].which_piece);
						gameSquares[temp_x][i+1].setSquare(temp_x,i+1,0,1,gameSquares[temp_x][i+1].which_piece,gameSquares[temp_x][i+1].kill_him);
						set_data_highlight(temp_x,i+1,gameSquares[temp_x][i+1].which_piece,1);
						gameSquares[temp_x][i+1].printPiece(temp_x,i+1,11,gameSquares[temp_x][i+1].which_piece);
						break;
					}
					pinkHighlightStep(temp_x,i,BLANK);
					gameSquares[temp_x][i+1].setSquare(temp_x,i+1,1,1,BLANK,0);
					set_data_highlight(temp_x,i+1,BLANK,1);
				}
			}
		}
	}

    else if (thisPiece == QUEEN) {
		if (gameSquares[cx][cy].kill_him == 0) {
			printPiece(cx,cy,14,QUEEN);
			int temp_x, temp_y;

			temp_x = cx; temp_y = cy;
			if (temp_x >= 8 || temp_y >= 8) { }
			else {
				for (int i=cx+1, j=cy; ; i++, j++) {
					if (i > 8 || j >= 8) { break; }
					if (gameSquares[i][j+1].is_empty==0 && gameSquares[i][j+1].kill_him==0) { break; }
					if (gameSquares[i][j+1].is_empty==0 && gameSquares[i][j+1].kill_him==1) {
						pinkHighlightStep(i,j,gameSquares[i][j+1].which_piece);
						gameSquares[i][j+1].setSquare(i,j+1,0,1,gameSquares[i][j+1].which_piece,gameSquares[i][j+1].kill_him);
						set_data_highlight(i,j+1,gameSquares[i][j+1].which_piece,1);
						gameSquares[i][j+1].printPiece(i,j+1,11,gameSquares[i][j+1].which_piece);
						break;
					}
					pinkHighlightStep(i,j,BLANK);
					gameSquares[i][j+1].setSquare(i,j+1,1,1,BLANK,0);
					set_data_highlight(i,j+1,BLANK,1);
				}
			}

			if (temp_x < 1 || temp_y >= 8) { }
			else {
				for (int i=cx-1, j=cy;  ; i--, j++) {
					if (i < 1 || j > 7) { break; }
					if (gameSquares[i][j+1].is_empty==0 && gameSquares[i][j+1].kill_him==0) { break; }
					if (gameSquares[i][j+1].is_empty==0 && gameSquares[i][j+1].kill_him==1) {
						pinkHighlightStep(i,j,gameSquares[i][j+1].which_piece);
						gameSquares[i][j+1].setSquare(i,j+1,0,1,gameSquares[i][j+1].which_piece,gameSquares[i][j+1].kill_him);
						set_data_highlight(i,j+1,gameSquares[i][j+1].which_piece,1);
						gameSquares[i][j+1].printPiece(i,j+1,11,gameSquares[i][j+1].which_piece);
						break;
					}
					pinkHighlightStep(i,j,BLANK);
					gameSquares[i][j+1].setSquare(i,j+1,1,1,BLANK,0);
					set_data_highlight(i,j+1,BLANK,1);
				}
			}

			if (temp_x < 1 || temp_y < 1) { }
			else {
				for (int i=cx-1, j=cy-2;; i--, j--) {
					if (i <= 0 || j < 0) { break; }
					if (gameSquares[i][j+1].is_empty==0 && gameSquares[i][j+1].kill_him==0) { break; }
					if (gameSquares[i][j+1].is_empty==0 && gameSquares[i][j+1].kill_him==1) {
						pinkHighlightStep(i,j,gameSquares[i][j+1].which_piece);
						gameSquares[i][j+1].setSquare(i,j+1,0,1,gameSquares[i][j+1].which_piece,gameSquares[i][j+1].kill_him);
						set_data_highlight(i,j+1,gameSquares[i][j+1].which_piece,1);
						gameSquares[i][j+1].printPiece(i,j+1,11,gameSquares[i][j+1].which_piece);
						break;
					}
					pinkHighlightStep(i,j,BLANK);
					gameSquares[i][j+1].setSquare(i,j+1,1,1,BLANK,0);
					set_data_highlight(i,j+1,BLANK,1);
				}
			}

			if (temp_x >= 8 || temp_y < 1) { }
			else {
				for (int i=cx+1, j=cy-2; ; i++, j--) {
					if (i > 8 || j < 0) { break; }
					if (gameSquares[i][j+1].is_empty==0 && gameSquares[i][j+1].kill_him==0) { break; }
					if (gameSquares[i][j+1].is_empty==0 && gameSquares[i][j+1].kill_him==1) {
						pinkHighlightStep(i,j,gameSquares[i][j+1].which_piece);
						gameSquares[i][j+1].setSquare(i,j+1,0,1,gameSquares[i][j+1].which_piece,gameSquares[i][j+1].kill_him);
						set_data_highlight(i,j+1,gameSquares[i][j+1].which_piece,1);
						gameSquares[i][j+1].printPiece(i,j+1,11,gameSquares[i][j+1].which_piece);
						break;
					}
					pinkHighlightStep(i,j,BLANK);
					gameSquares[i][j+1].setSquare(i,j+1,1,1,BLANK,0);
					set_data_highlight(i,j+1,BLANK,1);
				}
			}

			temp_x = cx; temp_y = cy-1;
			if ( temp_x >= 8 ) { }
			else {
				for (int i=cx+1; ; i++) {
					if (i > 8) { break; }
					if (gameSquares[i][temp_y+1].is_empty==0 && gameSquares[i][temp_y+1].kill_him==0) { break; }
					if (gameSquares[i][temp_y+1].is_empty==0 && gameSquares[i][temp_y+1].kill_him==1) {
						pinkHighlightStep(i,temp_y,gameSquares[i][temp_y+1].which_piece);
						gameSquares[i][temp_y+1].setSquare(i,temp_y+1,0,1,gameSquares[i][temp_y+1].which_piece,gameSquares[i][temp_y+1].kill_him);
						set_data_highlight(i,temp_y+1,gameSquares[i][temp_y+1].which_piece,1);
						gameSquares[i][temp_y+1].printPiece(i,temp_y+1,11,gameSquares[i][temp_y+1].which_piece);
						break;
					}
					pinkHighlightStep(i,temp_y,BLANK);
					gameSquares[i][temp_y+1].setSquare(i,temp_y+1,1,1,BLANK,0);
					set_data_highlight(i,temp_y+1,BLANK,1);
				}
			}

			temp_x = cx; temp_y = cy-1;
			if ( temp_x < 1 ) { }
			else {
				for (int i=cx-1;  ; i--) {
					if (i < 1) { break; }
					if (gameSquares[i][temp_y+1].is_empty==0 && gameSquares[i][temp_y+1].kill_him==0) { break; }
					if (gameSquares[i][temp_y+1].is_empty==0 && gameSquares[i][temp_y+1].kill_him==1) {
						pinkHighlightStep(i,temp_y,gameSquares[i][temp_y+1].which_piece);
						gameSquares[i][temp_y+1].setSquare(i,temp_y+1,0,1,gameSquares[i][temp_y+1].which_piece,gameSquares[i][temp_y+1].kill_him);
						set_data_highlight(i,temp_y+1,gameSquares[i][temp_y+1].which_piece,1);
						gameSquares[i][temp_y+1].printPiece(i,temp_y+1,11,gameSquares[i][temp_y+1].which_piece);
						break;
					}
					pinkHighlightStep(i,temp_y,BLANK);
					gameSquares[i][temp_y+1].setSquare(i,temp_y+1,1,1,BLANK,0);
					set_data_highlight(i,temp_y+1,BLANK,1);
				}
			}

			temp_x = cx; temp_y = cy;
			if ( temp_y >= 8 ) { }
			else {
				for (int i=cy; ; i++) {
					if (i >= 8) { break; }
					if (gameSquares[temp_x][i+1].is_empty==0 && gameSquares[temp_x][i+1].kill_him==0) { break; }
					if (gameSquares[temp_x][i+1].is_empty==0 && gameSquares[temp_x][i+1].kill_him==1) {
						pinkHighlightStep(temp_x,i,gameSquares[temp_x][i+1].which_piece);
						gameSquares[temp_x][i+1].setSquare(temp_x,i+1,0,1,gameSquares[temp_x][i+1].which_piece,gameSquares[temp_x][i+1].kill_him);
						set_data_highlight(temp_x,i+1,gameSquares[temp_x][i+1].which_piece,1);
						gameSquares[temp_x][i+1].printPiece(temp_x,i+1,11,gameSquares[temp_x][i+1].which_piece);
						break;
					}
					pinkHighlightStep(temp_x,i,BLANK);
					gameSquares[temp_x][i+1].setSquare(temp_x,i+1,1,1,BLANK,0);
					set_data_highlight(temp_x,i+1,BLANK,1);
				}
			}

			temp_x = cx; temp_y = cy;
			if ( temp_y < 0 ) { }
			else {
				for (int i=cy-2;  ; i--) {
					if (i < 0) { break; }
					if (gameSquares[temp_x][i+1].is_empty==0 && gameSquares[temp_x][i+1].kill_him==0) { break; }
					if (gameSquares[temp_x][i+1].is_empty==0 && gameSquares[temp_x][i+1].kill_him==1) {
						pinkHighlightStep(temp_x,i,gameSquares[temp_x][i+1].which_piece);
						gameSquares[temp_x][i+1].setSquare(temp_x,i+1,0,1,gameSquares[temp_x][i+1].which_piece,gameSquares[temp_x][i+1].kill_him);
						set_data_highlight(temp_x,i+1,gameSquares[temp_x][i+1].which_piece,1);
						gameSquares[temp_x][i+1].printPiece(temp_x,i+1,11,gameSquares[temp_x][i+1].which_piece);
						break;
					}
					pinkHighlightStep(temp_x,i,BLANK);
					gameSquares[temp_x][i+1].setSquare(temp_x,i+1,1,1,BLANK,0);
					set_data_highlight(temp_x,i+1,BLANK,1);
				}
			}
	    }
		else  {
			printPiece(cx,cy,14,QUEEN);
			int temp_x, temp_y;

			temp_x = cx; temp_y = cy;
			if (temp_x >= 8 || temp_y >= 8) { }
			else {
				for (int i=cx+1, j=cy; ; i++, j++) {
					if (i > 8 || j >= 8) { break; }
					if (gameSquares[i][j+1].is_empty==0 && gameSquares[i][j+1].kill_him==1) { break; }
					if (gameSquares[i][j+1].is_empty==0 && gameSquares[i][j+1].kill_him==0) {
						pinkHighlightStep(i,j,gameSquares[i][j+1].which_piece);
						gameSquares[i][j+1].setSquare(i,j+1,0,1,gameSquares[i][j+1].which_piece,gameSquares[i][j+1].kill_him);
						set_data_highlight(i,j+1,gameSquares[i][j+1].which_piece,1);
						gameSquares[i][j+1].printPiece(i,j+1,11,gameSquares[i][j+1].which_piece);
						break;
					}
					pinkHighlightStep(i,j,BLANK);
					gameSquares[i][j+1].setSquare(i,j+1,1,1,BLANK,0);
					set_data_highlight(i,j+1,BLANK,1);
				}
			}

			if (temp_x < 1 || temp_y >= 8) { }
			else {
				for (int i=cx-1, j=cy;  ; i--, j++) {
					if (i < 1 || j > 7) { break; }
					if (gameSquares[i][j+1].is_empty==0 && gameSquares[i][j+1].kill_him==1) { break; }
					if (gameSquares[i][j+1].is_empty==0 && gameSquares[i][j+1].kill_him==0) {
						pinkHighlightStep(i,j,gameSquares[i][j+1].which_piece);
						gameSquares[i][j+1].setSquare(i,j+1,0,1,gameSquares[i][j+1].which_piece,gameSquares[i][j+1].kill_him);
						set_data_highlight(i,j+1,gameSquares[i][j+1].which_piece,1);
						gameSquares[i][j+1].printPiece(i,j+1,11,gameSquares[i][j+1].which_piece);
						break;
					}
					pinkHighlightStep(i,j,BLANK);
					gameSquares[i][j+1].setSquare(i,j+1,1,1,BLANK,0);
					set_data_highlight(i,j+1,BLANK,1);
				}
			}

			if (temp_x < 1 || temp_y < 1) { }
			else {
				for (int i=cx-1, j=cy-2; ; i--, j--) {
					if (i <= 0 || j < 0) { break; }
					if (gameSquares[i][j+1].is_empty==0 && gameSquares[i][j+1].kill_him==1) { break; }
					if (gameSquares[i][j+1].is_empty==0 && gameSquares[i][j+1].kill_him==0) {
						pinkHighlightStep(i,j,gameSquares[i][j+1].which_piece);
						gameSquares[i][j+1].setSquare(i,j+1,0,1,gameSquares[i][j+1].which_piece,gameSquares[i][j+1].kill_him);
						set_data_highlight(i,j+1,gameSquares[i][j+1].which_piece,1);
						gameSquares[i][j+1].printPiece(i,j+1,11,gameSquares[i][j+1].which_piece);
						break;
					}
					pinkHighlightStep(i,j,BLANK);
					gameSquares[i][j+1].setSquare(i,j+1,1,1,BLANK,0);
					set_data_highlight(i,j+1,BLANK,1);
				}
			}

			if (temp_x >= 8 || temp_y < 1) { }
			else {
				for (int i=cx+1, j=cy-2; ; i++, j--) {
					if (i > 8 || j < 0) { break; }
					if (gameSquares[i][j+1].is_empty==0 && gameSquares[i][j+1].kill_him==1) { break; }
					if (gameSquares[i][j+1].is_empty==0 && gameSquares[i][j+1].kill_him==0) {
						pinkHighlightStep(i,j,gameSquares[i][j+1].which_piece);
						gameSquares[i][j+1].setSquare(i,j+1,0,1,gameSquares[i][j+1].which_piece,gameSquares[i][j+1].kill_him);
						set_data_highlight(i,j+1,gameSquares[i][j+1].which_piece,1);
						gameSquares[i][j+1].printPiece(i,j+1,11,gameSquares[i][j+1].which_piece);
						break;
					}
					pinkHighlightStep(i,j,BLANK);
					gameSquares[i][j+1].setSquare(i,j+1,1,1,BLANK,0);
					set_data_highlight(i,j+1,BLANK,1);
				}
			}

			temp_x = cx; temp_y = cy-1;
			if ( temp_x >= 8 ) { }
			else {
				for (int i=cx+1;  ; i++) {
					if (i > 8) { break; }
					if (gameSquares[i][temp_y+1].is_empty==0 && gameSquares[i][temp_y+1].kill_him==1) { break; }
					if (gameSquares[i][temp_y+1].is_empty==0 && gameSquares[i][temp_y+1].kill_him==0) {
						pinkHighlightStep(i,temp_y,gameSquares[i][temp_y+1].which_piece);
						gameSquares[i][temp_y+1].setSquare(i,temp_y+1,0,1,gameSquares[i][temp_y+1].which_piece,gameSquares[i][temp_y+1].kill_him);
						set_data_highlight(i,temp_y+1,gameSquares[i][temp_y+1].which_piece,1);
						gameSquares[i][temp_y+1].printPiece(i,temp_y+1,11,gameSquares[i][temp_y+1].which_piece);
						break;
					}
					pinkHighlightStep(i,temp_y,BLANK);
					gameSquares[i][temp_y+1].setSquare(i,temp_y+1,1,1,BLANK,0);
					set_data_highlight(i,temp_y+1,BLANK,1);
				}
			}

			temp_x = cx; temp_y = cy-1;
			if ( temp_x < 1 ) { }
			else {
				for (int i=cx-1; ; i--) {
					if (i < 1) { break; }
					if (gameSquares[i][temp_y+1].is_empty==0 && gameSquares[i][temp_y+1].kill_him==1) { break; }
					if (gameSquares[i][temp_y+1].is_empty==0 && gameSquares[i][temp_y+1].kill_him==0) {
						pinkHighlightStep(i,temp_y,gameSquares[i][temp_y+1].which_piece);
						gameSquares[i][temp_y+1].setSquare(i,temp_y+1,0,1,gameSquares[i][temp_y+1].which_piece,gameSquares[i][temp_y+1].kill_him);
						set_data_highlight(i,temp_y+1,gameSquares[i][temp_y+1].which_piece,1);
						gameSquares[i][temp_y+1].printPiece(i,temp_y+1,11,gameSquares[i][temp_y+1].which_piece);
						break;
					}
					pinkHighlightStep(i,temp_y,BLANK);
					gameSquares[i][temp_y+1].setSquare(i,temp_y+1,1,1,BLANK,0);
					set_data_highlight(i,temp_y+1,BLANK,1);
				}
			}

			temp_x = cx; temp_y = cy;
			if ( temp_y >= 8 ) { }
			else {
				for (int i=cy;  ; i++) {
					if (i >= 8) { break; }
					if (gameSquares[temp_x][i+1].is_empty==0 && gameSquares[temp_x][i+1].kill_him==1) { break; }
					if (gameSquares[temp_x][i+1].is_empty==0 && gameSquares[temp_x][i+1].kill_him==0) {
						pinkHighlightStep(temp_x,i,gameSquares[temp_x][i+1].which_piece);
						gameSquares[temp_x][i+1].setSquare(temp_x,i+1,0,1,gameSquares[temp_x][i+1].which_piece,gameSquares[temp_x][i+1].kill_him);
						set_data_highlight(temp_x,i+1,gameSquares[temp_x][i+1].which_piece,1);
						gameSquares[temp_x][i+1].printPiece(temp_x,i+1,11,gameSquares[temp_x][i+1].which_piece);
						break;
					}
					pinkHighlightStep(temp_x,i,BLANK);
					gameSquares[temp_x][i+1].setSquare(temp_x,i+1,1,1,BLANK,0);
					set_data_highlight(temp_x,i+1,BLANK,1);
				}
			}

			temp_x = cx; temp_y = cy;
			if ( temp_y < 0 ) { }
			else {
				for (int i=cy-2;  ; i--) {
					if (i < 0) { break; }
					if (gameSquares[temp_x][i+1].is_empty==0 && gameSquares[temp_x][i+1].kill_him==1) { break; }
					if (gameSquares[temp_x][i+1].is_empty==0 && gameSquares[temp_x][i+1].kill_him==0) {
						pinkHighlightStep(temp_x,i,gameSquares[temp_x][i+1].which_piece);
						gameSquares[temp_x][i+1].setSquare(temp_x,i+1,0,1,gameSquares[temp_x][i+1].which_piece,gameSquares[temp_x][i+1].kill_him);
						set_data_highlight(temp_x,i+1,gameSquares[temp_x][i+1].which_piece,1);
						gameSquares[temp_x][i+1].printPiece(temp_x,i+1,11,gameSquares[temp_x][i+1].which_piece);
						break;
					}
					pinkHighlightStep(temp_x,i,BLANK);
					gameSquares[temp_x][i+1].setSquare(temp_x,i+1,1,1,BLANK,0);
					set_data_highlight(temp_x,i+1,BLANK,1);
				}
			}
	    }
	}
	//Movemant króla
    else if (thisPiece == KING) {
		if (gameSquares[cx][cy].kill_him == 0) {
			printPiece(cx,cy,14,KING);
			int temp_x, temp_y;
			//Prawy górny
			temp_x = cx; temp_y = cy;
			if (temp_x >= 8 || temp_y >= 8) { }
			else {
				temp_x = cx+1; temp_y = cy;
				if (gameSquares[temp_x][temp_y+1].is_empty==0 && gameSquares[temp_x][temp_y+1].kill_him==0) { }
				else if (gameSquares[temp_x][temp_y+1].is_empty==0 && gameSquares[temp_x][temp_y+1].kill_him==1) {
					pinkHighlightStep(temp_x,temp_y,gameSquares[temp_x][temp_y+1].which_piece);
					gameSquares[temp_x][temp_y+1].setSquare(temp_x,temp_y+1,0,1,gameSquares[temp_x][temp_y+1].which_piece,1);
					set_data_highlight(temp_x,temp_y+1,gameSquares[temp_x][temp_y+1].which_piece,1);
					gameSquares[temp_x][temp_y+1].printPiece(temp_x,temp_y+1,11,gameSquares[temp_x][temp_y+1].which_piece);
				}
				else {
					pinkHighlightStep(temp_x,temp_y,BLANK);
					gameSquares[temp_x][temp_y+1].setSquare(temp_x,temp_y+1,1,1,BLANK,0);
					set_data_highlight(temp_x,temp_y+1,BLANK,1);
				}
			}
			//Lewy górny
			temp_x = cx; temp_y = cy;
			if (temp_x <= 1 || temp_y >= 8) { }
			else {
				temp_x = cx-1; temp_y = cy;
				if (gameSquares[temp_x][temp_y+1].is_empty==0 && gameSquares[temp_x][temp_y+1].kill_him==0) { }
				else if (gameSquares[temp_x][temp_y+1].is_empty==0 && gameSquares[temp_x][temp_y+1].kill_him==1) {
					pinkHighlightStep(temp_x,temp_y,gameSquares[temp_x][temp_y+1].which_piece);
					gameSquares[temp_x][temp_y+1].setSquare(temp_x,temp_y+1,0,1,gameSquares[temp_x][temp_y+1].which_piece,1);
					set_data_highlight(temp_x,temp_y+1,gameSquares[temp_x][temp_y+1].which_piece,1);
					gameSquares[temp_x][temp_y+1].printPiece(temp_x,temp_y+1,11,gameSquares[temp_x][temp_y+1].which_piece);
				}
				else {
					pinkHighlightStep(temp_x,temp_y,BLANK);
					gameSquares[temp_x][temp_y+1].setSquare(temp_x,temp_y+1,1,1,BLANK,0);
					set_data_highlight(temp_x,temp_y+1,BLANK,1);
				}
			}
			//Prawy dolny
			temp_x = cx; temp_y = cy;
			if (temp_x >= 8 || temp_y <= 1) { }
			else {
				temp_x = cx+1; temp_y = cy-2;
				if (gameSquares[temp_x][temp_y+1].is_empty==0 && gameSquares[temp_x][temp_y+1].kill_him==0) { }
				else if (gameSquares[temp_x][temp_y+1].is_empty==0 && gameSquares[temp_x][temp_y+1].kill_him==1) {
					pinkHighlightStep(temp_x,temp_y,gameSquares[temp_x][temp_y+1].which_piece);
					gameSquares[temp_x][temp_y+1].setSquare(temp_x,temp_y+1,0,1,gameSquares[temp_x][temp_y+1].which_piece,1);
					set_data_highlight(temp_x,temp_y+1,gameSquares[temp_x][temp_y+1].which_piece,1);
					gameSquares[temp_x][temp_y+1].printPiece(temp_x,temp_y+1,11,gameSquares[temp_x][temp_y+1].which_piece);
				}
				else {
					pinkHighlightStep(temp_x,temp_y,BLANK);
					gameSquares[temp_x][temp_y+1].setSquare(temp_x,temp_y+1,1,1,BLANK,0);
					set_data_highlight(temp_x,temp_y+1,BLANK,1);
				}
			}
			//Lewy dolny
			temp_x = cx; temp_y = cy;
			if (temp_x <= 1 || temp_y <= 1) { }
			else {
				temp_x = cx-1; temp_y = cy-2;
				if (gameSquares[temp_x][temp_y+1].is_empty==0 && gameSquares[temp_x][temp_y+1].kill_him==0) { }
				else if (gameSquares[temp_x][temp_y+1].is_empty==0 && gameSquares[temp_x][temp_y+1].kill_him==1) {
					pinkHighlightStep(temp_x,temp_y,gameSquares[temp_x][temp_y+1].which_piece);
					gameSquares[temp_x][temp_y+1].setSquare(temp_x,temp_y+1,0,1,gameSquares[temp_x][temp_y+1].which_piece,1);
					set_data_highlight(temp_x,temp_y+1,gameSquares[temp_x][temp_y+1].which_piece,1);
					gameSquares[temp_x][temp_y+1].printPiece(temp_x,temp_y+1,11,gameSquares[temp_x][temp_y+1].which_piece);
				}
				else {
					pinkHighlightStep(temp_x,temp_y,BLANK);
					gameSquares[temp_x][temp_y+1].setSquare(temp_x,temp_y+1,1,1,BLANK,0);
					set_data_highlight(temp_x,temp_y+1,BLANK,1);
				}
			}
			//Prawy
			temp_x = cx; temp_y = cy;
			if ( temp_x >= 8 ) { }
			else {
				temp_x = cx+1; temp_y = cy-1;
				if (gameSquares[temp_x][temp_y+1].is_empty==0 && gameSquares[temp_x][temp_y+1].kill_him==0) { }
				else if (gameSquares[temp_x][temp_y+1].is_empty==0 && gameSquares[temp_x][temp_y+1].kill_him==1) {
					pinkHighlightStep(temp_x,temp_y,gameSquares[temp_x][temp_y+1].which_piece);
					gameSquares[temp_x][temp_y+1].setSquare(temp_x,temp_y+1,0,1,gameSquares[temp_x][temp_y+1].which_piece,1);
					set_data_highlight(temp_x,temp_y+1,gameSquares[temp_x][temp_y+1].which_piece,1);
					gameSquares[temp_x][temp_y+1].printPiece(temp_x,temp_y+1,11,gameSquares[temp_x][temp_y+1].which_piece);
				}
				else {
					pinkHighlightStep(temp_x,temp_y,BLANK);
					gameSquares[temp_x][temp_y+1].setSquare(temp_x,temp_y+1,1,1,BLANK,0);
					set_data_highlight(temp_x,temp_y+1,BLANK,1);
				}
			}
			//Lewy
			temp_x = cx; temp_y = cy;
			if ( temp_x <= 1 ) { }
			else {
				temp_x = cx-1; temp_y = cy-1;
				if (gameSquares[temp_x][temp_y+1].is_empty==0 && gameSquares[temp_x][temp_y+1].kill_him==0) { }
				else if (gameSquares[temp_x][temp_y+1].is_empty==0 && gameSquares[temp_x][temp_y+1].kill_him==1) {
					pinkHighlightStep(temp_x,temp_y,gameSquares[temp_x][temp_y+1].which_piece);
					gameSquares[temp_x][temp_y+1].setSquare(temp_x,temp_y+1,0,1,gameSquares[temp_x][temp_y+1].which_piece,1);
					set_data_highlight(temp_x,temp_y+1,gameSquares[temp_x][temp_y+1].which_piece,1);
					gameSquares[temp_x][temp_y+1].printPiece(temp_x,temp_y+1,11,gameSquares[temp_x][temp_y+1].which_piece);
				}
				else {
					pinkHighlightStep(temp_x,temp_y,BLANK);
					gameSquares[temp_x][temp_y+1].setSquare(temp_x,temp_y+1,1,1,BLANK,0);
					set_data_highlight(temp_x,temp_y+1,BLANK,1);
				}
			}
			//Góra
			temp_x = cx; temp_y = cy;
			if ( temp_y >= 8 ) { }
			else {
				temp_x = cx; temp_y = cy;
				if (gameSquares[temp_x][temp_y+1].is_empty==0 && gameSquares[temp_x][temp_y+1].kill_him==0) { }
				else if (gameSquares[temp_x][temp_y+1].is_empty==0 && gameSquares[temp_x][temp_y+1].kill_him==1) {
					pinkHighlightStep(temp_x,temp_y,gameSquares[temp_x][temp_y+1].which_piece);
					gameSquares[temp_x][temp_y+1].setSquare(temp_x,temp_y+1,0,1,gameSquares[temp_x][temp_y+1].which_piece,1);
					set_data_highlight(temp_x,temp_y+1,gameSquares[temp_x][temp_y+1].which_piece,1);
					gameSquares[temp_x][temp_y+1].printPiece(temp_x,temp_y+1,11,gameSquares[temp_x][temp_y+1].which_piece);
				}
				else {
					pinkHighlightStep(temp_x,temp_y,BLANK);
					gameSquares[temp_x][temp_y+1].setSquare(temp_x,temp_y+1,1,1,BLANK,0);
					set_data_highlight(temp_x,temp_y+1,BLANK,1);
				}
			}
			//Dół
			temp_x = cx; temp_y = cy;
			if ( temp_y <= 1 ) { }
			else {
				temp_x = cx; temp_y = cy-2;
				if (gameSquares[temp_x][temp_y+1].is_empty==0 && gameSquares[temp_x][temp_y+1].kill_him==0) { }
				else if (gameSquares[temp_x][temp_y+1].is_empty==0 && gameSquares[temp_x][temp_y+1].kill_him==1) {
					pinkHighlightStep(temp_x,temp_y,gameSquares[temp_x][temp_y+1].which_piece);
					gameSquares[temp_x][temp_y+1].setSquare(temp_x,temp_y+1,0,1,gameSquares[temp_x][temp_y+1].which_piece,1);
					set_data_highlight(temp_x,temp_y+1,gameSquares[temp_x][temp_y+1].which_piece,1);
					gameSquares[temp_x][temp_y+1].printPiece(temp_x,temp_y+1,11,gameSquares[temp_x][temp_y+1].which_piece);
				}
				else {
					pinkHighlightStep(temp_x,temp_y,BLANK);
					gameSquares[temp_x][temp_y+1].setSquare(temp_x,temp_y+1,1,1,BLANK,0);
					set_data_highlight(temp_x,temp_y+1,BLANK,1);
				}
			}
		}
		else if (gameSquares[cx][cy].kill_him == 1) {
			printPiece(cx,cy,14,KING);
			int temp_x, temp_y;
			//Prawy górny
			temp_x = cx; temp_y = cy;
			if (temp_x >= 8 || temp_y >= 8) { }
			else {
				temp_x = cx+1; temp_y = cy;
				if (gameSquares[temp_x][temp_y+1].is_empty==0 && gameSquares[temp_x][temp_y+1].kill_him==1) { }
				else if (gameSquares[temp_x][temp_y+1].is_empty==0 && gameSquares[temp_x][temp_y+1].kill_him==0) {
					pinkHighlightStep(temp_x,temp_y,gameSquares[temp_x][temp_y+1].which_piece);
					gameSquares[temp_x][temp_y+1].setSquare(temp_x,temp_y+1,0,1,gameSquares[temp_x][temp_y+1].which_piece,gameSquares[temp_x][temp_y+1].kill_him);
					set_data_highlight(temp_x,temp_y+1,gameSquares[temp_x][temp_y+1].which_piece,1);
					gameSquares[temp_x][temp_y+1].printPiece(temp_x,temp_y+1,11,gameSquares[temp_x][temp_y+1].which_piece);
				}
				else {
					pinkHighlightStep(temp_x,temp_y,BLANK);
					gameSquares[temp_x][temp_y+1].setSquare(temp_x,temp_y+1,1,1,BLANK,0);
					set_data_highlight(temp_x,temp_y+1,BLANK,1);
				}
			}
			//Lewy górny
			temp_x = cx; temp_y = cy;
			if (temp_x <= 1 || temp_y >= 8) { }
			else {
				temp_x = cx-1; temp_y = cy;
				if (gameSquares[temp_x][temp_y+1].is_empty==0 && gameSquares[temp_x][temp_y+1].kill_him==1) { }
				else if (gameSquares[temp_x][temp_y+1].is_empty==0 && gameSquares[temp_x][temp_y+1].kill_him==0) {
					pinkHighlightStep(temp_x,temp_y,gameSquares[temp_x][temp_y+1].which_piece);
					gameSquares[temp_x][temp_y+1].setSquare(temp_x,temp_y+1,0,1,gameSquares[temp_x][temp_y+1].which_piece,gameSquares[temp_x][temp_y+1].kill_him);
					set_data_highlight(temp_x,temp_y+1,gameSquares[temp_x][temp_y+1].which_piece,1);
					gameSquares[temp_x][temp_y+1].printPiece(temp_x,temp_y+1,11,gameSquares[temp_x][temp_y+1].which_piece);
				}
				else {
					pinkHighlightStep(temp_x,temp_y,BLANK);
					gameSquares[temp_x][temp_y+1].setSquare(temp_x,temp_y+1,1,1,BLANK,0);
					set_data_highlight(temp_x,temp_y+1,BLANK,1);
				}
			}
			//Prawy dolny
			temp_x = cx; temp_y = cy;
			if (temp_x >= 8 || temp_y <= 1) { }
			else {
				temp_x = cx+1; temp_y = cy-2;
				if (gameSquares[temp_x][temp_y+1].is_empty==0 && gameSquares[temp_x][temp_y+1].kill_him==1) { }
				else if (gameSquares[temp_x][temp_y+1].is_empty==0 && gameSquares[temp_x][temp_y+1].kill_him==0) {
					pinkHighlightStep(temp_x,temp_y,gameSquares[temp_x][temp_y+1].which_piece);
					gameSquares[temp_x][temp_y+1].setSquare(temp_x,temp_y+1,0,1,gameSquares[temp_x][temp_y+1].which_piece,gameSquares[temp_x][temp_y+1].kill_him);
					set_data_highlight(temp_x,temp_y+1,gameSquares[temp_x][temp_y+1].which_piece,1);
					gameSquares[temp_x][temp_y+1].printPiece(temp_x,temp_y+1,11,gameSquares[temp_x][temp_y+1].which_piece);
				}
				else {
					pinkHighlightStep(temp_x,temp_y,BLANK);
					gameSquares[temp_x][temp_y+1].setSquare(temp_x,temp_y+1,1,1,BLANK,0);
					set_data_highlight(temp_x,temp_y+1,BLANK,1);
				}
			}
			//Lewy dolny
			temp_x = cx; temp_y = cy;
			if (temp_x <= 1 || temp_y <= 1) { }
			else {
				temp_x = cx-1; temp_y = cy-2;
				if (gameSquares[temp_x][temp_y+1].is_empty==0 && gameSquares[temp_x][temp_y+1].kill_him==1) { }
				else if (gameSquares[temp_x][temp_y+1].is_empty==0 && gameSquares[temp_x][temp_y+1].kill_him==0) {
					pinkHighlightStep(temp_x,temp_y,gameSquares[temp_x][temp_y+1].which_piece);
					gameSquares[temp_x][temp_y+1].setSquare(temp_x,temp_y+1,0,1,gameSquares[temp_x][temp_y+1].which_piece,gameSquares[temp_x][temp_y+1].kill_him);
					set_data_highlight(temp_x,temp_y+1,gameSquares[temp_x][temp_y+1].which_piece,1);
					gameSquares[temp_x][temp_y+1].printPiece(temp_x,temp_y+1,11,gameSquares[temp_x][temp_y+1].which_piece);
				}
				else {
					pinkHighlightStep(temp_x,temp_y,BLANK);
					gameSquares[temp_x][temp_y+1].setSquare(temp_x,temp_y+1,1,1,BLANK,0);
					set_data_highlight(temp_x,temp_y+1,BLANK,1);
				}
			}
			//Prawy
			temp_x = cx; temp_y = cy;
			if ( temp_x >= 8 ) { }
			else {
				temp_x = cx+1; temp_y = cy-1;
				if (gameSquares[temp_x][temp_y+1].is_empty==0 && gameSquares[temp_x][temp_y+1].kill_him==1) { }
				else if (gameSquares[temp_x][temp_y+1].is_empty==0 && gameSquares[temp_x][temp_y+1].kill_him==0) {
					pinkHighlightStep(temp_x,temp_y,gameSquares[temp_x][temp_y+1].which_piece);
					gameSquares[temp_x][temp_y+1].setSquare(temp_x,temp_y+1,0,1,gameSquares[temp_x][temp_y+1].which_piece,gameSquares[temp_x][temp_y+1].kill_him);
					set_data_highlight(temp_x,temp_y+1,gameSquares[temp_x][temp_y+1].which_piece,1);
					gameSquares[temp_x][temp_y+1].printPiece(temp_x,temp_y+1,11,gameSquares[temp_x][temp_y+1].which_piece);
				}
				else {
					pinkHighlightStep(temp_x,temp_y,BLANK);
					gameSquares[temp_x][temp_y+1].setSquare(temp_x,temp_y+1,1,1,BLANK,0);
					set_data_highlight(temp_x,temp_y+1,BLANK,1);
				}
			}
			//Lewy
			temp_x = cx; temp_y = cy;
			if ( temp_x <= 1 ) { }
			else {
				temp_x = cx-1; temp_y = cy-1;
				if (gameSquares[temp_x][temp_y+1].is_empty==0 && gameSquares[temp_x][temp_y+1].kill_him==1) { }
				else if (gameSquares[temp_x][temp_y+1].is_empty==0 && gameSquares[temp_x][temp_y+1].kill_him==0) {
					pinkHighlightStep(temp_x,temp_y,gameSquares[temp_x][temp_y+1].which_piece);
					gameSquares[temp_x][temp_y+1].setSquare(temp_x,temp_y+1,0,1,gameSquares[temp_x][temp_y+1].which_piece,gameSquares[temp_x][temp_y+1].kill_him);
					set_data_highlight(temp_x,temp_y+1,gameSquares[temp_x][temp_y+1].which_piece,1);
					gameSquares[temp_x][temp_y+1].printPiece(temp_x,temp_y+1,11,gameSquares[temp_x][temp_y+1].which_piece);
				}
				else {
					pinkHighlightStep(temp_x,temp_y,BLANK);
					gameSquares[temp_x][temp_y+1].setSquare(temp_x,temp_y+1,1,1,BLANK,0);
					set_data_highlight(temp_x,temp_y+1,BLANK,1);
				}
			}
			//Góra
			temp_x = cx; temp_y = cy;
			if ( temp_y >= 8 ) { }
			else {
				temp_x = cx; temp_y = cy;
				if (gameSquares[temp_x][temp_y+1].is_empty==0 && gameSquares[temp_x][temp_y+1].kill_him==1) { }
				else if (gameSquares[temp_x][temp_y+1].is_empty==0 && gameSquares[temp_x][temp_y+1].kill_him==0) {
					pinkHighlightStep(temp_x,temp_y,gameSquares[temp_x][temp_y+1].which_piece);
					gameSquares[temp_x][temp_y+1].setSquare(temp_x,temp_y+1,0,1,gameSquares[temp_x][temp_y+1].which_piece,gameSquares[temp_x][temp_y+1].kill_him);
					set_data_highlight(temp_x,temp_y+1,gameSquares[temp_x][temp_y+1].which_piece,1);
					gameSquares[temp_x][temp_y+1].printPiece(temp_x,temp_y+1,11,gameSquares[temp_x][temp_y+1].which_piece);
				}
				else {
					pinkHighlightStep(temp_x,temp_y,BLANK);
					gameSquares[temp_x][temp_y+1].setSquare(temp_x,temp_y+1,1,1,BLANK,0);
					set_data_highlight(temp_x,temp_y+1,BLANK,1);
				}
			}
			//Dół
			temp_x = cx; temp_y = cy;
			if ( temp_y <= 1 ) { }
			else {
				temp_x = cx; temp_y = cy-2;
				if (gameSquares[temp_x][temp_y+1].is_empty==0 && gameSquares[temp_x][temp_y+1].kill_him==1) { }
				else if (gameSquares[temp_x][temp_y+1].is_empty==0 && gameSquares[temp_x][temp_y+1].kill_him==0) {
					pinkHighlightStep(temp_x,temp_y,gameSquares[temp_x][temp_y+1].which_piece);
					gameSquares[temp_x][temp_y+1].setSquare(temp_x,temp_y+1,0,1,gameSquares[temp_x][temp_y+1].which_piece,gameSquares[temp_x][temp_y+1].kill_him);
					set_data_highlight(temp_x,temp_y+1,gameSquares[temp_x][temp_y+1].which_piece,1);
					gameSquares[temp_x][temp_y+1].printPiece(temp_x,temp_y+1,11,gameSquares[temp_x][temp_y+1].which_piece);
				}
				else {
					pinkHighlightStep(temp_x,temp_y,BLANK);
					gameSquares[temp_x][temp_y+1].setSquare(temp_x,temp_y+1,1,1,BLANK,0);
					set_data_highlight(temp_x,temp_y+1,BLANK,1);
				}
			}
		}
	}
}
//Szachowanie
void tell_about_check(int cx, int cy) {
	//Dla pionka
	if (gameSquares[cx][cy].which_piece == PAWN) {
		if (gameSquares[cx][cy].kill_him == 0) {	//Jeśli jest to pionek gracza
			if (gameSquares[cx+1][cy+1].kill_him == 1 && gameSquares[cx+1][cy+1].which_piece == KING) {
				gotoxy(5,15);
				HANDLE hConsole;
				hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, 207);
				cout<<"Check";
			}
			if (gameSquares[cx-1][cy+1].kill_him == 1 && gameSquares[cx-1][cy+1].which_piece == KING) {
				gotoxy(5,15);
				HANDLE hConsole;
				hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, 207);
				cout<<"Check";
			}
		}
		else {
			if (gameSquares[cx+1][cy-1].kill_him == 0 && gameSquares[cx+1][cy-1].which_piece == KING) {
				gotoxy(5,15);
				HANDLE hConsole;
				hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, 207);
				cout<<"Check";
			}
			if (gameSquares[cx-1][cy-1].kill_him == 0 && gameSquares[cx+1][cy-1].which_piece == KING) {
				gotoxy(5,15);
				HANDLE hConsole;
				hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, 207);
				cout<<"Check";
			}
		}
	}
	//Dla konia
	if (gameSquares[cx][cy].which_piece == KNIGHT) {
		if (gameSquares[cx][cy].kill_him == 0) {
			//(x+1,y+2)
			if (gameSquares[cx+1][cy+2].kill_him == 1 && gameSquares[cx+1][cy+2].which_piece == KING) {
				gotoxy(5,15);
				HANDLE hConsole;
				hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, 207);
				cout<<"Check";
			}
			//(x+1,y-2)
			else if (gameSquares[cx+1][cy-2].kill_him == 1 && gameSquares[cx+1][cy-2].which_piece == KING) {
				gotoxy(5,15);
				HANDLE hConsole;
				hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, 207);
				cout<<"Check";
			}
			//(x-1,y+2)
			else if (gameSquares[cx-1][cy+2].kill_him == 1 && gameSquares[cx-1][cy+2].which_piece == KING) {
				gotoxy(5,15);
				HANDLE hConsole;
				hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, 207);
				cout<<"Check";
			}
			//(x-1,y-2)
			else if (gameSquares[cx-1][cy-2].kill_him == 1 && gameSquares[cx-1][cy-2].which_piece == KING) {
				gotoxy(5,15);
				HANDLE hConsole;
				hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, 207);
				cout<<"Check";
			}
			//(x+2,y+1)
			else if (gameSquares[cx+2][cy+1].kill_him == 1 && gameSquares[cx+2][cy+1].which_piece == KING) {
				gotoxy(5,15);
				HANDLE hConsole;
				hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, 207);
				cout<<"Check";
			}
			//(x+2,y-1)
			else if (gameSquares[cx+2][cy-1].kill_him == 1 && gameSquares[cx+2][cy-1].which_piece == KING) {
				gotoxy(5,15);
				HANDLE hConsole;
				hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, 207);
				cout<<"Check";
			}
			//(x-2,y+1)
			else if (gameSquares[cx-2][cy+1].kill_him == 1 && gameSquares[cx-2][cy+1].which_piece == KING) {
				gotoxy(5,15);
				HANDLE hConsole;
				hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, 207);
				cout<<"Check";
			}
			//(x-2,y-1)
			else if (gameSquares[cx-2][cy-1].kill_him == 1 && gameSquares[cx-2][cy-1].which_piece == KING) {
				gotoxy(5,15);
				HANDLE hConsole;
				hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, 207);
				cout<<"Check";
			}
		}
		else {
			//(x+1,y+2)
			if (gameSquares[cx+1][cy+2].kill_him == 0 && gameSquares[cx+1][cy+2].which_piece == KING) {
				gotoxy(5,15);
				HANDLE hConsole;
				hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, 207);
				cout<<"Check";
			}
			//(x+1,y-2)
			else if (gameSquares[cx+1][cy-2].kill_him == 0 && gameSquares[cx+1][cy-2].which_piece == KING) {
				gotoxy(5,15);
				HANDLE hConsole;
				hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, 207);
				cout<<"Check";
			}
			//(x-1,y+2)
			else if (gameSquares[cx-1][cy+2].kill_him == 0 && gameSquares[cx-1][cy+2].which_piece == KING) {
				gotoxy(5,15);
				HANDLE hConsole;
				hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, 207);
				cout<<"Check";
			}
			//(x-1,y-2)
			else if (gameSquares[cx-1][cy-2].kill_him == 0 && gameSquares[cx-1][cy-2].which_piece == KING) {
				gotoxy(5,15);
				HANDLE hConsole;
				hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, 207);
				cout<<"Check";
			}
			//(x+2,y+1)
			else if (gameSquares[cx+2][cy+1].kill_him == 0 && gameSquares[cx+2][cy+1].which_piece == KING) {
				gotoxy(5,15);
				HANDLE hConsole;
				hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, 207);
				cout<<"Check";
			}
			//(x+2,y-1)
			else if (gameSquares[cx+2][cy-1].kill_him == 0 && gameSquares[cx+2][cy-1].which_piece == KING) {
				gotoxy(5,15);
				HANDLE hConsole;
				hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, 207);
				cout<<"Check";
			}
			//(x-2,y+1)
			else if (gameSquares[cx-2][cy+1].kill_him == 0 && gameSquares[cx-2][cy+1].which_piece == KING) {
				gotoxy(5,15);
				HANDLE hConsole;
				hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, 207);
				cout<<"Check";
			}
			//(x-2,y-1)
			else if (gameSquares[cx-2][cy-1].kill_him == 0 && gameSquares[cx-2][cy-1].which_piece == KING) {
				gotoxy(5,15);
				HANDLE hConsole;
				hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, 207);
				cout<<"Check";
			}
		}
	}
	//Dla gońca
	if (gameSquares[cx][cy].which_piece == BISHOP) {
		if (gameSquares[cx][cy].kill_him == 0) {
			int temp_x, temp_y;
			//1 Wariant (+ve x , +ve y)
			temp_x = cx; temp_y = cy;
			if (temp_x >= 8 || temp_y >= 8) { }
			else {
				for (int i=cx+1, j=cy; /*<No Condition>*/ ; i++, j++) {
					if (i > 8 || j >= 8) { break; }
					if (gameSquares[i][j+1].is_empty==0 && gameSquares[i][j+1].kill_him==0) { break; }
					if (gameSquares[i][j+1].is_empty==0 && gameSquares[i][j+1].kill_him==1) { break; }
					if (gameSquares[i][j+1].is_empty==KING && gameSquares[i][j+1].kill_him==1) {
						gotoxy(5,15);
						HANDLE hConsole;
						hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
						SetConsoleTextAttribute(hConsole, 207);
						cout<<"Check";
						break;
					}
				}
			}
			//2 Wariant (x -ve , y +ve)
			if (temp_x < 1 || temp_y >= 8) { }
			else {
				for (int i=cx-1, j=cy; /*<No Condition>*/ ; i--, j++) {
					if (i < 1 || j > 7) { break; }
					if (gameSquares[i][j+1].is_empty==0 && gameSquares[i][j+1].kill_him==0) { break; }
					if (gameSquares[i][j+1].is_empty==0 && gameSquares[i][j+1].kill_him==1) { break; }
					if (gameSquares[i][j+1].is_empty==KING && gameSquares[i][j+1].kill_him==1) {
						gotoxy(5,15);
						HANDLE hConsole;
						hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
						SetConsoleTextAttribute(hConsole, 207);
						cout<<"Check";
						break;
					}
				}
			}
			//3 Wariant (x -ve , y -ve)
			if (temp_x < 1 || temp_y < 1) { }
			else {
				for (int i=cx-1, j=cy-2; /*<No Condition>*/ ; i--, j--) {
					if (i <= 0 || j < 0) { break; }
					if (gameSquares[i][j+1].is_empty==0 && gameSquares[i][j+1].kill_him==0) { break; }
					if (gameSquares[i][j+1].is_empty==0 && gameSquares[i][j+1].kill_him==1) { break; }
					if (gameSquares[i][j+1].is_empty==KING && gameSquares[i][j+1].kill_him==1) {
						gotoxy(5,15);
						HANDLE hConsole;
						hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
						SetConsoleTextAttribute(hConsole, 207);
						cout<<"Check";
						break;
					}
				}
			}
			//4 Wariant (x +ve , y -ve)
			if (temp_x >= 8 || temp_y < 1) { }
			else {
				for (int i=cx+1, j=cy-2; /*<No Condition>*/ ; i++, j--) {
					if (i > 8 || j < 0) { break; }
					if (gameSquares[i][j+1].is_empty==0 && gameSquares[i][j+1].kill_him==0) { break; }
					if (gameSquares[i][j+1].is_empty==0 && gameSquares[i][j+1].kill_him==1) { break; }
					if (gameSquares[i][j+1].is_empty==KING && gameSquares[i][j+1].kill_him==1) {
						gotoxy(5,15);
						HANDLE hConsole;
						hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
						SetConsoleTextAttribute(hConsole, 207);
						cout<<"Check";
						break;
					}
				}
			}
		}
	}
}

//Anulowanie podświetlania_______________________
void CPiece::unhighlightStep(int cx, int cy){
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if ( cx%2==0 && cy%2==0 ) {            //Jęsli x i y są parzyste
        HANDLE hConsole;
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 8);          //Ustawianie szarego koloru
        int X = (cx * 5)+16-3;
        int Y = 24-(cy * 3)+1;
        X = X-2;
        Y = Y-1;
        gotoxy(X,Y);
        for (int i=0; i<3; i++) {
            for (int i=0; i<5; i++) {
                cout<<"\xDB";
            }
            Y++;
            gotoxy(X,Y);
        }
    }
    else if ( cx%2!=0 && cy%2!=0 ) {       //Jęsli x i y są nieparzyste
        HANDLE hConsole;
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 8);          //Ustawianie szarego koloru
        int X = (cx * 5)+16-3;
        int Y = 24-(cy * 3)+1;
        X = X-2;
        Y = Y-1;
        gotoxy(X,Y);
        for (int i=0; i<3; i++) {
            for (int i=0; i<5; i++) {
                cout<<"\xDB";
            }
            Y++;
            gotoxy(X,Y);
        }
    }
    else if ( cx%2!=0 && cy%2==0 ) {       //Jeśli x jest nie parzyste a y  parzyste
        HANDLE hConsole;
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 2);          //Ustawianie szarego koloru
        int X = (cx * 5)+16-3;
        int Y = 24-(cy * 3)+1;
        X = X-2;
        Y = Y-1;
        gotoxy(X,Y);
        for (int i=0; i<3; i++) {
            for (int i=0; i<5; i++) {
                cout<<"\xB0";
            }
            Y++;
            gotoxy(X,Y);
        }
    }
    else if ( cx%2==0 && cy%2!=0 ) {      //Jeśli x jest parzyste a y nie parzyste
        HANDLE hConsole;
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 2);          //Ustawianie szarego koloru
        int X = (cx * 5)+16-3;
        int Y = 24-(cy * 3)+1;
        X = X-2;
        Y = Y-1;
        gotoxy(X,Y);
        for (int i=0; i<3; i++) {
            for (int i=0; i<5; i++) {
                cout<<"\xB0";
            }
            Y++;
            gotoxy(X,Y);
        }
    }
	//////////////////////////////

	if (gameSquares[cx][cy].is_empty == 1) {
		gameSquares[cx][cy].setSquare(cx,cy,1,0,0,0);
	}
	else {
		if (gameSquares[cx][cy].kill_him == 1){
			gameSquares[cx][cy].setSquare(cx,cy,0,0,gameSquares[cx][cy].which_piece,gameSquares[cx][cy].kill_him);
			gameSquares[cx][cy].printPiece(cx,cy,15,gameSquares[cx][cy].which_piece);
		}
		else {
			gameSquares[cx][cy].setSquare(cx,cy,0,0,gameSquares[cx][cy].which_piece,gameSquares[cx][cy].kill_him);
			gameSquares[cx][cy].printPiece(cx,cy,10,gameSquares[cx][cy].which_piece);
		}
	}
}
//Podświetlanie możliwych ruchów
void CPiece::pinkHighlightStep(int cx, int cy, int pieceNum){
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if ( cx%2==0 && cy%2==0 ) {            //Jeśli x i y są parzyste
        HANDLE hConsole;
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 5);          //Ustawianie koloru ciemno różowy
        int X = (cx * 5)+16-3;
        int Y = 24-(cy * 3)+1;
        int tempX = X - 2;
        int tempY = Y - 4;
        gotoxy(tempX,tempY);
        for (int i=0; i<3; i++) {
            for (int i=0; i<5; i++) {
                cout<<"\xDB";
            }
            tempY++;
            gotoxy(tempX,tempY);
        }
    }
    else if ( cx%2!=0 && cy%2!=0 ) {       //Jeśli x i y są nieparzyste
        HANDLE hConsole;
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 5);          //Ustawianie koloru ciemno różowy
        int X = (cx * 5)+16-3;
        int Y = 24-(cy * 3)+1;
        int tempX = X - 2;
        int tempY = Y - 4;
        gotoxy(tempX,tempY);
        for (int i=0; i<3; i++) {
            for (int i=0; i<5; i++) {
                cout<<"\xDB";
            }
            tempY++;
            gotoxy(tempX,tempY);
        }
    }
    else if ( cx%2!=0 && cy%2==0 ) {       //Jeśli x jest nie parzyste a y parzyste
        HANDLE hConsole;
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 13);          //Ustawienie koloru jasny różowy
        int X = (cx * 5)+16-3;
        int Y = 24-(cy * 3)+1;
        int tempX = X - 2;
        int tempY = Y - 4;
        gotoxy(tempX,tempY);
        for (int i=0; i<3; i++) {
            for (int i=0; i<5; i++) {
                cout<<"\xDB";
            }
            tempY++;
            gotoxy(tempX,tempY);
        }
    }
    else if ( cx%2==0 && cy%2!=0 ) {       //Jeśli x jest parzyste a y nie parzyste
        HANDLE hConsole;
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 13);          //Ustawienie koloru jasny różowy
        int X = (cx * 5)+16-3;
        int Y = 24-(cy * 3)+1;
        int tempX = X - 2;
        int tempY = Y - 4;
        gotoxy(tempX,tempY);
        for (int i=0; i<3; i++) {
            for (int i=0; i<5; i++) {
                cout<<"\xDB";
            }
            tempY++;
            gotoxy(tempX,tempY);
        }
    }
}
