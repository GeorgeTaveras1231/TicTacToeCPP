
#include "player.h"
#include "console_grid.h"
#include "game_logic.h"
#include "console_interface.h"


game_logic::game_logic(
                       short int max_players,                                   
                       const short int grid_dimenssions,                     
                       const std::string& symbols                               
)
{
    MAX_PLAYERS = max_players;
    TOTAL_PLAYERS = 0;
    
    GRID_WIDTH = grid_dimenssions;
    GRID_HEIGHT = grid_dimenssions;
    GRID_AREA = GRID_WIDTH*GRID_HEIGHT;
    
    VALID_SYMBOLS = symbols;
    
    /*
     controller_grid
     
     */
    _controllerGrid = new console_grid(GRID_WIDTH,GRID_HEIGHT); //must be deleted
    
    int index;
    std::stringstream buttons;
    for(index = 0; index < GRID_AREA; index++)
    {
        buttons<<index;
    }
    _controllerGrid->writeToGrid(buttons.str());                                      
    /*
     game_grid
     
     */
    _gameGrid = new console_grid(GRID_WIDTH,GRID_HEIGHT); //must be deleted
}

game_logic::~game_logic()
{
   
}

void game_logic::newPlayer
                            (
                             const std::string& name,
                             char symbol
                             )
                                                            throw(
                                                                  GameExcept::player_limit,
                                                                  GameExcept::existing_player,
                                                                  GameExcept::invalid_symbol
                                                                  )
{
    
    
    std::stringstream errMsg;
    
    if (TOTAL_PLAYERS == MAX_PLAYERS)                                           
    {
        errMsg<<"too many players.";
        throw GameExcept::player_limit(errMsg.str());
    }
    
    short int index;
    for(index = 0 ; index < (int)_players.size(); index++)
    {
        if(_players[index]->getName() == name)
        {
            errMsg<<name<<" already exists. Please choose another name.";
            throw GameExcept::existing_player(errMsg.str());         
        }
    }
    for(index = 0 ; index < (int)_players.size(); index++)
    {
        if(_players[index]->getSymbol() == symbol)
        {
            errMsg<<symbol<<" belongs to "<<_players[index]->getName()<<".";
            throw GameExcept::invalid_symbol(errMsg.str());         
        }
    }
    for(index = 0 ; index < (int)VALID_SYMBOLS.size(); index++)
    {
        if((char)VALID_SYMBOLS[index] == symbol)
        {
            break;
        }
        else if((char)VALID_SYMBOLS[index] != symbol && index == (int)VALID_SYMBOLS.size() - 1){
            errMsg << symbol<<" is an invalid symbol.";
            throw GameExcept::invalid_symbol(errMsg.str());                
        }
    }
    
    _players.push_back(new player(this));                                       
    _players[TOTAL_PLAYERS]->setName(name);
    _players[TOTAL_PLAYERS]->setSymbol(symbol);
    
    TOTAL_PLAYERS++;
    
}

void game_logic::clearPlayers()                                                
                            throw(GameExcept::player_limit)
{
    if(TOTAL_PLAYERS == 0)
    {
        throw (GameExcept::player_limit("No players to delete."));
    }
    for(auto& iter: _players)
    {
        delete iter;
    }
    _players.clear();
}


bool game_logic::isBoxLegal(short int box)
{
    for(auto& iter:_illegal_moves)
    {
       if (box == iter)
       {
           return false;
       }
    }
    return true;
}

