#include <string>
#include <fstream>
#include <iostream>
using namespace std;

class chess
{
public:
	chess();
	~chess();
	void setupBoard();
	void movePiece();
	void printBoard() const;
	bool isCheck(int, int);
	bool isCheckMate(int, int);
	string returnPiece(string);

private:
	string chessBoard[8][8];
	string capturedBlack[15];
	string capturedWhite[15];
	int wCaptured;
	int bCaptured;
	int turn;
	int whiteKing;
	int blackKing;
	bool moveBlackPawn(int, int, int, int);	//(fromCol, fromRow, toCol, toRow)
	bool moveWhitePawn(int, int, int, int);
	bool moveRook(int, int, int, int);	
	bool moveKnight(int, int, int, int);
	bool moveBishop(int, int, int, int);
	bool moveQueen(int, int, int, int);
	bool moveKing(int, int, int, int);
	void swapPieces(int, int, int, int);
	void capturePiece(int, int); //(toCol, toRow)
};