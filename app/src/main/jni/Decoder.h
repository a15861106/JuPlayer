//
// Created by Juwan on 8/25/2015.
//

#ifndef DECODER_H
#define DECODER_H


class Decoder {
public:
    Decoder();
    ~Decoder();

    virtual bool Start() = 0;
    virtual bool Close() = 0;
    virtual bool Decode(char *pData, int size, char *pOutputBuffer, int *pOutputSize) = 0;
};


#endif //JUPLAYER_DECODER_H
