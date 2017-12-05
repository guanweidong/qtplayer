#ifndef PACKAGEQUEUE_H
#define PACKAGEQUEUE_H
#include <iostream>
#include <pthread.h>
#include "ffmpeg_const.h"

class PackageQueue
{
private:
    AVPacketList * firs_pkt;
    AVPacketList * last_pkt ;
    int nb_packets ;
    int  size ;
    int abort_request ;
    int max_size;
    int serial ;
    int queuesize ;
    int eof_reached ;
    struct CondtionLock{
        pthread_mutex_t mutex ;
        pthread_cond_t  cond ;
        int ready ;
    }condtionLock={
        PTHREAD_MUTEX_INITIALIZER,PTHREAD_COND_INITIALIZER
    };
public:
    //初始化锁
    PackageQueue(int  size );
    void put(AVPacket * packt, bool block );
    int  get(AVPacket *packt, bool block );
    void flush(void);
};

#endif // PACKAGEQUEUE_H
