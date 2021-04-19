#include "file_archive.h"
#include "archive.h"
#include <iostream>
#include <string>
#include <fstream>
#include <memory>

using namespace std;

FileArchive::FileArchive(ArchivatorFactory::ArchivatorType type)
: archivator(ArchivatorFactory::Get(type))
{}

string FileName(const string& filename){
    return filename;
}
int FileNameSize(const string& filename){
    return filename.length();
}
bool FileArchive::IsEmpty(const string& fileName) const
{
    ifstream pFile(fileName);
    return pFile.peek() == ifstream::traits_type::eof();
}

bool FileArchive::Compress(const string &fromInfo, const string &toInfo) const
{
    string fromData, toData;
    if (ReadFile(fromInfo, fromData))
    {
        return archivator->Compress(fromData, toData) && WriteFile(toInfo, toData);
    }
    return false;
}

bool FileArchive::Decompress(const string& fromInfo, const string& toInfo) const
{
    string fromData, toData;
    if (ReadFile(fromInfo, fromData))
    {
        if(fromData.substr(0, 2) == to_string(FileNameSize(fromInfo))){
            fromData.erase(0,2 + FileNameSize(fromInfo));
        }
        return archivator->Decompress(fromData, toData) && WriteFile(toInfo, toData);
    }
    return false;
}

bool FileArchive::ReadFile(const string& fileName, string& data) const
{

int fileNameSkip = fileName.length()+2;
    ifstream inputFile(fileName, ifstream::binary);
    if(inputFile.good()) 
    {
        if (inputFile.is_open()) 
        {
            if (IsEmpty(fileName)) 
            {
                cout << "file " << fileName << " is empty" << endl;
                return false;
            }

            inputFile.seekg(0, inputFile.end);
            size_t length = inputFile.tellg();
            inputFile.seekg(0, inputFile.beg);
            data.resize(length);


            std::cout << "Reading " << length << " characters... " << endl;
            // read data as a block:
            inputFile.read((char *) data.c_str(), length);
            return true;
        }
         inputFile.close();
    }
    cout << "File does not exist. Closing the program..." << endl;
    return false;
}

bool FileArchive::WriteFile(const string& fileName,  string& data)  const
{
    const string fname = FileNameRecord(fileName);
    data = to_string(FileNameSize(fname)) + fname + data;
    ofstream outputFile;
    outputFile.open(fileName, ofstream::binary);
    if (outputFile.is_open())
    {
        outputFile.write(data.c_str(), data.length());
        return true;
    }
    outputFile.close();
    return false;
}

