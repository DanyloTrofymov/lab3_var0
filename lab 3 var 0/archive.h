#pragma once

#include <string>

using namespace std;

class Archive {
public:
	Archive() = default;
	Archive(const Archive& _archive) = default;
	Archive(Archive&& _archive) = default;
	~Archive() = default;

	Archive& operator= (const Archive& _archive) = default;
	Archive& operator= (Archive && _archive) = default;
	
	void Compress(const string& fromInfo, string& toInfo);
	void Decompress(const string& fromInfo, string& toInfo);
protected:

};