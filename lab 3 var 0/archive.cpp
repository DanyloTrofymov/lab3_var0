#include "archive.h"

using namespace std;

void LZWArchivator::encodeName(const string& fileName, string& toInfo) const
{
    string fileName_t = fileName;
    int pos = fileName_t.find_last_of('/');
    if (pos == UINT_MAX) {
        pos = 0;
    }
    string name = fileName_t.substr(pos+1);
    toInfo += "???" + name + "???";
}

string LZWArchivator::decodeName(string& fromInfo) const
{
    string code = "???";
    string name;
    int pos = fromInfo.find_first_of(code);
    fromInfo.erase(pos, 3);
    pos = fromInfo.find_first_of(code);
    name = fromInfo.substr(0, pos);
    fromInfo.erase(0, name.size()+3);
    return name;
}


bool LZWArchivator::Compress(const string& fromInfo, string& toInfo, string& fileName) const
{
    encodeName(fileName, toInfo);

    unordered_map<string, int> vocabulary;
    for (int i = 0; i <= 255; i++) 
    {
        vocabulary[{char(i)}] = i;
    }
    string firstCharacter = "", nextCharacter = "";
    firstCharacter += fromInfo[0];
    int vocabCode = 256;
    for (int i = 0; i < fromInfo.length(); i++) 
    {
        if (i != fromInfo.length() - 1)
            nextCharacter += fromInfo[i + 1];
        if (vocabulary.find(firstCharacter + nextCharacter) != vocabulary.end()) 
        {
            firstCharacter = firstCharacter + nextCharacter;
        }
        else 
        {
            toInfo += ToString(vocabulary[firstCharacter]);
            vocabulary[firstCharacter + nextCharacter] = vocabCode;
            vocabCode++;
            firstCharacter = nextCharacter;
        }
        nextCharacter = "";
    }
    toInfo += ToString(vocabulary[firstCharacter]);
    return true;
}

vector<int> LZWArchivator::Parse(string& str) const
{

    vector<int> codes;
    int val = -1;
    while (!str.empty()) 
    {
        val = FromString(str);
        if (val == -1)
        {
            break;
        }
        codes.push_back(val);
        str.erase(0, Next(str));
    }
    return codes;
}

bool LZWArchivator::Decompress(const string& fromInfo, string& toInfo) const
{

    string fromInfo_t = fromInfo;

    unordered_map<int, string> vocabulary;
    for (int i = 0; i <= 255; i++) 
    {

        vocabulary[i] = { char(i) };
    }

    vector<int> parsed = Parse(fromInfo_t);

    int firstCodedCharacter = parsed[0];
    int nextCodedCharacter;
    string translatedCharacter = vocabulary[firstCodedCharacter];
    string c = translatedCharacter;
    toInfo += translatedCharacter;
    int count = 256;
    for (int i = 0; i < parsed.size() - 1; i++) 
    {
        nextCodedCharacter = parsed[i + 1];
        if (vocabulary.find(nextCodedCharacter) == vocabulary.end()) 
        {
            translatedCharacter = vocabulary[firstCodedCharacter];
            translatedCharacter = translatedCharacter + c;
        }
        else 
        {
            translatedCharacter = vocabulary[nextCodedCharacter];
        }
        toInfo += translatedCharacter;
        c = "";
        c += translatedCharacter[0];
        vocabulary[count] = vocabulary[firstCodedCharacter] + c;
        count++;
        firstCodedCharacter = nextCodedCharacter;
    }
    return true;
}

string LZWArchivator::ToString(int code)			const
{
    string result;
    int bits = 0;
    while (code != 0)
    {
        uint_fast8_t v = code % 256;
        result = (char)v + result;
        code /= 256;
        bits += 8;
    }
    result = (char)bits + result;
    return result;
}

int LZWArchivator::FromString(const string& data)	const
{
    if (data.empty())
        return -1;
    int result = 0;
    int bits = (uint_fast8_t)data[0];
    int i = 1;
    while (bits > 0)
    {
        uint_fast8_t v = data[i];
        result = result * 256 + v;
        bits -= 8;
        i++;
    }
    return result;
}

int LZWArchivator::Next(const string& data)		const
{
    if (data.empty())
    {
        return 0;
    }
    int result = 1;
    int bits = (uint_fast8_t)data[0];
    while (bits > 0)
    {
        bits -= 8;
        result++;
    }
    return result;
}

bool RLEArchivator::Compress(const string& fromInfo, string& toInfo, string& fileName) const
{
	if (fromInfo.empty()) 
    {
		return false;
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

    return true;
}

bool RLEArchivator::Decompress(const string& fromInfo, string& toInfo) const
{
	if (fromInfo.empty()) 
    {
		return false;
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
    return true;
}