
#include "player.h"
#include "game_logic.h"
#include "console_grid.h"
#include "game_exceptions.h"

player::player (game_logic* brain)
{
    _brain = brain;
}

player::~player()
{
    _brain->TOTAL_PLAYERS--;
    _brain = nullptr;
}

void player::play(int box) throw (GameExcept::out_of_bounds)
{
    std::stringstream errMsg;
    if(!_brain->isBoxLegal(box))
    {
        errMsg<<"illegal move: "<<box;
        throw GameExcept::illegal_move(errMsg.str());
    }
    if(box < 0 || box> _brain->GRID_AREA-1)
    {
        errMsg<<"out of bounds: "<<box<<". Play withing the controller bounds.";
        throw GameExcept::illegal_move(errMsg.str());
    }
    _brain->_illegal_moves.push_back(box);                          //make the box illegal
    
    _brain->_gameGrid->setBoxValueAt(box,this->getSymbol());        //change the value of the address on the game grid to the players symbol
    _brain->_controllerGrid->clearBoxAt(box);                       //clear the box on the controller grid to show that it is illegal
    
                                        //check conditions of game
}
