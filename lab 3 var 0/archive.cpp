#include "archive.h"

using namespace std;


bool LZWArchivator::Compress(const string& fromInfo, string& toInfo) const
{
    toInfo.clear();
    unordered_map<string, int> table;
    for (int i = 0; i <= 255; i++) {
        table[{char(i)}] = i;
    }

    string p = "", c = "";
    p += fromInfo[0];
    int code = 256;
    for (int i = 0; i < fromInfo.length(); i++) {
        if (i != fromInfo.length() - 1)
            c += fromInfo[i + 1];
        if (table.find(p + c) != table.end()) {
            p = p + c;
        }
        else {
            //cheat! need refac it
            toInfo += ToString(table[p]);
            table[p + c] = code;
            code++;
            p = c;
        }
        c = "";
    }
    toInfo += ToString(table[p]);
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
    /*
    cout << "\nDecoding\n";
    unordered_map<int, string> table;
    for (int i = 0; i <= 255; i++) {
        string ch = "";
        ch += char(i);
        table[i] = ch;
    }
    string fromInfo_t = fromInfo;
    vector<int> op = Parse(fromInfo_t);
    int old = op[0], n;
    string s = table[old];
    string c = "";
    c += s[0];
    cout << s;
    int count = 256;
    for (int i = 0; i < op.size() - 1; i++) {
        n = op[i + 1];
        if (table.find(n) == table.end()) {
            s = table[old];
            s = s + c;
        }
        else {
            s = table[n];
        }
        cout << s;
        c = "";
        c += s[0];
        table[count] = table[old] + c;
        count++;
        old = n;
    }
    */
    unordered_map<int, string> table;
    for (int i = 0; i <= 255; i++) {

        table[i] = { char(i) };
    }
    string fromInfo_t = fromInfo;
    vector<int> parsed = Parse(fromInfo_t);

    int old = parsed[0];
    int n;
    string s = table[old];
    string c = s;
    toInfo += s;
    int count = 256;
    for (int i = 0; i < parsed.size() - 1; i++) {
        n = parsed[i + 1];
        if (table.find(n) == table.end()) {
            s = table[old];
            s = s + c;
        }
        else {
            s = table[n];
        }
        toInfo += s;
        c = "";
        c += s[0];
        table[count] = table[old] + c;
        count++;
        old = n;
    }
    return true;
}


string LZWArchivator::ToString(int code)			const
{
    string result;
    int bits = 0;
    //cout <<"{"<< code <<"}";
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
    //cout << "[" << result << "]";
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

bool RLEArchivator::Compress(const string& fromInfo, string& toInfo) const
{
	if (fromInfo.empty()) {
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
	if (fromInfo.empty()) {
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