#pragma once

#include "iarchivator.h"
#include <iostream>
#include <unordered_map>
#include <vector>
#include <unordered_map>
#include <vector>

class LZWArchivator : public IArhivator
{
public:
	LZWArchivator()												= default;
	LZWArchivator(const LZWArchivator& _archive)				= default;
	LZWArchivator(LZWArchivator&& _archive)						= default;
	virtual ~LZWArchivator()									= default;

	LZWArchivator& operator=(const LZWArchivator& _archive)		= default;
	LZWArchivator& operator=(LZWArchivator&& _archive)			= default;
	
	virtual bool Compress(const string& fromInfo, string& toInfo)	const override;
	virtual bool Decompress(const string& fromInfo, string& toInfo)	const override;
	
protected:
	vector<int> Parse(string& str)		const;
	string ToString(int code)			const;
	int FromString(const string& data)	const;
	int Next(const string& data)		const;


};

class RLEArchivator : public IArhivator
{
public:
	RLEArchivator()												= default;
	RLEArchivator(const RLEArchivator& _archive)				= default;
	RLEArchivator(RLEArchivator&& _archive)						= default;
	virtual ~RLEArchivator()									= default;

	RLEArchivator& operator= (const RLEArchivator& _archive)	= default;
	RLEArchivator& operator= (RLEArchivator&& _archive)			= default;

	virtual bool Compress(const string& fromInfo, string& toInfo)	const override;
	virtual bool Decompress(const string& fromInfo, string& toInfo)	const override;
};