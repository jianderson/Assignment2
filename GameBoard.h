#include <iostream>

using namespace std;

class GameBoard
{
public:
    //declares the GameBoard constructors
    GameBoard(int rows, int columns, float density, int gameMode);

    GameBoard(int rows, int columns, int gameMode, string prevGen);

    GameBoard(string userFile, int gameMode);
    //declares the GameBoard destructor
    ~GameBoard();


//declare methods for GameBoard
    void MakeGrid();
    string getString();
    int getPopulation(string inputString);
    int NeighborCount(int x, int y);
    string StringMaker();
    void GridInitialization(string s);
    string GetNextGen();
    bool isNeighbor(int x, int y, int centerX, int centerY);
    bool isOnBoarder(int x, int y);

//declare variables for GameBoards
    int rows;
    int columns;
    float density;
    string popString;
    float population;
    int gameMode;
    int popCount;

//declare the myGrid pointer
    char** myGrid;

};
