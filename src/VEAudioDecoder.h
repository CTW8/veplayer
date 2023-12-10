#ifndef __VE_AUDIO_DECODER__
#define __VE_AUDIO_DECODER__

#include<string>
#include<memory>
#include"VEMediaDef.h"

extern "C"
{
    #include "libavformat/avformat.h"
    #include "libavcodec/avcodec.h"
    #include "libavutil/avutil.h"
    #include "libavutil/timestamp.h"
}

class VEAudioDecoder{
public:
    VEAudioDecoder(/* args */);
    ~VEAudioDecoder();

    ///init
    int init(VEMediaInfo *info);

    ///flush
    int flush();

    ///send packet
    int sendPacket(VEPacket *pack);

    ///decodeFrame
    int readFrame(VEFrame *frame);
    ///uninit
    int uninit();
private:
    /* data */
    AVCodecContext * mVideoCtx=nullptr;
    VEMediaInfo * mMediaInfo=nullptr;

        // 音频帧缓冲区
    AVFrame *mFrame = nullptr;

    // 音频帧数据大小
    int mFrameSize = 0;
}

#endif