#include "archive.h"

void Archive::Compress(const string& fromInfo, string& toInfo)
{
	if (fromInfo.empty()) {
		return;
	}
	toInfo.clear();
	int i = 1;
	int count = 1;
	char t = fromInfo[0];
	while (i < fromInfo.length())
	{
		if (t == fromInfo[i] && count <= 255) 
		{
			count++;
		} 
		else if (t == fromInfo[i] && count > 255) 
		{
			toInfo += t;
			toInfo += char(255);
			count = 1;
		}
		else if (t != fromInfo[i])
		{
			toInfo += t;
			toInfo+=char(count);
			count = 1;
			t = fromInfo[i];
		}
		i++;
	}
	toInfo += t;
	toInfo += char(count);


}
void Archive::Decompress(const string& fromInfo, string& toInfo)
{
	if (fromInfo.empty()) {
		return;
	}
	toInfo.clear();
	int i = 0;
	int count = 0;
	char t = 0;
	while (i < fromInfo.length())
	{
		t = fromInfo[i];
		count = int(fromInfo[i + 1]);
		toInfo += string(count, t);
		i += 2;
	}
}