#pragma once

#include "iarchivator.h"
#include <memory>

using namespace std;

class ArchivatorFactory
{
public:
	enum ArchivatorType
	{
		LZW,
		RLE
	};

public:
	ArchivatorFactory()                                                = default;
    ArchivatorFactory(const ArchivatorFactory& archive)                = default;
    ArchivatorFactory(ArchivatorFactory&& archive)                     = default;
    ~ArchivatorFactory()											   = default;

    ArchivatorFactory& operator= (const ArchivatorFactory& archive)    = default;
    ArchivatorFactory& operator= (ArchivatorFactory&& archive)         = default;

	static unique_ptr<IArhivator> Get(ArchivatorType type = ArchivatorType::LZW);
};