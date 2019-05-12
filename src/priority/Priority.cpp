#include "Priority.hpp"
#include <iostream>

unsigned int Priority::BallCount(){
    return heap.size();
}

unsigned int Priority::ParentIndex(unsigned int index){
    // if((index - 1) / 2 >= BallCount())
    //     std::cout << "\tTrying to access ball at index " << (index - 1) / 2 << " with max index of " << BallCount() - 1 << "\n";
    Clean((index - 1) / 2);
    return (index - 1) / 2;
}

unsigned int Priority::LeftChildIndex(unsigned int index){
    // if((2 * index) + 1 >= BallCount())
    //     std::cout << "\tTrying to access ball at index " << (2 * index) + 1 << " with max index of " << BallCount() - 1 << "\n";
    Clean((2 * index) + 1);
    return (2 * index) + 1;
}

unsigned int Priority::RightChildIndex(unsigned int index){
    // if((2 * index) + 2 >= BallCount())
    //     std::cout << "\tTrying to access ball at index " << (2 * index) + 2 << " with max index of " << BallCount() - 1 << "\n";
    Clean((2 * index) + 2);
    return (2 * index) + 2;
}
        

std::shared_ptr<Ball> Priority::GetNode(unsigned int index){    
    Clean(index);
    // std::cout << "Getting node " << index << "\n";
    // if(index > BallCount())
    //     std::cout << "\tTrying to access ball at index " << index << " with max index of " << BallCount() - 1 << "\n";
    return heap[index];
}

std::shared_ptr<Ball> Priority::GetParent(unsigned int index){
    // std::cout << "Getting parent of " << index << " node (" << ParentIndex(index) << ")\n";
    return GetNode(ParentIndex(index));
}

std::shared_ptr<Ball> Priority::GetLeftChild(unsigned int index){
    // std::cout << "Getting left child node\n";
    return GetNode(LeftChildIndex(index));
}

std::shared_ptr<Ball> Priority::GetRightChild(unsigned int index){
    // std::cout << "Getting right child node\n";
    return GetNode(RightChildIndex(index));
}

void Priority::RemoveNode(unsigned int index){

    std::shared_ptr<Ball> oldBall = heap[index];
    oldBall->SetValidity(false);

    heap[index] = heap[heap.size() - 1]; //Copy last element to one removed
    heap.pop_back(); //Remove last element from vector
    
    HeapDown(index); //Heap up or down
    
}

void Priority::SwapBalls(unsigned int index1, unsigned int index2){
    // std::cout << "Swapping balls\n";
    //Ensure these are valid balls
    if(!IndexExists(index1)){
        std::cout << "\tTried swapping ball1 but it's index1 (" << index1 << ") is invalid\n";
        return;
    }
    if(!IndexExists(index2)){
        std::cout << "\tTried swapping ball2 but it's index2 (" << index2 << ") is invalid\n";
        return;
    }
    std::shared_ptr<Ball> tmp = heap[index1];
    heap[index1] = heap[index2];
    heap[index2] = tmp;
}

void Priority::Add (std::shared_ptr<Ball> ball){
    heap.push_back(ball);
    HeapUp(heap.size() - 1);
}


void Priority::HeapUp(unsigned int ballIndex){
    if(ballIndex == 0 || !IndexExists(ballIndex))
        return;

    // std::cout << "Reached Heap Up\n";
    
    while(
        IndexExists(ballIndex)
        &&
        IndexExists(ParentIndex(ballIndex))
        &&
        BallCompare(GetNode(ballIndex), GetParent(ballIndex)) > 0
    ){
        //Swap ball with parent
        SwapBalls(ballIndex, ParentIndex(ballIndex));
        ballIndex = ParentIndex(ballIndex);
    }
}

void Priority::HeapDown(unsigned int ballIndex){
    // std::cout << "Reached Heaping Down\n";
    
    if(!IndexExists(ballIndex))
        return;


    bool isRightSmaller = true, isLeftSmaller = true;

    while(isRightSmaller || isLeftSmaller){
        //First find out which child is larger
        unsigned int swapIndex = ballIndex; //Give's us the max integer value

        isRightSmaller = 
            IndexExists(RightChildIndex(ballIndex))
            &&
            BallCompare(GetNode(ballIndex), GetRightChild(ballIndex)) < 0;
        isLeftSmaller = 
            IndexExists(LeftChildIndex(ballIndex))
            &&
            BallCompare(GetNode(ballIndex), GetLeftChild(ballIndex)) < 0;

        if(!isRightSmaller && !isLeftSmaller)
            return;

        if(isRightSmaller && isLeftSmaller){ //Find the larger of the two
            swapIndex = 
                BallCompare(GetRightChild(ballIndex), GetLeftChild(ballIndex)) > 0
                ? RightChildIndex(ballIndex) : LeftChildIndex(ballIndex);

        }else
        if(isRightSmaller || isLeftSmaller){
            swapIndex = 
                isRightSmaller ? RightChildIndex(ballIndex) : LeftChildIndex(ballIndex);
        }
        //Neither is smaller
        if(swapIndex == ballIndex)
            return; //We are done
        SwapBalls(ballIndex, swapIndex);
        ballIndex = swapIndex;
    }
}

void Priority::AutoHeap(unsigned int ballIndex){
    
    if(!IndexExists(ballIndex))
        return;

    if(!heap[ballIndex]->IsValid())
        RemoveNode(ballIndex); //Bit of sneaky recursion here
    
    if(
        IndexExists(ParentIndex(ballIndex))
        &&
        BallCompare(GetNode(ballIndex), GetParent(ballIndex)) > 0
    )
        HeapUp(ballIndex);
    else if(
        (
            IndexExists(LeftChildIndex(ballIndex))
            &&
            BallCompare(GetNode(ballIndex), GetLeftChild(ballIndex)) < 0
        )
        ||
        (
            IndexExists(RightChildIndex(ballIndex))
            &&
            BallCompare(GetNode(ballIndex), GetRightChild(ballIndex)) < 0
        )
    )
        HeapDown(ballIndex);
}

signed char Priority::BallCompare(std::shared_ptr<Ball> a, std::shared_ptr<Ball> b){
    //If ball 'a' has a higher priority than 'b', return 1.
    //If balls 'a' and 'b' have equal priorities, return 0.
    //If ball 'a' has a lower priority than 'b', return -1.
    return 0;
}

bool Priority::IndexExists(unsigned int index){
    Clean(index);
    return index < BallCount();
}

void Priority::Clean(unsigned int index){
    if(index < BallCount() && !heap[index]->IsValid())
        RemoveNode(index);
}