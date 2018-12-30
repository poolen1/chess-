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
	wCaptured = 0;
	bCaptured = 0;
	whiteKing = 74;
	blackKing = 04;

	for (int i=0; i<15; i++){
		capturedBlack[i] = " ";
		capturedWhite[i] = " ";
	}

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
	chessBoard[1][0] = "♘";
	chessBoard[2][0] = "♗";
	chessBoard[3][0] = "♕";	//Queen
	chessBoard[4][0] = "♔";	//King
	chessBoard[5][0] = "♗";
	chessBoard[6][0] = "♘";
	chessBoard[7][0] = "♖";
	chessBoard[0][1] = "♙";
	chessBoard[1][1] = "♙";
	chessBoard[2][1] = "♙";
	chessBoard[3][1] = "♙";
	chessBoard[4][1] = "♙";
	chessBoard[5][1] = "♙";
	chessBoard[6][1] = "♙";
	chessBoard[7][1] = "♙";

	//white pieces
	chessBoard[0][7] = "♜";
	chessBoard[1][7] = "♞";
	chessBoard[2][7] = "♝";
	chessBoard[3][7] = "♛"; //Queen
	chessBoard[4][7] = "♚";	//King
	chessBoard[5][7] = "♝";
	chessBoard[6][7] = "♞";
	chessBoard[7][7] = "♜";
	chessBoard[0][6] = "♟";
	chessBoard[1][6] = "♟";
	chessBoard[2][6] = "♟";
	chessBoard[3][6] = "♟";
	chessBoard[4][6] = "♟";
	chessBoard[5][6] = "♟";
	chessBoard[6][6] = "♟";
	chessBoard[7][6] = "♟";
}

