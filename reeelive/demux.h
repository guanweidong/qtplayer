#ifndef DEMUX_H
#define DEMUX_H
#include "ffmpeg_const.h"
#include "packagequeue.h"
#include "rsvideoasset.h"

class Demux
{
public:
        Demux(RSVideoAsset *mediaAsset,bool needSave);
        void startDemux(void);
        void cancleDemux(void);
private:
        bool mNeedSave ;
        AVFormatContext * mInputformatContext ;
        PackageQueue    * mvideoPackageQueue;
        PackageQueue    * maudioPackageQueue;
        RSVideoAsset    * mvideoAsset ;
        pthread_t         demux_thread ;
        static void     * demuxMedia(void * ptr);
};

#endif // DEMUX_H
