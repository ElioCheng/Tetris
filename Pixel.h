#ifndef __CELL_H__
#define __CELL_H__
#include <iostream>
#include <string>
using namespace std;

class Pixel {
  bool blind;
  string color;
  int currentLevel;
  int blockNumber;

 public:
  Pixel(); 
  ~Pixel(); 
  void TurnBlind();
  void NotBlind();
  bool getBlind();
  string GetColor ();
  void SetColor (string colorName);
  void setLevel(int level);
  int getLevel();
  void setNumber(int num);
  int getNumber();
  friend ostream& operator<<(ostream &out, const Pixel &c);
};


#endif
