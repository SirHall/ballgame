#include <iostream>
#include "Ball.hpp"
#include "Game.hpp"
#include "Players.hpp"
#include "Scott_Priority.hpp"
#include "Rusty_Priority.hpp"
#include "BallParser.hpp"

int main(int argc, char* argv[]){
    // std::cout << "Hello world!\n";

    auto games = BallParser::ParseFile("data/inputLeScore.txt");

    for(unsigned int i = 0; i < games->size(); i++){
        std::cout << "Round " << i << "\n";
        while(games->at(i)->CanPlayRound())
            games->at(i)->PlayRound();
        games->at(i)->PrintScores();
    }

    return 0;
}
