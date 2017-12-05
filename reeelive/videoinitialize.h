#ifndef VIDEOINITIALIZE_H
#define VIDEOINITIALIZE_H
#include<iostream>
#include "ffmpeg_const.h"

class VideoInitialize
{
public:
    VideoInitialize();
    /**
     * See Log level.
     */
    //#define AV_LOG_QUIET    -8

    /**
     * Something went really wrong and we will crash now.
     */
    //#define AV_LOG_PANIC     0

    /**
     * Something went wrong and recovery is not possible.
     * For example, no header was found for a format which depends
     * on headers or an illegal combination of parameters is used.
     */
    //#define AV_LOG_FATAL     8

    /**
     * Something went wrong and cannot losslessly be recovered.
     * However, not all future data is affected.
     */
    //#define AV_LOG_ERROR    16

    /**
     * Something somehow does not look correct. This may or may not
     * lead to problems. An example would be the use of '-vstrict -2'.
     */
    //#define AV_LOG_WARNING  24

    /**
     * Standard information.
     */
    //#define AV_LOG_INFO     32

    /**
     * Detailed information.
     */
    //#define AV_LOG_VERBOSE  40

    /**
     * Stuff which is only useful for libav* developers.
     */
    //#define AV_LOG_DEBUG    48

    /**
     * Extremely verbose debugging, useful for libav* development.
     */
    //#define AV_LOG_TRACE    56
    void setLogLevel(int level);
    /**
     *  初始化ffmpeg
     *
     *  @return 是不是成功初始化
     */
    bool isInitialization();
    /**
     *  单例
     *
     *  @return 该类的实例
     */
    static VideoInitialize&GetInstance()
    {
        static VideoInitialize instance;
        instance.isInitialization();
        return instance;
    }
private:
    bool isInitializationed;
    static void ffmpeg_log_callback(void *ptr ,int leavel ,const char * fmt ,va_list vl);
};

#endif // VIDEOINITIALIZE_H
