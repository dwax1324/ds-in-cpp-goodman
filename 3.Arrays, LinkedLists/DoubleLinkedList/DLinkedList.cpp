#include "DLinkedList.hpp"
#include <iostream>
int main(){
    DLinkedList<int>DL;
    for(int i=0; i < 10; i++){
        DL.addBack(i);
    }
    std::cout << DL;
}