// #pragma once
#ifndef Scott_Priority_hpp
#define Scott_Priority_hpp

#include "Priority.hpp"

class Scott_Priority : public Priority{
    public:
        Scott_Priority() = default;
        virtual ~Scott_Priority() = default;

        virtual signed char BallCompare(std::shared_ptr<Ball> a, std::shared_ptr<Ball> b);
};

#endif