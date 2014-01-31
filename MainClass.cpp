#include "MainClass.h"


MainClass::MainClass()
{
    theBrains = new game_logic(2,3,"XO");
}
void MainClass::Main()
{
    console_interface::Intro();
    console_interface::Init(theBrains);
    
    console_interface::InitPlayers();
    console_interface::InitGameLoop();
    
    theBrains->endGame();
}
