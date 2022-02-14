#include "CircBuffer.h";
#include <iostream>

CircBuffer::CircBuffer(int size, int numSamplesDelay) :
 size(size), numSamplesDelay(numSamplesDelay)
{
    if(numSamplesDelay > size){
        throw("Circbuffer:CircBuffernumSamplesDelay exceeds size.")
    }
    buffer = new float[size];
    for(int i = 0; i < size; i++){
        buffer[i] = 0;
    }
}

CircBuffer::~CircBuffer()
{  
    delete [] buffer;
}

void CircBuffer::write(int value)
{
    buffer[writeH++] = value;
    writeH = wrapH(writeH);
}

float CircBuffer::read()
{
    float tmpvalue = buffer[readH++]
    readH = wrapH(readH);
    return tmpvalue;
}

void CircBuffer::wrapH(int head)
{
    if(size >= head) head -= size;
    return head;
    }
}

int CircBuffer::getDistanceRW()
{
    if(writeH < readH){
        int tempWH = writeH;
        tempWH += size;
        //TODO finish
    }
}