#ifndef INPUTFILE_H
#define INPUTFILE_H
#include <iostream>
#include "ffmpeg_const.h"


class InputFile
{
public:

    InputFile(const std::string &filePath);
    std::string getFilePath()const;
    FileType getFileType()const ;

private:
    std::string mFilePath;
    FileType type ;
};

#endif // INPUTFILE_H
