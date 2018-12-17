#include <iostream>
#include <string>
#include <time.h>
#include <stdlib.h>

using namespace std;

// Board properties
const int row = 5;
const int col = 5;
string gameBoard[row][col];
string enemyBoard[row][col];
string playerBoard[row][col];

// Ship properties
int shipAmount = 0;
int shipSize = 0;

// Game properties
int score = 0;
int game = 0;

// Console functions
int InputConverter(string k);

// Game functions
void DisplayTitle();
int Deploy(int mode, int x, int y); 
bool WinChecker(string board[][col]);

// Board functions
void InitBoard(string board[][col]);
void DisplayBoard(string board[][col]);
bool IsAvailable(string type, int orientation, int x , int y);
void InitEnemyShips(int amount, int size);
void OrientationPos();

int main() 
{
	srand(time(NULL));
	bool mainExit = false;
	
	do
	{ 
		string winner;
		string k;
		do
		{
			system("cls");
			DisplayTitle();
			cout << "How many enemy ships would you like to go against? (1 - 4)" << endl;
			cin >> k;
			if ((InputConverter(k) < 5) && (InputConverter(k)))
				break;
			
			cout << endl;
			cout << "Invalid input. Please try again." << endl;
			system("pause");
		} while(true);
		shipAmount = InputConverter(k);
		
		do
		{
			system("cls");
			DisplayTitle();
			cout << "Number of ship you have chosen: " << shipAmount << "." << endl;
			cout << "How big are the ships? (1 - 4)" << endl;
			cin >> k;
			if ((InputConverter(k) < 5) && (InputConverter(k)))
				break;
			
			cout << endl;
			cout << "Invalid input. Please try again." << endl;
			system("pause");
		} while(true);
		shipSize = InputConverter(k);
		
		InitBoard(enemyBoard);
		InitEnemyShips(shipAmount, shipSize);
		
		int x = 0, y = 0, orientation = -1;
		InitBoard(playerBoard);
		OrientationPos();
		InitBoard(gameBoard);
		bool hit;
		bool firstTurn = true;
		while(true)
		{
			system("cls");
			DisplayTitle();
			cout << "Enemy's territory" << endl;
			DisplayBoard(gameBoard);
			cout << endl << "Your territory" << endl;
			DisplayBoard(playerBoard);
			cout << endl;
			
			if (firstTurn)
				cout << "Destroy them!" << endl;
			else
			{
				if (!hit)
					cout << "We are POWERRFULL!! They missed." << endl;
				else
					cout << "Damn, you got hit." << endl;
			}
			firstTurn = false;
			
			do
			{
				do
				{
					cout << "Choose x-coordinate that you wish to attack: ";
					cin >> k;
					
					if (InputConverter(k) == 0)
						cout << endl << "Invalid input. Please try again." << endl;
				} while(!InputConverter(k));
				x = InputConverter(k) - 1;
				
				do
				{
					cout << "Choose y-coordinate that you wish to attack: ";
					cin >> k;
					
					if (InputConverter(k) == 0)
						cout << endl << "Invalid input. Please try again." << endl;
				} while(!InputConverter(k));
				y = InputConverter(k) - 1;
				
				if (gameBoard[x][y] != ".")
					cout << endl << "The coordinate is no longer used." << endl;
				else
				{
					int count = 0;
					cout << "Attacking the following coordinate (X: " << x + 1 << " Y: " << y + 1 << ")..." << endl;
					for (int i = 0; i < col; i++)
					{
						for (int j = 0; j < row; j++)
						{
							if (gameBoard[i][j] == "*")
								count++;
						}
					}
					count = (shipAmount * shipSize) - count - 1;
					if (enemyBoard[x][y] == "E")
						cout << endl << "Nice Shot!! " << count << " ships left!"<< endl;
					else if (enemyBoard[x][y] == ".")
						cout << endl << "BOHOO, you missed." << endl;
						
					cout << endl;
					system("pause");
					enemyBoard[x][y] == "E" ? gameBoard[x][y] = "*" : gameBoard[x][y] = "o"; // if ? then : else ;
					break;
				}
			} while(true);
			
			if (WinChecker(gameBoard))
			{
				winner = "player";
				score++;
				break;
			}	

			do
			{
				x = rand() % 5;
				y = rand() % 5;
				if (playerBoard[x][y] == "P")
				{
					hit = true;
					break;
				}
				else if (playerBoard[x][y] == ".")
				{
					hit = false;
					break;
				}
			} while(true);
			playerBoard[x][y] == "P" ? playerBoard[x][y] = "*" : playerBoard[x][y] = "o";
			
			if (WinChecker(playerBoard))
			{
				winner = "foe";
				break;
			}
		}
		
		system("cls");
		DisplayTitle();
		game++;
		if (winner == "player")
			cout << "GG, you have won the game! Your score is " << score << " and you have played " << game << " games in total." << endl;
		else if (winner == "foe")
			cout << "GG, Putang Ina, you have been defeated. Your score is " << score << " and you have played " << game << " games in total." << endl;
			
		cout << endl;
		cout << "Do you want to play again? (y): ";
		cin >> k;
		if ((k == "Y") || (k == "y"))
			continue;
		else
			mainExit = true;
	} while(!mainExit);

	system("pause");
	return 0;
}

