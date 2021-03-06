#include "SLinkedList.hpp"
#include <iostream>
int main(){
    SLinkedList<int>SL;
    for(int i=0; i< 10 ;i++){
        SL.addFront(i);
    }
    std::cout << SL;
}