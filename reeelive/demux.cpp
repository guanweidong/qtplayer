#include "demux.h"
using namespace std;
Demux::Demux(RSVideoAsset * mediaAsset , bool needSave)
{
    if (mediaAsset ==NULL) {
        av_log(NULL ,AV_LOG_ERROR,"inputformat Context can not exesit\n");
    }
    mvideoAsset = mediaAsset;
    mvideoPackageQueue = new PackageQueue(kFFMaxVideoQueueSize);
    maudioPackageQueue = new PackageQueue(kFFMaxAudioQueueSize);
    mInputformatContext = mediaAsset->getFormatContext();
    mNeedSave = needSave;
}

void Demux::startDemux(void )
{
    pthread_create(&demux_thread, NULL, demuxMedia,this);
    pthread_join(demux_thread, NULL);
}
 void * Demux::demuxMedia(void * ptr)
{
    Demux * mediaDemux  = (Demux *)ptr;
    RSVideoAsset    * mediaAsset    = mediaDemux->mvideoAsset;
    AVFormatContext * inputformat   = mediaAsset->getFormatContext();
    AVPacket        * pReadPkt      = av_packet_alloc();
    int ret = 0 ;
    for (; ; )
    {
        ret = av_read_frame(inputformat, pReadPkt);
        if(ret<0)
        {
            if (inputformat->pb!=NULL && inputformat->pb->error!= 0)
            {
                usleep(10000);
                continue;
            }
        }
        if (pReadPkt->stream_index == mediaAsset->st_index[AVMEDIA_TYPE_VIDEO])
        {
            mediaDemux->mvideoPackageQueue->put(pReadPkt, true);
            av_log(NULL ,AV_LOG_INFO,"视频解复合成功\n");

        }else if (pReadPkt->stream_index==mediaAsset->st_index[AVMEDIA_TYPE_AUDIO])
        {
            cout<<"音频解复合成功"<<endl;
            mediaDemux->maudioPackageQueue->put(pReadPkt, true);
        }else
        {
            av_packet_unref(pReadPkt);
            pReadPkt =NULL;
        }
        if (pReadPkt) {
            av_packet_unref(pReadPkt);
        }
    }
    return 0 ;
}

void Demux::cancleDemux()
{
    pthread_cancel(demux_thread);
}
