#ifndef AI_HPP
#define AI_HPP

#include "OthelloAI.hpp"

namespace mbedwany
{
    class MinaOthello : public OthelloAI
    {
    public:
        virtual std::pair<int,int> chooseMove(const OthelloGameState& state);
        virtual int search(const OthelloGameState& state, int depth, bool isplayerwhite, int a, int b);
        virtual int eval(const OthelloGameState& state, bool isplayerwhite);

    private:
        int depth;
        bool isplayerwhite;
        int playerx;
        int playery;
        int validmoves;
        int currentscore;
        int bestscore;
        int a;
        int b;


    };
}


#endif
