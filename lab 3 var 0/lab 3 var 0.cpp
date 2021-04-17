#include <iostream>
#include "archive.h"
#include "file_archive.h"
#include <vector>

using namespace std;

int main(/*int argc, char* argv[]*/)
{
	FileArchive file( ArchivatorFactory::ArchivatorType::RLE);
	file.Compress("in.txt", "encoded.txt");
	file.Decompress("encoded.txt", "out.txt");
	file.Compress("1.jpg", "encoded1.txt");
	file.Decompress("encoded1.txt", "2.jpg");
	return 0;
}