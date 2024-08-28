#include "Gameboard.h"
#include "Player.h"
#include "Level.h"
#include "Level0.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "Level4.h"
#include "Level5.h"
#include "StarBlock.h"
#include <iostream>
#include "window.h"
#include <string>
#include <cctype>

using namespace std;
const int ROW = 18;
const int COL = 11;

Gameboard::Gameboard() : player1{new Player}, player2{new Player} {}

Gameboard::~Gameboard() {
    delete player1;
    delete player2;
}

Player* Gameboard::GetPlayer1() { 
    return player1; 
}

Player* Gameboard::GetPlayer2() { 
    return player2; 
}

int Gameboard::GetScore(Player* player) { 
    return player->Score; 
}

// initialize all fields in Player class
void Gameboard::initPlayer(int levelPlayer1, int levelPlayer2, int hiscore1, int hiscore2, bool command1, bool command2,
                            string file1, string file2, string seq1, string seq2) {
    player1->Score = 0;
    player1->HiScore = hiscore1;
    player1->total = 0;
    player1->uncleared = 0;
    player1->starAdd = 0;
    player1->fileName = file1;
    player1->gameover = false;
    player1->levelupNow = false;
    player1->levelupLater = false;
    player1->leveldownNow = false;
    player1->terminate = false;
    player1->leveldownLater = false;
    player1->command = command1;
    player1->level = levelPlayer1;
    player2->Score = 0;
    player2->HiScore = hiscore2;
    player2->total = 0;
    player2->uncleared = 0;
    player2->starAdd = 0;
    player2->fileName = file2;
    player2->gameover = false;
    player2->levelupNow = false;
    player2->terminate = false;
    player2->levelupLater = false;
    player2->leveldownNow = false;
    player2->leveldownLater = false;
    player2->command = command2;
    player2->level = levelPlayer2;
    player1->Range.resize(ROW);
    player2->Range.resize(ROW);
    // initialize of the PixelList
    player1->PixelList.resize(100);
    player2->PixelList.resize(100);
    // initialize of Range
    for (int i = 0; i < ROW; i++){
        player1->Range[i].resize(COL);
        player2->Range[i].resize(COL);
        for (int j = 0; j < COL; j++){
            player1->Range[i][j] = Pixel();
            player2->Range[i][j] = Pixel();
        }
    }
    // initialize of nextArea
    player1->nextArea.resize(2);
    player2->nextArea.resize(2);
    for (int i = 0; i < 2; i++) {
        player1->nextArea[i].resize(COL);
        player2->nextArea[i].resize(COL);
        for (int j = 0; j < COL; j++) {
            player1->nextArea[i][j] = Pixel();
            player2->nextArea[i][j] = Pixel();
        }
    }
    if (levelPlayer1 == 0) player1->lev = new Level0(seq1);
    if (levelPlayer2 == 0) player2->lev = new Level0(seq2);
    if (levelPlayer1 == 1) player1->lev = new Level1();
    if (levelPlayer2 == 1) player2->lev = new Level1();
    if (levelPlayer1 == 2) player1->lev = new Level2();
    if (levelPlayer2 == 2) player2->lev = new Level2();
    if (levelPlayer1 == 3) player1->lev = new Level3();
    if (levelPlayer2 == 3) player2->lev = new Level3();
    if (levelPlayer1 == 4) player1->lev = new Level4();
    if (levelPlayer2 == 4) player2->lev = new Level4();
    if (levelPlayer1 == 5) player1->lev = new Level5();
    if (levelPlayer2 == 5) player2->lev = new Level5();


}

