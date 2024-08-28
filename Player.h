#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Block.h"
#include "Pixel.h"
#include <vector>
#include <iostream>
#include <string>
#include <memory>
#include "Level.h"
using namespace std;

struct Player{
    vector<vector<Pixel>> Range;
    vector<vector<Pixel>> nextArea;
    vector<int> PixelList;
    int Score;
    int HiScore;
    int total;
    int level;
    int col;
    int row;
    int uncleared;
    int starAdd;
    string fileName;
    Level* lev;
    bool validCW;
    bool validCCW;
    bool gameover;
    bool isHeavy;
    bool isBlind;
    bool levelupNow;
    bool levelupLater;
    bool leveldownNow;
    bool leveldownLater;
    bool command;
    bool terminate;
    void totalUp() {
        total++;
        return;
    }
};

#endif