bool game_logic::victory()
{
    bool answer = false;
    
    int width = GRID_WIDTH;
    int height = GRID_HEIGHT;
    int area= GRID_AREA;
    
    int index;
    for(index = 0; index < area; index++)
    {
        if (index == 0 || index % width == 0)
        {
            //compare horizontally
            int hCheckIndex;                                        //horizontal check index
            for(hCheckIndex = index; _gameGrid->compareBoxes(hCheckIndex, ++hCheckIndex) && hCheckIndex-index<width;){
            
                if(hCheckIndex-index == width -1)
                {
                    //victory
                    
                    answer = true;
                }
            }
        }
        //compare vertically
        if (index < width)
        {
            int vCheckIndex;                                        //vertical check index
            for(vCheckIndex = index; _gameGrid->compareBoxes(vCheckIndex, vCheckIndex+width) && vCheckIndex-index<= width * (height-1);){
                vCheckIndex+=width;
                
                if(vCheckIndex-index == width * (height-1))
                {
                    //victory
                    
                    answer = true;
                }
            }
        }
        //compare diagonal
        if (index == 0)
        {
            int dCheckIndex;                                        //diagonal check index (left to right)
            for(dCheckIndex = index; _gameGrid->compareBoxes(dCheckIndex, dCheckIndex+width+1)&& dCheckIndex<=(width * height)-1;)
            {
                dCheckIndex+=width+1;
                if(dCheckIndex-index == (width * height)-1)
                {
                    //victory
                    answer = true;
                }
            }
        }
        if (index == width-1)
        {
            int dCheckIndex;                                        //diagonal check index (right to left)
            for(dCheckIndex = index; _gameGrid->compareBoxes(dCheckIndex, dCheckIndex+width-1)&& dCheckIndex<=area - width;)
            {
                dCheckIndex+=width-1;
                if(dCheckIndex == area - width)
                {
                    //victory
                    answer = true;
                }
            }
        }
    }
    
    
    return answer;
}

bool game_logic::victory(player& givenPlayer)
{
    bool answer = false;
    
    int width = GRID_WIDTH;
    int height = GRID_HEIGHT;
    int area = GRID_AREA;
    
    char symbol = givenPlayer.getSymbol();
    //calculate indexes that must be equal in order
    int index;
    for(index = 0; index < width*height; index++)
    {
        
        if(_gameGrid->getBoxValueAt(index) == symbol)
        {
            if (index == 0 || index % width == 0)
            {
                //compare horizontally
                int hCheckIndex;
                for(hCheckIndex = index; _gameGrid->compareBoxes(hCheckIndex, ++hCheckIndex)&& hCheckIndex-index<width;){
                    
                    if(hCheckIndex-index == width -1)
                    {
                        //victory
                        answer = true;
                    }
                }
            }
            //compare vertically
            if (index < width)
            {
                int vCheckIndex;
                for(vCheckIndex = index; _gameGrid->compareBoxes(vCheckIndex, vCheckIndex+width)&& vCheckIndex-index<=width * (height-1);)
                {
                    vCheckIndex+=width;
                    if(vCheckIndex-index == width * (height-1))
                    {
                        //victory
                        answer = true;
                    }
                }
            }
            //compare diagonal
            if (index == 0)
            {
                int dCheckIndex;
                for(dCheckIndex = index; _gameGrid->compareBoxes(dCheckIndex, dCheckIndex+width+1)&& dCheckIndex<=area - 1;)
                {
                    dCheckIndex+=width+1;
                    if(dCheckIndex-index == area - 1)
                    {
                        //victory
                        answer = true;
                    }
                }
            }
            if (index == width-1)
            {
                int dCheckIndex;
                for(dCheckIndex = index; _gameGrid->compareBoxes(dCheckIndex, dCheckIndex+width-1)&& dCheckIndex<=area - width;)
                {
                    dCheckIndex+=width-1;
                    if(dCheckIndex == area - width)
                    {
                        //victory
                        answer = true;
                    }
                }
            }
        }
        
        if(answer) _winner = &givenPlayer;
    }
    
    
    return answer;
}

bool game_logic::tie()
{
    if(!victory() && (int)_illegal_moves.size()>= GRID_AREA){
        return true;
        _winner = nullptr;
    }
    
    return false;
}

bool game_logic::gameOver()
{
    if (tie()){
        return true;
    }
    
    
    for(auto& iter: _players)
    {
        if(victory(*iter))
        {
            return true;
        }
    }
    return false;
}

void game_logic::endGame()
{
    this->clearPlayers();
    delete _controllerGrid;
    delete _gameGrid;
}