// render gameboard display showing player stat (level, current score, highest score), 
// player next block, and current gameboard
void Gameboard::generate(Player* player1, Player* player2){
    cout << "Level:    " << player1->level << "     "
         << "Level:    " << player2->level << endl;
    cout << "Score:    " << player1->Score << "     "
         << "Score:    " << player2->Score << endl;
    cout << "HiScore:    " << player1->HiScore << "   "
         << "HiScore:    " << player2->HiScore << endl;
    cout << "-----------     -----------" << endl;
    // output Range
    for (int row = 0; row < ROW; row++){
        for (int col1 = 0; col1 < COL; col1++){
            cout << player1->Range[row][col1];
        }
        cout << "     ";
        for (int col2 = 0; col2 < COL; col2++){
            cout << player2->Range[row][col2];
        }
        cout << endl;
        if ((row + 1) == ROW){
            cout << "-----------     -----------" << endl;
            cout << "Next:           Next:      " << endl;
        }
    }
    // output nextArea
    for (int i = 0; i < 2; i++) {
        for (int col1 = 0; col1 < COL; col1++){
            cout << player1->nextArea[i][col1];
        }
        cout << "     ";
        for (int col2 = 0; col2 < COL; col2++){
            cout << player2->nextArea[i][col2];
        }
        cout << endl;
    }
    cout << endl;
}

