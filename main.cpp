#include <iostream>
#include "VEDemux.h"
#include "VEAudioDecoder.h"
using namespace std;

extern "C"
{
#include "libavformat/avformat.h"
#include "libavcodec/avcodec.h"
#include "libavutil/avutil.h"
#include "libavutil/timestamp.h"
}

#define FILE_NAME "/Users/lizhen/Downloads/test.mp4"

int main(int, char **)
{
    VEDemux *tmp = new VEDemux();
    tmp->open(FILE_NAME);
    shared_ptr<VEMediaInfo> info = tmp->getFileInfo();
    printf("h:%d w:%d\n", info->height, info->width);

    VEAudioDecoder *audioDec = new VEAudioDecoder();
    shared_ptr<VEMediaInfo> mediaInfo = tmp->getFileInfo();
    audioDec->init(mediaInfo.get());

    VEPacket packet;
    packet.frame = av_packet_alloc();

    VEFrame frame;
    frame.frame = av_frame_alloc();

    while (tmp->read(&packet) >= 0)
    {
        if (packet.frame->stream_index == mediaInfo->audio_stream_index)
        {
            printf("stream_index:%d  pts:%lld\n", packet.frame->stream_index, packet.frame->pts);
            audioDec->sendPacket(&packet);
            audioDec->readFrame(&frame);
            printf("samplerate:%d  nb_smaples:%d  pts:%lld  pts_ms:%f  num:%d den:%d\n",frame.frame->sample_rate,frame.frame->nb_samples,frame.frame->pts,frame.frame->pts * av_q2d(mediaInfo->mAudioTimeBase),mediaInfo->mAudioTimeBase.num,mediaInfo->mAudioTimeBase.den);
        }
    }
    delete tmp;
    return 0;
}
