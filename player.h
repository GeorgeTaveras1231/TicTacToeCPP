//
//  player.h
//  TicTacToe
//
//  Created by George Taveras on 10/24/13.
//  Copyright (c) 2013 George Taveras. All rights reserved.
//

#ifndef TicTacToe_player_h
#define TicTacToe_player_h

#include <string>
#include <vector>
#include "game_exceptions.h"

class game_logic;

class player
{
private:
    std::string _name;
    char _symbol;
    
    game_logic* _brain;
    
    player(game_logic*);                                                        //constructor takes the main game logic object as a reference
                                                                                //in order to build a connection between the player and the game
    
public:
    friend class game_logic;
    
    ~player();
    
    inline void setName(const std::string& name){ _name = name;};
    inline void setSymbol(char symbol){ _symbol = symbol;};
    
    inline std::string getName(){return _name;}
    inline char getSymbol(){return _symbol;}
    
    void play (int) throw(GameExcept::out_of_bounds);
    
};


#endif