// upload the block to graph everytime and check whether it's valid
void Gameboard::BlockUpdate(Player* player, Block* block) {
    char name = block->getType();
    int size = player->PixelList.size();
    int total = player->total;
    if (total == size - 1) {
        player->PixelList.resize(size * 2);
    }
    // check for names and render respective Block represented by Pixels
    if (name == 'I') {
        if (player->Range[3][0].GetColor() != " " || player->Range[3][1].GetColor() != " " || 
            player->Range[3][2].GetColor() != " " || player->Range[3][3].GetColor() != " ") {
                player->gameover = true;
            } else {
                player->Range[3][0].SetColor("I");
                player->Range[3][0].setNumber(player->total);
                player->Range[3][0].setLevel(player->level);

                player->Range[3][1].SetColor("I");
                player->Range[3][1].setNumber(player->total);
                player->Range[3][1].setLevel(player->level);

                player->Range[3][2].SetColor("I");
                player->Range[3][2].setNumber(player->total);
                player->Range[3][2].setLevel(player->level);

                player->Range[3][3].SetColor("I");
                player->Range[3][3].setNumber(player->total);
                player->Range[3][3].setLevel(player->level);
                player->PixelList[total] = 4;
                player->totalUp();

                for (int i = 0; i < 4; i++) {
                    block->set("X", i, 3);
                    block->set("Y", i, i);
                }
            }
    } else if (name == 'J') {
        if (player->Range[3][0].GetColor() != " " || player->Range[3][1].GetColor() != " " || 
            player->Range[3][2].GetColor() != " " || player->Range[2][0].GetColor() != " ") {
                player->gameover = true;
            } else {
                player->Range[3][0].SetColor("J");
                player->Range[3][0].setNumber(player->total);
                player->Range[3][0].setLevel(player->level);

                player->Range[3][1].SetColor("J");
                player->Range[3][1].setNumber(player->total);
                player->Range[3][1].setLevel(player->level);

                player->Range[3][2].SetColor("J");
                player->Range[3][2].setNumber(player->total);
                player->Range[3][2].setLevel(player->level);

                player->Range[2][0].SetColor("J");
                player->Range[2][0].setNumber(player->total);
                player->Range[2][0].setLevel(player->level);
                player->PixelList[total] = 4;
                player->totalUp();

                for (int i = 0; i < 3; i++) {
                    block->set("X", i, 3);
                    block->set("Y", i, i);
                }
                block->set("X",3, 2);
                block->set("Y", 3, 0);
            }
    } else if (name == 'L') {
        if (player->Range[3][0].GetColor() != " " || player->Range[3][1].GetColor() != " " || 
            player->Range[3][2].GetColor() != " " || player->Range[2][2].GetColor() != " ") {
                player->gameover = true;
            } else {
                player->Range[3][0].SetColor("L");
                player->Range[3][0].setNumber(player->total);
                player->Range[3][0].setLevel(player->level);

                player->Range[3][1].SetColor("L");
                player->Range[3][1].setNumber(player->total);
                player->Range[3][1].setLevel(player->level);

                player->Range[3][2].SetColor("L");
                player->Range[3][2].setNumber(player->total);
                player->Range[3][2].setLevel(player->level);

                player->Range[2][2].SetColor("L");
                player->Range[2][2].setNumber(player->total);
                player->Range[2][2].setLevel(player->level);
                player->PixelList[total] = 4;
                player->totalUp();

                for (int i = 0; i < 3; i++) {
                    block->set("X", i, 3);
                    block->set("Y", i, i);
                }
                block->set("X",3, 2);
                block->set("Y", 3, 2);
            }

    } else if (name == 'O') {
        if (player->Range[3][0].GetColor() != " " || player->Range[3][1].GetColor() != " " || 
            player->Range[2][0].GetColor() != " " || player->Range[2][1].GetColor() != " ") {
                player->gameover = true;
            } else {
                player->Range[3][0].SetColor("O");
                player->Range[3][0].setNumber(player->total);
                player->Range[3][0].setLevel(player->level);

                player->Range[3][1].SetColor("O");
                player->Range[3][1].setNumber(player->total);
                player->Range[3][1].setLevel(player->level);

                player->Range[2][1].SetColor("O");
                player->Range[2][1].setNumber(player->total);
                player->Range[2][1].setLevel(player->level);
                
                player->Range[2][0].SetColor("O");
                player->Range[2][0].setNumber(player->total);
                player->Range[2][0].setLevel(player->level);
                player->PixelList[total] = 4;
                player->totalUp();

                for (int i = 0; i < 2; i++) {
                    block->set("X", i, 3);
                    block->set("Y", i, i);
                }
                for (int i = 2; i < 4; i++) {
                    block->set("X", i, 2);
                    block->set("Y", i, i-2);
                }
            }
        
    } else if (name == 'S') {
        if (player->Range[3][0].GetColor() != " " || player->Range[3][1].GetColor() != " " || 
            player->Range[2][2].GetColor() != " " || player->Range[2][1].GetColor() != " ") {
                player->gameover = true;
            } else {
                player->Range[3][0].SetColor("S");
                player->Range[3][0].setNumber(player->total);
                player->Range[3][0].setLevel(player->level);

                player->Range[3][1].SetColor("S");
                player->Range[3][1].setNumber(player->total);
                player->Range[3][1].setLevel(player->level);

                player->Range[2][2].SetColor("S");
                player->Range[2][2].setNumber(player->total);
                player->Range[2][2].setLevel(player->level);
                
                player->Range[2][1].SetColor("S");
                player->Range[2][1].setNumber(player->total);
                player->Range[2][1].setLevel(player->level);
                player->PixelList[total] = 4;
                player->totalUp();

                for (int i = 0; i < 2; i++) {
                    block->set("X", i, 3);
                    block->set("Y", i, i);
                }
                for (int i = 2; i < 4; i++) {
                    block->set("X", i, 2);
                    block->set("Y", i, i-1);
                }
            }
        
    } else if (name == 'T') {
        if (player->Range[2][0].GetColor() != " " || player->Range[2][1].GetColor() != " " || 
            player->Range[2][2].GetColor() != " " || player->Range[3][1].GetColor() != " ") {
                player->gameover = true;
            } else {
                player->Range[2][0].SetColor("T");
                player->Range[2][0].setNumber(player->total);
                player->Range[2][0].setLevel(player->level);

                player->Range[2][1].SetColor("T");
                player->Range[2][1].setNumber(player->total);
                player->Range[2][1].setLevel(player->level);

                player->Range[2][2].SetColor("T");
                player->Range[2][2].setNumber(player->total);
                player->Range[2][2].setLevel(player->level);

                player->Range[3][1].SetColor("T");
                player->Range[3][1].setNumber(player->total);
                player->Range[3][1].setLevel(player->level);
                player->PixelList[total] = 4;
                player->totalUp();

                for (int i = 0; i < 3; i++) {
                    block->set("X", i, 2);
                    block->set("Y", i, i);
                }
                block->set("X", 3, 3);
                block->set("Y", 3, 1);
            }
        
    } else if (name == 'Z') {
        if (player->Range[2][0].GetColor() != " " || player->Range[3][1].GetColor() != " " || 
            player->Range[3][2].GetColor() != " " || player->Range[2][1].GetColor() != " ") {
                player->gameover = true;
            } else {
                player->Range[2][0].SetColor("Z");
                player->Range[2][0].setNumber(player->total);
                player->Range[2][0].setLevel(player->level);

                player->Range[3][1].SetColor("Z");
                player->Range[3][1].setNumber(player->total);
                player->Range[3][1].setLevel(player->level);
                
                player->Range[3][2].SetColor("Z");
                player->Range[3][2].setNumber(player->total);
                player->Range[3][2].setLevel(player->level);

                player->Range[2][1].SetColor("Z");
                player->Range[2][1].setNumber(player->total);
                player->Range[2][1].setLevel(player->level);
                player->PixelList[total] = 4;
                player->totalUp();

            }
            for (int i = 0; i < 2; i++) {
                    block->set("X", i, 2);
                    block->set("Y", i, i);
                }
            for (int i = 2; i < 4; i++) {
                    block->set("X", i, 3);
                    block->set("Y", i, i - 1);
                }
    } else if (name == '*') {
        if (player->Range[3][0].GetColor() != " ") {
                player->gameover = true;
            } else {
                player->Range[3][0].SetColor("*");
                player->Range[3][0].setNumber(player->total);
                player->Range[3][0].setLevel(player->level);
                player->PixelList[total] = 1;
                player->totalUp();
                block->set("X", 0, 3);
                block->set("Y", 0, 0);
            }
    }
}

