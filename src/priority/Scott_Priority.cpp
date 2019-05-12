#include "Scott_Priority.hpp"
#include <iostream>

signed char Scott_Priority::BallCompare(std::shared_ptr<Ball> a, std::shared_ptr<Ball> b){
    // std::cout << "Comparing balls\n";
    if(a.get() == nullptr || b.get() == nullptr)
        return 0;
    //     std::cout << "Compared balls but one is null\n";

    if(a->IsLargerThan(*b, Player::Scott))
        return 1;
    else if(b->IsLargerThan(*a, Player::Scott))
        return -1;
    else
        return 0;
}