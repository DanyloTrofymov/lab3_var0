#include <iostream>
#include "file_archive.h"
#include "iarchivator.h"

using namespace std;

int main(int argc, char* argv[])
{
    if(argc == 4){
    string action = argv[1];
    string inputFile = argv[2];
    string outputFile = argv[3];

    if(
            ((action == "--compress") || (action == "--decompress"))
        && !inputFile.empty()
        && !outputFile.empty()) {
        string archivatorType ;
            cout << "What solution algorithm would you choose? (type LZW or RLE)" << endl;
            cin >> archivatorType;
        if (archivatorType == "LZW") {
            FileArchive file(ArchivatorFactory::ArchivatorType::LZW);
            if (action == "--compress") {
                file.Compress(inputFile, outputFile);
                cout << "Packed successfully! The result was recorded to file "<<outputFile<<endl;
                return 0;
            } else if (action == "--decompress") {
                file.Decompress(inputFile, outputFile);
                cout << "Unpacked successfully! The result was recorded to file "<<outputFile<<endl;
                return 0;
            }
        } else if (archivatorType == "RLE") {
            FileArchive file(ArchivatorFactory::ArchivatorType::RLE);
            {
                file.Compress(inputFile, outputFile);
                if (action == "--compress") {
                    file.Compress(inputFile, outputFile);
                    cout << "Packed successfully! The result was recorded to file "<<outputFile<<endl;
                    return 0;

                } else if (action == "--decompress") {
                    file.Decompress(inputFile, outputFile);
                    cout << "Unpacked successfully! The result was recorded to file "<<outputFile<<endl;
                    return 0;
                }
            }
        }
        else {
            cout << "Archiving method was entered incorrectly. Closing the program..."<< endl;
            return 0;
        }
    }
    } else {
        cout << "Some parameters were entered incorrectly. Closing the program..."<< endl;
        return 0;
    }
//    FileArchive file(ArchivatorFactory::ArchivatorType::LZW);
//    file.Compress("/Users/user/Desktop/test/in.txt" , "/Users/user/Desktop/test/out.bin");
   // file.Decompress("/Users/user/Desktop/test/out.bin", "/Users/user/Desktop/test/out2.txt");
//	file.Compress("1.jpg", "encoded1.txt");
//	file.Decompress("encoded1.txt", "2.jpg");
	return 0;

}