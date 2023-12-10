#ifndef __VE_PACKET__
#define __VE_PACKET__

#include<memory>

typedef struct _VEPacket{
    int type;
    AVPacket *frame;
}VEPacket;

#endif