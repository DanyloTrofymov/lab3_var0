#pragma once

#include <string>

using namespace::std;

class IArhivator
{
public:
    IArhivator()                                                    = default;
    IArhivator(const IArhivator& archive)                           = default;
    IArhivator(IArhivator&& archive)                                = default;
    virtual ~IArhivator()                                           = default;

    IArhivator& operator= (const IArhivator& archive)               = default;
    IArhivator& operator= (IArhivator&& archive)                    = default;

    virtual bool Compress(const string& fromInfo, string& toInfo)   const = 0;
    virtual bool Decompress(const string& fromInfo, string& toInfo) const = 0;
};