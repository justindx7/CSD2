#pragma once
#include <iostream>
#include "effect.h"
#include "AudioFile.h"
#include <algorithm>
#include <vector>
using namespace std;
#include "writeToFile.h"

class SampleShaper : public effect
{
public:
  SampleShaper(float drywet,bool bypass);
  ~SampleShaper();

  void fillBuffer();

private:
  vector<float> v;

  float floatCount;
  int vectorSize;
  int bufSize;
  void fillBuffer();
  void sampleAverage();


};
