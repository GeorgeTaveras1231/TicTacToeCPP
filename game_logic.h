//
//  game_logic.h
//  TicTacToe
//
//  Created by George Taveras on 10/24/13.
//  Copyright (c) 2013 George Taveras. All rights reserved.
//

#ifndef TicTacToe_game_logic_h
#define TicTacToe_game_logic_h

#include <vector>
#include "game_exceptions.h"


class console_grid;
class player;
class console_interface;

class game_logic
{
    std::vector<player*> _players;
    
    player* _winner;
    
    console_grid* _gameGrid;
    console_grid* _controllerGrid;
    
    
    short int MAX_PLAYERS;                                         // = 2
    short int TOTAL_PLAYERS;
    
    short int GRID_WIDTH;
    short int GRID_HEIGHT;
    short int GRID_AREA;
    
    
    std::string VALID_SYMBOLS;                                     //each character is a legal symbol

    std::vector<int> _illegal_moves;
    
public:
    
    friend class player;
    friend class console_interface;
    
    game_logic();
    game_logic(short int,const short int,const std::string&);
    ~game_logic();
    
   
    
    inline short int getTotalPlayers(){return TOTAL_PLAYERS;}
    
    void newPlayer(const std::string&, char)
                                            throw (GameExcept::player_limit,
                                                   GameExcept::existing_player,
                                                   GameExcept::invalid_symbol);
    void clearPlayers()
                        throw (GameExcept::player_limit);
    
    
    
    bool isBoxLegal(short int);                                         //checks if it is legal to play in a certain box(specified by the index)
    
    bool victory();                                                    //checks for victory conditions
    bool victory(player&);                                             //checks if given player won
    
        bool horizontalVictory();
        bool verticalVictory();
        bool diagonalVictory();
    
    
    bool tie();
    
    bool gameOver();
    
    void endGame();
    
};

#endif
