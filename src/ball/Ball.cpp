#include "Ball.hpp"
#include "Game.hpp"
#include <iostream>
#include <memory>

std::unique_ptr<std::vector<std::shared_ptr<Ball>>> ConstructBalls(std::vector<unsigned int> ints){
    auto balls = std::unique_ptr<std::vector<std::shared_ptr<Ball>>>(
        new std::vector<std::shared_ptr<Ball>>()
    );
    for(unsigned int val : ints)
        balls->push_back(std::shared_ptr<Ball>(new Ball(val)));
    return std::move(balls);
}

Ball::Ball(unsigned int faceValue){
    this->value = faceValue;
    this->digitSum = CalcDigitSum(faceValue);
}

unsigned int Ball::GetValue() const{
    return this->value;
}

unsigned int Ball::GetDigitSum() const{
    return this->digitSum;
}

unsigned int Ball::CalcDigitSum(unsigned int val) const{
    unsigned int sum = 0;
    while(val > 0){
        sum += val % 10; //Get the ones place and add it to the sum
        val /= 10; //Knock off the ones digit
    }
    return sum;
}

bool Ball::IsLargerThan(const Ball& otherBall, Player player) const{

    //Is the player Scott
    if(player == Player::Scott)
        return GetValue() > otherBall.GetValue();

    if(!isValid)
        return -1;

    //The player is Rusty
    return //If the digit sum is larger than the parent...
        GetDigitSum() > otherBall.GetDigitSum()
        || //...OR...
        (
            //...the digit sums are equal...
            GetDigitSum() == otherBall.GetDigitSum()
            && //...AND the value is large than the parent...
            GetValue() > otherBall.GetValue()
        );

}

bool Ball::IsValid(){
    return isValid;
}

void Ball::SetValidity(bool val){
    isValid = val;
}