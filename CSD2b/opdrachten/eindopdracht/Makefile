CXX= g++
CFLAGS = -I/usr/local/include -Wall -std=c++1z
LDFLAGS= -ljack
SOURCE=jack_module.o sine.o oscillator.o main.o
TARGET=synth

$(TARGET) : $(SOURCE)
	$(CXX) -o $@ $(CFLAGS) $(SOURCE) $(LDFLAGS)

.cpp.o:
	$(CXX) -c $< $(CFLAGS)

clean:
	rm -f $(TARGET) *.o
