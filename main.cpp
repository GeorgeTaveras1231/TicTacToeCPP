#include <iostream>

#include "MainClass.h"


int main(int argc, const char * argv[])
{
    MainClass *TicTacToe = new MainClass;

    TicTacToe->Main();
    
    delete TicTacToe;
    
    return 0;
}

