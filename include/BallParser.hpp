#pragma once
#ifndef BallParser_hpp
#define BallParser_hpp

#include <string>
#include <fstream>
#include "Ball.hpp"
#include "Game.hpp"
#include <memory>
#include <vector>

namespace BallParser{
    std::unique_ptr<std::vector<std::shared_ptr<Game>>> ParseFile(std::string fileName);
}

#endif