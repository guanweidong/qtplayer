#include "packagequeue.h"
using namespace std;
PackageQueue::PackageQueue(int  sSize )
{
    this->firs_pkt = NULL;
    this->last_pkt = NULL;
    this->nb_packets = 0;
    this->size =  0;
    this->queuesize = sSize;
    this->eof_reached = 0;
}

void PackageQueue:: put(AVPacket * packt,bool block )
{
    if(packt ==NULL)
    {
        this->eof_reached = 1 ;
        pthread_cond_signal(&this->condtionLock.cond);
        return;
    }
    AVPacketList * pktlist;
    AVPacket * newPackt = av_packet_alloc();
    int error = 0 ;
    pthread_mutex_lock(&this->condtionLock.mutex);
    for (;;) {
        if (size > this->queuesize)
        {
            if (block)
            {
                av_log(NULL, AV_LOG_INFO, "put packet wait\n");
                pthread_cond_wait(&this->condtionLock.cond, &this->condtionLock.mutex);
            }else
            {
                break;
            }
        }else
        {
            if((av_copy_packet(newPackt, packt)<0)){
                error = 0 ;
                break ;
            }
            pktlist =(AVPacketList *)av_malloc(sizeof(AVPacketList));
            if (!pktlist) {
                av_log(NULL,AV_LOG_ERROR,"malloc pktlist faild\n");
                error = 0 ;
                break;
            }
            pktlist->pkt = *newPackt;
            pktlist->next = NULL;
            if (!last_pkt) {
                firs_pkt = pktlist ;
            }else
            {
                last_pkt->next = pktlist;
            }
            last_pkt = pktlist;
            nb_packets ++;
            size +=pktlist->pkt.size;
            cout<<"paket size = "<<pktlist->pkt.size<<endl;
            pthread_cond_signal(&this->condtionLock.cond);
            break;
        }
    }
    cout<<"paket size all= "<<size<<endl;
    av_log(NULL, AV_LOG_INFO, "packt 生产线程\n");
    pthread_mutex_unlock(&this->condtionLock.mutex);
}

int  PackageQueue:: get(AVPacket *packt,bool block )
{

    AVPacketList * pktList ;
    pthread_mutex_lock(&this->condtionLock.mutex);
    int error = 0 ;
    for (;;)
    {
        pktList = firs_pkt;
        if (pktList)
        {
            firs_pkt = pktList->next;
            if (!firs_pkt)
            {
                last_pkt = NULL;
            }
            nb_packets --;
            size -=pktList->pkt.size;
            *packt = pktList->pkt;
            av_free(pktList);
            error = 1 ;
            pthread_cond_signal(&this->condtionLock.cond);
            break;
        }else if (!block)
        {
            error =  0 ;
            break ;
        }else
        {
            if (this->eof_reached&&nb_packets == 0) {
                av_log(NULL,AV_LOG_INFO,"线程等待");
                return  error = -1;
            }
            av_log(NULL,AV_LOG_INFO,"线程等待");
            pthread_cond_wait(&this->condtionLock.cond, &this->condtionLock.mutex);
        }
    }
    av_log(NULL,AV_LOG_INFO,"packt 消费线程");
    pthread_mutex_unlock(&this->condtionLock.mutex);

    return error;
}

void PackageQueue::flush(void)
{
    AVPacketList * pkt , *pkt1 ;
    pthread_mutex_lock(&this->condtionLock.mutex);
    for (pkt = firs_pkt; pkt != NULL; pkt =pkt1) {
        pkt1= pkt->next;
        av_packet_unref(&pkt->pkt);
        av_free(&pkt);
    }
    last_pkt = NULL;
    firs_pkt = NULL;
    nb_packets = 0 ;
    size = 0 ;
    pthread_mutex_unlock(&this->condtionLock.mutex);
}


