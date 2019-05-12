#ifndef Game_hpp
#define Game_hpp

#include <memory>
#include <vector>
#include "Ball.hpp"
#include "Players.hpp"
#include "Priority.hpp"
#include "Scott_Priority.hpp"
#include "Rusty_Priority.hpp"

class Game{
    private:
        Priority* scottPriority;
        Priority* rustyPriority;
        unsigned int turnsPerRound, currentTurns, totalTurns;
        Player currentPlayer;
        
        std::vector<Priority*> vec;

        unsigned long scottPoints, rustyPoints;

        std::vector<unsigned long*> pointsVec;

        Game(const Game&); //Delete the copy constructor

    public:
        Game(
            Player startingTurn, 
            unsigned int turnsPerRound,
            std::unique_ptr<std::vector<std::shared_ptr<Ball>>> balls
        );
        ~Game();

        void PlayRound(bool print = false);

        bool CanPlayRound();

        void PrintScores();
};


#endif