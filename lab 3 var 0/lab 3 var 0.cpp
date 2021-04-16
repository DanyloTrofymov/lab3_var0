#include <iostream>
#include "archive.h"
#include "file_archive.h"
#include <vector>

using namespace std;

int main(/*int argc, char* argv[]*/)
{
	FileArchive file;
	//Archive archive;
	//string dich = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";
		//"Lorem ipsum dolor sit amet,\nconsectetur adipiscing elit,\nsed do eiusmod tempor incididunt ut labore et dolore magna aliqua.\nUt enim ad minim veniam,\nquis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.\nDuis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur.\nExcepteur sint occaecat cupidatat non proident,\nsunt in culpa qui officia deserunt mollit anim id est laborum.";
	//string r1, r2;
	//archive.LZWCompress(dich, r1);
	//archive.LZWDecompress(r1, r2);
	//cout << dich << endl;
	//cout << r1 << endl;
	//cout << r2 << endl;
	//cout << archive.ToString(647)<<endl;
	//cout << archive.FromString(archive.ToString(647))<<endl;
	//cout << archive.Next(archive.ToString(10000))<<endl;
	file.Compress("in.txt", "encoded.txt");
	file.Decompress("encoded.txt", "out.txt");
	return 0;
}