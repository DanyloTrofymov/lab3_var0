#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Archive {
public:
	Archive() = default;
	Archive(const Archive& _archive) = default;
	Archive(Archive&& _archive) = default;
	~Archive() = default;

	Archive& operator= (const Archive& _archive) = default;
	Archive& operator= (Archive && _archive) = default;
	/*
	vector<int> encoding(string s1);
	void decoding(vector<int> op);
	*/

	void LZWCompress(const string& fromInfo, string& toInfo);
	void LZWDecompress(const string& fromInfo, string& toInfo);
	

	void RLECompress(const string& fromInfo, string& toInfo);
	void RLEDecompress(const string& fromInfo, string& toInfo);
protected:
	vector<int> Parse(string& str);
	string ToString(int code)			const;
	int FromString(const string& data)	const;
	int Next(const string& data)		const;


};