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
    string fromData;
    if (inputFile.is_open()) 
    {
        if (is_empty(inputFile)) 
        {
            cout << "Input file is empty" << endl;
            return;
        }
        inputFile.seekg(0, inputFile.end);
        size_t length = inputFile.tellg();
        inputFile.seekg(0, inputFile.beg);
        fromData.resize(length);

        //std::cout << "Reading " << length << " characters... ";
        // read data as a block:
        inputFile.read((char*)fromData.c_str(), length);
    }
    inputFile.close();
    ofstream outputFile;
    outputFile.open(toInfo, ofstream::out | ofstream::trunc);
    if (outputFile.is_open()) 
    {
        Archive archive;
        string toData;
        archive.LZWCompress(fromData, toData);
        outputFile.write(toData.c_str(), toData.length());
    }
    cout << "Archived successfully!" << endl;
    outputFile.close();
}

void FileArchive::Decompress(const string& fromInfo, const string& toInfo) 
{
    ifstream inputFile(fromInfo);
    string fromData;
    if (inputFile.is_open())
    {
        if (is_empty(inputFile))
        {
            cout << "Input file is empty" << endl;
            return;
        }
        inputFile.seekg(0, inputFile.end);
        size_t length = inputFile.tellg();
        inputFile.seekg(0, inputFile.beg);
        fromData.resize(length);
        inputFile.read((char*)fromData.c_str(), length);
    }
    inputFile.close();
    ofstream outputFile;
    outputFile.open(toInfo, ofstream::out | ofstream::trunc);
    if (outputFile.is_open())
    {
        Archive archive;
        string toData;
        archive.LZWDecompress(fromData, toData);
        outputFile.write(toData.c_str(), toData.length());
        cout << "Unpacked successfully!" << endl;
    }
    outputFile.close();
}

