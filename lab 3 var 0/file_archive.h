#pragma once

#include <string>
#include <fstream>
#include "archive.h"

using namespace std;

class FileArchive : public Archive{
public:
    void Compress(const string &fromInfo, const string &toInfo);
    void Decompress(const string& fromInfo, string& toInfo);
    bool is_empty(std::ifstream& pFile);


};