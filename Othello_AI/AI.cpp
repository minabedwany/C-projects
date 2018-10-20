#include <ics46/factory/DynamicFactory.hpp>
#include "AI.hpp"

ICS46_DYNAMIC_FACTORY_REGISTER(OthelloAI, mbedwany::MinaOthello, "Mina's Othello AI (Required)");

std::pair<int, int> mbedwany::MinaOthello::chooseMove(const OthelloGameState& state)
{
    if(state.isWhiteTurn())
        isplayerwhite = true;
    else
        isplayerwhite = false;

    a = -10000;
    b = 10000;

    validmoves = 0;
    for(int x = 0; x < state.board().width(); ++x)
        for(int y = 0; y < state.board().height(); ++y)
            if(state.isValidMove(x,y))
                ++validmoves;

    if(validmoves > 0 && validmoves < 6)
        depth = 6;
    else
        depth = 5;

    bestscore = -5000;
    for(int x = 0; x < state.board().width(); ++x)
        for(int y = 0; y < state.board().height(); ++y)
            if(state.isValidMove(x,y))
            {
                std::unique_ptr<OthelloGameState> temp = state.clone();
                temp->makeMove(x,y);

                currentscore = search(*temp, depth, isplayerwhite, a, b);

                if(currentscore > bestscore)
                {
                    bestscore = currentscore;
                    playerx = x;
                    playery = y;
                }

            }

    return std::make_pair(playerx, playery);
}


