//
//  console_interface.h
//  TicTacToe
//
//  Created by George Taveras on 10/26/13.
//  Copyright (c) 2013 George Taveras. All rights reserved.
//


#ifndef TicTacToe_console_interface_h
#define TicTacToe_console_interface_h

/*console_interface
 
 The console_interface class has a singleton design
 it will take care of displaying the texts to the players
 informing them of the rules and the current state of the program
 aka GUI interface
 */

class game_logic;

class console_interface
{
private:
    
public:
    
    friend class MainClass;
    
    static int msgSpeed;
    static game_logic* _brains;
    static void Init(game_logic*);
    
    static void Intro();
    
    static void InitPlayers();
    static void GUIPlayers(int);                           //loop that gets player info
    
    static void displayGrids();
    
    static void promptMoves();
    
    static void InitGameLoop();                                               //main game loop
    
    static void AnnounceWinner();
    
    
    
};

#endif