void Gameboard::starblockAdd(Player* player) {
    for (int i = 3; i < ROW; i++) {
        if (player->Range[i][5].GetColor() == " ") {
            if ((i != ROW - 1 && player->Range[i + 1][5].GetColor() != " ") || i == ROW - 1) {
                player->Range[i][5].SetColor("*");
                player->Range[i][5].setNumber(player->total);
                player->totalUp();
                player->Range[i][5].setLevel(player->level);
                return;
            }
        } else if (i == ROW - 1) {
            player->gameover = true;
        }
    }
    return;
}

void Gameboard::replaceBlock(Player* player, Block* block1, Block* block2) {
    for (int i = 0; i < 4; i++) {
        int x = block1->get("X", i);
        int y = block1->get("Y", i);
        player->Range[x][y] = Pixel();
    }
    bool state = block1->getState();
    block2->setState(state);
    (player->total)--;
    BlockUpdate(player, block2);
}

void Gameboard::nextUpdate(Player* player, Block* block) {
    char name = block->getType();
    if (name == 'I') {
        player->nextArea[1][0].SetColor("I");
        player->nextArea[1][1].SetColor("I");
        player->nextArea[1][2].SetColor("I");
        player->nextArea[1][3].SetColor("I");
    } else if (name == 'J') {
        player->nextArea[0][0].SetColor("J");
        player->nextArea[1][0].SetColor("J");
        player->nextArea[1][1].SetColor("J");
        player->nextArea[1][2].SetColor("J");
    } else if (name == 'L') {
        player->nextArea[0][2].SetColor("L");
        player->nextArea[1][0].SetColor("L");
        player->nextArea[1][1].SetColor("L");
        player->nextArea[1][2].SetColor("L");
    } else if (name == 'O') {
        player->nextArea[0][0].SetColor("O");
        player->nextArea[1][0].SetColor("O");
        player->nextArea[1][1].SetColor("O");
        player->nextArea[0][1].SetColor("O");
    } else if (name == 'S') {
        player->nextArea[0][1].SetColor("S");
        player->nextArea[0][2].SetColor("S");
        player->nextArea[1][1].SetColor("S");
        player->nextArea[1][0].SetColor("S");
    } else if (name == 'T') {
        player->nextArea[0][0].SetColor("T");
        player->nextArea[0][1].SetColor("T");
        player->nextArea[0][2].SetColor("T");
        player->nextArea[1][1].SetColor("T");
    } else if (name == 'Z') {
        player->nextArea[0][0].SetColor("Z");
        player->nextArea[0][1].SetColor("Z");
        player->nextArea[1][2].SetColor("Z");
        player->nextArea[1][1].SetColor("Z");
    } else if (name == '*') {
        player->nextArea[0][0].SetColor("*");
    } 
}

