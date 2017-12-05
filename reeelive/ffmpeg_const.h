#ifndef FFMPEG_CONST_H
#define FFMPEG_CONST_H

extern "C"{
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
#include <libavutil/avstring.h>
#include <libavutil/time.h>
#include <libavutil/log.h>
#include <libavutil/opt.h>
#include <libswresample/swresample.h>
#include <libavfilter/buffersink.h>
#include <libavfilter/buffersrc.h>
#include <libavutil/mathematics.h>
#include <libavutil/samplefmt.h>
#include <libavutil/pixdesc.h>
#include <libavutil/imgutils.h>
#include <libavutil/pixfmt.h>
#include <libavutil/audio_fifo.h>
}


/**
 * 文件类型
 */
enum FileType{
    FileType_File,
    FileType_Protocol_RTSP,
    FileType_Protocol_HTTP
};


#define FFMPEG_LOG_PRINT 1
#define FFMPEG_LOG_TOFILE 0
#define kFFMaxVideoQueueSize (5 * 256 * 1024) // ~ 1MB
//#define kFFMaxVideoQueueSize (1920*1280*3*4)
#define kFFMaxAudioQueueSize (5 * 16 * 1024)

#endif // FFMPEG_CONST_H