/*---------------------------------------
FUNCTION NAME:
PARAMETER(S):
RETURN TYPE:
POSTCONDITION(S): 
---------------------------------------*/
void chess::movePiece()
{
	string fromHere;
	string toThere;
	bool fromInput = false;	//Valid input flag
	bool toInput = false;	//Valid input flag
	//bool blocked = false;	//Checks movement paths
	int fromCol;	//Processed fromColumn coordinate
	int fromRow;	//Processed fromRow coordinate
	int toCol;		//Processed toColumn coordinate
	int toRow;		//Processed toRow coordinate
	bool moved; 	//Valid move flag

	if (turn == 0)
		cout << "Player 1" << endl;
	if (turn == 1)
		cout << "Player 2" << endl;

	//Choose a piece to move
	while (fromInput == false){
		cout << "Move from: ";
		cin >> fromHere;

		//TEST
		//cout << "Col: " << fromHere[0] << endl;
		//cout << "Row: " << fromHere[1] << endl;

		//string processing
		fromCol = tolower(fromHere[0]);
		fromCol = fromCol - 'a';
		//cout << "Col: " << col << endl;
		fromRow = (fromHere[1] - '0') - 1;
		//cout << "Row: " << row << endl;

		if (fromCol < 0 || fromCol > 7 || fromRow < 0 || fromRow > 7){
			cout << "Invalid square. Enter letter a-h, then number 1-8." << endl;
			continue;
		}

		//Adjust for board coordinates
		if (fromRow == 7)
			fromRow = 0;
		else if (fromRow == 6)
			fromRow = 1;
		else if (fromRow == 5)
			fromRow = 2;
		else if (fromRow == 4)
			fromRow = 3;
		else if (fromRow == 3)
			fromRow = 4;
		else if (fromRow == 2)
			fromRow = 5;
		else if (fromRow == 1)
			fromRow = 6;
		else if (fromRow == 0)
			fromRow = 7;

		//TEST
		cout << "fromCol: " << fromCol << endl;
		cout << "fromRow: " << fromRow << endl;
		cout << "Piece: " << chessBoard[fromCol][fromRow] << endl;


		if (chessBoard[fromCol][fromRow] == " "){
			cout << "There is no piece there to move!" << endl;
			continue;
		}

		if (turn == 0){
			if (chessBoard[fromCol][fromRow] == "♕" || chessBoard[fromCol][fromRow] == "♔"
				|| chessBoard[fromCol][fromRow] == "♗" || chessBoard[fromCol][fromRow] == "♘"
				|| chessBoard[fromCol][fromRow] == "♖" || chessBoard[fromCol][fromRow] == "♙"){
				cout << "You can only move the white pieces!" << endl;
				continue;
			}
		}
		else if (turn == 1){
			if (chessBoard[fromCol][fromRow] == "♛" || chessBoard[fromCol][fromRow] == "♚"
				|| chessBoard[fromCol][fromRow] == "♝" || chessBoard[fromCol][fromRow] == "♞"
				|| chessBoard[fromCol][fromRow] == "♜" || chessBoard[fromCol][fromRow] == "♟"){
				cout << "You can only move the black pieces!" << endl;
				continue;
			}
		}

		fromInput = true;
	}
	
	//Choose a square to move to
	while (toInput == false){
		cout << "Move to: ";
		cin >> toThere;

		//string processing
		toCol = tolower(toThere[0]);
		toCol = toCol - 'a';
		cout << "toCol: " << toCol << endl;
		toRow = (toThere[1] - '0') - 1;
		cout << "toRow: " << toRow << endl;

		if (toCol < 0 || toCol > 7 || toRow < 0 || toRow > 7){
			cout << "Invalid square. Enter letter a-h, then number 1-8." << endl;
			continue;
		}

		//Adjust for board coordinates
		if (toRow == 7)
			toRow = 0;
		else if (toRow == 6)
			toRow = 1;
		else if (toRow == 5)
			toRow = 2;
		else if (toRow == 4)
			toRow = 3;
		else if (toRow == 3)
			toRow = 4;
		else if (toRow == 2)
			toRow = 5;
		else if (toRow == 1)
			toRow = 6;
		else if (toRow == 0)
			toRow = 7;

		//TEST
		cout << "toCol: " << toCol << endl;
		cout << "toRow: " << toRow << endl;
		cout << "Piece: " << chessBoard[toCol][toRow] << endl;

		if (turn == 1){
			if (chessBoard[toCol][toRow] == "♕" || chessBoard[toCol][toRow] == "♔"
				|| chessBoard[toCol][toRow] == "♗" || chessBoard[toCol][toRow] == "♘"
				|| chessBoard[toCol][toRow] == "♖" || chessBoard[toCol][toRow] == "♙"){
				cout << "You can't capture your own pieces!" << endl;
				continue;
			}

			//move black pawn
			if (chessBoard[fromCol][fromRow] == "♙"){
				moved = moveBlackPawn(fromCol, fromRow, toCol, toRow);
				if (!moved)
					continue;
			}		
		}

		else if (turn == 0){
			if (chessBoard[toCol][toRow] == "♛" || chessBoard[toCol][toRow] == "♚"
				|| chessBoard[toCol][toRow] == "♝" || chessBoard[toCol][toRow] == "♞"
				|| chessBoard[toCol][toRow] == "♜" || chessBoard[toCol][toRow] == "♟"){
				cout << "You can't capture your own pieces!" << endl;
				continue;
			}

			//move white pawn
			if (chessBoard[fromCol][fromRow] == "♟"){
				moved = moveWhitePawn(fromCol, fromRow, toCol, toRow);
				if (!moved)
					continue;
			}

			//swapPieces(fromCol, fromRow, toCol, toRow);
		}

		if (chessBoard[fromCol][fromRow] == "♜"
			|| chessBoard[fromCol][fromRow] == "♖"){
			moveRook(fromCol, fromRow, toCol, toRow);
		}
		else if (chessBoard[fromCol][fromRow] == "♞"
			|| chessBoard[fromCol][fromRow] == "♘"){
			moveKnight(fromCol, fromRow, toCol, toRow);
		}
		else if (chessBoard[fromCol][fromRow] == "♝"
			|| chessBoard[fromCol][fromRow] == "♗"){
			moveBishop(fromCol, fromRow, toCol, toRow);
		}
		else if (chessBoard[fromCol][fromRow] == "♚"
			|| chessBoard[fromCol][fromRow] == "♔"){
			moveKing(fromCol, fromRow, toCol, toRow);
		}
		else if (chessBoard[fromCol][fromRow] == "♛"
			|| chessBoard[fromCol][fromRow] == "♕"){
			moveQueen(fromCol, fromRow, toCol, toRow);
		}

		toInput = true;
	}
	
	if (turn == 0)
		turn = 1;
	else if (turn == 1)
		turn = 0;
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

	cout << endl;

	for (int i=0; i<7; i++)
		cout << " " << capturedWhite[i];

	cout << endl;

	cout << "    +---+---+---+---+---+---+---+---+" << endl;
	cout << "  8 |";
	for (int j=0; j<8; j++){
		cout << " " << chessBoard[j][0] << " |";
		if (j==7)
			cout << endl;
	}
	cout << "    +---+---+---+---+---+---+---+---+" << endl;
	cout << "  7 |";
	for (int j=0; j<8; j++){
		cout << " " << chessBoard[j][1] << " |";
		if (j==7)
			cout << endl;
	}
	cout << "    +---+---+---+---+---+---+---+---+" << endl;
	cout << "  6 |";
	for (int j=0; j<8; j++){
		cout << " " << chessBoard[j][2] << " |";
		if (j==7)
			cout << endl;
	}
	cout << "    +---+---+---+---+---+---+---+---+" << endl;
	cout << "  5 |";
	for (int j=0; j<8; j++){
		cout << " " << chessBoard[j][3] << " |";
		if (j==7)
			cout << endl;
	}
	cout << "    +---+---+---+---+---+---+---+---+" << endl;
	cout << "  4 |";
	for (int j=0; j<8; j++){
		cout << " " << chessBoard[j][4] << " |";
		if (j==7)
			cout << endl;
	}
	cout << "    +---+---+---+---+---+---+---+---+" << endl;
	cout << "  3 |";
	for (int j=0; j<8; j++){
		cout << " " << chessBoard[j][5] << " |";
		if (j==7)
			cout << endl;
	}
	cout << "    +---+---+---+---+---+---+---+---+" << endl;
	cout << "  2 |";
	for (int j=0; j<8; j++){
		cout << " " << chessBoard[j][6] << " |";
		if (j==7)
			cout << endl;
	}
	cout << "    +---+---+---+---+---+---+---+---+" << endl;
	cout << "  1 |";
	for (int j=0; j<8; j++){
		cout << " " << chessBoard[j][7] << " |";
		if (j==7)
			cout << endl;
	}
	cout << "    +---+---+---+---+---+---+---+---+" << endl;
	cout << "      a   b   c   d   e   f   g   h  " << endl;

	for (int i=0; i<7; i++)
		cout << " " << capturedBlack[i];

	cout << endl << endl;

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

/*---------------------------------------
FUNCTION NAME:
PARAMETER(S):
RETURN TYPE:
POSTCONDITION(S): 
---------------------------------------*/
bool chess::moveBlackPawn(int fromCol, int fromRow, int toCol, int toRow)
{
	//TEST
	cout << "Black Pawn Test" << endl;

	if (toRow == fromRow+1 && chessBoard[toCol][toRow] == " " && toCol == fromCol)
		swapPieces(fromCol, fromRow, toCol, toRow);
	else if (fromRow == 1 && toRow == fromRow+2 && chessBoard[toCol][toRow] == " "
		&& toCol == fromCol)
		swapPieces(fromCol, fromRow, toCol, toRow);
	else if (toRow == fromRow+1 && chessBoard[toCol][toRow] != " " 
		&& (toCol == fromCol-1 || toCol == fromCol+1))
		swapPieces(fromCol, fromRow, toCol, toRow);
	else{
		cout << "Pawns cannot move that way!" << endl;
		return false;
	}

	return true;
}

/*---------------------------------------
FUNCTION NAME:
PARAMETER(S):
RETURN TYPE:
POSTCONDITION(S): 
---------------------------------------*/
bool chess::moveWhitePawn(int fromCol, int fromRow, int toCol, int toRow)
{
	//TEST
	cout << "White Pawn Test" << endl;

	if (toRow == fromRow-1 && chessBoard[toCol][toRow] == " " && toCol == fromCol)
		swapPieces(fromCol, fromRow, toCol, toRow);
	else if (fromRow == 6 && toRow == fromRow-2 && chessBoard[toCol][toRow] == " "
		&& toCol == fromCol)
		swapPieces(fromCol, fromRow, toCol, toRow);
	else if (toRow == fromRow-1 && chessBoard[toCol][toRow] != " " 
		&& (toCol == fromCol-1 || toCol == fromCol+1))
		swapPieces(fromCol, fromRow, toCol, toRow);
	else{
		cout << "Pawns cannot move that way!" << endl;
		return false;
	}

	return true;
}

/*---------------------------------------
FUNCTION NAME:
PARAMETER(S):
RETURN TYPE:
POSTCONDITION(S): 
---------------------------------------*/
bool chess::moveRook(int fromCol, int fromRow, int toCol, int toRow)
{
	return true;
}

/*---------------------------------------
FUNCTION NAME:
PARAMETER(S):
RETURN TYPE:
POSTCONDITION(S): 
---------------------------------------*/
bool chess::moveKnight(int fromCol, int fromRow, int toCol, int toRow)
{
	return true;
}

/*---------------------------------------
FUNCTION NAME:
PARAMETER(S):
RETURN TYPE:
POSTCONDITION(S): 
---------------------------------------*/
bool chess::moveBishop(int fromCol, int fromRow, int toCol, int toRow)
{
	return true;
}

/*---------------------------------------
FUNCTION NAME:
PARAMETER(S):
RETURN TYPE:
POSTCONDITION(S): 
---------------------------------------*/
bool chess::moveQueen(int fromCol, int fromRow, int toCol, int toRow)
{
	return true;
}

/*---------------------------------------
FUNCTION NAME:
PARAMETER(S):
RETURN TYPE:
POSTCONDITION(S): 
---------------------------------------*/
bool chess::moveKing(int fromCol, int fromRow, int toCol, int toRow)
{
	return true;
}

/*---------------------------------------
FUNCTION NAME:
PARAMETER(S):
RETURN TYPE:
POSTCONDITION(S): 
---------------------------------------*/
void chess::swapPieces(int fromCol, int fromRow, int toCol, int toRow)
{
	//TEST 
	cout << "Swap Test" << endl;

	string temp;

	cout << "From: " << chessBoard[fromCol][fromRow] << endl;
	cout << "To: " << chessBoard[toCol][toRow] << endl;

	temp = chessBoard[toCol][toRow];

	if (temp != " ")
		capturePiece(toCol, toRow);

	chessBoard[toCol][toRow] = chessBoard[fromCol][fromRow];
	chessBoard[fromCol][fromRow] = " ";
}

/*---------------------------------------
FUNCTION NAME:
PARAMETER(S):
RETURN TYPE:
POSTCONDITION(S): 
---------------------------------------*/
void chess::capturePiece(int toCol, int toRow)
{
	if (chessBoard[toCol][toRow] == "♛" || chessBoard[toCol][toRow] == "♝" 
		|| chessBoard[toCol][toRow] == "♞" || chessBoard[toCol][toRow] == "♜" 
		|| chessBoard[toCol][toRow] == "♟"){
		capturedWhite[wCaptured] = chessBoard[toCol][toRow];
		wCaptured++;
	}
	else if (chessBoard[toCol][toRow] == "♚"){
		cout << "Go for checkmate!" << endl;
		return;
	}

	else if (chessBoard[toCol][toRow] == "♕" || chessBoard[toCol][toRow] == "♗" 
		|| chessBoard[toCol][toRow] == "♘" || chessBoard[toCol][toRow] == "♖" 
		|| chessBoard[toCol][toRow] == "♙"){
		capturedBlack[bCaptured] = chessBoard[toCol][toRow];
		bCaptured++;
	}
	else if (chessBoard[toCol][toRow] == "♔"){
		cout << "Go for checkmate!" << endl;
		return;
	}
}