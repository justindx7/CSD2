class CircBuffer 
{
    public:
    CircBuffer(int size, int numSamplesDelay);
    ~CircBuffer();

   void write(float value);
    float read();

    private:
    void wrapH(int head);
    void getDistanceRW();
    int size = 0;
    int numSamplesDelay = 0;
    float* buffer;

    int readH = size - numSamplesDelay;
    int writeH = 0;
};