// after dropping a block, clear opponent player's next block area to blank
void Gameboard::clearNext(Player* player) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < COL; j++) {
            player->nextArea[i][j].SetColor(" ");
        }
    }
}

// clear a line with same element
void Gameboard::clearLine(Player* player, int& num, int& add) {
    for (int i = ROW - 1; i >= 3; i--) {
        bool judge = true;
        for (int j = 0; j < COL; j++) {
            if (player->Range[i][j].GetColor() == " ") {
                judge = false;
                break;
            }
        }
        // need to add special action later...
        if (judge) {
            num++;
            for (int clear = i; clear >= 3; clear--) {
                for (int j = 0; j < COL; j++) {
                    int num = player->Range[i][j].getNumber();
                    int pixel = player->PixelList[num];
                    int level = player->Range[i][j].getLevel();
                    int newnum = player->Range[i - 1][j].getNumber();
                    int newlevel = player->Range[i - 1][j].getLevel();
                    if (clear == i) {
                        if (pixel == 1) {
                        add += ((1 + level) * (1 + level));
                    }
                    (player->PixelList[num])--;
                    }
                    string color = player->Range[i - 1][j].GetColor();
                    player->Range[i][j].SetColor(color);
                    player->Range[i][j].setNumber(newnum);
                    player->Range[i][j].setLevel(newlevel);
                }
            }
        }
    }
}

// reads commands and moves blocks
void Gameboard::move(string direction, Player* player, Block* block) {
    char name = block->getType();
    // check if move in desired direction is possible, and update judge if impossible
    bool judge = true;
    for (int i = 0; i < 4; i++) {
        if (name != '*' || i == 0) {
        int x = block->get("X", i);
        int y = block->get("Y", i);
            if (direction == "left") {
                if ( y == 0 || (player->Range[x][y - 1].GetColor() != " " && !(block->exist(x, y - 1)))) {
                    judge = false;
                }
            } else if (direction == "right") {
                if ( y == COL - 1 || ((player->Range[x][y + 1].GetColor() != " ") && !(block->exist(x, y + 1)))) {
                    judge = false;
                }
            } else if (direction == "down") {
                if (x == ROW - 1 || (player->Range[x + 1][y].GetColor() != " " && !(block->exist(x + 1, y)))) {
                    judge = false;
                }
            } 
        }
    }
    if (judge) {
        Block* copy = block->getPtr();
        block->getCopy(copy);    
        // moves each cell of the block in the desired direction and updates the game board.
        for (int i = 0; i < 4; i++) {
            if (name != '*' || i == 0) {
                int x = block->get("X", i);
                int y = block->get("Y", i);
                string color = player->Range[x][y].GetColor();
                int num = player->Range[x][y].getNumber();
                int level = player->Range[x][y].getLevel();
                if (direction == "left") {
                    player->Range[x][y - 1].SetColor(color);
                    player->Range[x][y - 1].setNumber(num);
                    player->Range[x][y - 1].setLevel(level);
                    block->set("Y", i, y - 1);
                } else if (direction == "right") {
                    player->Range[x][y + 1].SetColor(color);
                    player->Range[x][y + 1].setNumber(num);
                    player->Range[x][y + 1].setLevel(level);
                    block->set("Y", i, y + 1);
                }else if (direction == "down") {
                    player->Range[x + 1][y].SetColor(color);
                    player->Range[x + 1][y].setNumber(num);
                    player->Range[x + 1][y].setLevel(level);
                    block->set("X", i, x + 1);
                } 
            }
        }
        // resets the old position of the block on the game board.
        for (int i = 0; i < 4; i++) {
            int x = copy->get("X", i);
            int y = copy->get("Y", i);
            if (!(block->exist(x, y))) {
                player->Range[x][y] = Pixel();
            }
        }
    }
}

