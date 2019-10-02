#include <iostream>
//this is the filestream
#include <fstream>

using namespace std;

class FileReader
{
public:
    //filereader constructor
    FileReader(string userFile);
//filereader methods
    void ReadFile(string userFile);
    bool isWidthCorrect(string*& fileLines, int lineCount, int columns);
    static void WriteToFile(string userFile, string strToWrite);
//filereader variables
    int rows;
    int columns;
    string fileGridString;
};
