#include <iostream>
    float NNMap(float value, int low, int high)
    {
        
        return (value > 0.5) ? low : high;
    }
    float mapInRange(float value, int xLow, int xHigh, int yLow, int yHigh )
    {
        float output;
        output = yLow + (value - xLow) * ((yHigh - yLow) / (xHigh - xLow));
        return output;
    }
    float linMap(float value, int low, int high)
    {
        float output;
        output = mapInRange(value, 0,0,low,high);
        return output;
    }

int main(int argc, char **argv)
{
}
