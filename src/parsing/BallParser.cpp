#include "BallParser.hpp"

#include <string>
#include "Players.hpp"
#include <fstream>
#include "Ball.hpp"
#include "Game.hpp"
#include <memory>
#include <vector>
#include <iostream>

namespace BallParser{
    std::unique_ptr<std::vector<std::shared_ptr<Game>>> ParseFile(std::string fileName){    
        
        auto games = std::unique_ptr<std::vector<std::shared_ptr<Game>>>(
            new std::vector<std::shared_ptr<Game>>());

        std::string line = "";
        std::ifstream file(fileName, std::ifstream::in);

        unsigned int totalGames = 0;

        if(!file.is_open()){
            std::cout << "Could not find file\n";
            return std::move(games);
        }

        //First line is how many games we should prepare
        std::getline(file, line);
        totalGames = std::stoi(line);

        for(unsigned int i = 0; i < totalGames; i++){
            auto balls = std::vector<unsigned int>();
            unsigned totalBalls = 0, turnsPerRound = 0;
            file >> totalBalls;
            file >> turnsPerRound;
            for(unsigned int j = 0; j < totalBalls; j++){
                unsigned int ballVal;
                file >> ballVal;
                balls.push_back(ballVal);
            }
            std::string firstPlayerStr;
            file >> firstPlayerStr;
            Player firstPlayer = 
                firstPlayerStr == "HEADS" ? Player::Scott : Player::Rusty;
            games->push_back(
                std::shared_ptr<Game>(
                    new Game(
                        firstPlayer,
                        turnsPerRound,
                        ConstructBalls(balls)
                    )
                )
            );           
        }
        file.close();
        return games;
    }
}