CXX= g++
CFLAGS = -Wall -std=c++1z
LDFLAGS= 
SOURCE=snare.o guitar.o violin.o pitchedInstrument.o percussiveInstrument.o instrument.o instrumentMain.o
TARGET=instrument

$(TARGET) : $(SOURCE)
	$(CXX) -o $@ $(CFLAGS) $(SOURCE) $(LDFLAGS)

.cpp.o:
	$(CXX) -c $< $(CFLAGS)

clean:
	rm -f $(TARGET) *.o
