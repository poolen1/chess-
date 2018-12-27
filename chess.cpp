#include "chess.h"
#include <cstdlib>
#include <iomanip>
#include <cctype>
#include <string>
using namespace std;

/*---------------------------------------
Constructor
PARAMETER(S): ifstream& in
POSTCONDITION(S): inits playerGrid to starting positions,
	checkMate to false
---------------------------------------*/
chess::chess()
{
	//TEST
	//cout << "Rows instantiated." << endl;

	for (int i=0; i<8; i++)
		for (int j=0; j<8; j++){
			chessBoard[i][j] = " ";
			//cout << "Row: " << i << " Col: " << j << endl;
		}

	turn = 0;
	whiteKing = 74;
	blackKing = 04;
	

	//TEST
	//cout << "Columns instantiated." << endl;
}

/*---------------------------------------
Destructor
PARAMETER(S):
POSTCONDITION(S): 
---------------------------------------*/
chess::~chess()
{}

/*---------------------------------------
FUNCTION NAME:
PARAMETER(S):
RETURN TYPE:
POSTCONDITION(S): 
---------------------------------------*/
void chess::setupBoard()
{
	//black pieces
	chessBoard[0][0] = "♖";
	chessBoard[0][1] = "♘";
	chessBoard[0][2] = "♗";
	chessBoard[0][3] = "♕";
	chessBoard[0][4] = "♔";
	chessBoard[0][5] = "♗";
	chessBoard[0][6] = "♘";
	chessBoard[0][7] = "♖";
	chessBoard[1][0] = "♙";
	chessBoard[1][1] = "♙";
	chessBoard[1][2] = "♙";
	chessBoard[1][3] = "♙";
	chessBoard[1][4] = "♙";
	chessBoard[1][5] = "♙";
	chessBoard[1][6] = "♙";
	chessBoard[1][7] = "♙";

	//white pieces
	chessBoard[7][0] = "♜";
	chessBoard[7][1] = "♞";
	chessBoard[7][2] = "♝";
	chessBoard[7][3] = "♛";
	chessBoard[7][4] = "♚";
	chessBoard[7][5] = "♝";
	chessBoard[7][6] = "♞";
	chessBoard[7][7] = "♜";
	chessBoard[6][0] = "♟";
	chessBoard[6][1] = "♟";
	chessBoard[6][2] = "♟";
	chessBoard[6][3] = "♟";
	chessBoard[6][4] = "♟";
	chessBoard[6][5] = "♟";
	chessBoard[6][6] = "♟";
	chessBoard[6][7] = "♟";
}

/*---------------------------------------
FUNCTION NAME:
PARAMETER(S):
RETURN TYPE:
POSTCONDITION(S): 
---------------------------------------*/
void chess::movePiece(string)
{
	string fromHere;
	string toThere;

	if (turn == 0)
		cout << "Player 1" << endl;
	if (turn == 1)
		cout << "Player 2" << endl;

	while (turn == 0){
		cout << "Player 1" << endl;
		cout << "Move from: ";
		cin >> fromHere;
		cout << "Move to: ";
		cin >> toThere;
	}
}

/*---------------------------------------
FUNCTION NAME:
PARAMETER(S):
RETURN TYPE:
POSTCONDITION(S): 
---------------------------------------*/
void chess::printBoard() const
{
	/*
	for (int i=0; i<8; i++){
		for (int j=0; j<8; j++){
			cout << chessBoard[i][j] << " ";
			if (j==7)
				cout << endl;
		}
	}
	*/

	cout << "    +---+---+---+---+---+---+---+---+" << endl;
	cout << "  8 |";
	for (int j=0; j<8; j++){
		cout << " " << chessBoard[0][j] << " |";
		if (j==7)
			cout << endl;
	}
	cout << "    +---+---+---+---+---+---+---+---+" << endl;
	cout << "  7 |";
	for (int j=0; j<8; j++){
		cout << " " << chessBoard[1][j] << " |";
		if (j==7)
			cout << endl;
	}
	cout << "    +---+---+---+---+---+---+---+---+" << endl;
	cout << "  6 |";
	for (int j=0; j<8; j++){
		cout << " " << chessBoard[2][j] << " |";
		if (j==7)
			cout << endl;
	}
	cout << "    +---+---+---+---+---+---+---+---+" << endl;
	cout << "  5 |";
	for (int j=0; j<8; j++){
		cout << " " << chessBoard[3][j] << " |";
		if (j==7)
			cout << endl;
	}
	cout << "    +---+---+---+---+---+---+---+---+" << endl;
	cout << "  4 |";
	for (int j=0; j<8; j++){
		cout << " " << chessBoard[4][j] << " |";
		if (j==7)
			cout << endl;
	}
	cout << "    +---+---+---+---+---+---+---+---+" << endl;
	cout << "  3 |";
	for (int j=0; j<8; j++){
		cout << " " << chessBoard[5][j] << " |";
		if (j==7)
			cout << endl;
	}
	cout << "    +---+---+---+---+---+---+---+---+" << endl;
	cout << "  2 |";
	for (int j=0; j<8; j++){
		cout << " " << chessBoard[6][j] << " |";
		if (j==7)
			cout << endl;
	}
	cout << "    +---+---+---+---+---+---+---+---+" << endl;
	cout << "  1 |";
	for (int j=0; j<8; j++){
		cout << " " << chessBoard[7][j] << " |";
		if (j==7)
			cout << endl;
	}
	cout << "    +---+---+---+---+---+---+---+---+" << endl;
	cout << "      a   b   c   d   e   f   g   h  " << endl;
	cout << endl;

}

/*---------------------------------------
FUNCTION NAME:
PARAMETER(S):
RETURN TYPE:
POSTCONDITION(S): 
---------------------------------------*/
bool chess::isCheck(int, int)
{
	return false;
}

/*---------------------------------------
FUNCTION NAME:
PARAMETER(S):
RETURN TYPE:
POSTCONDITION(S): 
---------------------------------------*/
bool chess::isCheckMate(int, int)
{
	return false;
}

/*---------------------------------------
FUNCTION NAME:
PARAMETER(S):
RETURN TYPE:
POSTCONDITION(S): 
---------------------------------------*/
string chess::returnPiece(string)
{
	return 0;
}