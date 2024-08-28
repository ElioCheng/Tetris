#include "Player.h"
#include "Pixel.h"
#include "Gameboard.h"
#include "Block.h"
#include "IBlock.h"
#include "JBlock.h"
#include "LBlock.h"
#include "OBlock.h"
#include "SBlock.h"
#include "TBlock.h"
#include "ZBlock.h"
#include "StarBlock.h"
#include "window.h"
#include "Level.h"
#include "Level0.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "Level4.h"
#include "Level5.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <termios.h>
#include <cctype>

using namespace std;
const string SEQUENCE_ONE = "sequence1.txt";
const string SEQUENCE_TWO = "sequence2.txt";

int main(int args, char *argv[]) {
    string seq1 = SEQUENCE_ONE;
    string seq2 = SEQUENCE_TWO;
    vector<string> cmd1;
    vector<string> cmd2;
    int index1;
    int index2;
    int initlevel = 0;
    int turn = 0;
    bool bonus = false;
    bool LevelRestrict1 = false;
    bool LevelRestrict2 = false;
    bool quit = false;
    bool neverAdd1 = false;
    bool neverAdd2 = false;
    Gameboard board;
    for (int i = 1; i < args; ++i) {
        string cmd = argv[i];
        if (cmd == "-text") {
            // only text display
            board.GraphicDisplay = false;
        } else if (cmd == "-seed") {
            // sets the random number generator’s seed to unsigned int number
            i++;
            istringstream iss(argv[i]);
            unsigned int number;
            iss >> number;
            srand(number);
        } else if (cmd == "-scriptfile1") {
            // store filename
            seq1 = argv[++i];
        } else if (cmd == "-scriptfile2") {
            // store filename
            seq2 = argv[++i];
        } else if (cmd == "-startlevel") {
            // update level number
            istringstream iss(argv[++i]);
            iss >> initlevel;
        } else if (cmd == "-enablebonus") {
            bonus = true;
        }
    }
    // initialize players, gameboard, and display
    board.initPlayer(initlevel,initlevel, 0,0,false,false,"","",seq1,seq2);
    Player* playerone = board.GetPlayer1();
    Player* playertwo = board.GetPlayer2();
    string command;
    Xwindow *window = nullptr;
    // initialize the board
    if (board.GraphicDisplay) {
        window = new Xwindow(400, 600);
    }
    board.generate(playerone, playertwo);
    if (board.GraphicDisplay) board.graphicDisplay(playerone, playertwo, window);
    Block* leftBlock = playerone->lev->generateBlock();
    Block* rightBlock = playertwo->lev->generateBlock();
    board.BlockUpdate(playerone, leftBlock);
    board.nextUpdate(playertwo, rightBlock);
    board.generate(playerone, playertwo);
    if (board.GraphicDisplay) board.graphicDisplay(playerone, playertwo, window);
    while (!quit) {
    // start to read commands and play game
    while (cin >> command) {
        // turn is even: player1 turn; turn is odd: player2 turn
        if (turn % 2 == 0) {
            // player 1 turn
            // judge is a first time check
            bool judge = true;
            while ((playerone->command || judge || cin >> command) && !playerone->gameover) {
                if (playerone->command) {
                    command = cmd1[index1];
                    index1++; 
                    int size = cmd1.size();
                    if (index1 >= size) {
                        playerone->terminate = true;
                    }
                }
                // // bonus: support for keyboard left/right/down arrow input
                if (bonus) {
                    istringstream iss(command);
                    char c,d,e;
                    iss >> c >> d >> e;
                    // eg. left arrow is read as : ^[D, which corresponds to char 27, 91, 68
                    if ((c==27)&&(d==91)) {
                        if (e==66) { command = "down"; }
                        if (e==67) { command = "right"; }
                        if (e==68) { command = "left"; }
                    }    
                }
                // commands and several shortcuts
                if (command == "drop" || command == "ss") {
                    for (int i = 0; i < 15; i++) {
                        board.move("down", playerone, leftBlock);   
                    }
                    if (playerone->isBlind) {
                        for (int i = 3; i < 12; i++) {
                            for (int j = 3; j < 9; j++) {
                                playerone->Range[i][j].NotBlind();
                            }
                        }
                        playerone->isBlind = false;
                    }
                    break;
                } else if (command == "left" || command == "a" || command == "lef") {
                    board.move("left", playerone, leftBlock);
                    if (playerone->isHeavy) {
                        board.move("down", playerone, leftBlock);
                        board.move("down", playerone, leftBlock);
                    }
                } else if (command == "right" || command == "d" || command == "ri" || 
                           command == "rig" || command == "righ") {
                    board.move("right", playerone, leftBlock);
                    if (playerone->isHeavy) {
                        board.move("down", playerone, leftBlock);
                        board.move("down", playerone, leftBlock);
                    }
                } else if (command == "down" || command == "s" || command == "dow") {
                    board.move("down", playerone, leftBlock);
                } else if (command == "clockwise" || command == "e" || command == "cw") {
                    board.CW(playerone, leftBlock);
                } else if (command == "counterclockwise" || command == "q" || command == "ccw") {
                    board.CW(playerone, leftBlock);
                    board.CW(playerone, leftBlock);
                    board.CW(playerone, leftBlock);
                // levelup
                } else if (command == "levelup") {
                    if (playerone->level < 4 || (playerone->level == 4 && LevelRestrict1)) {
                        playerone->levelupLater = true;
                        (playerone->level)++;
                    } else {
                        cout << "unable to level up" << endl;
                    }
                // leveldown
                } else if (command == "leveldown") {
                    if (playerone->level > 0) {
                        playerone->leveldownLater = true;
                        (playerone->level)--;
                    } else {
                        cout << "unable to level down" << endl;
                    }
                } else if (command == "norandom" && playerone->level >= 3) {
                    string fileName;
                    if (playerone->command) {
                        fileName = cmd1[index1];
                        index1++; 
                        int size = cmd1.size();
                        if (index1 >= size) {
                            playerone->terminate = true;
                        }
                    } else {
                        cin >> fileName;
                    }
                    playerone->lev = new Level0(fileName);
                } else if (command == "random") {
                    if (playerone->level == 3) {
                        playerone->lev = new Level3();
                    } else if (playerone->level == 4) {
                        playerone->lev = new Level4();
                    } else if (playerone->level == 5) {
                        playerone->lev = new Level5();
                    }
                // replace the block
                } else if (command == "I") {
                    IBlock iblock;
                    Block* newBlock = iblock.getPtr();
                    board.replaceBlock(playerone, leftBlock, newBlock);
                    leftBlock = newBlock;
                } else if (command == "J") {
                    JBlock jblock;
                    Block* newBlock = jblock.getPtr();
                    board.replaceBlock(playerone, leftBlock, newBlock);
                    leftBlock = newBlock;
                } else if (command == "L") {
                    LBlock lblock;
                    Block* newBlock = lblock.getPtr();
                    board.replaceBlock(playerone, leftBlock, newBlock);
                    leftBlock = newBlock;
                } else if (command == "O") {
                    OBlock oblock;
                    Block* newBlock = oblock.getPtr();
                    board.replaceBlock(playerone, leftBlock, newBlock);
                    leftBlock = newBlock;
                } else if (command == "S") {
                    SBlock sblock;
                    Block* newBlock = sblock.getPtr();
                    board.replaceBlock(playerone, leftBlock, newBlock);
                    leftBlock = newBlock;
                } else if (command == "T") {
                    TBlock tblock;
                    Block* newBlock = tblock.getPtr();
                    board.replaceBlock(playerone, leftBlock, newBlock);
                    leftBlock = newBlock;
                } else if (command == "Z") {
                    ZBlock zblock;
                    Block* newBlock = zblock.getPtr();
                    board.replaceBlock(playerone, leftBlock, newBlock);
                    leftBlock = newBlock;
                } else if (command == "restart") {
                    board.initPlayer(playerone->level,playertwo->level, playerone->HiScore, playertwo->HiScore, playerone->command, playertwo->command,
                    playerone->fileName, playertwo->fileName, seq1, seq2);
                } else if (command == "sequence") {
                    string fileName;
                    cin >> fileName;
                    ifstream file{fileName};
                    string cmd;
                    while (file >> cmd) {
                        cmd1.push_back(cmd);
                    }
                    playerone->command = true;
                } else {
                    // shortcut input support: eg. 3down, 2levelup
                    int times = 0;
                    string cmd = board.shortcut(command, times);
                    if ((cmd == "down" || cmd == "right" || cmd == "left") && leftBlock->getState() == true){
                        for (int i = 0; i < times; i++) {
                            board.move("down", playerone, leftBlock);
                        }
                    }
                    if (cmd == "right") {
                        for (int i = 0; i < times; i++) {
                            board.move("right", playerone, leftBlock);
                            if (playerone->isHeavy) {
                                board.move("down", playerone, leftBlock);
                                board.move("down", playerone, leftBlock);
                            }
                        }
                    } else if (cmd == "left") {
                        for (int i = 0; i < times; i++) {
                            board.move("left", playerone, leftBlock);
                            if (playerone->isHeavy) {
                                board.move("down", playerone, leftBlock);
                                board.move("down", playerone, leftBlock);
                            }
                        }
                    } else if (cmd == "down") {
                        for (int i = 0; i < times; i++) {
                            board.move("down", playerone, leftBlock);
                        }
                    } else if (cmd == "levelup") {
                        int newlevel = playerone->level + times;
                        if (newlevel <= 5 && times != 0) {
                            playerone->level = newlevel;
                            playerone->levelupNow = true;
                            if (newlevel == 0) {
                                playerone->lev = new Level0(seq1);
                            } else if (newlevel == 1) {
                                playerone->lev = new Level1();
                            } else if (newlevel == 2) {
                                playerone->lev = new Level2();
                            } else if (newlevel == 3) {
                                playerone->lev = new Level3();
                            } else if (newlevel == 4) {
                                playerone->lev = new Level4();
                            } else if (newlevel == 5) {
                                if (LevelRestrict1) {
                                    playerone->lev = new Level5();
                                } else {
                                    playerone->levelupLater = false;
                                    playerone->level = newlevel - times;
                                    cout << "Sorry, You didn't meet requirement of Level5. Please try winning at least one time with level4" << endl;
                                }
                            }
                        }
                    } else if (cmd == "leveldown") {
                        int newlevel = playerone->level - times;
                        if (newlevel >= 0) {
                            playerone->leveldownLater = true;
                            playerone->level = newlevel;
                            if (newlevel == 0) {
                                playerone->lev = new Level0(seq1);
                            } else if (newlevel == 1) {
                                playerone->lev = new Level1();
                            } else if (newlevel == 2) {
                                playerone->lev = new Level2();
                            } else if (newlevel == 3) {
                                playerone->lev = new Level3();
                            } else if (newlevel == 4) {
                                playerone->lev = new Level4();
                            } else if (newlevel == 5) {
                                if (LevelRestrict1) {
                                    playerone->lev = new Level5();
                                } else {
                                    playerone->leveldownLater = false;
                                    playerone->level = newlevel - times;
                                    cout << "Sorry, You didn't meet requirement of Level5. Please try winning at least one time with level4" << endl;
                                }
                            }
                        }
                    }
                }
                // update and render graphic after reading commands
                board.generate(playerone, playertwo);
                if (board.GraphicDisplay) board.graphicDisplay(playerone, playertwo, window);
                if (board.endCheck(playerone, leftBlock)) {
                    // playerone finished
                    if (playerone->isBlind) {
                        for (int i = 3; i < 12; i++) {
                            for (int j = 3; j <9; j++) {
                                playerone->Range[i][j].NotBlind();
                            }
                        }
                        playerone->isBlind = false;
                    }
                    break;
                }
                judge = false;
            }
            // check if game is over and needs to determinate
            if(playerone->gameover != true || playerone->terminate != true) {
                int clear = 0;
                int add = 0;
                board.clearLine(playerone, clear, add);
                // Level5 restrict
                if (playerone->level != 5) {
                    playerone->Score += add;
                } else {
                    if (clear == 0 && (playerone->uncleared + 1 == 10)) {
                        neverAdd1 = true;
                    }
                    if (!neverAdd1){
                        playerone->Score += add;
                    }
                }
                // level-specific features eg. not clearing any row in five turns -> add starblock
                if (clear != 0) {
                    playerone->Score += ((playerone->level + clear) * (playerone->level + clear));
                    playerone->uncleared = 0;
                } else if (playerone->level == 4){
                    (playerone->uncleared)++;
                    if (playerone->uncleared == 10) {
                        playerone->uncleared = 0;
                        board.starblockAdd(playerone);
                    } else if (playerone->uncleared == 5) {
                        board.starblockAdd(playerone);
                    } 
                }
                board.clearLine(playerone, clear, add);
                board.clearLine(playerone, clear, add);
                board.clearLine(playerone, clear, add);
                if (playerone->Score > playerone->HiScore) {
                    playerone->HiScore = playerone->Score;
                }
                // special actions
                if (clear >= 2) {
                    board.generate(playerone, playertwo);
                    if (board.GraphicDisplay) board.graphicDisplay(playerone, playertwo, window);
                    cout << "Congratulations! You have triggered special Action! You can choose blind, heavy or force!" << endl;
                    cout << "Please enter which you want to enable." << endl;
                    while (cin >> command) {
                        if (command == "blind") {
                            playertwo->isBlind = true;
                            for (int i = 3; i < 12; i++) {
                                for (int j = 3; j < 9; j++) {
                                    playertwo->Range[i][j].TurnBlind();
                                }
                            }
                            break;
                        } else if (command == "heavy") {
                            playertwo->isHeavy = true;
                            break;
                        } else if (command == "force") {
                            cout << "please choose a block to replace your opponent's current block." << endl;
                            while(cin >> command) {
                                if (command == "I") {
                                    IBlock iblock;
                                    rightBlock = iblock.getPtr();
                                    board.clearNext(playertwo);
                                    board.nextUpdate(playertwo, rightBlock);
                                    break;
                                } else if (command == "J") {
                                    JBlock jblock;
                                    rightBlock = jblock.getPtr();
                                    board.clearNext(playertwo);
                                    board.nextUpdate(playertwo, rightBlock);
                                    break;
                                } else if (command == "L") {
                                    LBlock lblock;
                                    rightBlock = lblock.getPtr();
                                    board.clearNext(playertwo);
                                    board.nextUpdate(playertwo, rightBlock);
                                    break;
                                } else if (command == "O") {
                                    OBlock oblock;
                                    rightBlock = oblock.getPtr();
                                    board.clearNext(playertwo);
                                    board.nextUpdate(playertwo, rightBlock);
                                    break;
                                } else if (command == "S") {
                                    SBlock sblock;
                                    rightBlock = sblock.getPtr();
                                    board.clearNext(playertwo);
                                    board.nextUpdate(playertwo, rightBlock);
                                    break;
                                } else if (command == "T") {
                                    TBlock tblock;
                                    rightBlock = tblock.getPtr();
                                    board.clearNext(playertwo);
                                    board.nextUpdate(playertwo, rightBlock);
                                    break;
                                } else if (command == "Z") {
                                    ZBlock zblock;
                                    rightBlock = zblock.getPtr();
                                    board.clearNext(playertwo);
                                    board.nextUpdate(playertwo, rightBlock);
                                    break;
                                } else {
                                    cout << "There's no this kind of block, please enter again!" << endl;
                                }
                            }
                                break;
                            }
                            board.generate(playerone, playertwo);
                            if (board.GraphicDisplay) board.graphicDisplay(playerone, playertwo, window);
                        }
                    }
                board.clearNext(playertwo);
                if (playerone->levelupLater) {
                    leftBlock = playerone->lev->generateBlock();
                    playerone->levelupNow = true;
                    playerone->levelupLater = false;
                } else if (playerone->levelupNow) {
                    // levelup now command
                    playerone->levelupNow = false;
                    int level = playerone->level;
                    if (level == 0) {
                        playerone->lev = new Level1();
                    } else if (level == 1) {
                        playerone->lev = new Level2();
                    } else if (level == 2) {
                        playerone->lev = new Level3();
                    } else if (level == 3) {
                        playerone->lev = new Level4();
                    } else if (level == 4) {
                        if (LevelRestrict1) {
                            playerone->lev = new Level5();
                        } else {
                            cout << "Sorry, You didn't meet requirement of Level5. Please try winning at least one time with level4" << endl;
                        }
                    } else if (level == 5) {
                        cout << "sorry, there is no higher level" << endl;
                    }
                    leftBlock = playerone->lev->generateBlock();
                } else if (playerone->leveldownLater) {
                    leftBlock = playerone->lev->generateBlock();
                    playerone->leveldownNow = true;
                } else if (playerone->leveldownNow) {
                    // leveldown now command
                    int level = playerone->level;
                    if (level == 0) {
                        cout << "sorry, there is no lower level" << endl;
                    } else if (level == 1) {
                        playerone->lev = new Level0(seq1);
                    } else if (level == 2) {
                        playerone->lev = new Level1();
                    } else if (level == 3) {
                        playerone->lev = new Level2();
                    } else if (level == 4) {
                        playerone->lev = new Level3();
                    }
                    leftBlock = playerone->lev->generateBlock();
                } else {
                    leftBlock = playerone->lev->generateBlock();
                }
                board.BlockUpdate(playertwo, rightBlock);
                board.nextUpdate(playerone, leftBlock);
                board.generate(playerone, playertwo);
                if (board.GraphicDisplay) board.graphicDisplay(playerone, playertwo, window);
            } else if (playerone->gameover){
                // check for player2 winning
                cout << "player 2 wins" << endl;
                if (playertwo->level == 5) {
                    LevelRestrict2 = true;
                }
                cout << "Do you want to play it again? Please type yes or no!" << endl;
                string answer;
                while(cin >> answer) {
                    if (answer == "yes") {
                        board.initPlayer(playerone->level,playertwo->level, playerone->HiScore, playertwo->HiScore, playerone->command, playertwo->command,
                        playerone->fileName, playertwo->fileName, seq1, seq2);   
                        playerone->gameover = false;
                    } else {
                        quit = true;
                        break;
                    }
                }
            } else if (playerone->terminate) {
                // check for game termination
                cout << "Game terminates" << endl;
                quit = true;
                break;
            }
        } else {
            // player2 turn 
            bool judge = true;
            while ((playertwo->command|| judge || cin >> command) && !playertwo->gameover) {
                if (playertwo->command) {
                        command = cmd2[index2];
                        index2++; 
                        int size = cmd2.size();
                        if (index2 >= size) {
                            playertwo->terminate = true;
                        }
                    } 
                // bonus: support for keyboard left/right/down arrow input
                if (bonus) {
                    istringstream iss(command);
                    char c,d,e;
                    iss >> c >> d >> e;
                    if ((c==27)&&(d==91)) {
                        if (e==66) { command = "down"; }
                        if (e==67) { command = "right"; }
                        if (e==68) { command = "left"; }
                    }    
                }
                // commands and shortcuts
                if ((command == "left" || command == "right" || command == "down" || command == "clockwise" 
                    || command == "counterclockwise") && playertwo->level >= 3) {
                        board.move("down", playertwo, rightBlock);
                    }
                if (command == "drop" || command == "ss") {
                    for (int i = 0; i < 15; i++) {
                        board.move("down", playertwo, rightBlock);
                    }
                    if (playertwo->isBlind) {
                        for (int i = 3; i < 12; i++) {
                            for (int j = 3; j < 9; j++) {
                                playertwo->Range[i][j].NotBlind();
                            }
                        }
                        playertwo->isBlind = false;
                    }
                    break;
                } else if (command == "left" || command == "a" || command == "lef") {
                    board.move("left", playertwo, rightBlock);
                    if (playertwo->isHeavy) {
                        board.move("down", playertwo, rightBlock);
                        board.move("down", playertwo, rightBlock);
                    }
                } else if (command == "right" || command == "d" || command == "ri" ||
                           command == "rig" || command == "righ") {
                    board.move("right", playertwo, rightBlock);
                    if (playertwo->isHeavy) {
                        board.move("down", playertwo, rightBlock);
                        board.move("down", playertwo, rightBlock);
                    }
                } else if (command == "down" || command == "s" || command == "dow") {
                    board.move("down", playertwo, rightBlock);
                } else if (command == "clockwise" || command == "e" || command == "cw") {
                    board.CW(playertwo, rightBlock);
                } else if (command == "counterclockwise" || command == "q" || command == "ccw") {
                    board.CW(playertwo, rightBlock);
                    board.CW(playertwo, rightBlock);
                    board.CW(playertwo, rightBlock);
                // levelup
                } else if (command == "levelup") {
                    if (playertwo->level < 4 || (playertwo->level == 4 && LevelRestrict2)) {
                        playertwo->levelupLater = true;
                        (playertwo->level)++;
                    } else {
                        cout << "unable to level up" << endl;
                    }
                // leveldown
                } else if (command == "leveldown") {
                    if (playertwo->level > 0) {
                        playertwo->leveldownLater = true;
                        (playertwo->level)--;
                    } else {
                        cout << "unable to level down" << endl;
                    }
                } else if (command == "norandom" && playertwo->level >= 3) {
                    string fileName;
                    if (playertwo->command) {
                        fileName = cmd2[index2];
                        index2++; 
                        int size = cmd2.size();
                        if (index2 >= size) {
                            playertwo->terminate = true;
                        }
                    } else {
                        cin >> fileName;
                    }
                    playertwo->lev = new Level0(fileName);
                } else if (command == "random") {
                    if (playertwo->level == 3) {
                        playertwo->lev = new Level3();
                    } else if (playertwo->level == 4) {
                        playertwo->lev = new Level4();
                    } else if (playertwo->level == 5) {
                        playertwo->lev = new Level5();
                    }
                } else if (command == "I") {
                    IBlock iblock;
                    Block* newBlock = iblock.getPtr();
                    board.replaceBlock(playerone, rightBlock, newBlock);
                    rightBlock = newBlock;
                } else if (command == "J") {
                    JBlock jblock;
                    Block* newBlock = jblock.getPtr();
                    board.replaceBlock(playerone, rightBlock, newBlock);
                    rightBlock = newBlock;
                } else if (command == "L") {
                    LBlock lblock;
                    Block* newBlock = lblock.getPtr();
                    board.replaceBlock(playerone, rightBlock, newBlock);
                    rightBlock = newBlock;
                } else if (command == "O") {
                    OBlock oblock;
                    Block* newBlock = oblock.getPtr();
                    board.replaceBlock(playerone, rightBlock, newBlock);
                    rightBlock = newBlock;
                } else if (command == "S") {
                    SBlock sblock;
                    Block* newBlock = sblock.getPtr();
                    board.replaceBlock(playerone, rightBlock, newBlock);
                    rightBlock = newBlock;
                } else if (command == "T") {
                    TBlock tblock;
                    Block* newBlock = tblock.getPtr();
                    board.replaceBlock(playerone, rightBlock, newBlock);
                    rightBlock = newBlock;
                } else if (command == "Z") {
                    ZBlock zblock;
                    Block* newBlock = zblock.getPtr();
                    board.replaceBlock(playerone, rightBlock, newBlock);
                    rightBlock = newBlock;
                } else if (command == "restart") {
                    board.initPlayer(playerone->level,playertwo->level, playerone->HiScore, playertwo->HiScore, playerone->command, playertwo->command,
                    playerone->fileName, playertwo->fileName,seq1,seq2);                           
                } else if (command == "sequence") {
                    string fileName;
                    cin >> fileName;
                    ifstream file{fileName};
                    string cmd;
                    while (file >> cmd) {
                        cmd2.push_back(cmd);
                    }
                } else {
                    int times = 0;
                    string cmd = board.shortcut(command, times);
                    if ((cmd == "down" || cmd == "right" || cmd == "left") && rightBlock->getState() == true){
                        for (int i = 0; i < times; i++) {
                            board.move("down", playertwo, rightBlock);
                        }
                    }
                    if (cmd == "right") {
                        for (int i = 0; i < times; i++) {
                            board.move("right", playertwo, rightBlock);
                            if (playertwo->isHeavy) {
                                board.move("down", playertwo, rightBlock);
                                board.move("down", playertwo, rightBlock);
                            }
                        }
                    } else if (cmd == "left") {
                        for (int i = 0; i < times; i++) {
                            board.move("left", playertwo, rightBlock);
                            if (playertwo->isHeavy) {
                                board.move("down", playertwo, rightBlock);
                                board.move("down", playertwo, rightBlock);
                            }
                        }
                    } else if (cmd == "down") {
                        for (int i = 0; i < times; i++) {
                            board.move("down", playertwo, rightBlock);
                        }
                    } else if (cmd == "levelup") {
                        int newlevel = playertwo->level + times;
                        if (newlevel <= 4) {
                            playertwo->levelupLater = true;
                            playertwo->level = newlevel;
                            if (newlevel == 0) {
                                playertwo->lev = new Level0(seq2);
                            } else if (newlevel == 1) {
                                playertwo->lev = new Level1();
                            } else if (newlevel == 2) {
                                playertwo->lev = new Level2();
                            } else if (newlevel == 3) {
                                playertwo->lev = new Level3();
                            } else if (newlevel == 4) {
                                playertwo->lev = new Level4();
                            } else if (newlevel == 5) {
                                if (LevelRestrict2) {
                                    playertwo->lev = new Level5();
                                } else {
                                    playerone->levelupLater = false;
                                    playertwo->level = newlevel - times;
                                    cout << "Sorry, You didn't meet requirement of Level5. Please try winning at least one time with level4" << endl;
                                }
                            }
                        }
                    } else if (cmd == "leveldown") {
                        int newlevel = playertwo->level - times;
                        if (newlevel >= 0) {
                            playertwo->level = newlevel;
                            playertwo->leveldownLater = true;
                            if (newlevel == 0) {
                                playertwo->lev = new Level0(seq2);
                            } else if (newlevel == 1) {
                                playertwo->lev = new Level1();
                            } else if (newlevel == 2) {
                                playertwo->lev = new Level2();
                            } else if (newlevel == 3) {
                                playertwo->lev = new Level3();
                            } else if (newlevel == 4) {
                                playertwo->lev = new Level4();
                            } else if (newlevel == 5) {
                                if (LevelRestrict2) {
                                    playertwo->lev = new Level5();
                                } else {
                                    playertwo->leveldownLater = false;
                                    playertwo->level = newlevel - times;
                                    cout << "Sorry, You didn't meet requirement of Level5. Please try winning at least one time with level4" << endl;
                                }
                            }
                        }
                    }
                }
                if (board.endCheck(playertwo, rightBlock)) {
                    // playertwo finished
                    if (playertwo->isBlind) {
                        for (int i = 3; i < 12; i++) {
                            for (int j = 3; j <9; j++) {
                                playertwo->Range[i][j].NotBlind();
                            }
                        }
                        playertwo->isBlind = false;
                    }
                    break;
                }
                board.generate(playerone, playertwo);
                if (board.GraphicDisplay) board.graphicDisplay(playerone, playertwo, window);
                judge = false;
            }
            // check if player2 gameover and needs termination
            if (playertwo->gameover != true || playertwo->terminate) {
                int clear = 0;
                int add = 0;
                board.clearLine(playertwo, clear, add);
                if (playertwo->level != 5) {
                    playertwo->Score += add;
                } else {
                    if (clear == 0 && (playertwo->uncleared + 1 == 10)) {
                        neverAdd2 = true;
                    }
                    if (!neverAdd2){
                        playertwo->Score += add;
                    }
                }
                if (clear != 0) {
                    playertwo->Score += ((playertwo->level + clear) * (playertwo->level + clear));
                    playertwo->uncleared = 0;
                } else if (playertwo->level == 4){
                    (playertwo->uncleared)++;
                    if (playertwo->uncleared == 5) {
                        (playertwo->starAdd)++;
                        playertwo->uncleared = 0;
                        board.starblockAdd(playertwo);
                    }
                }
                board.clearLine(playertwo, clear, add);
                board.clearLine(playertwo, clear, add);
                board.clearLine(playertwo, clear, add);
                if (playertwo->Score > playertwo->HiScore) {
                    playertwo->HiScore = playertwo->Score;
                }
                // special action
                if (clear >= 2) {
                    board.generate(playerone, playertwo);
                    if (board.GraphicDisplay) board.graphicDisplay(playerone, playertwo, window);
                    cout << "Congratulations! You have triggered special Action! You can choose blind, heavy or force!" << endl;
                    cout << "Please enter which you want to enable." << endl;
                    while (cin >> command) {
                        if (command == "blind") {
                            playerone->isBlind = true;
                            for (int i = 3; i < 12; i++) {
                                for (int j = 3; j < 9; j++) {
                                    playerone->Range[i][j].TurnBlind();
                                }
                            }
                            break;
                        } else if (command == "heavy") {
                            playerone->isHeavy = true;
                            break;
                        } else if (command == "force") {
                            cout << "please choose a block to replace your opponent's current block." << endl;
                            while (cin >> command) {
                                if (command == "I") {
                                    IBlock iblock;
                                    leftBlock = iblock.getPtr();
                                    board.clearNext(playerone);
                                    board.nextUpdate(playerone, leftBlock);
                                    break;
                                } else if (command == "J") {
                                    JBlock jblock;
                                    leftBlock = jblock.getPtr();
                                    board.clearNext(playerone);
                                    board.nextUpdate(playerone, leftBlock);
                                    break;
                                } else if (command == "L") {
                                    LBlock lblock;
                                    leftBlock = lblock.getPtr();
                                    board.clearNext(playerone);
                                    board.nextUpdate(playerone, leftBlock);
                                    break;
                                } else if (command == "O") {
                                    OBlock oblock;
                                    leftBlock = oblock.getPtr();
                                    board.clearNext(playerone);
                                    board.nextUpdate(playerone, leftBlock);
                                    break;
                                } else if (command == "S") {
                                    SBlock sblock;
                                    leftBlock = sblock.getPtr();
                                    board.clearNext(playerone);
                                    board.nextUpdate(playerone, leftBlock);
                                    break;
                                } else if (command == "T") {
                                    TBlock tblock;
                                    leftBlock = tblock.getPtr();
                                    board.clearNext(playerone);
                                    board.nextUpdate(playerone, leftBlock);
                                    break;
                                } else if (command == "Z") {
                                    ZBlock zblock;
                                    leftBlock = zblock.getPtr();
                                    board.clearNext(playerone);
                                    board.nextUpdate(playerone, leftBlock);
                                    break;
                                } else {
                                    cout << "There's no this kind of block, please enter again!" << endl;
                                }
                            }
                        } else {
                            cout << "There's no this kind of force, please enter again!"<< endl;
                        }
                    }
                }
                // levelup now and leveldown now
                if (playertwo->levelupLater) {
                    rightBlock = playertwo->lev->generateBlock();
                    playertwo->levelupNow = true;
                    playertwo->levelupLater = false;
                } else if (playertwo->levelupNow) {
                    playertwo->levelupNow = false;
                    int level = playertwo->level;
                    if (level == 0) {
                        playertwo->lev = new Level1();
                    } else if (level == 1) {
                        playertwo->lev = new Level2();
                    } else if (level == 2) {
                        playertwo->lev = new Level3();
                    } else if (level == 3) {
                        playertwo->lev = new Level4();
                    } else if (level == 4) {
                        
                        if (LevelRestrict2) {
                            playertwo->lev = new Level5();
                        } else {
                            cout << "Sorry, You didn't meet requirement of Level5. Please try winning at least one time with level4" << endl;
                        }
                    }
                } else if (playertwo->leveldownLater) {
                    rightBlock = playertwo->lev->generateBlock();
                    playertwo->leveldownNow = true;
                } else if (playertwo->leveldownNow) {
                    int level = playertwo->level;
                    if (level == 0) {
                        cout << "sorry, there is no lower level" << endl;
                    } else if (level == 1) {
                        playertwo->lev = new Level0(seq2);
                    } else if (level == 2) {
                        playertwo->lev = new Level1();
                    } else if (level == 3) {
                        playertwo->lev = new Level2();
                    } else if (level == 4) {
                        playertwo->lev = new Level3();
                    } else if (level == 5) {
                        playertwo->lev = new Level5();
                    }
                } else {
                    rightBlock = playertwo->lev->generateBlock();
                }
                // update game and get ready for next player's block
                board.BlockUpdate(playerone, leftBlock);
                board.nextUpdate(playertwo, rightBlock);
                board.clearNext(playerone);
                board.generate(playerone, playertwo);
                if (board.GraphicDisplay) board.graphicDisplay(playerone, playertwo, window);
            } else if (playertwo->gameover){
                // check for player winning
                if (playerone->level == 5) {
                    LevelRestrict1 = true;
                }
                cout << "player 1 wins" << endl;
                cout << "Do you want to play it again? Please type yes or no!" << endl;
                string answer;
                while(cin >> answer) {
                    if (answer == "yes") {
                        board.initPlayer(playerone->level,playertwo->level, playerone->HiScore, playertwo->HiScore, playerone->command, playertwo->command,
                        playerone->fileName, playertwo->fileName,seq1,seq2);   
                        playertwo->gameover = false;
                    } else {
                        quit = true;
                        break;
                    }
                }
                break;
            } else if (playertwo->terminate) {
                // check for game termination
                cout << "Game terminates" << endl;
                quit = true;
                break;
            }
        }
        // if game not over, take new turns and loop again
        turn++;
        }
    }
    // delete all dynamically allocated memories
    if (window) {
        delete window;
    }
    return 0;
}
