
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
