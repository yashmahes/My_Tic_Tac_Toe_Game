// YourGameName.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>   // std::cout
#include <string>     // std::string, std::stoi
#include <ctime>
using namespace std;

// set the time time limit for a player to make a move
double time_limit = 10;
double elapsed_secs;
// initialize computer stats
int computerWins = 0;
int computerLosses = 0;
int computerDraws = 0;
// displays menu
string menu()
{
	string optionChosen;
	while (true)
	{
		cout << "Please choose from the following options : \n";
		cout << "1. Play Computer vs Human \n";
		cout << "2. Play Human vs Human \n";
		cout << "3. Play Computer vs Computer \n";
		cout << "4. Exit \n";

		cout << "Please enter your choice : ";

		cin >> optionChosen;


		if (optionChosen == "4" || optionChosen == "3" || optionChosen == "2" || optionChosen == "1")
		{
			break;
		}

		else
		{
			cout << "Invalid choice. Please enter a valid choice which are 1, 2, 3, and 4 \n";
		}

	}

	return optionChosen;

}

// displays board
void displayBoard(string values[3][3])
{
	cout << "\nGame Board \n";
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (j == 2)
			{
				cout << values[i][j] << endl;
			}
			else
			{
				cout << values[i][j] << "|";
			}
		}

		if (i != 2)
		{
			cout << "- - - \n";
		}
		else
		{
			cout << endl;
		}
	}
}

// checks if a player wins or not
bool isWin(string board[3][3], string symbol)
{
	for (int i = 0; i < 3; i++)
	{
		if (board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol)
		{
			return true;
		}
	}

	for (int j = 0; j < 3; j++)
	{
		if (board[0][j] == symbol && board[1][j] == symbol && board[2][j] == symbol)
		{
			return true;
		}
	}

	if (board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol)
	{
		return true;
	}

	if (board[2][0] == symbol && board[1][1] == symbol && board[0][2] == symbol)
	{
		return true;
	}

	return false;

}

// gets the name of player
string getName(string prompt)
{
	string player_name;
	cout << "\nPlease enter the name of " << prompt << endl;
	cin >> player_name;

	return player_name;
}

// code to make a move of a player
int makeMove(string name, string myBoard[3][3], string symbol)
{
	int flag = 0;
	while (flag != 1)
	{
		displayBoard(myBoard);
		cout << name << ", please enter the position where you want to put an " << symbol << ", you have 10 seconds to enter your choice.  \n";
		string pos;
		clock_t begin = clock();
		cin >> pos;
		clock_t end = clock();
		elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
		if (elapsed_secs > time_limit)
		{
			cout << "Time out!! The game is aborted. You lose because you took " << elapsed_secs << " seconds which is more than 10 seconds" << endl;
			return 0;
		}

		if (pos == "X" || pos == "O")
		{
			cout << "Invalid choice. Please try again. \n";
			continue;
		}

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (myBoard[i][j] == pos)
				{
					myBoard[i][j] = symbol;
					flag = 1;
					return 1;
				}
			}

		}

		cout << "Invalid choice. Please try again. \n";

	}
	return 0;
}



// we are making computer intelligent
bool isValid(string s[], string mySymbol, string opponentSymbol)
{
	if (s[0] == opponentSymbol && s[1] == opponentSymbol && s[2] != mySymbol)
	{
		s[2] = mySymbol;
		return true;
	}

	if (s[1] == opponentSymbol && s[2] == opponentSymbol && s[0] != mySymbol)
	{
		s[0] = mySymbol;
		return true;
	}

	if (s[2] == opponentSymbol && s[0] == opponentSymbol && s[1] != mySymbol)
	{
		s[1] = mySymbol;
		return true;
	}

	return false;
}

