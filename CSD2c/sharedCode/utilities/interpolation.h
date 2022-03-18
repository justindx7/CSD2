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

    static float mapInRange(float value, int xLow, int xHigh, int yLow, int yHigh);
    static float linMap(float value, int low, int high);
};