// checks whether the game has ended for a particular player and block
bool Gameboard::endCheck(Player* player, Block* block) {
    for (int i = 0; i < 4; i++) {
        int x = block->get("X", i);
        int y = block->get("Y", i);
        if (x == ROW - 1) {
            return true;
        } else if (player->Range[x + 1][y].GetColor() != " ") {
            if (!(block->exist(x + 1, y))) {
                return true;
            }
        }
    }
    return false;
}

// rotates a given block in the clockwise direction on the game board for a specific player
void Gameboard::CW(Player* player, Block* block) {
    Block* copy = block->getPtr();
    block->getCopy(copy);
    // rotate block
    block->CW();
    // resets the color of the old position of the block on the game board
    for (int i = 0; i < 4; i++) {
        int x = copy->get("X", i);
        int y = copy->get("Y", i);
        player->Range[x][y].SetColor(" ");
    }
    // updates the color of the new position of the block on the game board
    for (int i = 0; i < 4; i++) {
        int x = block->get("X", i);
        int y = block->get("Y", i);
        int num = player->Range[x][y].getNumber();
        int level = player->Range[x][y].getLevel();
        player->Range[x][y].setNumber(num);
        player->Range[x][y].setLevel(level);
        char color = block->getType();
        if (color == 'I') {
            player->Range[x][y].SetColor("I");
        } else if (color == 'J') {
            player->Range[x][y].SetColor("J");
        } else if (color == 'L') {
            player->Range[x][y].SetColor("L");
        } else if (color == 'O') {
            player->Range[x][y].SetColor("O");
        } else if (color == 'S') {
            player->Range[x][y].SetColor("S");
        } else if (color == '*') {
            player->Range[x][y].SetColor("*");
        } else if (color == 'T') {
            player->Range[x][y].SetColor("T");
        } else if (color == 'Z') {
            player->Range[x][y].SetColor("Z");
        }
    }
}

