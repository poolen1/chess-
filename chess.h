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
	void movePiece(string);
	void printBoard() const;
	bool isCheck(int, int);
	bool isCheckMate(int, int);
	string returnPiece(string);

private:
	string chessBoard[8][8];
	string capturedBlack[16];
	string capturedWhite[16];
	int turn;
	int whiteKing;
	int blackKing;
};