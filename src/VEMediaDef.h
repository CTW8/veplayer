#ifndef     __VE_MEDIA_DEF__
#define     __VE_MEDIA_DEF__
extern "C"{
#include"libavcodec/avcodec.h"
#include"libavformat/avformat.h"
}

typedef struct __VEMediaInfo{
    int width;
    int height;
    int fps;
    uint64_t duration;
    
    int channels;
    int sampleRate;
    int sampleFormat;

    AVCodecParameters *mAudioCodecParams;
    AVCodecParameters *mVideoCodecParams;

}VEMediaInfo;



#endif