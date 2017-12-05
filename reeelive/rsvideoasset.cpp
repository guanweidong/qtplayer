#include "rsvideoasset.h"
#include "videoinitialize.h"
using namespace std;
RSVideoAsset::RSVideoAsset(const InputFile & inputfile)
{
    VideoInitialize engine = VideoInitialize::GetInstance();
    if(engine.isInitialization())
    {
        av_log(NULL,AV_LOG_INFO, "ffmpeg init success\n");
    }else
    {
        av_log(NULL,AV_LOG_INFO, "ffmpeg init faild\n");
        return;
    }
    this->videoPath = inputfile.getFilePath();
    this->iformatContext = NULL;
    this->iformatContext = avformat_alloc_context();
    int error ;
    this->inputFormat = NULL;
    AVDictionary* options = NULL;
    if (inputfile.getFileType() ==FileType_Protocol_RTSP) {
        av_dict_set(&options, "rtsp_transport", "tcp", 0);
    }
    error = avformat_open_input(&(this->iformatContext), videoPath.c_str(), this->inputFormat, &options);
    if(error<0)
    {
        av_log(NULL,AV_LOG_ERROR, "open input file Faild\n");
        avformat_close_input(&this->iformatContext);
    }
    error = avformat_find_stream_info(this->iformatContext, NULL);
    if (error < 0) {
        av_log(NULL,AV_LOG_ERROR,"find stream faild\n");
    }
    av_dump_format(iformatContext, 0, this->videoPath.c_str(), 0);
    this->findVideoStream();
}



string RSVideoAsset::getVideoPath()
{
    return this->videoPath;
}
void RSVideoAsset:: findVideoStream()
{
    memset(st_index, -1, sizeof(st_index));
    this->st_index[AVMEDIA_TYPE_VIDEO] = av_find_best_stream(this->iformatContext, AVMEDIA_TYPE_VIDEO,this->st_index[AVMEDIA_TYPE_VIDEO], -1, NULL,0);
    this->st_index[AVMEDIA_TYPE_AUDIO]= av_find_best_stream(this->iformatContext, AVMEDIA_TYPE_AUDIO, this->st_index[AVMEDIA_TYPE_AUDIO], st_index[AVMEDIA_TYPE_VIDEO], NULL, 0);

    st_index[AVMEDIA_TYPE_SUBTITLE]= av_find_best_stream(this->iformatContext, AVMEDIA_TYPE_SUBTITLE, st_index[AVMEDIA_TYPE_SUBTITLE], (st_index[AVMEDIA_TYPE_AUDIO]>=0 ?st_index[AVMEDIA_TYPE_AUDIO]:st_index[AVMEDIA_TYPE_VIDEO]), NULL, 0);
    if(st_index[AVMEDIA_TYPE_VIDEO]>=0){
        videoStream = this->iformatContext->streams[st_index[AVMEDIA_TYPE_VIDEO]];
        videoCodecContext = videoStream->codec;
        videoCodec=videoCodecContext->codec;
        videoCodec = avcodec_find_decoder( videoCodecContext->codec_id);

    }
    if(st_index[AVMEDIA_TYPE_AUDIO]>=0){
        audioStream = this->iformatContext->streams[st_index[AVMEDIA_TYPE_AUDIO]];
        audioCodecContext = audioStream->codec;
        audioCodec = avcodec_find_decoder( audioCodecContext->codec_id);
    }
}

int RSVideoAsset::getVideoWidth()
{
    return videoCodecContext->width;
}

int RSVideoAsset::getVideoHeight()
{
    return videoCodecContext->height;
}


AVRational RSVideoAsset::getFrameRate()
{
    return  videoStream->r_frame_rate ;
}
AVRational RSVideoAsset::getTimeBase()
{
    return videoCodecContext->time_base;
}

int64_t RSVideoAsset::getBitRate()
{
    return  videoCodecContext->bit_rate;
}

int RSVideoAsset::getSampleRate()
{
    return audioCodecContext->sample_rate;
}

int RSVideoAsset::getChannalCount()
{
    return audioCodecContext->channels;
}

int RSVideoAsset:: getVideoCodecType()
{
    return this->videoCodec->id;
}
int RSVideoAsset:: getAudioCodecType()
{
    return this->audioCodec->id;
}

AVFormatContext * RSVideoAsset::getFormatContext()
{
    return this->iformatContext;
}

AVStream* RSVideoAsset::getVideoStream()
{
    return this->videoStream;
}
AVStream * RSVideoAsset::getAudioStream()
{
    return this->audioStream;
}

AVCodecContext  *RSVideoAsset:: getVideoCodecContex()
{
    return this->videoCodecContext;
}
AVCodecContext  *RSVideoAsset::getAudioCodecContex()
{
    return this->audioCodecContext;
}
AVPixelFormat RSVideoAsset:: getVideoPixelFormat()
{
    return videoCodecContext->pix_fmt;
}

AVSampleFormat RSVideoAsset:: getAudioSampleFormat()
{
    return audioCodecContext->sample_fmt;
}

AVCodecID RSVideoAsset::getAudiopcmCodecId()
{
    return av_get_pcm_codec(this->getAudioSampleFormat(), -1);
}

int RSVideoAsset::getAudioBitPreChannel()
{
    return av_get_bits_per_sample(this->getAudiopcmCodecId());
}

std::string RSVideoAsset::getVideoCodecName()
{
   return  string(videoCodec->name);

}

std::string RSVideoAsset::getAudioCodecName()
{
  return    string(audioCodec->name);
}
