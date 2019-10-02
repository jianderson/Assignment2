#include <iostream>
#include "GameBoard.h"
#include <time.h>
#include "FileReader.h"
#include <chrono> //required to pause between generations
#include <thread> //to pause/ stop threads

using namespace std::this_thread;
using namespace std::chrono;
using namespace std;
bool KeepRunning(GameBoard*& curGen, GameBoard*& nextGen);

//used to count stabilized generations
int stabGen = 0;
//array to hold the last three generation strings
string prevGenStrings[3];


int main()
{
    //this line is needed to make sure the numbers are actually random
srand(time(NULL));
int height = 0;
int width = 0;
float density = 0.0;
int gameMode = 0;
string userFile = "";

cout << "Hello! Welcome to the game of life!!!" << endl;

cout << "Would you like to provide a map file of your world or be given a random assignment? " << endl;
cout << "Type 1 for map file and 2 for random!" << endl;

int answerMapRandom;
cin >> answerMapRandom;


GameBoard* curGen;

if(answerMapRandom == 1) //if the user provides a map file
{

    cout << "Okay, enter the name of the file you would like to use: " << endl;
    cin >> userFile;

    cout << "What game mode would you like to play? (1 for Classic Mode, 2 for Doughnut Mode, and 3 for Mirror Mode): " << endl;
    cin >> gameMode;
    //check to see if the gamemode is valid
    if(gameMode >= 1 && gameMode <= 3)
    {

    }
    else
    {
        cout << "You entered an invalid game mode! No! You cannot play!" << endl;
        return 1;
    }
    try
    {
    curGen = new GameBoard(userFile, gameMode);
    }
    catch(runtime_error e) //catch an error to see if the file cant be opened
    {
        cout << "The file you entered does not exist of could not be opened. You cannot play!!" << endl;
        return 1;
    }
    height = curGen -> rows;
    width = curGen -> columns;




}
//if the user wants a random assignment
else if(answerMapRandom == 2)
{
        cout << "Okay great! Enter an integer for the number of rows you want: " << endl;
        cin >> height;
//if height is invalid
        if(height < 1)
        {
            cout << "You entered an invalid number of rows. You need to have at least 1 row. You cannot play!" << endl;
            return 1;
        }
//now get width
        cout << "Nice okay! Enter an integer for the number of columns you want: " << endl;
        cin >> width;
//if width is invalid
        if(width < 1)
        {
            cout << "You entered an invalid number of columns. You need to have at least 1 column. You cannot play!" << endl;
            return 1;
        }
//get density
        cout << "Okay now we need a decimal value between 0 and 1 that will act as your initial population density: " << endl;
        cin >> density;
//check if density is valid
        if(density < 0 || density > 1)
        {
            cout << "You entered an invalid density. It has to be a decimal number between 0 and 1. You cannot play!" << endl;
            return 1;
        }
//get gamemode
        cout << "Lastly, what game mode would you like to play? (1 for Classic Mode, 2 for Doughnut Mode, and 3 for Mirror Mode): " << endl;
        cin >> gameMode;
//check if game mode is valid
        if(gameMode > 3 || gameMode < 1)
        {
            cout << "You entered an invalid Game Mode. You need to choose a 1, a 2 or a 3. You cannot play!" << endl;
            return 1;
        }

        curGen = new GameBoard(height, width, density, gameMode);
}
else
{
    cout << "No! That's WRONG!!!!!! YOU DIDN'T DO WHAT I SAID! You cannot play." << endl;
    return 1;

}
//give user options for results
cout << "You have a few options on how to get your game results!" << endl;
cout << "Enter 1 for a brief pause between your generations as they print out." << endl;
cout << "Enter 2 if you would like your generations to print out one by one by pressing the enter key on your keyboard. " << endl;
cout << "Enter 3 if you would like your results to be printed to an output file." << endl;

int outputResultsResponseNum = 0;
cin >> outputResultsResponseNum;
//responses for results
string outputFileName;
if(outputResultsResponseNum == 3)
{

    cout << " Okay! What do you want your results file to be named: " << endl;
    cin >> outputFileName;
}

// print out initial generation for results 1
if(outputResultsResponseNum == 1)
{
    string curGenOutputStr = curGen->getString();

    cout << "Generation 0" << endl;
    cout << "PopCount: " << to_string(curGen -> getPopulation(curGenOutputStr)) << endl;
    cout << curGenOutputStr << endl;
    sleep_for(seconds(1));
}
//initial generation for results 2
else if(outputResultsResponseNum == 2)
{
    string curGenOutputStr = curGen->getString();
    cout << "Generation 0" << endl;
    cout << "PopCount: " << to_string(curGen -> getPopulation(curGenOutputStr)) << endl;
    cout << curGenOutputStr << endl;

    cout << "Press enter to print the next generation." << endl;
    cin.get();

}
else if(outputResultsResponseNum == 3)
{
    string curGenOutputSt = curGen -> getString();
    string tempOut = "Generation 0: \n";
    FileReader::WriteToFile(outputFileName, tempOut);
    tempOut = "Population Count: " + to_string(curGen -> getPopulation(curGenOutputSt)) + "\n";
    FileReader::WriteToFile(outputFileName, tempOut);
    tempOut =  curGen -> getString() + "\n";
    FileReader::WriteToFile(outputFileName, tempOut);

}
else
{
    cout << "You did not enter a 1, 2, or 3. You cannot play!" << endl;
    return 1;
}


int genCounter = 0;
bool stillRunning = true;
cin.get(); //clears the cin buffer
//while loop for the generations
while(stillRunning)
{
    string nextGenStr = curGen->GetNextGen();

    GameBoard* nextGen = new GameBoard(height, width, gameMode, nextGenStr);


    string outString = nextGen->getString();
    cout << "Generation " << genCounter + 1 << endl;
//generation 2+ for output 1
if(outputResultsResponseNum == 1)
{
    cout << "PopCount: " << nextGen->popCount << endl;
    cout << outString << endl;

    sleep_for(seconds(1));//will wait before printing the next one
}
//gen 2+ for ouput 2
else if(outputResultsResponseNum == 2)
{
    cout << "PopCount: " << nextGen->popCount << endl;

    cout << outString << endl;
    cout << "Press enter to print the next generation." << endl;
    cin.get(); //clears the cin buffer

}
//gen 2+ for output 3
else if(outputResultsResponseNum == 3)
{

    string tempOut = "Generation " + to_string((genCounter + 1)) + "\n";
    FileReader::WriteToFile(outputFileName, tempOut);
    tempOut = "Population Count: " + to_string(nextGen -> getPopulation(outString)) + "\n";
    FileReader::WriteToFile(outputFileName, tempOut);
    FileReader::WriteToFile(outputFileName, outString);

}
else
{//error checking
    cout << "You did not enter a 1, 2, or 3. You cannot play!" << endl;
    return 1;
}
    prevGenStrings[genCounter % 3] = curGen->getString();
    prevGenStrings[(genCounter + 1) % 3] = nextGen->getString();

//run keep running method to see if the program should end
    stillRunning = KeepRunning(curGen, nextGen);

    curGen -> ~GameBoard();

    curGen = nextGen;


    genCounter++;

}
return 0;
}


//keep running method to use in the while loop for the main method
bool KeepRunning(GameBoard*& curGen, GameBoard*& nextGen)
{
    if(nextGen->popCount == 0)
        return false;

    string curGenString = curGen->getString();
    string nextGenString = nextGen->getString();
    bool areTheyEqual = true;
    //check for repeated generations
    for(int i = 0; i < curGenString.length(); ++i)
    {
        if(curGenString[i] != nextGenString[i])
        {
            areTheyEqual = false;
            break;
        }
    }
if(areTheyEqual == true)
{
    return false;
}
if(curGen->popCount == nextGen->popCount)
{
    stabGen++;
    if(stabGen > 15)
        return false;
}
else
{
    stabGen = 0;
}
//uses the array of previous generations and cheaks for osciliating generations
for(int i = 0; i < 3; ++i)
{
    for (int j = 0; j < 3; ++j)
    {
        if (i == j)
            continue;
        if(prevGenStrings[i] == prevGenStrings[j])
            return false;
    }
}




return true;
}
