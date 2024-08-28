#include "Pixel.h"

using namespace std;

Pixel::Pixel(): blind(false), color(" "), currentLevel(0), blockNumber(0) {}

Pixel::~Pixel() {}

void Pixel::TurnBlind() { 
    blind = true; 
}

void Pixel::NotBlind(){
    blind = false; 
}

bool Pixel::getBlind() {
    return blind;
}

void Pixel::setLevel(int level) {
    currentLevel = level;
    return;
}

int Pixel::getLevel() { 
    return currentLevel; 
}
  
void Pixel::setNumber(int num) {
    blockNumber = num;
    return;
}

int Pixel::getNumber() { 
    return blockNumber; 
}

ostream &operator<<(ostream &out, const Pixel &c) {
    if (!(c.blind)){
        out << c.color;
    }
    else {
        out << "?";
    }
    return out;
}

string Pixel::GetColor () { 
    return color; 
}

void Pixel::SetColor(string colorName) { 
    color = colorName;
}
