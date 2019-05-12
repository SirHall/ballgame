// #pragma once
#ifndef Priority_hpp
#define Priority_hpp

#include "Ball.hpp"
// #include "Game.hpp"
#include <memory>
//Uses a max heap

class Priority{

    private:
        //Stores the index positions in a priority queue using a heap
        std::vector<std::shared_ptr<Ball>> heap;

    public:
        Priority() = default;
        virtual ~Priority() = default;

        unsigned int BallCount();

        unsigned int ParentIndex(unsigned int index);
        unsigned int LeftChildIndex(unsigned int index);
        unsigned int RightChildIndex(unsigned int index);
        
        std::shared_ptr<Ball> GetNode(unsigned int index);
        std::shared_ptr<Ball> GetParent(unsigned int index);
        std::shared_ptr<Ball> GetLeftChild(unsigned int index);
        std::shared_ptr<Ball> GetRightChild(unsigned int index);

        void RemoveNode(unsigned int index);
        void Add (std::shared_ptr<Ball> ball);

        void HeapUp(unsigned int ballIndex);
        void HeapDown(unsigned int ballIndex);
        void AutoHeap(unsigned int ballIndex);

        void SwapBalls(unsigned index1, unsigned index2);

        virtual signed char BallCompare(std::shared_ptr<Ball> a, std::shared_ptr<Ball> b);

        bool IndexExists(unsigned int index);

        void Clean(unsigned int index);
};

#endif