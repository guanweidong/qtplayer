#include "videoinitialize.h"

VideoInitialize::VideoInitialize()
{

}

void VideoInitialize::ffmpeg_log_callback(void *ptr ,int leavel ,const char * fmt ,va_list vl)
{
#if FFMPEG_LOG_PRINT
    va_list vl2;
    char line[1024];
    static int print_prefix = 1;

    va_copy(vl2, vl);
    av_log_format_line(ptr, leavel, fmt, vl2, line, sizeof(line), &print_prefix);
    va_end(vl2);
    printf("ffmpeg %s\n",line);
#else

    const size_t len = strlen(fmt);
    char * format ;
    format = (char * )malloc(sizeof(char)*len+1);
    strcat(format, fmt);

    printf("ffmpeg log: %s",format);
    FILE * fp = fopen("log.txt", "a+");
    if(fp){
        vfprintf(fp, format, vl);
        fflush(fp);
        format = NULL;
    }
    free(format);
    format =NULL;
#endif
}


bool VideoInitialize::isInitialization()
{
    if (this->isInitializationed) {
        return this->isInitializationed;
    }
    av_log_set_flags(AV_LOG_SKIP_REPEATED);
    av_log_set_level(AV_LOG_WARNING);
    av_register_all();
    avformat_network_init();
    av_log_set_callback(ffmpeg_log_callback);
    this->isInitializationed = true;
    return this->isInitializationed;
}
void VideoInitialize::setLogLevel(int level)
{
    av_log_set_level(level);
}

