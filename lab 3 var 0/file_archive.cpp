#include "file_archive.h"
#include <fstream>
#include <iostream>

using namespace std;

bool FileArchive::is_empty(ifstream& pFile)
{
    return pFile.peek() == ifstream::traits_type::eof();
}

void FileArchive::Compress(const string &fromInfo, const string &toInfo)
{
    ifstream inputFile(fromInfo);
    if (inputFile.is_open())
    {
        if (is_empty(inputFile))
        {
            cout << "Input file is empty" << endl;
            return;
        }
    }
    ofstream outputFile;

    if (inputFile.is_open())
    {
        outputFile.open(toInfo, ofstream::out | ofstream::trunc);
        if (outputFile.is_open())
        {
            while (true)
            {
                string line;
                string result;
                getline(inputFile, line);
                Archive archive;
                archive.Compress(line, result);
                outputFile << result << endl;
                if (inputFile.eof()) {
                    break;
                }
            }
        }
        cout << "Archived successfully!" << endl;
    }
    else {
        cout << "Cannot open the file" << endl;
    }
}

void FileArchive::Decompress(const string& fromInfo, const string& toInfo)
{
    ifstream inputFile(fromInfo);
    if (inputFile.is_open())
    {
        if (is_empty(inputFile))
        {
            cout << "Input file is empty" << endl;
            return;
        }
    }
    ofstream outputFile;

    if (inputFile.is_open())
    {
        outputFile.open(toInfo, ofstream::out | ofstream::trunc);
        if (outputFile.is_open())
        {
            while (true)
            {
                string line;
                string result;
                getline(inputFile, line);
                Archive archive;
                archive.Decompress(line, result);
                outputFile << result << endl;
                if (inputFile.eof()) {
                    break;
                }
            }
        }
        cout << "Unpacked successfully!" << endl;
    }
    else {
        cout << "Cannot open the file" << endl;
    }
}

