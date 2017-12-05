#ifndef RSVIDEOASSET_H
#define RSVIDEOASSET_H
#include <iostream>
#include "ffmpeg_const.h"
#include "InputFile.h"
#include <string>
class RSVideoAsset
{
private:
    AVFormatContext * iformatContext;
    AVStream        * videoStream ;
    AVStream        * audioStream ;
    AVCodecContext  * videoCodecContext;
    AVCodecContext  * audioCodecContext;
    std::string            videoPath ;
    AVInputFormat   * inputFormat;
   const  AVCodec * videoCodec;
   const AVCodec * audioCodec;
   void findVideoStream();

public:
    int  st_index[AVMEDIA_TYPE_NB];
    void test(void);

    /**
     *  构造方法
     */
    RSVideoAsset(const InputFile &inputfile);
    /**
     *  获取输入视频url
     *
     *  @return input video URL
     */
    std::string getVideoPath(void);
    /**
     *  获取视频宽度
     *
     *  @return 视频宽度
     */
    int getVideoWidth();
    /**
     *  视频高度
     *
     *  @return 视频高度
     */
    int getVideoHeight();
    /**
     *  视频 帧率
     *
     *  @return 视频帧率
     */
    AVRational getFrameRate();
    /**
     *
     *
     *  @return 视频timebase
     */
    AVRational getTimeBase();
    /**
     *  比特率
     *
     *  @return 比特率
     */
    int64_t getBitRate();
    /**
     *  音频采样率
     *
     *  @return 音频采样率
     */
    int getSampleRate();
    /**
     *  音频channel数
     *
     *  @return 音频channel数
     */
    int getChannalCount();
    /**
     *  获取视频codecId
     *
     *  @return 获取视频codecId
     */
    int getVideoCodecType();
    /**
     *  获取音频codecId
     *
     *  @return 获取音频codecId
     */
    int getAudioCodecType();
    /**
     *  获取视频流
     *
     *  @return 视频流
     */
    AVStream *getVideoStream();
    /**
     *  获取音频流
     *
     *  @return 获取音频流
     */
    AVStream *getAudioStream();
    /**
     *  获取复合器
     *
     *  @return 获取复合器
     */
    AVFormatContext * getFormatContext();
    /**
     *  获取视频codec上下文
     *
     *  @return 获取视频codec上下文
     */
    AVCodecContext  * getVideoCodecContex();
    /**
     *  获取音频codec上下文
     *
     *  @return 获取音频codec上下文
     */
    AVCodecContext  * getAudioCodecContex();
    /**
     *  获取视频的像素格式
     *
     *  @return 视频像素格式
     */
    AVPixelFormat getVideoPixelFormat();
    /**
     *  获取音频的采用格式
     *
     *  @return 音频采样格式
     */
    AVSampleFormat getAudioSampleFormat();
    /**
     *  获取音频pcm codecId
     *
     *  @return pcm codecId
     */
    AVCodecID getAudiopcmCodecId();
    /**
     *  获取采样大小
     *
     *  @return 获取采用大小
     */
    int getAudioBitPreChannel();
    /**
     * 获取视频解码器名称
     * @brief getVideoCodecName
     * @return
     */
    std::string getVideoCodecName();
    /**
     * 获取音频解码器名称
     * @brief getAudioCodecName
     * @return
     */
    std::string getAudioCodecName();
};

#endif // RSVIDEOASSET_H
