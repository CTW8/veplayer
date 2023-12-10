#include"VEAudioDecoder.h"

VEAudioDecoder::VEAudioDecoder(){
    mVideoCtx = nullptr;
    mMediaInfo = nullptr;
    mFrame = nullptr;
    mFrameSize = 0;
}

VEAudioDecoder::~VEAudioDecoder()
{
    uninit();
}

int VEAudioDecoder::init(VEMediaInfo *info)
{
    if (info == nullptr) {
        return -1;
    }

    // 根据音频编码格式初始化解码器
    const AVCodec *codec = avcodec_find_decoder(info->audio_codec_id);
    if (codec == nullptr) {
        return -1;
    }

    // 创建解码器上下文
    mVideoCtx = avcodec_alloc_context3(codec);
    if (mVideoCtx == nullptr) {
        return -1;
    }

    // 设置解码器参数
    avcodec_parameters_to_context(mVideoCtx, info->audio_param);

    // 打开解码器
    if (avcodec_open2(mVideoCtx, codec, nullptr) != 0) {
        return -1;
    }

    // 分配音频帧缓冲区
    mFrameSize = av_samples_get_buffer_size(
        nullptr,
        mVideoCtx->channels,
        mVideoCtx->sample_rate,
        mVideoCtx->sample_fmt,
        1);
    mFrame = av_frame_alloc();
    if (mFrame == nullptr) {
        return -1;
    }

    // 设置音频帧数据大小
    mFrame->nb_samples = mVideoCtx->frame_size;
    mFrame->format = mVideoCtx->sample_fmt;
    mFrame->channels = mVideoCtx->channels;
    mFrame->sample_rate = mVideoCtx->sample_rate;
    return 0;
}

int VEAudioDecoder::flush()
{
    if (!mAudioCtx) {
        return -1; // 解码器上下文为空
    }

    // 刷新解码器状态
    avcodec_flush_buffers(mAudioCtx);

    return 0;
}

int VEAudioDecoder::sendPacket(VEPacket *pack)
{
       if (pack == nullptr) {
        return -1;
    }

    // 将音频包送入解码器
    return avcodec_send_packet(mVideoCtx, pack->data);

}

int VEAudioDecoder::readFrame(VEFrame *frame)
{
    if (frame == nullptr) {
        return -1;
    }

    // 从解码器中读取音频帧
    int ret = avcodec_receive_frame(mVideoCtx, frame->data);
    if (ret == AVERROR(EAGAIN)) {
        return 0;
    } else if (ret < 0) {
        return -1;
    }

    // 设置音频帧参数
    frame->pts = av_frame_get_best_effort_timestamp(frame->data);
    frame->dts = av_frame_get_best_effort_dts(frame->data);

    return 0;
}

int VEAudioDecoder::uninit()
{
    // 释放资源，包括解码器上下文等
    if (mAudioCtx) {
        avcodec_free_context(&mAudioCtx);
    }

    mMediaInfo = nullptr;
    return 0;
}
