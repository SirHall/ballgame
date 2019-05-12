// #pragma once
#ifndef Rusty_Priority_hpp
#define Rusty_Priority_hpp

#include "Priority.hpp"

class Rusty_Priority : public Priority{
    public:
        Rusty_Priority() = default;
        virtual ~Rusty_Priority() = default;

        virtual signed char BallCompare(std::shared_ptr<Ball> a, std::shared_ptr<Ball> b);
};

#endif