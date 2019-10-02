#include <iostream>
#include "GameBoard.h"
//used for shuffling the string representing the grid
#include <algorithm>
#include "FileReader.h"

using namespace std;
//constructor for declaring the first generation grid
GameBoard::GameBoard(int r, int c, float d, int g)
{
    rows = r;
    columns = c;
    density = d;
    gameMode = g;
    myGrid = new char*[rows];
    //call MakeGrid function inside constructor
    MakeGrid();
    //make the grid a string and shuffle it
    string gameBoardString = StringMaker();
    //initialize the grid using the string
    GridInitialization(gameBoardString);
}

//define the GameBoard destructor
GameBoard::~GameBoard()
{
    //iterate through the grid and delte everything
    for(int i = 0; i < rows; ++i)
    {
        delete[] myGrid[i];

    }
    delete[] myGrid;
}
//overloaded constructor to make the grid for the second generation on
GameBoard::GameBoard(int r, int c, int g, string prevGen)
{
    rows = r;
    columns = c;
    gameMode = g;
    //make the grid
    MakeGrid();
    //initialize it
    GridInitialization(prevGen);
    //get the population
    getPopulation(prevGen);
}
//constructor that is used when reading from a file
GameBoard::GameBoard(string userFile, int gameMode)
{
    //double check the gameMode entry was correct
    if(gameMode < 1 || gameMode > 3)
    {
        throw runtime_error("The game mode you entered was invalid. Please only enter one of the following: 1, 2, or 3.");
    }
    //assign the game mode
    this -> gameMode = gameMode;
    //start up the file reader
    FileReader reader(userFile);
    //assign the rows
    rows = reader.rows;
    //assigns the columns
    columns = reader.columns;

    //make the grid
    MakeGrid();
    //initialize it
    GridInitialization(reader.fileGridString);
    //get the population
    getPopulation(reader.fileGridString);
}

//make grid method
void GameBoard::MakeGrid()
{
    //set mygrid equal to the pointer
    myGrid = new char*[rows];
    //set the columns in the rows and then set them to -
    for(int i = 0; i < rows; ++i)
    {
        myGrid[i] = new char[columns];
        for(int j = 0; j < columns; ++j)
        {
            myGrid[i][j] = '-';
        }
    }
}
//method to use the grid to set it into a string
string GameBoard::getString()
{
    //iterate through the rows of the array

    string gridPrintOut = "";
//iterate through grid
    for(int i = 0; i < rows; ++i)
    {
        for(int j = 0; j < columns; ++j)
        {
            gridPrintOut += myGrid[i][j];
        }
        gridPrintOut += "\n";
    }

    return gridPrintOut;

}
//method to make the grid into a string
string GameBoard::StringMaker()
{
    //find total number of cells
    int totalCells = rows * columns;
    //find the population based on the density
    population = density * totalCells;
    //cast to an int
    population = (int)population;
    //find non occupies cells
    int remainingCells = totalCells - population;
    //populate with X
    for( int i = 0; i < population; ++i)
    {
    popString += "X";
    }
    //populate with -
    for(int i = 0; i < remainingCells; ++i)
    {
        popString += "-";
    }
//shuffle it up
    random_shuffle(popString.begin(), popString.end());

    return popString;
}


//method to initialize the grid
void GameBoard::GridInitialization(string popString)
{
    //iterate through and use the string to populate the array by easasing the first index of the string every time
    for(int i = 0; i < rows; ++i)
    {

        for(int j = 0; j < columns; ++j)
        {
            myGrid[i][j] = popString[0];
            popString.erase(0,1);
        }
    }


}
//method to see whether a poind on the grid at those coordinates is a neighbor of another point
bool GameBoard::isNeighbor(int x, int y, int centerX, int centerY)
{
//for gameMode 1
if(gameMode == 1)
{
    if(x < 0)
        return false;
    if(y < 0)
        return false;
    if(x >= rows)
        return false;
    if(y >= columns)
        return false;
    if(myGrid[x][y] == '-')
        return false;
    if(myGrid[x][y] == 'X')
        return true;
}
//for gameMode 2
if(gameMode == 2)
{
    if(isOnBoarder(centerX, centerY))
    {
        if(x < 0)
            x = rows -1;
        else if(x >= rows)
            x = 0;
        if(y < 0)
            y = columns -1;
        else if(y >= columns)
            y = 0;
    }
    if(myGrid[x][y] == 'X')
        return true;

    else
        return false;

}
//for Game mode 3
if(gameMode == 3)
{
    if(isOnBoarder(centerX, centerY))
    {
        if (x < 0)
            x = 0;
        else if(x >= rows)
            x = rows - 1;

        if(y < 0)
            y = 0;
        else if(y >= columns)
            y = columns - 1;
    }

    if(myGrid[x][y] == 'X')
        return true;
    else
        return false;
}

}
//method to see how many occupied neighbors each position on the array has
int GameBoard::NeighborCount(int x, int y)
{
//declare the total number of neighbors
    int totalNeighbors = 0;
//check each position around it by calling the isneighbor method
    if(isNeighbor(x+1, y,x,y))
    {
        totalNeighbors++;
    }

    if(isNeighbor(x-1, y,x,y))
    {
        totalNeighbors++;
    }

    if(isNeighbor(x, y+1,x,y))
    {
        totalNeighbors++;
    }
    if(isNeighbor(x, y-1,x,y))
    {
        totalNeighbors++;
    }
    if(isNeighbor(x+1, y+1,x,y))
    {
        totalNeighbors++;
    }
    if(isNeighbor(x-1, y-1,x,y))
    {
        totalNeighbors++;
    }
    if(isNeighbor(x+1, y-1,x,y))
    {
        totalNeighbors++;
    }
    if(isNeighbor(x-1, y+1,x,y))
    {
        totalNeighbors++;
    }
//return the total neighbors
    return totalNeighbors;

}
//method to get the next generation
string GameBoard::GetNextGen()
{
    string gridString = "";
//populate a string for the next gen
    for(int i = 0; i < rows; ++i)
    {
        for(int j = 0; j < columns; ++j)

        {
            //these are all the rules of the game meaning if it is an X or if it is a - and has a certain number of neighbors
            if(myGrid[i][j] == 'X')
            {
                if(NeighborCount(i,j) == 2)
                {
                    gridString+= "X";
                }
                else if(NeighborCount(i,j) == 3)
                {
                    gridString+= "X";
                }
                else
                {
                    gridString += "-";
                }
            }
            else if(myGrid[i][j] == '-')
            {
                if(NeighborCount(i,j) == 3)
                {
                    gridString += "X";
                }
                else
                {
                    gridString += "-";
                }
            }
        }
    }
    //return the string for the next generation
    return gridString;
}
//this is a method to get the population of a given generation
int GameBoard::getPopulation(string inputString)
{
    //if it is populated with an X add to the counter
    int xCounter = 0;
    for(int i = 0; i < inputString.length(); ++i)
    {
        if(inputString[i] == 'X')
        {
            xCounter++;
        }
    }
    //return the counter
    popCount = xCounter;
    return popCount;

}
//this method checks if the cell is on the parimeter and therefor has different behaviors for different methods
bool GameBoard::isOnBoarder(int x, int y)
{
    //if its on x perimeter
    if (x == 0)
        return true;
    else if(x == (rows-1))
        return true;

//if its on y perimeter
    if (y == 0)
        return true;
    else if(y == (columns - 1))
        return true;


    return false;
}
