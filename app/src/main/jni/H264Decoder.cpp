//
// Created by Juwan on 8/25/2015.
//

#include "H264Decoder.h"

#define __STDC_FORMAT_MACROS

extern "C"
{
#include <libavutil/imgutils.h>
#include <libavutil/samplefmt.h>
#include <libavutil/timestamp.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}

H264Decoder::H264Decoder() {
    m_pVideo_dec_ctx = NULL;
    m_pCurFrame = NULL;

    m_sws_ctx = NULL;
}

H264Decoder::~H264Decoder() {
    if (m_pVideo_dec_ctx) {
        avcodec_close(m_pVideo_dec_ctx);
        av_free(m_pVideo_dec_ctx);
        m_pVideo_dec_ctx = NULL;
    }

    if (m_sws_ctx) {
        sws_freeContext(m_sws_ctx);
        m_sws_ctx = NULL;
    }
}


void H264Decoder::Register() {
    LOGD("CH264Decoder::Register().");
    /* register all formats and codecs */
    av_register_all();
}

bool H264Decoder::Start() {
    LOGD("CH264Decoder::Start().");
    AVCodec *pAVCodec = avcodec_find_decoder(AV_CODEC_ID_H264);

    m_pVideo_dec_ctx = avcodec_alloc_context3(pAVCodec);
    /* For some codecs, such as msmpeg4 and mpeg4, width and height
    MUST be initialized there because this information is not
    available in the bitstream. */

    /* open it */
    avcodec_open2(m_pVideo_dec_ctx, pAVCodec, NULL);

    m_pCurFrame = av_frame_alloc();

    return true;
}

bool H264Decoder::Close() {
    if (m_pCurFrame) {
        av_frame_free(&m_pCurFrame);
        m_pCurFrame = NULL;
    }
    if (m_sws_ctx) {
        sws_freeContext(m_sws_ctx);
        m_sws_ctx = NULL;
    }
    if (m_pVideo_dec_ctx) {
        avcodec_close(m_pVideo_dec_ctx);
        //av_free(m_pVideo_dec_ctx);
        m_pVideo_dec_ctx = NULL;
    }

    return true;
}

bool H264Decoder::Decode(char *pData, int size, char *pOutputBuffer, int *pOutputSize) {
    LOGD("Decode().");
    int len, got_frame;
    AVPacket pkt;
    av_init_packet(&pkt);
    pkt.size = size;
    pkt.data = (uint8_t *) pData;

    len = avcodec_decode_video2(m_pVideo_dec_ctx, m_pCurFrame, &got_frame, &pkt);

    if (got_frame) {
        uint8_t *pBuffer = (uint8_t *) pOutputBuffer;

        int W = m_pCurFrame->width;
        int H = m_pCurFrame->height;

        if (m_sws_ctx == NULL) {
            m_sws_ctx = sws_getContext(W, H, AV_PIX_FMT_YUV420P, W, H,
                                       AV_PIX_FMT_RGB565, SWS_FAST_BILINEAR, 0, 0, 0);
        }

        int inLinesize[1] = {2 * W}; // RGB stride , 画面的宽度,画面高度缺少一半,由4变为2;
        sws_scale(m_sws_ctx, m_pCurFrame->data, m_pCurFrame->linesize, 0, H, &pBuffer, inLinesize);

        *pOutputSize = W * H * 4;
    }

    return got_frame;
}