// render graphic display
void Gameboard::graphicDisplay(Player* playerone, Player* playertwo, Xwindow *window) {
    int infoStartX1 = 10; // Adjust these values based on the desired position
    int infoStartY1 = 10;
    int score1 = playerone->Score;
    int level1 = playerone->level;
    int hiscore1 = playerone->HiScore;
    string levelInfo1 = "Level: " + to_string(level1);
    string scoreInfo1 = "Score: " + to_string(score1);
    string hiInfo1 = "HiScore: " + to_string(hiscore1);
    window->drawString(infoStartX1, infoStartY1, levelInfo1);
    window->drawString(infoStartX1, infoStartY1 + 20, scoreInfo1);
    window->drawString(infoStartX1, infoStartY1 + 40, hiInfo1);

    // Draw the player two information
    int infoStartX2 = 200; // Adjust these values based on the desired position
    int infoStartY2 = 10;
    int score2 = playertwo->Score;
    int level2 = playertwo->level;
    int hiscore2 = playertwo->HiScore;
    string levelInfo2 = "Level: " + to_string(level2);
    string scoreInfo2 = "Score: " + to_string(score2);
    string hiInfo2 = "HiScore: " + to_string(hiscore2);
    window->drawString(infoStartX2, infoStartY2, levelInfo2);
    window->drawString(infoStartX2, infoStartY2 + 20, scoreInfo2);
    window->drawString(infoStartX2, infoStartY2 + 40, hiInfo2);
    int linestartX = 10;
    int linestartY = 60;
    window->drawString(linestartX, linestartY, "---------------------------     ---------------------------");
    int boardStartX1 = 10; // Adjust these values based on the desired position
    int boardStartY1 = 60;
    int boardStartX2 = 200;
    int boardStartY2 = 60;
    int blockSize = 10; // Adjust the block size as needed
    for (int row = 0; row < ROW; row++) {
        for (int col = 0; col < COL; col++) {
            string leftcolor = player1->Range[row][col].GetColor();
            string rightcolor = player2->Range[row][col].GetColor();
            int x1 = boardStartX1 + col * blockSize;
            int y1 = boardStartY1 + row * blockSize;
            int x2 = boardStartX2 + col * blockSize;
            int y2 = boardStartY2 + row * blockSize;
            if (player1->isBlind) {
                window->fillRectangle(x1, y1, blockSize, blockSize, Xwindow::Cyan);
            } else if (leftcolor == " ") {
                window->fillRectangle(x1, y1, blockSize, blockSize, Xwindow::White);
            } else if (leftcolor == "I") {
                window->fillRectangle(x1, y1, blockSize, blockSize, Xwindow::Black);
            } else if (leftcolor == "J") {
                window->fillRectangle(x1, y1, blockSize, blockSize, Xwindow::Blue);
            } else if (leftcolor == "L") {
                window->fillRectangle(x1, y1, blockSize, blockSize, Xwindow::Red);
            } else if (leftcolor == "O") {
                window->fillRectangle(x1, y1, blockSize, blockSize, Xwindow::Green);
            } else if (leftcolor == "T") {
                window->fillRectangle(x1, y1, blockSize, blockSize, Xwindow::Yellow);
            } else if (leftcolor == "Z") {
                window->fillRectangle(x1, y1, blockSize, blockSize, Xwindow::Orange);
            } else if (leftcolor == "*") {
                window->fillRectangle(x1, y1, blockSize, blockSize, Xwindow::Brown);
            } else if (leftcolor == "S") {
                window->fillRectangle(x1, y1, blockSize, blockSize, Xwindow::Magenta);
            }

            if (player2->isBlind) {
                window->fillRectangle(x2, y2, blockSize, blockSize, Xwindow::Cyan);
            } if (rightcolor == " ") {
                window->fillRectangle(x2, y2, blockSize, blockSize, Xwindow::White);
            } else if (rightcolor == "I") {
                window->fillRectangle(x2, y2, blockSize, blockSize, Xwindow::Black);
            } else if (rightcolor == "J") {
                window->fillRectangle(x2, y2, blockSize, blockSize, Xwindow::Blue);
            } else if (rightcolor == "L") {
                window->fillRectangle(x2, y2, blockSize, blockSize, Xwindow::Red);
            } else if (rightcolor == "O") {
                window->fillRectangle(x2, y2, blockSize, blockSize, Xwindow::Green);
            } else if (rightcolor == "T") {
                window->fillRectangle(x2, y2, blockSize, blockSize, Xwindow::Yellow);
            } else if (rightcolor == "Z") {
                window->fillRectangle(x2, y2, blockSize, blockSize, Xwindow::Orange);
            } else if (rightcolor == "*") {
                window->fillRectangle(x2, y2, blockSize, blockSize, Xwindow::Brown);
            } else if (rightcolor == "S") {
                window->fillRectangle(x2, y2, blockSize, blockSize, Xwindow::Magenta);
            }
            }
        }
    int linestartX2 = 10;
    int linestartY2 = 260;
    window->drawString(linestartX2, linestartY2, "---------------------------     ---------------------------");
    int nextStartX1 = 10;
    int nextStartY1 = 280;
    int nextStartX2 = 200;
    int nextStartY2 = 280;
    window->drawString(nextStartX1, nextStartY1, "Next: ");
    window->drawString(nextStartX2, nextStartY2, "Next: ");
    int boardStartX3 = 10; // Adjust these values based on the desired position
    int boardStartY3 = 300;
    int boardStartX4 = 200;
    int boardStartY4 = 300;
    for (int row = 0; row < 2; row++) {
        for (int col = 0; col < COL; col++) {
            string leftcolor = player1->nextArea[row][col].GetColor();
            string rightcolor = player2->nextArea[row][col].GetColor();
            int x3 = boardStartX3 + col * blockSize;
            int y3 = boardStartY3 + row * blockSize;
            int x4 = boardStartX4 + col * blockSize;
            int y4 = boardStartY4 + row * blockSize;
            if (leftcolor == " ") {
                window->fillRectangle(x3, y3, blockSize, blockSize, Xwindow::White);
            } else if (leftcolor == "I") {
                window->fillRectangle(x3, y3, blockSize, blockSize, Xwindow::Black);
            } else if (leftcolor == "J") {
                window->fillRectangle(x3, y3, blockSize, blockSize, Xwindow::Blue);
            } else if (leftcolor == "L") {
                   window->fillRectangle(x3, y3, blockSize, blockSize, Xwindow::Red);
            } else if (leftcolor == "O") {
                window->fillRectangle(x3, y3, blockSize, blockSize, Xwindow::Green);
            } else if (leftcolor == "T") {
                window->fillRectangle(x3, y3, blockSize, blockSize, Xwindow::Yellow);
            } else if (leftcolor == "Z") {
                window->fillRectangle(x3, y3, blockSize, blockSize, Xwindow::Orange);
            } else if (leftcolor == "*") {
                window->fillRectangle(x3, y3, blockSize, blockSize, Xwindow::Brown);
            } else if (leftcolor == "S") {
                window->fillRectangle(x3, y3, blockSize, blockSize, Xwindow::Magenta);
            }

            if (rightcolor == " ") {
                window->fillRectangle(x4, y4, blockSize, blockSize, Xwindow::White);
            } else if (rightcolor == "I") {
                window->fillRectangle(x4, y4, blockSize, blockSize, Xwindow::Black);
            } else if (rightcolor == "J") {
                window->fillRectangle(x4, y4, blockSize, blockSize, Xwindow::Blue);
            } else if (rightcolor == "L") {
                window->fillRectangle(x4, y4, blockSize, blockSize, Xwindow::Red);
            } else if (rightcolor == "O") {
                window->fillRectangle(x4, y4, blockSize, blockSize, Xwindow::Green);
            } else if (rightcolor == "T") {
                window->fillRectangle(x4, y4, blockSize, blockSize, Xwindow::Yellow);
            } else if (rightcolor == "Z") {
                window->fillRectangle(x4, y4, blockSize, blockSize, Xwindow::Orange);
            } else if (rightcolor == "S") {
                window->fillRectangle(x4, y4, blockSize, blockSize, Xwindow::Magenta);
            } else if (rightcolor == "*") {
                window->fillRectangle(x4, y4, blockSize, blockSize, Xwindow::Brown);
            }
            }
        }
    
}

// update gameboard based on shortcut input, eg. 3down, 2levelup
string Gameboard::shortcut(string cmd, int& times) {
    int length = cmd.length();
    string number = "";
    int index = 0;
    bool nodigit = true;
    for (int i = 0; i < length; i++) {
        char letter = cmd[i];
        if (isdigit(letter)) {
            string str(1, letter);
            number += str;
            index++;
            nodigit = false;
        } else {
            break;
        }
    }
    if (number != "" || (number == "" && nodigit)) {
        if (number != "") {
            times = stoi(number);
        } else {
            times = 1;
        }
        string command = cmd.substr(index, length - index);
        if (command == "dr" || command == "dro" || command == "drop") {
            return "drop";
        } else if (command == "lef" || command == "left") {
            return "left";
        } else if (command == "levelu" || command == "levelup") {
            return "levelup";
        } else if (command == "leveld" || command == "leveldo" || command == "leveldow" || command == "leveldown") {
            return "leveldown";
        } else if (command == "do" || command == "dow" || command == "down") {
            return "down";
        } else if (command == "r" || command == "ri" || command == "rig" || command == "righ" || command == "right") {
            return "right";
        }
    }
    return "";
}
