#include <iostream>
#include "archive.h"
#include "file_archive.h"
#include <vector>
#include "iarchivator.h"

using namespace std;

int main(/*int argc, char* argv[]*/)
{
	FileArchive file( ArchivatorFactory::ArchivatorType::LZW);
    file.Compress("/Users/user/Desktop/test/in.txt", "/Users/user/Desktop/test/out.bin");
   // file.Decompress("/Users/user/Desktop/test/out.bin", "/Users/user/Desktop/test/out2.txt");
//	file.Compress("1.jpg", "encoded1.txt");
//	file.Decompress("encoded1.txt", "2.jpg");
	return 0;

}