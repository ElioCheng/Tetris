#ifndef Gameboard_hpp
#define Gameboard_hpp
#include "Player.h"
#include "Pixel.h"
#include "window.h"
#include "StarBlock.h"
#include <iostream>
#include <vector>
#include <string>
#include <memory>
using namespace std;


class Gameboard {
    Player* player1;
    Player* player2;
  public:
    bool TextDisplay = true;
    bool GraphicDisplay = true;
    Gameboard();
    ~Gameboard ();
    void initPlayer(int levelPlayer1, int levelPlayer2, int hiscore1, int hiscore2, 
                    bool command1, bool command2, string file1, string file2, string seq1, string seq2);
    Player* GetPlayer1();
    Player* GetPlayer2();
    int GetScore(Player* player);
    void generate(Player* player1, Player* player2);
    void BlockUpdate(Player* player, Block* block);
    void clearLine(Player* player, int& num, int& add);
    void move(string direction, Player* player, Block* block);
    void CW(Player* player, Block* block);
    void nextUpdate(Player* player, Block* block);
    void clearNext(Player* player);
    void replaceBlock(Player* player, Block* block1, Block* block2);
    bool endCheck(Player* player, Block* block);
    void starblockAdd(Player* player);
    void graphicDisplay(Player* playerone, Player* playertwo,Xwindow *window);
    string shortcut(string cmd, int& times);
};

#endif 