int InputConverter(string k)
{
	if (k == "1")
		return 1;
	else if (k == "2")
		return 2;
	else if (k == "3")
		return 3;
	else if (k == "4")
		return 4;
	else if (k == "5")
		return 5;
	else
		return 0;
}

void DisplayTitle()
{	
	cout << "=========================" << endl;
	cout << "||                     ||" << endl;
	cout << "||      Battleship     ||" << endl;
	cout << "||                     ||" << endl;
	cout << "=========================" << endl;
	cout << endl;
}

int Deploy(int mode, int x, int y)
{
	string k;
	do
	{
		switch(mode)
		{
			case 0:
				cout << "X-coordinate: ";
				break;
			case 1:
				cout << "X-coordinate: " << x + 1 << endl << "Y-coordinate: ";
				break;
			case 2:
				cout << "X-coordinate: " << x + 1 << endl << "Y-coordinate: " << y + 1 << endl << "Orientation: ";
				break;
		}
		cin >> k;
		
		if ((mode < 2) && (InputConverter(k) != 0))
			break;
		else if (mode == 2)
		{
			if (k == "0")
				return 0;
			else if (k == "1")
				return 1;
			else
				return -1;
		}
		else
			cout << endl << "Invalid input. Please try again." << endl;
	} while(true);
	return InputConverter(k) - 1;
}

bool WinChecker(string board[][col])
{
	int counter = 0;
	for(int i = 0; i < col; i++)
	{
		for(int j = 0; j < row; j++)
		{
			if (board[i][j] == "*")
				counter++;
		}
	}
	if (counter == (shipAmount * shipSize))
		return true;
	else
		return false;
}

void InitBoard(string board[][col])
{
	for (int i = 0; i < col; i++)
	{
		for (int j = 0; j < row; j++)
		{
			board[j][i] = ".";
		}
	}
}

void DisplayBoard(string board[][col])
{
	cout << "  ";
	
	for (int i = 0; i < row; i++)
	{
		if (i < 9)
			cout << " " << i + 1 << "|";
		else
			cout << i + 1 << "|";
	}
	
	cout << endl;
	
	for (int i = 0; i < col; i++)
	{
		if (i < 9)
			cout << " " << i + 1;
		else
			cout << i + 1;
		
		for (int j = 0; j < row; j++)
		{
			cout << " " << board[j][i] << "|";
		}
		
		cout << endl;
	}
}

bool IsAvailable(string type, int orientation, int x, int y)
{
	for(int i = 0; i < shipAmount; i++)
	{
		switch(orientation)
		{
			case 0:
			{
				for(int j = 0; j < shipSize; j++)
				{
					if (((type == "player") && (playerBoard[x + j][y] != ".")) || ((type == "foe") && (enemyBoard[x + j][y] != ".")))
						return false;
				}
				return true;
			}
			case 1:
			{
				for(int k = 0; k < shipSize; k++)
				{
					if (((type == "player") && (playerBoard[x][y + k] != ".")) || ((type == "foe") && (enemyBoard[x][y + k] != ".")))
						return false;
				}
				return true;
			}
		}
	}
}

void InitEnemyShips(int amount, int size)
{
	for(int i = 0; i < amount; i++)
	{
		int x = 0;
		int y = 0;
		int orientation;
		
		do
		{
			orientation = rand() % 2;
			if (orientation == 0)
			{
				x = rand() % (row - size);
				y = rand() % col;
			}
			else if (orientation == 1)
			{
				x = rand() % row;
				y = rand() % (col - size);
			}
		}
		while(!IsAvailable("foe", orientation, x, y));
				
		for (int j = 0; j < size; j++)
		{
			//! Horizontal orientation
			if (orientation == 0)
			{
				enemyBoard[x + j][y] = "E";
			}
			//! Vertical orientation
			else if (orientation == 1)
			{
				enemyBoard[x][y + j] = "E";
			}
		}
	}
}

void OrientationPos()
{
	int x = 0, y = 0, orientation = -1;
	for(int i = shipAmount; i > 0; i--)
	{
		for(int j = 0; j < 3; j++)
			{
				system("cls");
				DisplayTitle();
				DisplayBoard(playerBoard);
				cout << endl;
				cout << "Where would you like to place your ship and its orientation? (Horizontal-right: 0, Vertical-downwards: 1)" << endl;
				cout << "Ships to deploy: " << i << endl;
				
				switch (j)
				{
					case 0:
						x = Deploy(j, 0, 0);
						break;
					case 1:
						y = Deploy(j, x, 0);
						break;
					case 2:
						do
						{
						orientation = Deploy(j, x, y);
						if (orientation == -1)
							cout << endl << "Invalid input. Please try again." << endl;
						else
							break;
						} while(true);
						break;
				}
			}
				
			if ((orientation == 0) && (x > (col - shipSize)) ||
				(orientation == 1) && (y > (row - shipSize)) ||
				!IsAvailable("player", orientation, x, y))
			{
				cout << endl << "Wrong input. Please try again." << endl;
				system("pause");
				i++;
			}
			else
			{
				for(int l = 0; l < shipSize; l++)
				{
					if (orientation == 0)
						playerBoard[x + l][y] = "P";
					else if (orientation == 1)
						playerBoard[x][y + l] = "P";
				}
			}
	}

}
