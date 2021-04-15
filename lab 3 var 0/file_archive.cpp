#include "file_archive.h"
#include <fstream>
#include <iostream>

using namespace std;

bool FileArchive::is_empty(std::ifstream& pFile){
    return pFile.peek() == ifstream::traits_type::eof();
}
void FileArchive::Compress(const string &fromInfo, const string &toInfo) {
    ifstream inputFile(fromInfo);
    if (inputFile.is_open()) {
        if (is_empty(inputFile)) {
            cout << "Input file is empty" << endl;
            return;
        }
    }
    ofstream outputFile;
    outputFile.open(toInfo, ofstream::out | ofstream::trunc);
    outputFile.close();


    if (inputFile.is_open()) {
        outputFile.open(toInfo);
        if (outputFile.is_open()) {
            while (true) {
                string line;
                string result;
                getline(inputFile, line);

                int i = 1;
                int count = 1;
                char t = line[0];
                while (i < line.length()) {
                    if (t == line[i] && count <= 255) {
                        count++;
                    } else if (t == line[i] && count > 255) {
                        result += t;
                        result += char(255);
                        count = 1;
                    } else if (t != line[i]) {
                        result += t;
                        result += char(count);
                        count = 1;
                        t = line[i];
                    }
                    i++;
                }
                result += t;
                result += char(count);
                outputFile << result << endl;
                if (inputFile.eof()) {
                    break;
                }
            }
        }

    } else {
        cout << "Cannot open the file" << endl;
    }
   cout << "Archived successfully!" << endl;
}


