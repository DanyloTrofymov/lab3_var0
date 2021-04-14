#include <iostream>
#include "archive.h"

using namespace std;

void main() 
{
	string t1 = "hhhhhbbbbbdddd";
	string t2 = "222 huuuu  44";
	string t3 = "nnmkjjp";

	Archive archive;

	string r1, r2, r3;
	archive.Compress(t1, r1);
	archive.Compress(t2, r2);
	archive.Compress(t3, r3);

	cout << r1 << endl;
	cout << r2 << endl;
	cout << r3 << endl;

	string d1, d2, d3;
	archive.Decompress(r1, d1);
	archive.Decompress(r2, d2);
	archive.Decompress(r3, d3);

	cout << d1 << endl;
	cout << d2 << endl;
	cout << d3 << endl;
}