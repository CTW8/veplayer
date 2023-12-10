#include <iostream>
#include"VEDemux.h"
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
    printf("h:%d w:%d\n",info->height,info->width);
    AVPacket pack;
    av_init_packet(&pack);
    while(tmp->read(&pack)>=0){
        printf("stream_index:%d  pts:%lld\n",pack.stream_index,pack.pts);
    }
    delete tmp;
    return 0;
}
