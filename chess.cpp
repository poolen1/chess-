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
	wKingCol = 7;
	wKingRow = 4;
	bKingCol = 0;
	bKingRow = 4;
	wKingCheck = false;
	bKingCheck = false;

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

		//Adjust for board matrix coordinates
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
			if (isBlack(fromCol, fromRow)){
				cout << "You can only move the white pieces!" << endl;
				continue;
			}
		}
		else if (turn == 1){
			if (isWhite(fromCol, fromRow)){
				cout << "You can only move the black pieces!" << endl;
				continue;
			}
		}

		if (isBlocked(chessBoard[fromCol][fromRow], fromCol, fromRow)){
			if ((chessBoard[fromCol][fromRow] == "♚" || chessBoard[fromCol][fromRow] == "♚")){

			}
			cout << "That piece cannot move!" << endl;
			continue;
		}

		/*
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
		*/

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

		//Adjust for board matrix coordinates
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
		cout << "toCol input: " << toCol << endl;
		cout << "toRow input: " << toRow << endl;
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
			moved = moveRook(fromCol, fromRow, toCol, toRow);
			if (!moved)
				continue;
		}
		else if (chessBoard[fromCol][fromRow] == "♞"
			|| chessBoard[fromCol][fromRow] == "♘"){
			moved = moveKnight(fromCol, fromRow, toCol, toRow);
			if (!moved)
				continue;
		}
		else if (chessBoard[fromCol][fromRow] == "♝"
			|| chessBoard[fromCol][fromRow] == "♗"){
			moved = moveBishop(fromCol, fromRow, toCol, toRow);
			if (!moved)
				continue;
		}
		else if (chessBoard[fromCol][fromRow] == "♚"
			|| chessBoard[fromCol][fromRow] == "♔"){
			moved = moveKing(fromCol, fromRow, toCol, toRow);
			if (!moved)
				continue;
		}
		else if (chessBoard[fromCol][fromRow] == "♛"
			|| chessBoard[fromCol][fromRow] == "♕"){
			moved = moveQueen(fromCol, fromRow, toCol, toRow);
			if (!moved)
				continue;
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
bool chess::isPath(int kingCol, int kingRow)
{
	int rowPath;
	int colPath;
	//white king check
	//i==col, j==row
	for (int i=0; i<8; i++)
		for (int j=0; j<8; j++){
			
			if (turn == 1){
				//white pawn path
				if (chessBoard[i][j] == "♟"){
					if ((j+1<7 && chessBoard[i-1][j+1] == chessBoard[kingCol][kingRow])
						|| (j-1>=0 && chessBoard[i-1][j-1] == chessBoard[kingCol][kingRow]))
						return true;
				}
				
				//white rook path
				if (chessBoard[i][j] == "♜"){
					//rook left
					colPath = i;
					rowPath = j;
					while (colPath >= 0){
						if (chessBoard[colPath][rowPath] == chessBoard[kingCol][kingRow])
							return true;
						colPath--;
					}
					//rook right
					colPath = i;
					rowPath = j;
					while (colPath < 8){
						if (chessBoard[colPath][rowPath] == chessBoard[kingCol][kingRow])
							return true;
						colPath++;
					}
					//rook up
					colPath = i;
					rowPath = j;
					while (rowPath >= 0){
						if (chessBoard[colPath][rowPath] == chessBoard[kingCol][kingRow])
							return true;
						rowPath--;
					}
					//rook down
					colPath = i;
					rowPath = j;
					while (rowPath < 8){
						if (chessBoard[colPath][rowPath] == chessBoard[kingCol][kingRow])
							return true;
						rowPath++;
					}
				}
				
				//white knight path
				if (chessBoard[i][j] == "♞"){
					if ((chessBoard[i+1][j+2] == chessBoard[kingCol][kingRow] && i+1<8 && j+2<8)
						|| (chessBoard[i+2][j+1] == chessBoard[kingCol][kingRow] && i+2<8 && j+1<8)
						|| (chessBoard[i-1][j+2] == chessBoard[kingCol][kingRow] && i-1>=0 && j+2<8)
						|| (chessBoard[i-2][j+1] == chessBoard[kingCol][kingRow] && i-2>=0 && j+1<8)
						|| (chessBoard[i+1][j-2] == chessBoard[kingCol][kingRow] && i+1<8 && j-2>=0)
						|| (chessBoard[i+2][j-1] == chessBoard[kingCol][kingRow] && i+2<8 && j-1>=0)
						|| (chessBoard[i-1][j-2] == chessBoard[kingCol][kingRow] && i-1>=0 && j-2>=0)
						|| (chessBoard[i-2][j-1] == chessBoard[kingCol][kingRow] && i-2>=0 && j-1>=0))
						return true;
				}

				//white bishop path
				if (chessBoard[i][j] == "♝"){
					//bishop upleft
					colPath = i;
					rowPath = j;
					while (colPath<8 || rowPath<8){
						if (chessBoard[colPath][rowPath] == chessBoard[kingCol][kingRow])
							return true;
						colPath--;
						rowPath--;
					}

					//bishop upright
					colPath = i;
					rowPath = j;
					while (colPath>0 || rowPath<8){
						if (chessBoard[colPath][rowPath] == chessBoard[kingCol][kingRow])
							return true;
						colPath--;
						rowPath++;
					}

					//bishop downright
					colPath = i;
					rowPath = j;
					while (colPath>0 || rowPath>0){
						if (chessBoard[colPath][rowPath] == chessBoard[kingCol][kingRow])
							return true;
						colPath++;
						rowPath++;
					}

					//bishop downleft
					colPath = i;
					rowPath = j;
					while (colPath<8 || rowPath>0){
						if (chessBoard[colPath][rowPath] == chessBoard[kingCol][kingRow])
							return true;
						colPath++;
						rowPath++;
					}
				}

				//white queen path
				if (chessBoard[i][j] == "♛"){
					
					//queen left
					colPath = i;
					rowPath = j;
					while (colPath >= 0){
						if (chessBoard[colPath][rowPath] == chessBoard[kingCol][kingRow])
							return true;
						colPath--;
					}
					
					//queen right
					colPath = i;
					rowPath = j;
					while (colPath < 8){
						if (chessBoard[colPath][rowPath] == chessBoard[kingCol][kingRow])
							return true;
						colPath++;
					}
					
					//queen up
					colPath = i;
					rowPath = j;
					while (rowPath >= 0){
						if (chessBoard[colPath][rowPath] == chessBoard[kingCol][kingRow])
							return true;
						rowPath--;
					}
					
					//queen down
					colPath = i;
					rowPath = j;
					while (rowPath < 8){
						if (chessBoard[colPath][rowPath] == chessBoard[kingCol][kingRow])
							return true;
						rowPath++;
					}
					
					//queen upleft
					colPath = i;
					rowPath = j;
					while (colPath<8 || rowPath<8){
						if (chessBoard[colPath][rowPath] == chessBoard[kingCol][kingRow])
							return true;
						colPath--;
						rowPath--;
					}

					//queen upright
					colPath = i;
					rowPath = j;
					while (colPath>0 || rowPath<8){
						if (chessBoard[colPath][rowPath] == chessBoard[kingCol][kingRow])
							return true;
						colPath--;
						rowPath++;
					}

					//queen downright
					colPath = i;
					rowPath = j;
					while (colPath>0 || rowPath>0){
						if (chessBoard[colPath][rowPath] == chessBoard[kingCol][kingRow])
							return true;
						colPath++;
						rowPath++;
					}

					//queen downleft
					colPath = i;
					rowPath = j;
					while (colPath<8 || rowPath>0){
						if (chessBoard[colPath][rowPath] == chessBoard[kingCol][kingRow])
							return true;
						colPath++;
						rowPath++;
					}
				}


				//white king path
				if (chessBoard[i][j] == "♚"){
					if ((chessBoard[i][j-1] == chessBoard[kingCol][kingRow] && j-1>=0)
						|| (chessBoard[i+1][j-1] == chessBoard[kingCol][kingRow] && i+1<8 && j-1>=0)
						|| (chessBoard[i+1][j] == chessBoard[kingCol][kingRow] && i+1<8)
						|| (chessBoard[i+1][j+1] == chessBoard[kingCol][kingRow] && i+1<8 && j+1<8)
						|| (chessBoard[i][j+1] == chessBoard[kingCol][kingRow] && j+1<8)
						|| (chessBoard[i-1][j+1] == chessBoard[kingCol][kingRow] && i-1>=0 && j+1<8)
						|| (chessBoard[i-1][j] == chessBoard[kingCol][kingRow] && i-1>=0)
						|| (chessBoard[i-1][j-1] == chessBoard[kingCol][kingRow] && i-1>=0 && j-1>=0))
						return true;
				}

			}

			else if (turn == 0){
				//black pawn path
				if (chessBoard[i][j] == "♙"){
					if ((j+1<7 && chessBoard[i-1][j+1] == chessBoard[kingCol][kingRow])
						|| (j-1>=0 && chessBoard[i-1][j-1] == chessBoard[kingCol][kingRow]))
						return true;
				}
				
				//black rook path
				if (chessBoard[i][j] == "♖"){
					//rook left
					colPath = i;
					rowPath = j;
					while (colPath >= 0){
						if (chessBoard[colPath][rowPath] == chessBoard[kingCol][kingRow])
							return true;
						colPath--;
					}
					//rook right
					colPath = i;
					rowPath = j;
					while (colPath < 8){
						if (chessBoard[colPath][rowPath] == chessBoard[kingCol][kingRow])
							return true;
						colPath++;
					}
					//rook up
					colPath = i;
					rowPath = j;
					while (rowPath >= 0){
						if (chessBoard[colPath][rowPath] == chessBoard[kingCol][kingRow])
							return true;
						rowPath--;
					}
					//rook down
					colPath = i;
					rowPath = j;
					while (rowPath < 8){
						if (chessBoard[colPath][rowPath] == chessBoard[kingCol][kingRow])
							return true;
						rowPath++;
					}
				}
				
				//black knight path
				if (chessBoard[i][j] == "♘"){
					if ((chessBoard[i+1][j+2] == chessBoard[kingCol][kingRow] && i+1<8 && j+2<8)
						|| (chessBoard[i+2][j+1] == chessBoard[kingCol][kingRow] && i+2<8 && j+1<8)
						|| (chessBoard[i-1][j+2] == chessBoard[kingCol][kingRow] && i-1>=0 && j+2<8)
						|| (chessBoard[i-2][j+1] == chessBoard[kingCol][kingRow] && i-2>=0 && j+1<8)
						|| (chessBoard[i+1][j-2] == chessBoard[kingCol][kingRow] && i+1<8 && j-2>=0)
						|| (chessBoard[i+2][j-1] == chessBoard[kingCol][kingRow] && i+2<8 && j-1>=0)
						|| (chessBoard[i-1][j-2] == chessBoard[kingCol][kingRow] && i-1>=0 && j-2>=0)
						|| (chessBoard[i-2][j-1] == chessBoard[kingCol][kingRow] && i-2>=0 && j-1>=0))
						return true;
				}

				//black bishop path
				if (chessBoard[i][j] == "♗"){
					//bishop upleft
					colPath = i;
					rowPath = j;
					while (colPath<8 || rowPath<8){
						if (chessBoard[colPath][rowPath] == chessBoard[kingCol][kingRow])
							return true;
						colPath--;
						rowPath--;
					}

					//bishop upright
					colPath = i;
					rowPath = j;
					while (colPath>0 || rowPath<8){
						if (chessBoard[colPath][rowPath] == chessBoard[kingCol][kingRow])
							return true;
						colPath--;
						rowPath++;
					}

					//bishop downright
					colPath = i;
					rowPath = j;
					while (colPath>0 || rowPath>0){
						if (chessBoard[colPath][rowPath] == chessBoard[kingCol][kingRow])
							return true;
						colPath++;
						rowPath++;
					}

					//bishop downleft
					colPath = i;
					rowPath = j;
					while (colPath<8 || rowPath>0){
						if (chessBoard[colPath][rowPath] == chessBoard[kingCol][kingRow])
							return true;
						colPath++;
						rowPath++;
					}
				}

				//black queen path
				if (chessBoard[i][j] == "♕"){
					
					//queen left
					colPath = i;
					rowPath = j;
					while (colPath >= 0){
						if (chessBoard[colPath][rowPath] == chessBoard[kingCol][kingRow])
							return true;
						colPath--;
					}
					
					//queen right
					colPath = i;
					rowPath = j;
					while (colPath < 8){
						if (chessBoard[colPath][rowPath] == chessBoard[kingCol][kingRow])
							return true;
						colPath++;
					}
					
					//queen up
					colPath = i;
					rowPath = j;
					while (rowPath >= 0){
						if (chessBoard[colPath][rowPath] == chessBoard[kingCol][kingRow])
							return true;
						rowPath--;
					}
					
					//queen down
					colPath = i;
					rowPath = j;
					while (rowPath < 8){
						if (chessBoard[colPath][rowPath] == chessBoard[kingCol][kingRow])
							return true;
						rowPath++;
					}
					
					//queen upleft
					colPath = i;
					rowPath = j;
					while (colPath<8 || rowPath<8){
						if (chessBoard[colPath][rowPath] == chessBoard[kingCol][kingRow])
							return true;
						colPath--;
						rowPath--;
					}

					//queen upright
					colPath = i;
					rowPath = j;
					while (colPath>0 || rowPath<8){
						if (chessBoard[colPath][rowPath] == chessBoard[kingCol][kingRow])
							return true;
						colPath--;
						rowPath++;
					}

					//queen downright
					colPath = i;
					rowPath = j;
					while (colPath>0 || rowPath>0){
						if (chessBoard[colPath][rowPath] == chessBoard[kingCol][kingRow])
							return true;
						colPath++;
						rowPath++;
					}

					//queen downleft
					colPath = i;
					rowPath = j;
					while (colPath<8 || rowPath>0){
						if (chessBoard[colPath][rowPath] == chessBoard[kingCol][kingRow])
							return true;
						colPath++;
						rowPath++;
					}
				}


				//white king path
				if (chessBoard[i][j] == "♔"){
					if ((chessBoard[i][j-1] == chessBoard[kingCol][kingRow] && j-1>=0)
						|| (chessBoard[i+1][j-1] == chessBoard[kingCol][kingRow] && i+1<8 && j-1>=0)
						|| (chessBoard[i+1][j] == chessBoard[kingCol][kingRow] && i+1<8)
						|| (chessBoard[i+1][j+1] == chessBoard[kingCol][kingRow] && i+1<8 && j+1<8)
						|| (chessBoard[i][j+1] == chessBoard[kingCol][kingRow] && j+1<8)
						|| (chessBoard[i-1][j+1] == chessBoard[kingCol][kingRow] && i-1>=0 && j+1<8)
						|| (chessBoard[i-1][j] == chessBoard[kingCol][kingRow] && i-1>=0)
						|| (chessBoard[i-1][j-1] == chessBoard[kingCol][kingRow] && i-1>=0 && j-1>=0))
						return true;
				}
			}


		}

	return false;
}

/*---------------------------------------
FUNCTION NAME:
PARAMETER(S):
RETURN TYPE:
POSTCONDITION(S): 
---------------------------------------*/
bool chess::isStaleMate(int kingCol, int kingRow)
{
	for (int i=0; i<8; i++)
		for (int j=0; j<8; j++){
			if (turn == 0){
				if (isWhite(i,j) && !isBlocked(chessBoard[i][j],i,j))
					return false;
			}
		}

	if (isPath(kingCol, kingRow-1) && isPath(kingCol+1, kingRow-1)
		&& isPath(kingCol+1, kingRow) && isPath(kingCol+1, kingRow+1)
		&& isPath(kingCol, kingRow+1) && isPath(kingCol-1, kingRow+1) 
		&& isPath(kingCol-1, kingRow) && isPath(kingCol-1, kingRow-1)
		&& !isPath(kingCol, kingRow))
		return true;

	return false;
}

/*---------------------------------------
FUNCTION NAME:
PARAMETER(S):
RETURN TYPE:
POSTCONDITION(S): 
---------------------------------------*/
bool chess::isCheckMate(int kingCol, int kingRow)
{
	if (isPath(kingCol, kingRow-1) && isPath(kingCol+1, kingRow-1)
		&& isPath(kingCol+1, kingRow) && isPath(kingCol+1, kingRow+1)
		&& isPath(kingCol, kingRow+1) && isPath(kingCol-1, kingRow+1) 
		&& isPath(kingCol-1, kingRow) && isPath(kingCol-1, kingRow-1)
		&& isPath(kingCol, kingRow))
		return true;

	return false;
}

/*---------------------------------------
FUNCTION NAME:
PARAMETER(S):
RETURN TYPE:
POSTCONDITION(S): 
---------------------------------------*/
bool chess::isBlocked(string piece, int fromCol, int fromRow)
{
	//Pawn
	if (piece == "♟" && isWhite(fromCol, fromRow-1) 
		&& (isWhite(fromCol-1, fromRow-1) || chessBoard[fromCol-1][fromRow-1] == " " || fromCol-1<0) 
		&& (isWhite(fromCol+1, fromRow-1) || chessBoard[fromCol+1][fromRow-1] == " " || fromCol+1>7))
		return true;
	else if (piece == "♙" && isBlack(fromCol, fromRow+1) 
		&& (isBlack(fromCol-1, fromRow+1) || chessBoard[fromCol-1][fromRow+1] == " " || fromCol-1<0) 
		&& (isBlack(fromCol+1, fromRow+1) || chessBoard[fromCol+1][fromRow+1] == " " || fromCol+1>7))
		return true;

	//Rook
	else if (piece == "♜" 
		&& (isWhite(fromCol+1, fromRow) || fromCol+1 > 7)
		&& (isWhite(fromCol-1, fromRow) || fromCol-1 < 0)
		&& (isWhite(fromCol, fromRow+1) || fromRow+1 > 7)
		&& (isWhite(fromCol, fromRow-1) || fromRow-1 < 0))
		return true;
	else if (piece == "♖" 
		&& (isBlack(fromCol+1, fromRow) || fromCol+1 > 7)
		&& (isBlack(fromCol-1, fromRow) || fromCol-1 < 0)
		&& (isBlack(fromCol, fromRow+1) || fromRow+1 > 7)
		&& (isBlack(fromCol, fromRow-1) || fromRow-1 < 0))
		return true;

	//"♘"
	//Knight
	else if (piece == "♞"
		&& (isWhite(fromCol+1, fromRow+2) || fromCol+1>7 || fromRow+2>7) 
		&& (isWhite(fromCol+2, fromRow+1) || fromCol+2>7 || fromRow+1>7)
		&& (isWhite(fromCol-1, fromRow+2) || fromCol-1<0 || fromRow+2>7) 
		&& (isWhite(fromCol-2, fromRow+1) || fromCol-2<0 || fromRow+1>7)
		&& (isWhite(fromCol+1, fromRow-2) || fromCol+1>7 || fromRow-2<7) 
		&& (isWhite(fromCol+2, fromRow-1) || fromCol+2>7 || fromRow-1<7) 
		&& (isWhite(fromCol-1, fromRow-2) || fromCol-1<0 || fromRow-2<0) 
		&& (isWhite(fromCol-2, fromRow-1) || fromCol-2<0 || fromRow-1<0))
		return true;
	else if (piece == "♘"
		&& (isBlack(fromCol+1, fromRow+2) || fromCol+1>7 || fromRow+2>7) 
		&& (isBlack(fromCol+2, fromRow+1) || fromCol+2>7 || fromRow+1>7)
		&& (isBlack(fromCol-1, fromRow+2) || fromCol-1<0 || fromRow+2>7) 
		&& (isBlack(fromCol-2, fromRow+1) || fromCol-2<0 || fromRow+1>7)
		&& (isBlack(fromCol+1, fromRow-2) || fromCol+1>7 || fromRow-2<7) 
		&& (isBlack(fromCol+2, fromRow-1) || fromCol+2>7 || fromRow-1<7) 
		&& (isBlack(fromCol-1, fromRow-2) || fromCol-1<0 || fromRow-2<0) 
		&& (isBlack(fromCol-2, fromRow-1) || fromCol-2<0 || fromRow-1<0))
		return true;

	//Bishop
	else if (piece == "♝"
		&& (isWhite(fromCol-1, fromRow-1) || fromCol-1<0 || fromRow-1<0)
		&& (isWhite(fromCol+1, fromRow-1) || fromCol+1>7 || fromRow-1<0)
		&& (isWhite(fromCol-1, fromRow+1) || fromCol-1<0 || fromRow+1>7)
		&& (isWhite(fromCol+1, fromRow+1) || fromCol+1>7 || fromRow+1>7))
		return true;
	else if (piece == "♗"
		&& (isBlack(fromCol-1, fromRow-1) || fromCol-1<0 || fromRow-1<0)
		&& (isBlack(fromCol+1, fromRow-1) || fromCol+1>7 || fromRow-1<0)
		&& (isBlack(fromCol-1, fromRow+1) || fromCol-1<0 || fromRow+1>7)
		&& (isBlack(fromCol+1, fromRow+1) || fromCol+1>7 || fromRow+1>7))
		return true;

	//Queen
	else if (piece == "♛"
		&& (isWhite(fromCol+1, fromRow) || fromCol+1 > 7)
		&& (isWhite(fromCol-1, fromRow) || fromCol-1 < 0)
		&& (isWhite(fromCol, fromRow+1) || fromRow+1 > 7)
		&& (isWhite(fromCol, fromRow-1) || fromRow-1 < 0)
		&& (isWhite(fromCol-1, fromRow-1) || fromCol-1<0 || fromRow-1<0)
		&& (isWhite(fromCol+1, fromRow-1) || fromCol+1>7 || fromRow-1<0)
		&& (isWhite(fromCol-1, fromRow+1) || fromCol-1<0 || fromRow+1>7)
		&& (isWhite(fromCol+1, fromRow+1) || fromCol+1>7 || fromRow+1>7))
		return true;
	else if (piece == "♕"
		&& (isBlack(fromCol+1, fromRow) || fromCol+1 > 7)
		&& (isBlack(fromCol-1, fromRow) || fromCol-1 < 0)
		&& (isBlack(fromCol, fromRow+1) || fromRow+1 > 7)
		&& (isBlack(fromCol, fromRow-1) || fromRow-1 < 0) 
		&& (isBlack(fromCol-1, fromRow-1) || fromCol-1<0 || fromRow-1<0)
		&& (isBlack(fromCol+1, fromRow-1) || fromCol+1>7 || fromRow-1<0)
		&& (isBlack(fromCol-1, fromRow+1) || fromCol-1<0 || fromRow+1>7)
		&& (isBlack(fromCol+1, fromRow+1) || fromCol+1>7 || fromRow+1>7))
		return true;

	//King
	else if (piece == "♚"
		&& (isWhite(fromCol+1, fromRow) || fromCol+1 > 7)
		&& (isWhite(fromCol-1, fromRow) || fromCol-1 < 0)
		&& (isWhite(fromCol, fromRow+1) || fromRow+1 > 7)
		&& (isWhite(fromCol, fromRow-1) || fromRow-1 < 0)
		&& (isWhite(fromCol-1, fromRow-1) || fromCol-1<0 || fromRow-1<0)
		&& (isWhite(fromCol+1, fromRow-1) || fromCol+1>7 || fromRow-1<0)
		&& (isWhite(fromCol-1, fromRow+1) || fromCol-1<0 || fromRow+1>7)
		&& (isWhite(fromCol+1, fromRow+1) || fromCol+1>7 || fromRow+1>7))
		return true;
	else if (piece == "♔"
		&& (isBlack(fromCol+1, fromRow) || fromCol+1 > 7)
		&& (isBlack(fromCol-1, fromRow) || fromCol-1 < 0)
		&& (isBlack(fromCol, fromRow+1) || fromRow+1 > 7)
		&& (isBlack(fromCol, fromRow-1) || fromRow-1 < 0) 
		&& (isBlack(fromCol-1, fromRow-1) || fromCol-1<0 || fromRow-1<0)
		&& (isBlack(fromCol+1, fromRow-1) || fromCol+1>7 || fromRow-1<0)
		&& (isBlack(fromCol-1, fromRow+1) || fromCol-1<0 || fromRow+1>7)
		&& (isBlack(fromCol+1, fromRow+1) || fromCol+1>7 || fromRow+1>7))
		return true;

	return false;
}

/*---------------------------------------
FUNCTION NAME:
PARAMETER(S):
RETURN TYPE:
POSTCONDITION(S): 
---------------------------------------*/
bool chess::isBlack(int fromCol, int fromRow)
{
	if (chessBoard[fromCol][fromRow] == "♕" || chessBoard[fromCol][fromRow] == "♔"
		|| chessBoard[fromCol][fromRow] == "♗" || chessBoard[fromCol][fromRow] == "♘"
		|| chessBoard[fromCol][fromRow] == "♖" || chessBoard[fromCol][fromRow] == "♙"){
		return true;
	}

	return false;
}

/*---------------------------------------
FUNCTION NAME:
PARAMETER(S):
RETURN TYPE:
POSTCONDITION(S): 
---------------------------------------*/
bool chess::isWhite(int fromCol, int fromRow)
{
	if (chessBoard[fromCol][fromRow] == "♛" || chessBoard[fromCol][fromRow] == "♚"
		|| chessBoard[fromCol][fromRow] == "♝" || chessBoard[fromCol][fromRow] == "♞"
		|| chessBoard[fromCol][fromRow] == "♜" || chessBoard[fromCol][fromRow] == "♟"){
		return true;
	}

	return false;
}

/*---------------------------------------
FUNCTION NAME:
PARAMETER(S):
RETURN TYPE:
POSTCONDITION(S): 
---------------------------------------*/
void chess::returnPiece(int toCol, int toRow)
{
	int recover;

	cout << "Choose a captured piece to return: " << endl;
	
	if (turn == 1){
		for (int i=0; i<15; i++)
			cout << " " << capturedBlack[i];
		cout << endl;
		for (int i=0; i<15; i++){
			if (capturedBlack[i] != " ")
				cout << " " << i;
		}

		cout << endl;
		cin >> recover;

		chessBoard[toCol][toRow] = capturedBlack[recover];
		capturedBlack[recover] = " ";
	}

	else if (turn ==0){
		for (int i=0; i<15; i++)
			cout << " " << capturedWhite[i];
		cout << endl;
		for (int i=0; i<15; i++){
			if (capturedWhite[i] != " ")
				cout << " " << i;
		}

		cout << endl;
		cin >> recover;

		chessBoard[toCol][toRow] = capturedWhite[recover];
		capturedWhite[recover] = " ";
	}
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

	//Return black piece
	if (toRow == 7)
		returnPiece(toCol, toRow);

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

	//Return white piece
	if (toRow == 0)
		returnPiece(toCol, toRow);

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
	//rook downboard
	if (toRow > fromRow && toCol == fromCol){
		for (int i=fromRow+1; i<toRow; i++){
			if (chessBoard[toCol][i] != " "){
				cout << "Rooks can't jump!" << endl;
				return false;
			}
		}
		swapPieces(fromCol, fromRow, toCol, toRow);
	//TEST
	//cout << "rook downtest" << endl;
	}

	//rook up
	else if (toRow < fromRow && toCol == fromCol){
		for (int i=fromRow-1; i>toRow; i--){
			if (chessBoard[toCol][i] != " "){
				cout << "Rooks can't jump!" << endl;
				return false;
			}
		}
		swapPieces(fromCol, fromRow, toCol, toRow);
	//TEST
	//cout << "rook uptest" << endl;
	}

	//rook right
	else if (toCol > fromCol && toRow == fromRow){
		for (int i=fromCol+1; i<toCol; i++){
			if (chessBoard[i][toRow] != " "){
				cout << "Rooks can't jump!" << endl;
				return false;
			}
		}
		swapPieces(fromCol, fromRow, toCol, toRow);
	//TEST
	//cout << "rook righttest" << endl;
	}

	//rook left
	else if (toCol < fromCol && toRow == fromRow){
		for (int i=fromCol-1; i>toCol; i--){
			if (chessBoard[i][toRow] != " "){
				cout << "Rooks can't jump!" << endl;
				return false;
			}
		}
		swapPieces(fromCol, fromRow, toCol, toRow);
	//TEST
	//cout << "rook lefttest" << endl;
	}

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
	if ((toCol==fromCol+1 && toRow==fromRow+2) || (toCol==fromCol+2 && toRow==fromRow+1)
		|| (toCol==fromCol-1 && toRow==fromRow+2) || (toCol==fromCol-2 && toRow==fromRow+1)
		|| (toCol==fromCol+1 && toRow==fromRow-2) || (toCol==fromCol+2 && toRow==fromRow-1) 
		|| (toCol==fromCol-1 && toRow==fromRow-2) || (toCol==fromCol-2 && toRow==fromRow-1))
		swapPieces(fromCol, fromRow, toCol, toRow);
	else{
		cout << "Knights can't move that way!" << endl;
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
bool chess::moveBishop(int fromCol, int fromRow, int toCol, int toRow)
{
	int i; //column
	int j; //row

	//bishop upleft (--)
	if (toRow < fromRow && toCol < fromCol){
		i = fromCol-1;
		j = fromRow-1;
		while (i>toCol && j>toRow){
			if (chessBoard[i][j] != " "){
				cout << "Bishops can't jump!" << endl;
				return false;
			}
			i--;
			j--;
		}
		swapPieces(fromCol, fromRow, toCol, toRow);
	//TEST
	cout << "bishop upleft test" << endl;
	}

	//bishop upright (-+)
	else if (toRow > fromRow && toCol < fromCol){
		i = fromCol-1;
		j = fromRow+1;
		while (i<toCol && j>toRow){
			if (chessBoard[i][j] != " "){
				cout << "Bishops can't jump!" << endl;
				return false;
			}
			i--;
			j++;
		}
		swapPieces(fromCol, fromRow, toCol, toRow);
	//TEST
	cout << "bishop upright test" << endl;
	}

	//bishop downright (++)
	else if (toCol > fromCol && toRow > fromRow){
		i = fromCol+1;
		j = fromRow+1;
		while (i<toCol && j<toRow){
				if (chessBoard[i][j] != " "){
					cout << "Bishops can't jump!" << endl;
					return false;
			}
			i++;
			j++;
		}
		swapPieces(fromCol, fromRow, toCol, toRow);
	//TEST
	cout << "bishop downright test" << endl;
	}

	//bishop downleft (+-)
	else if (toCol > fromCol && toRow < fromRow){
		i = fromCol+1;
		j = fromRow-1;
		while (i<toCol && j>toRow){
				if (chessBoard[i][j] != " "){
					cout << "Bishops can't jump!" << endl;
					return false;
			}
			i++;
			j--;
		}
		swapPieces(fromCol, fromRow, toCol, toRow);
	//TEST
	cout << "bishop downleft test" << endl;
	}

	else{
		cout << "Bishops can't move that way!" << endl;
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
bool chess::moveQueen(int fromCol, int fromRow, int toCol, int toRow)
{
	//queen downboard
	if (toRow > fromRow && toCol == fromCol){
		for (int i=fromRow+1; i<toRow; i++){
			if (chessBoard[toCol][i] != " "){
				cout << "The Queen can't jump!" << endl;
				return false;
			}
		}
		swapPieces(fromCol, fromRow, toCol, toRow);
	//TEST
	cout << "queen downtest" << endl;
	}

	//queen up
	else if (toRow < fromRow && toCol == fromCol){
		for (int i=fromRow-1; i>toRow; i--){
			if (chessBoard[toCol][i] != " "){
				cout << "The Queen can't jump!" << endl;
				return false;
			}
		}
		swapPieces(fromCol, fromRow, toCol, toRow);
	//TEST
	cout << "queen uptest" << endl;
	}

	//queen right
	else if (toCol > fromCol && toRow == fromRow){
		for (int i=fromCol+1; i<toCol; i++){
			if (chessBoard[i][toRow] != " "){
				cout << "The Queen can't jump!" << endl;
				return false;
			}
		}
		swapPieces(fromCol, fromRow, toCol, toRow);
	//TEST
	cout << "queen righttest" << endl;
	}

	//queen left
	else if (toCol < fromCol && toRow == fromRow){
		for (int i=fromCol-1; i>toCol; i--){
			if (chessBoard[i][toRow] != " "){
				cout << "The Queen can't jump!" << endl;
				return false;
			}
		}
		swapPieces(fromCol, fromRow, toCol, toRow);
	//TEST
	cout << "queen lefttest" << endl;
	}

	//queen upleft (--)
	if (toRow < fromRow && toCol < fromCol){
		for (int i=fromRow-1; i>toRow; i--)
			for (int j=fromCol-1; j>toCol; j--){
				if (chessBoard[j][i] != " "){
					cout << "The Queen can't jump!" << endl;
					return false;
			}
		}
		swapPieces(fromCol, fromRow, toCol, toRow);
	//TEST
	cout << "queen upleft test" << endl;
	}

	//queen upright (-+)
	else if (toRow > fromRow && toCol < fromCol){
		for (int i=fromRow+1; i>toRow; i++)
			for (int j=fromCol-1; j<toCol; j--){
				if (chessBoard[j][i] != " "){
					cout << "The Queen can't jump!" << endl;
					return false;
			}
		}
		swapPieces(fromCol, fromRow, toCol, toRow);
	//TEST
	cout << "queen upright test" << endl;
	}

	//queen downright (++)
	else if (toCol > fromCol && toRow > fromRow){
		for (int i=fromCol+1; i<toCol; i++)
			for (int j=fromRow+1; j<toRow; j++){
				if (chessBoard[i][j] != " "){
					cout << "The Queen can't jump!" << endl;
					return false;
			}
		}
		swapPieces(fromCol, fromRow, toCol, toRow);
	//TEST
	cout << "queen downright test" << endl;
	}

	//queen downleft (+-)
	else if (toCol > fromCol && toRow < fromRow){
		for (int i=fromCol+1; i>toCol; i++)
			for (int j=fromRow-1; j<toRow; j--){
				if (chessBoard[i][j] != " "){
					cout << "The Queen can't jump!" << endl;
					return false;
			}
		}
		swapPieces(fromCol, fromRow, toCol, toRow);
	//TEST
	cout << "queen downleft test" << endl;
	}

	else if ((toCol==fromCol+1 && toRow==fromRow+2) || (toCol==fromCol+2 && toRow==fromRow+1)
		|| (toCol==fromCol-1 && toRow==fromRow+2) || (toCol==fromCol-2 && toRow==fromRow+1)
		|| (toCol==fromCol+1 && toRow==fromRow-2) || (toCol==fromCol+2 && toRow==fromRow-1) 
		|| (toCol==fromCol-1 && toRow==fromRow-2) || (toCol==fromCol-2 && toRow==fromRow-1)){
		cout << "The Queen can't move that way!" << endl;
		return false;
	}

	else{
		cout << "The Queen can't move that way!" << endl;
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
bool chess::moveKing(int fromCol, int fromRow, int toCol, int toRow)
{
	if ((toCol==fromCol && toRow==fromRow-1) || (toCol==fromCol+1 && toRow==fromRow-1)
		|| (toCol==toCol+1 && toRow==fromRow) || (toCol==fromCol+1 && toRow==fromRow+1)
		|| (toCol==fromCol && toRow==fromRow+1) || (toCol==fromCol-1 && toRow==fromRow+1)
		|| (toCol==fromCol-1 && toRow==fromRow) || (toCol==fromCol-1 && toRow==fromRow-1))
		swapPieces(fromCol, fromRow, toCol, toRow);
	else{
		cout << "The King can't move that way!" << endl;
		return false;
	}

	if (turn==0){
		wKingCol = toCol;
		wKingRow = toRow;
	}
	else if (turn==1){
		bKingCol = toCol;
		bKingRow = toRow;
	}

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
