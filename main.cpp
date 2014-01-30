//
//  main.cpp
//  TicTacToe
//
//  Created by George Taveras on 10/18/13.
//  Copyright (c) 2013 George Taveras. All rights reserved.
//

#include <iostream>

#include "MainClass.h"


int main(int argc, const char * argv[])
{
    MainClass *TicTacToe = new MainClass;

    TicTacToe->Main();
    
    delete TicTacToe;
    
    return 0;
}

