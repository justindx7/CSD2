#include "wavetableGenerator.h"
#include "math.h"

void WavetableGenerator::generateWaveform(float* buffer, int bufSize,
  WaveformType waveformType) {
  Oscillator* osc;
  float freq = 1.0;
  switch(waveformType) {
    case WaveformType::SINE:
    {
      osc = new Sine(freq, bufSize);
      break;
    }
    case WaveformType::SAW:
    {
      osc = new Saw(freq, bufSize);
      break;
    }
    case WaveformType::SQUARE:
    {
      // TODO: alter calculation of to create a non-aliasing square,
      // similar to the calculation within the Saw class
      osc = new Square(freq, bufSize);
      break;
    }
    default:
      throw "WavetableGenerator::WavetableGenerator - incorrect waveformType.";
      break;
  }

  for(int i = 0; i < bufSize; i++) {
    buffer[i] = osc->genNextSample();
  }
  // release dynamically allocated oscillator object
  delete osc;
  osc = nullptr;
}

// generates an s-curve in the range [-1, 1], based arctangent function
// k: influences the curve,
//    k < 1, mimics linear function
//    k = 1, nearly linear
//    k > 1, more 'curvy'
//    k > 100, "square-like"
void WavetableGenerator::generateSCurve(float* buffer, int bufSize, float k)
{
  float normalizeFactor = 1.0f / atan(k);
  for(int i = 0; i < bufSize; i++) {
    // calculate s-curve with arctangent
    // calculate x in range [-1.0f, 1.0f]
    float x = mapInRange((float)i, 0, bufSize, -1.0f, 1.0f);
    // formula: Pirkle 2013, "Designing Audio Effect Plug-ins in C++" p. 497
    buffer[i] = normalizeFactor * atan(k * x);
  }
}

float WavetableGenerator::mapInRange(float value, int xLow, int xHigh, int yLow, int yHigh )
{
    float output;
    output = yLow + (value - xLow) * ((yHigh - yLow) / (xHigh - xLow));
    return output;
}
float WavetableGenerator::linMap(float value, int low, int high)
{
    float output;
    output = mapInRange(value, 0,0,low,high);
    return output;
}
