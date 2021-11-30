#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <iomanip>

using namespace std;

const int GRID_SIZE = 10;
const int SHIP_SIZE = 5;

enum cellType {EMPTY, SHIP, MISSED, HIT};
enum modeType {DEMO, SILENT, NORMAL};

void initializeGrid (cellType lGrid[][GRID_SIZE]);
void printGrid (cellType lGrid[][GRID_SIZE], modeType mode);
bool gameOver (cellType lGrid[][GRID_SIZE]);
void checkPlay (cellType lGrid[][GRID_SIZE], int x, int y);
void placeBattleShip (cellType lGrid[][GRID_SIZE]);
void playGame (cellType lGrid[][GRID_SIZE], modeType mode);

int main (int argc, char *argv[])
{
	srand(time(NULL));
	string str = " ";

	if (argc == 1)
	{
		modeType mode = NORMAL;
		cellType grid[GRID_SIZE][GRID_SIZE];
		initializeGrid(grid);
		placeBattleShip(grid);
		printGrid(grid, mode);
		playGame(grid, mode);
	}
	
	if (argc == 2)
	{
		for (int i = 1; i < argc; i++)
		{
			str = argv[i];
			if (str == "demo") //check to see if user enters demo
			{
				cellType grid[GRID_SIZE][GRID_SIZE];
				modeType mode = DEMO;
				initializeGrid(grid);
				placeBattleShip(grid);
				printGrid(grid, mode);
				playGame(grid, mode);
			}

			if (str == "normal")//check to see if user enters normal
			{
				cellType grid[GRID_SIZE][GRID_SIZE];
				modeType mode = NORMAL;
				initializeGrid(grid);
				placeBattleShip(grid);
				printGrid(grid, mode);
				playGame(grid, mode);
			}

			if (str == "silent")//check to see if the user enters silent
			{
				cellType grid[GRID_SIZE][GRID_SIZE];
				modeType mode = SILENT;
				initializeGrid(grid);
				placeBattleShip(grid);
				printGrid(grid, mode);
				playGame(grid, mode);
			}

			else// if user enters something else, the mode is kept normal
			{
				cellType grid[GRID_SIZE][GRID_SIZE];
				modeType mode = NORMAL;
				initializeGrid(grid);
				placeBattleShip(grid);
				printGrid(grid, mode);
				playGame(grid, mode);
			}
		}
	}

	if (argc > 2)//if the user passes more than 2 arguments, the mode will be kept to normal
	{
		cellType grid[GRID_SIZE][GRID_SIZE];
		modeType mode = NORMAL;
		initializeGrid(grid);
		placeBattleShip(grid);
		printGrid(grid, mode);
		playGame(grid, mode);
	}
}

void initializeGrid (cellType lGrid[][GRID_SIZE])
{
	for (int i = 0; i < GRID_SIZE; i++)
	{
		for (int j = 0; j < GRID_SIZE; j++)
		{
			lGrid[i][j] = EMPTY; //set all locations on the grid to empty
		}
	}			
}

