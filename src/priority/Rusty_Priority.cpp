#include "Rusty_Priority.hpp"
#include "Players.hpp"

signed char Rusty_Priority::BallCompare(std::shared_ptr<Ball> a, std::shared_ptr<Ball> b){
    if(a->IsLargerThan(*b, Player::Rusty))
        return 1;
    else if(b->IsLargerThan(*a, Player::Rusty))
        return -1;
    else
        return 0;
}