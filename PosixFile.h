#ifndef POSIXFILE_H
#define POSIXFILE_H

#include <string>
#include <cstdio>

#include "crc32generator.h"


/*PosixFile - Wrapper for posix-c-functions handling files*/
class PosixFile
{
    public:
        PosixFile(std::string FilePath);
        virtual ~PosixFile();
        std::string getFilePath() { return FilePath; }

        bool stepCRC32(int step);
        std::string getCRC32string();
        std::string buildCRC32string();

        unsigned long getFileSize();
    protected:
    private:
        FILE *Handle;
				crc32generator *Generator;
        std::string FilePath;
};

#endif // POSIXFILE_H