void printGrid (cellType lGrid[][GRID_SIZE], modeType mode)
{
	int k = 0;
	int l = 0;
	switch (mode)
	{
		case SILENT: //silent will not print the grud
			return;
			break;
		case NORMAL: //will print the grid with the hidden ship locations
			cout << "\033[2J\033[1;1H" << endl;
			cout << " ";
			for (int i = 0; i < GRID_SIZE; i++)
			{
				if (i < 10)
				{
					cout << " " << setw(1) << l++ << " ";
				}

				if (i >= 10)
				{
					cout << setw(1) << l++ << " ";
				}
			}
			
			for (int i = 0; i < GRID_SIZE; i++)
			{
				for (int j = 0; j < GRID_SIZE; j++)
				{	
					if (j % GRID_SIZE == 0)
					{
						cout << endl;
						cout << k++;
					}
	
					if ((lGrid[i][j] == EMPTY))
					{
						cout << " - ";
					}
					else if ((lGrid[i][j] == SHIP))
					{
						cout << " - ";
					}
					else if ((lGrid[i][j] == MISSED))
					{
						cout << " m ";
					}
					else if ((lGrid[i][j] == HIT))
					{
						cout << " x ";
					}
				}
			}
			cout << endl;
			break;

		case DEMO: //will print the grid with the ship locations being shown
			cout << "\033[2J\033[1;1H" << endl;
			cout << " ";
			for (int i = 0; i < GRID_SIZE; i++)
			{
				if (i < 10)
				{
					cout << " " << setw(1) << l++ << " ";
				}

				if (i >= 10)
				{
					cout << setw(1) << l++ << " ";
				}
			}
			for (int i = 0; i < GRID_SIZE; i++)
			{
				for (int j = 0; j < GRID_SIZE; j++)
				{
					if (j % GRID_SIZE == 0)
					{
						cout << endl;
						cout << k++;
					}
					if ((lGrid[i][j] == EMPTY))
					{
						cout << " - ";
					}
					else if ((lGrid[i][j] == SHIP))
					{
						cout << " s ";
					}
					else if ((lGrid[i][j] == MISSED))
					{
						cout << " m ";
					}
					else if ((lGrid[i][j] == HIT))
					{
						cout << " x ";
					}
				}
			}
			cout << endl;
			break;	
		default:
			break;
	}
}

bool gameOver (cellType lGrid[][GRID_SIZE])
{
	bool GAME = false;//we will set the bool variable to false everytime the function is called
	for (int i = 0; i < GRID_SIZE; i++)
	{
		for (int j = 0; j < GRID_SIZE; j++)
		{
			if (lGrid[i][j] != SHIP)
			{
				GAME = true; //true will end the program, telling the user he/she has won
			}
			else if (lGrid[i][j] == SHIP)
			{
				GAME = false; //false will make the program continue until every ship location is found
				return GAME;
			}
		}
	}
	return GAME;
}

void checkPlay (cellType lGrid[][GRID_SIZE], int x, int y)
{
	if (lGrid[x][y] == EMPTY) //will check the users grid point, and if it is a miss, it will display "MISSED"
	{
		lGrid[x][y] = MISSED;
		cout << "MISSED" << endl;
	}
	else if (lGrid[x][y] == SHIP)
	{
		lGrid[x][y] = HIT;
		cout << "HIT" << endl;//display "HIT", meaning that the user has hit a part of the ship
	}
}

