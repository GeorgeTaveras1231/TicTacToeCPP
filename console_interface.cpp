//
//  console_interface.cpp
//  TicTacToe
//
//  Created by George Taveras on 10/26/13.
//  Copyright (c) 2013 George Taveras. All rights reserved.
//
#include <iostream>
#include "game_logic.h"
#include "console_interface.h"
#include "console_grid.h"
#include "player.h"
#include <unistd.h>

game_logic* console_interface::_brains = nullptr;

int console_interface::msgSpeed = 1;

void console_interface::Intro()
{
    std::cout<< "TIC-TAC-TOE" <<std::endl
             << "created by George Taveras"<<std::endl
             << "v1.0" <<std::endl;
             sleep(msgSpeed);
    std::cout<<"\n\n";
             sleep(msgSpeed);
    std::cout<<"The rules are very simple..."<<std::endl;
             sleep(msgSpeed);
    std::cout<<"and you should know them by now"<<std::endl;
             sleep(msgSpeed);
             sleep(msgSpeed);
    std::cout<<"if you don't, kill yourself :)"<<std::endl
             <<"\n\n";
             sleep(msgSpeed);
             sleep(msgSpeed);
}


void console_interface::Init(game_logic* brains)
{
    _brains = brains;
}

void console_interface::InitPlayers()
{
   
    std::cout<<"Okay Player "<< _brains->TOTAL_PLAYERS+1 <<", give us your name and symbol(X or O) separated by space."<<std::endl;
    
    GUIPlayers(_brains->TOTAL_PLAYERS);
   
    
    std::cout <<"Okay we're ready!"<<std::endl
              <<"Let's begin.\n\n"<<std::endl;
}

void console_interface::GUIPlayers(int player_index = 0)
{
    try {
        
        short int index;
        std::string name;
        char symbol;
    
        for(index = player_index; index< _brains->MAX_PLAYERS; index++){
            std::cout<<"Player "<<index+1<<": ";
            std::cin >> name >> symbol;
        
            _brains->newPlayer(name, symbol);
        
        }
    }
    catch (GameExcept::invalid_entry& e)
    {
        std::cerr<<e.what()<<std::endl;
        GUIPlayers(_brains->TOTAL_PLAYERS);
    }
    
}



void console_interface::InitGameLoop()
{
    //displayGrids();
    promptMoves();
    AnnounceWinner();
}

void console_interface::displayGrids()
{
    sleep(msgSpeed);
    std::cout<< "Game: "<<std::endl
                        <<std::endl;
    _brains->_gameGrid->draw();                                         //draw the game grid
    sleep(msgSpeed);
    std::cout<<std::endl<< "Controller: "<<std::endl
                                         <<std::endl;
    _brains->_controllerGrid->draw();
    sleep(msgSpeed);
    
    std::cout<<std::endl<<std::endl;
}
void console_interface::AnnounceWinner()
{
    if (_brains->tie())
    {
        std::cout<<"There is no winner."<<std::endl;
    }
    else
    {
        std::cout<<"The winner is "<<_brains->_winner->getName()<<"!"<<std::endl;
    }
}

void console_interface::promptMoves()
{
    int move;
    
    int index;
    index = 0;
    
    displayGrids();
    while(!_brains->gameOver())
    {
        std::cout<<_brains->_players[index]->getName()<<", chose a box:";
        std::cin>> move;
        std::cout<<std::endl<<std::endl;
        
        
        try{
            _brains->_players[index]->play(move);
            
            displayGrids();
            if(index == (int)_brains->_players.size()-1){
                index = 0;
            }
            else{
                index ++;
            }
        }
        catch (GameExcept::invalid_entry& e)
        {
            std::cerr<<e.what()<<std::endl;
            continue;
            
        }
        
    }
}




