#include "Game.hpp"
#include <memory>
#include <iostream>
#include <vector>
#include "Ball.hpp"
#include "Players.hpp"
#include "Rusty_Priority.hpp"
#include "Scott_Priority.hpp"

Game::Game(
    Player startingTurn, 
    unsigned int turnsPerRound,
    std::unique_ptr<std::vector<std::shared_ptr<Ball>>> balls
){
    this->turnsPerRound = turnsPerRound;
    this->currentTurns = 0;
    this->totalTurns = balls->size();
    scottPriority = new Scott_Priority();
    rustyPriority = new Rusty_Priority();
    vec = std::vector<Priority*>({
        scottPriority, rustyPriority
    });
    scottPoints = 0;
    rustyPoints = 0;
    pointsVec = std::vector<unsigned long*>({
        &scottPoints, &rustyPoints
    });

    this->currentPlayer = startingTurn;
    for(std::shared_ptr<Ball>  ball : *balls){
        scottPriority->Add(ball);
        rustyPriority->Add(ball);
    }
}

Game::~Game(){
    delete scottPriority;
    delete rustyPriority;
}

void Game::PlayRound(bool print){
    if(!CanPlayRound())
        return;

    std::shared_ptr<Ball> removedBall;

    removedBall = vec[(unsigned int)currentPlayer]->GetNode(0);
    vec[(unsigned int)currentPlayer]->RemoveNode(0);
    
    if(print)
        std::cout << 
            (currentPlayer == Player::Scott ? "Scott" : "Rusty") << 
            " picked:\t" <<
            removedBall->GetValue() << "\t\t" << removedBall->GetDigitSum() << "\n";

    *pointsVec[(unsigned int)currentPlayer] += removedBall->GetValue();

    currentTurns++;
    if(currentTurns >= turnsPerRound){
        currentPlayer = (currentPlayer == Player::Scott) ? Player::Rusty : Player::Scott;
        currentTurns = 0;
    }
    totalTurns--;
}

bool Game::CanPlayRound(){
    return totalTurns > 0;
}

void Game::PrintScores(){
    std::cout << "Scores:\n";
    std::cout << "\tScott: " << scottPoints << "\n";
    std::cout << "\tRusty: " << rustyPoints << "\n";
}