// code to make a move of a computer
// computer should make a move intelligently
int makeComputerMove(string name, string myBoard[3][3], string mySymbol, string opponentSymbol)
{

	cout << name << " turn \n";

	if (isValid(myBoard[0], mySymbol, opponentSymbol))
	{
		return 1;
	}

	if (isValid(myBoard[1], mySymbol, opponentSymbol))
	{
		return 1;
	}
	if (isValid(myBoard[2], mySymbol, opponentSymbol))
	{
		return 1;
	}


	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (myBoard[i][j] != mySymbol && myBoard[i][j] != opponentSymbol)
			{
				myBoard[i][j] = mySymbol;
				return 1;
			}
		}

	}

	return 0;

}


// displays Computer Stats
void displayComputerStats()
{
	cout << "\nNumber of Games won by Computer : " << computerWins << endl;
	cout << "Number of Games lost by Computer : " << computerLosses << endl;
	cout << "Number of Games drawn by Computer : " << computerDraws << endl << endl;
}

// main function
int main()
{
	cout << "*********************************** Tic Tac Toe Game ********************************* \n\n";

	while (true)
	{
		displayComputerStats();
		// intialize board
		string myBoard[3][3];

		myBoard[0][0] = "A";
		myBoard[0][1] = "B";
		myBoard[0][2] = "C";
		myBoard[1][0] = "D";
		myBoard[1][1] = "E";
		myBoard[1][2] = "F";
		myBoard[2][0] = "G";
		myBoard[2][1] = "H";
		myBoard[2][2] = "I";

		// displays menu and gets the option chosen by user
		string optionChosen = menu();

		// if user chose option 1
		if (optionChosen == "1")
		{
			string player1_name = getName("Player");
			string player2_name = getName("Computer");
			while (true)
			{
				displayBoard(myBoard);
				makeComputerMove(player2_name, myBoard, "O", "X");

				if (isWin(myBoard, "O"))
				{
					displayBoard(myBoard);
					cout << "\nCongratulations!! " << player2_name << " wins\n";
					computerWins += 1;
					break;
				}

				makeMove(player1_name, myBoard, "X");

				if (elapsed_secs > time_limit)
				{
					computerWins += 1;
					break;
				}

				if (isWin(myBoard, "X"))
				{
					displayBoard(myBoard);
					cout << "\nCongratulations!! " << player1_name << " wins \n";
					break;
				}
			}
		}

		// if user chose option 2
		if (optionChosen == "2")
		{
			string player1_name = getName("Player1");
			string player2_name = getName("Player2");


			while (true)
			{
				makeMove(player1_name, myBoard, "X");

				if (elapsed_secs > time_limit)
				{
					break;
				}

				if (isWin(myBoard, "X"))
				{
					displayBoard(myBoard);
					cout << "\nCongratulations!! " << player1_name << " wins \n";
					break;
				}


				makeMove(player2_name, myBoard, "O");
				if (elapsed_secs > time_limit)
				{
					break;
				}


				if (isWin(myBoard, "O"))
				{
					displayBoard(myBoard);
					cout << "\nCongratulations!! " << player2_name << " wins\n";
					break;
				}

			}


		}

		// if user chose option 3
		if (optionChosen == "3")
		{
			string player1_name = getName("Computer1");
			string player2_name = getName("Computer2");
			while (true)
			{
				displayBoard(myBoard);
				makeComputerMove(player1_name, myBoard, "X", "O");

				if (isWin(myBoard, "X"))
				{
					displayBoard(myBoard);
					cout << "\nCongratulations!! " << player1_name << " wins\n";

					break;
				}

				displayBoard(myBoard);
				makeComputerMove(player2_name, myBoard, "O", "X");

				if (isWin(myBoard, "O"))
				{
					displayBoard(myBoard);
					cout << "\nCongratulations!! " << player2_name << " wins\n";
					break;
				}
			}
		}

		// if user chose option 4
		if (optionChosen == "4")
		{
			cout << "Bye!!!!" << endl;
			break;
		}

	}

	return 0;
}

