#pragma once
#include <iostream>

class Interpolation
{
public:
    Interpolation();
    ~Interpolation();

    // static to make them available in all classes without declaring the class

    // nearest neighbor map
    static float NNMap(float value, float low, float high);

    static float mapInRange(float value, float xLow, float xHigh, float yLow, float yHigh);
    static float linMapOld(float value, float low, float high);

    static float scale(float y, float x1From, float x2From, float x1To, float x2To);
    static float linMap(float x, float x1, float x2, float y1, float y2);
};