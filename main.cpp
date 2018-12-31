#include <iostream>
#include <string>
#include <cstdlib>
#include "chess.h"
using namespace std;

int main()
{
	chess myGame;
	myGame.setupBoard();

	cout << endl;
	cout << "	-------------------------------------------" << endl;
	cout << "	 _____   _    _   ______   ______   ______ " << endl;
	cout << "	| ____| | |  | | |  ____| |  ____| |  ____|" << endl;
	cout << "	| |   	| |__| | | |____  | |____  | |____ " << endl;
	cout << "	| | 	|  __  | |  ____| |____  | |____  |" << endl;
	cout << "	| |___  | |  | | | |____   ____| |  ____| |" << endl;
	cout << "	|_____| |_|  |_| |______| |______| |______|" << endl;
	cout << endl;
	cout << "	-------------------------------------------" << endl;
	cout << endl;

	cout << "Start!" << endl;

	while (true){
		myGame.printBoard();
		myGame.movePiece();
	}

	return 0;
}