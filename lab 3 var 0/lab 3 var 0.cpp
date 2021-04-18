#include <iostream>
#include "file_archive.h"
#include "iarchivator.h"

using namespace std;



int main(int argc, char* argv[])
{
    if (argc == 4)
    {
        string action = argv[1];
        string inputFile = argv[2];
        string outputFile = argv[3];
        if (
            ((action == "--compress") || (action == "--decompress"))
            && !inputFile.empty()
            && !outputFile.empty()
            )
        {
            string archivatorType;
            cout << "What solution algorithm would you choose? (type LZW or RLE)" << endl;
            cin >> archivatorType;
            if (archivatorType == "LZW")
            {
                FileArchive file(ArchivatorFactory::ArchivatorType::LZW);
                if (action == "--compress")
                {
                    if (file.Compress(inputFile, outputFile))
                    {
                        cout << "Packed successfully! The result was recorded to file " << outputFile << endl;
                    }
                }
                else if (action == "--decompress")
                {
                    if (file.Decompress(inputFile, outputFile))
                    {
                        cout << "Unpacked successfully! The result was recorded to file " << outputFile << endl;
                    }
                }
                return 0;
            }
            else if (archivatorType == "RLE")
            {
                FileArchive file(ArchivatorFactory::ArchivatorType::RLE);
                {
                    file.Compress(inputFile, outputFile);
                    if (action == "--compress")
                    {
                        file.Compress(inputFile, outputFile);
                        cout << "Packed successfully! The result was recorded to file " << outputFile << endl;
                        return 0;

                    }
                    else if (action == "--decompress")
                    {
                        file.Decompress(inputFile, outputFile);
                        cout << "Unpacked successfully! The result was recorded to file " << outputFile << endl;
                    }
                }
            }
            else
            {
                cout << "The algorithm was entered incorrectly. Closing the program..." << endl;
            }
        }
        else
        {
            cout << "The command was entered incorrectly. Closing the program..." << endl;
        }
    }
    else
    {
        cout << "Some parameters were entered incorrectly. Closing the program..." << endl;
    }
    return 0;
}