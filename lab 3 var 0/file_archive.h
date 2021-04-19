#pragma once

#include "archivator_factory.h"

class FileArchive
{
public:
    FileArchive(ArchivatorFactory::ArchivatorType type);
    FileArchive()                                                   = delete;
    FileArchive(const FileArchive& archive)                         = delete;
    FileArchive(FileArchive&& archive)                              = delete;
    ~FileArchive()                                                  = default;

    FileArchive& operator= (const FileArchive& archive)             = delete;
    FileArchive& operator= (FileArchive&& archive)                  = delete;

    bool Compress(const string& fromInfo, const string& toInfo)     const;
    bool Decompress(const string& fromInfo, const string& toInfo)   const;

protected:
    bool ReadFile(const string& fileName, string& data)             const;
    bool WriteFile(const string& fileName,  string& data)           const;
    bool IsEmpty(const string& fileName)                            const;
    string FileNameRecord(const string& filename)             const   ;

    unique_ptr<IArhivator> archivator;
};