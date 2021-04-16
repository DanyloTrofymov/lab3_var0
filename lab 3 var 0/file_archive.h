#pragma once

#include <string>
#include <fstream>
#include "archive.h"

using namespace std;

class FileArchive : public Archive{
public:
    void Compress(const string &fromInfo, const string &toInfo);
    void Decompress(const string& fromInfo, const string& toInfo);
protected:
    bool is_empty(ifstream& pFile);
};