int mbedwany::MinaOthello::eval(const OthelloGameState& state, bool isplayerwhite)
{
    const OthelloBoard& thisboard = state.board();
    int temp = 0;

    int w = state.board().width() -1;
    int h = state.board().height() -1; 

    if(isplayerwhite)
    {
        if(state.isGameOver() && (state.whiteScore() > state.blackScore()))
            temp += 10000;
        
        //corners advantage
        if((thisboard.cellAt(0,0) == OthelloCell::white) ||
           (thisboard.cellAt(0,h) == OthelloCell::white) ||
           (thisboard.cellAt(w,0) == OthelloCell::white) ||
           (thisboard.cellAt(w,h) == OthelloCell::white))
                temp += 1000;

        //corners disadvantage
        if((thisboard.cellAt(0,0) == OthelloCell::black) ||
           (thisboard.cellAt(0,h) == OthelloCell::black) ||
           (thisboard.cellAt(w,0) == OthelloCell::black) ||
           (thisboard.cellAt(w,h) == OthelloCell::black))
                temp -= 1000;

        //adjacent corners advantage
        if((thisboard.cellAt(0,1) == OthelloCell::white) ||
           (thisboard.cellAt(1,0) == OthelloCell::white) ||
           (thisboard.cellAt(1,1) == OthelloCell::white) ||
           (thisboard.cellAt(0,h-1) == OthelloCell::white) ||
           (thisboard.cellAt(1,h-1) == OthelloCell::white) ||
           (thisboard.cellAt(w-1,0) == OthelloCell::white) ||
           (thisboard.cellAt(w-1, 1) == OthelloCell::white) ||
           (thisboard.cellAt(1,h) == OthelloCell::white) ||
           (thisboard.cellAt(w,1) == OthelloCell::white) ||
           (thisboard.cellAt(w-1,h) == OthelloCell::white) ||
           (thisboard.cellAt(w-1,h-1) == OthelloCell::white) ||
           (thisboard.cellAt(w,h-1) == OthelloCell::white))
                temp -= 500;

        //adjacent corners disadvantage
        if((thisboard.cellAt(0,1) == OthelloCell::black) ||
           (thisboard.cellAt(1,0) == OthelloCell::black) ||
           (thisboard.cellAt(1,1) == OthelloCell::black) ||
           (thisboard.cellAt(0,h-1) == OthelloCell::black) ||
           (thisboard.cellAt(1,h-1) == OthelloCell::black) ||
           (thisboard.cellAt(w-1,0) == OthelloCell::black) ||
           (thisboard.cellAt(w-1, 1) == OthelloCell::black) ||
           (thisboard.cellAt(1,h) == OthelloCell::black) ||
           (thisboard.cellAt(w,1) == OthelloCell::black) ||
           (thisboard.cellAt(w-1,h) == OthelloCell::black) ||
           (thisboard.cellAt(w-1,h-1) == OthelloCell::black) ||
           (thisboard.cellAt(w,h-1) == OthelloCell::black)) 
                temp += 500;

        //top and bottom sides
        for(int width = 2; width<w-1; ++width)
        {
            //sides advantage
            if((thisboard.cellAt(width, h) == OthelloCell::white) ||
              (thisboard.cellAt(width, 0) == OthelloCell::white))
                temp += 15;
            
            //sides disadvantage
            if((thisboard.cellAt(width, h) == OthelloCell::black) ||
              (thisboard.cellAt(width, 0) == OthelloCell::black))
                temp -= 15;
        } 

        //left and right sides
        for(int height = 2; height<h-1; ++height)
        {
            //sides advantage
            if((thisboard.cellAt(w, height) == OthelloCell::white) ||
              (thisboard.cellAt(0, height) == OthelloCell::white))
                temp += 15;

            //sides disadvantage
            if((thisboard.cellAt(w, height) == OthelloCell::black) ||
              (thisboard.cellAt(0, height) == OthelloCell::black))
                temp -= 15;
        }


        temp += 100* (state.whiteScore() - state.blackScore()) / (state.whiteScore() + state.blackScore());
        return temp;
    }
    else
    {    
        if(state.isGameOver() && (state.blackScore() > state.whiteScore()))
            temp += 10000;

        //corners advantage 
        if((thisboard.cellAt(0,0) == OthelloCell::black) ||
           (thisboard.cellAt(0,h) == OthelloCell::black) ||
           (thisboard.cellAt(w,0) == OthelloCell::black) ||
           (thisboard.cellAt(w,h) == OthelloCell::black))
                temp += 1000;

        //corners disadvantage
        if((thisboard.cellAt(0,0) == OthelloCell::white) ||
           (thisboard.cellAt(0,h) == OthelloCell::white) ||
           (thisboard.cellAt(w,0) == OthelloCell::white) ||
           (thisboard.cellAt(w,h) == OthelloCell::white))
                temp -= 1000;

        //adjacent corners advantage
        if((thisboard.cellAt(0,1) == OthelloCell::black) ||
           (thisboard.cellAt(1,0) == OthelloCell::black) ||
           (thisboard.cellAt(1,1) == OthelloCell::black) ||
           (thisboard.cellAt(0,h-1) == OthelloCell::black) ||
           (thisboard.cellAt(1,h-1) == OthelloCell::black) ||
           (thisboard.cellAt(w-1,0) == OthelloCell::black) ||
           (thisboard.cellAt(w-1, 1) == OthelloCell::black) ||
           (thisboard.cellAt(1,h) == OthelloCell::black) ||
           (thisboard.cellAt(w,1) == OthelloCell::black) ||
           (thisboard.cellAt(w-1,h) == OthelloCell::black) ||
           (thisboard.cellAt(w-1,h-1) == OthelloCell::black) ||
           (thisboard.cellAt(w,h-1) == OthelloCell::black))
                temp -= 500;

        //adjacent corners disadvantage
        if((thisboard.cellAt(0,1) == OthelloCell::white) ||
           (thisboard.cellAt(1,0) == OthelloCell::white) ||
           (thisboard.cellAt(1,1) == OthelloCell::white) ||
           (thisboard.cellAt(0,h-1) == OthelloCell::white) ||
           (thisboard.cellAt(1,h-1) == OthelloCell::white) ||
           (thisboard.cellAt(w-1,0) == OthelloCell::white) ||
           (thisboard.cellAt(w-1, 1) == OthelloCell::white) ||
           (thisboard.cellAt(1,h) == OthelloCell::white) ||
           (thisboard.cellAt(w,1) == OthelloCell::white) ||
           (thisboard.cellAt(w-1,h) == OthelloCell::white) ||
           (thisboard.cellAt(w-1,h-1) == OthelloCell::white) ||
           (thisboard.cellAt(w,h-1) == OthelloCell::white))        
                temp += 500;  
      
        //top and bottom sides
        for(int width = 2; width<w-1; ++width)
        {
            //sides advantage
            if((thisboard.cellAt(width, h) == OthelloCell::black) ||
              (thisboard.cellAt(width, 0) == OthelloCell::black))
                temp += 15;

            //sides disadvantage
            if((thisboard.cellAt(width, h) == OthelloCell::white) ||
              (thisboard.cellAt(width, 0) == OthelloCell::white))
                temp -= 15;
        }

        //left and right sides
        for(int height = 2; height<h-1; ++height)
        {
            //sides advantage
            if((thisboard.cellAt(w, height) == OthelloCell::black) ||
              (thisboard.cellAt(0, height) == OthelloCell::black))
                temp += 15;

            //sides disadvantage
            if((thisboard.cellAt(w, height) == OthelloCell::white) ||
              (thisboard.cellAt(0, height) == OthelloCell::white))
                temp -= 15;
        }

        temp += 100* (state.blackScore() - state.whiteScore()) / (state.whiteScore() + state.blackScore());
        return temp;
    }
}

//minimax algorithm using alpha beta pruning
int mbedwany::MinaOthello::search(const OthelloGameState& state, int depth, bool isplayerwhite, int a, int b)
{
    if(depth == 0 || state.isGameOver())
        return eval(state, isplayerwhite);
    else
    {   
        if((isplayerwhite && state.isWhiteTurn()) || (!isplayerwhite && !state.isWhiteTurn()))
        {
            for(int x = 0; x < state.board().width(); ++x)
                for(int y = 0; y < state.board().height(); ++y)
                    if(state.isValidMove(x,y))
                    {
                        std::unique_ptr<OthelloGameState> myplayerstate = state.clone();
                        myplayerstate->makeMove(x,y);
                        int max = search(*myplayerstate, depth-1, isplayerwhite, a, b);

                        if(max > a)
                            a = max;
                        if(a >= b)
                            return a;
                    }
        return a;
        }
        
        else
        {
            for(int x = 0; x < state.board().width(); ++x)
                for(int y = 0; y < state.board().height(); ++y)
                    if(state.isValidMove(x,y))
                    {
                        std::unique_ptr<OthelloGameState> oppstate = state.clone();
                        oppstate->makeMove(x,y);
                        int min = search(*oppstate, depth-1, isplayerwhite, a, b);

                        if(min < b)
                            b = min;
                        if(a >= b)
                            return b;
                    }
        return b;            
        }
    }
}

