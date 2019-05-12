#pragma once

#ifndef Ball_hpp
#define Ball_hpp

// #include "Game.hpp"
#include "Players.hpp"
#include <vector>
#include <memory>


class Ball{
    private:
        unsigned int CalcDigitSum(unsigned int val) const;
        unsigned int value;
        unsigned int digitSum;
        bool isValid = true;
    public:
        Ball(unsigned int faceValue);
        ~Ball() = default;

        unsigned int GetValue() const;
        unsigned int GetDigitSum() const;

        bool IsLargerThan(const Ball& otherBall, const Player player) const;
        
        bool IsValid();
        void SetValidity(bool val);

};

std::unique_ptr<std::vector<std::shared_ptr<Ball>>> ConstructBalls(std::vector<unsigned int> ints);

#endif
