CXX= g++
CFLAGS = -g -I/usr/local/include -Wall -std=c++17
LDFLAGS= -ljack
SOURCE=jack_module.o sine.o square.o saw.o oscillator.o main.o writeToFile.o synth.o simpleSynth.o squareSynth.o adSynth.o melody.o
TARGET=synth

$(TARGET) : $(SOURCE)
	$(CXX) -o $@ $(CFLAGS) $(SOURCE) $(LDFLAGS)

.cpp.o:
	$(CXX) -c $< $(CFLAGS)

clean:
	rm -f $(TARGET) *.o
