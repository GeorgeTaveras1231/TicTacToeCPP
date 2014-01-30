//
//  MainClass.h
//  TicTacToe
//
//  Created by George Taveras on 10/31/13.
//  Copyright (c) 2013 George Taveras. All rights reserved.
//

#ifndef TicTacToe_MainClass_h
#define TicTacToe_MainClass_h
#include "game_logic.h"
#include "console_interface.h"

class MainClass
{
private:
    game_logic *theBrains;
    
public:

    MainClass();
    ~MainClass(){delete theBrains;};
    
    MainClass(const MainClass&);
    
    void Main ();
};

#endif
