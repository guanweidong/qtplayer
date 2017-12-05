#include "inputfile.h"
#include<iostream>
#include<string>
#include "ffmpeg_const.h"
#include "videoinitialize.h"
using namespace std;

InputFile::InputFile(const std::string &filePath)
{
    if(filePath.size()==0)
    {
        av_log(NULL, AV_LOG_ERROR, "must input a exesit file \n");
        return;
    }
    mFilePath = filePath;
    string::size_type pos =  mFilePath.find(":");
    if (pos == string::npos) {
        type = FileType_File;
    }else
    {
       string protocol = mFilePath.substr(0,pos);
        if(protocol.compare("http")==0)type = FileType_Protocol_HTTP;
        if(protocol.compare("rtsp")==0)type = FileType_Protocol_RTSP;
    }
    //初始化ffmpeg
    VideoInitialize::GetInstance().isInitialization();
    VideoInitialize::GetInstance().setLogLevel(AV_LOG_WARNING);
    AVFormatContext *inputFormatContext = avformat_alloc_context();
    AVInputFormat * inputFormat = NULL;
    if(avformat_open_input(&inputFormatContext, mFilePath.c_str(), inputFormat, NULL)<0)
    {
        av_log(NULL ,AV_LOG_ERROR,"open input file faild\n ");
        return ;
    }
    avformat_close_input(&inputFormatContext);
}
FileType InputFile::getFileType()const
{
    return type ;
}

string InputFile:: getFilePath()const
{
    return mFilePath;
}
