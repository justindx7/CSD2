#include <iostream>
#include <string>

class Instrument {
public:
    // explicit so you can only write a instrument(string) and not just a string.
    explicit Instrument(std::string _sound);
    ~Instrument();
    void play();
//this is private using an instance to change the value
private:
    std::string sound;
};
// : sound(_sound) == sound = _sound 
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

