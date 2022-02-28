#pragma once
#include <iostream>
#include "sine.h"
#include "saw.h"
#include "square.h"

class WavetableGenerator
{
public:
  enum WaveformType {
    SINE = 0, // ensure enum starts at 0
    SAW,
    SQUARE,
    SIZE // 3
  };

  // generates a standard waveform in the range [-1, 1]
  static void generateWaveform(float* buffer, int bufSize,
    WaveformType waveformType);

  // generates an s-curve in the range [-1, 1], based arctangent function
  // k: influences the curve,
  //    k < 1, mimics linear function
  //    k = 1, nearly linear
  //    k > 1, more 'curvy'
  //    k > 100, "square-like"
  static void generateSCurve(float* buffer, int bufSize, float k);

private:
  // hide default constructor
  WavetableGenerator() {};

   static float mapInRange(float value, int xLow, int xHigh, int yLow, int yHigh);

   static float linMap(float value, int low, int high);
   

};
