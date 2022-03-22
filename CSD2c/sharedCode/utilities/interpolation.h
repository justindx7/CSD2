#pragma once
#include <iostream>

class Interpolation
{
public:
    Interpolation();
    ~Interpolation();

    // static to make them available in all classes without declaring the class

    // nearest neighbor map
    static float NNMap(float value, int low, int high);

    static float mapInRange(float value, float xLow, float xHigh, float yLow, float yHigh);
    static float linMap(float value, float low, float high);
};