void placeBattleShip(cellType lGrid[][GRID_SIZE])
{
	int number = 0;
	int midNumber = 0;

	number = rand() % (GRID_SIZE - 1) + 1;//random number generator to see from 1 to GRID_SIZE

	if (number == ((GRID_SIZE/2) - 1) or number == ((GRID_SIZE/2)))
	{
		midNumber = rand() % 4;//this will check if the ship is placed up, down, left, or right on the grid

		if (midNumber == 0)
		{
			for (int i = 0; i < SHIP_SIZE; i++)
			{
				lGrid[i][number] = SHIP;
			}
		}
		else if (midNumber == 1)
		{
			for (int i = number; i < SHIP_SIZE + number; i++)
			{
				lGrid[i][number] = SHIP;
			}
		}
		else if (midNumber == 2)
		{
			for (int i = number; i < SHIP_SIZE + number; i++)
			{
				lGrid[number][i] = SHIP;
			}
		}
		else if (midNumber == 3)
		{
			for (int i = 0; i < SHIP_SIZE; i++)
			{
				lGrid[number][i] = SHIP;
			}
		}
	}			

	if (number == GRID_SIZE - GRID_SIZE)
	{
		for (int i = 0; i < SHIP_SIZE; i++)
		{
			lGrid[i][number] = SHIP;
		}
	}

	if (number == (GRID_SIZE - (GRID_SIZE - 1)))
	{
		for (int i = number; i < number + SHIP_SIZE; i++)
		{
			lGrid[i][number] = SHIP;
		}
	}

	if (number == (GRID_SIZE - (GRID_SIZE - 2)))
	{
		for (int i = number; i < number + SHIP_SIZE; i++)
		{
			lGrid[i][number] = SHIP;
		}
	}

	if (number == (GRID_SIZE - (GRID_SIZE - 3)))
	{
		for (int i = number; i < number + SHIP_SIZE; i++)
		{
			lGrid[i][number] = SHIP;
		}
	}

	if (number == ((GRID_SIZE/2) + 1))
	{
		for (int i = number; i > number - SHIP_SIZE; i--)
		{
			lGrid[number][i] = SHIP;
		}
	}

	if (number == ((GRID_SIZE/2) + 2))
	{
		for (int i = number; i > number - SHIP_SIZE; i--)
		{
			lGrid[number][i] = SHIP;
		}
	}

	if (number == ((GRID_SIZE/2) + 3))
	{
		for (int i = number; i > number - SHIP_SIZE; i--)
		{
			lGrid[number][i] = SHIP;
		}
	}

	if (number == ((GRID_SIZE/2) + 4)) 
	{
		for (int i = number; i > number - SHIP_SIZE; i--)
		{
			lGrid[number][i] = SHIP;
		}
	}

	else 
	{
		for (int i = 0; i > SHIP_SIZE; i++)
		{
			lGrid[number][i] = SHIP;
		}
	}

}

void playGame(cellType lGrid[][GRID_SIZE], modeType mode)//this function will call other functions to check the grid and the points
{
	int a, b;

	if (mode == SILENT) //mode silent will not display the grid, but will tell the user if he/she has hit or missed the ship
	{
		cout << "Please enter a Grid Point: ";
		cin >> a >> b;

		while (cin.fail())//clear the stream and ask again for a grid point
		{
			cin.clear();
			cin.ignore(100, '\n');
			cout << "Error: Please enter a Grid Point: " << endl;
			cin >> a >> b;
		}

		checkPlay(lGrid, a, b);
		gameOver(lGrid);

		while (gameOver(lGrid) == false)//while the gameOver functions returns false every time its called, the game will 
		{				//continue
			cout << "Please enter a Grid Point: ";
			cin >> a >> b;
			while (cin.fail())
			{
				cin.clear();
				cin.ignore(100, '\n');
				cout << "Error: Please enter a Grid Point: " << endl;
				cin >> a >> b;
			}
			checkPlay(lGrid, a, b);
			gameOver(lGrid);

			if (gameOver(lGrid) == true)//if gameOver returns true, the game is over and the uesr wins
			{
				cout << "You sunk my Battleship!" << endl;
				exit(0);
			}
		}
	}

	if (mode != SILENT)//if mode is Normal or in Demo
	{
		
	cout << "Please enter a Grid Point: ";
	cin >> a >> b;
	
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(100, '\n');
		cout << "Error: Please enter a Grid Point: " << endl;
		cin >> a >> b;
	}
	
		checkPlay(lGrid, a, b);
		printGrid(lGrid, mode);
		gameOver(lGrid);
		
		while (gameOver(lGrid) == false)//check to see if gameOver returns false to keep the game going
		{
			cout << "Please enter a Grid Point: ";
			cin >> a >> b;
	
			while (cin.fail())
			{
				cin.clear();
				cin.ignore(100, '\n');
				cout << "Error: Please enter a Grid Point: " << endl;
				cin >> a >> b;
			}
	
			checkPlay(lGrid, a, b);
			printGrid(lGrid, mode);
			gameOver(lGrid);
			
			if (gameOver(lGrid) == true)//if gameOver returns true, the game is over and the user wins
			{
				cout << "You sunk my Battleship! " << endl;
				exit(0);//will exit the program
			}
		}

	}
}