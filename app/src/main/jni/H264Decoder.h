//
// Created by Juwan on 8/25/2015.
//

#ifndef H264DECODER_H
#define H264DECODER_H

#include "Decoder.h"
#include "jni_log.h"

struct AVCodecContext;
struct AVFrame;
struct SwsContext;



class H264Decoder: public Decoder {

public:
    H264Decoder();
    ~H264Decoder();

    static void Register();

    bool Start();
    bool Close();
    bool Decode(char *pData, int size, char *pOutputBuffer, int *pOutputSize);

private:
    AVCodecContext* m_pVideo_dec_ctx;
    AVFrame* m_pCurFrame;

    SwsContext* m_sws_ctx;
};


#endif //JUPLAYER_H264DECODER_H
