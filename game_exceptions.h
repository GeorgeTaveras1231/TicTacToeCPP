#ifndef TicTacToe_exceptions_h
#define TicTacToe_exceptions_h

#include <iostream>
#include <exception>
#include <stdexcept>
#include <sstream>

/*
 Exceptions used through the Tic-Tac-Toe game
 
 */

namespace GameExcept
{
    
    class invalid_entry: public std::runtime_error                           //parent exception _ child of runtime_error
    {                                                                        //will handle all exceptions dealing with user input at the console
    public:
        explicit invalid_entry(const char* what): runtime_error(what){};
        explicit invalid_entry(const std::string& what): runtime_error(what){};
    };
    
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    class out_of_bounds: public invalid_entry                                //thrown when player attempts to make a move outside the controller.
    {
    public:
        explicit out_of_bounds(const char* what): invalid_entry(what){};
        explicit out_of_bounds(const std::string& what): invalid_entry(what){};
    };
    
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    class illegal_move: public out_of_bounds                                 //thrown when player attemtps to make a move on an occupied box
    {
    public:
        explicit illegal_move(const char* what): out_of_bounds(what){};
        explicit illegal_move(const std::string& what): out_of_bounds(what){};
    };
    
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    class player_limit: public invalid_entry                                //thrown when too many players are instantiated
    {
    public:
        explicit player_limit(const char* what): invalid_entry(what){};
        explicit player_limit(const std::string& what): invalid_entry(what){};
    };
    
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class existing_player: public invalid_entry                           //parent exception _ child of runtime_error
    {                                                                        //will handle all exceptions dealing with user input at the console
    public:
        explicit existing_player(const char* what): invalid_entry(what){};
        explicit existing_player(const std::string& what): invalid_entry(what){};
    };
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    class invalid_symbol: public invalid_entry                                //thrown when player attem
    {
    public:
        explicit invalid_symbol(const char* what): invalid_entry(what){};
        explicit invalid_symbol(const std::string& what): invalid_entry(what){};
    };
}


#endif
