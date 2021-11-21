#include <iostream>
#include <string>

class Instrument {
public:
    explicit Instrument(std::string _sound);
    ~Instrument();
    void play();
private:
    std::string sound;
};

Instrument::Instrument(std::string _sound): sound(_sound)
{
    std::cout <<"Concustructor called" << std::endl;
}
Instrument::~Instrument(){
    std::cout <<"Destructor called" << std::endl;

}
void Instrument::play(){
    std::cout << sound << std::endl;
}

int main()
{
    Instrument flute("ffffjt");
    Instrument snare("tak");
    flute.play();
    snare.play();
}

