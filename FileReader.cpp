#include "FileReader.h"

using namespace std;
//constructor
FileReader::FileReader(string userFile)
{
    ReadFile(userFile);
}
//method used to read the user file
void FileReader::ReadFile(string userFile)
{
    //declare stream object
    ifstream fileStream;
    //open user file through file streamer
    fileStream.open(userFile);
//checks if userfile fails to open
    if(!fileStream)
    {
        throw runtime_error("Could not open " + userFile);
    }

//counts number of lines
string line;
int lineCount = 0;
//iterate through each line of userfile
while(getline(fileStream, line))
{
    ++lineCount;
}

fileStream.clear();
//resets you back to the top so you can call the line again
fileStream.seekg(0);
//making array to hold all the lines for the userFile
string* fileLines = new string[lineCount];
//place each line into the array
int counter = 0;
while(getline(fileStream, line))
{
    fileLines[counter] = line;
    ++counter;
}
//resets file stream to position 0
fileStream.clear();
fileStream.seekg(0);

fileStream.close();

//Error checking - making sure the first two lines are nummbers representing the bumber of rows and columns
//parsing the first two lines( rows and columns) into integers
//lines after 1 and 2, followed by the grid

//parsing first line (which represnets the rows) into an integers
this-> rows = stoi((string)fileLines[0]);

//parsing he second line (representing columns)

this -> columns = stoi((string)fileLines[1]);
//check file layout
if(this -> rows != lineCount - 2 || isWidthCorrect(fileLines, lineCount, columns) == false)
{
    throw runtime_error("This file does not have a correct layout. ");
}


int numCells = 0;
int numPopCells = 0;
//create a fileGridString, and adds each element to the string
for(int i = 2; i < lineCount; ++i)
{
    for(int j = 0; j < fileLines[i].length(); ++j)
    {
        numCells++;
        fileGridString += fileLines[i][j];
        if(fileLines[i][j] == 'X')
        {
            ++numPopCells;
        }
    }
//check to make sure the grid part of the file only contains a - or a X
    for(int i = 0; i < fileGridString.length(); ++i)
    {
        if(fileGridString[i] == 'X' || fileGridString[i] == '-')
        {

        }
        else
        {
            throw runtime_error("The file's grid should only contain '-' and/or 'X'!!");
        }
    }

}



}
//method to check and see if the userFile width is accurate with the grid in the file
bool FileReader::isWidthCorrect(string*& fileLines,int lineCount,int columns)
{
    for(int i = 2; i < lineCount; ++i)
    {
        if(fileLines[i].length() != columns)
            return false;
    }
    return true;
}

//void method to output to file if the user chooses to do so
void FileReader::WriteToFile(string userFile, string strToWrite)


{
    //declaring output stream object and opening output file
    ofstream outFileStream;
    outFileStream.open(userFile, ofstream::app);
    if(!outFileStream)
    //throwing runtime_error if the file can't be found
        throw runtime_error("Cannot open output file.");
    outFileStream << strToWrite << endl;
    outFileStream.close();

}
