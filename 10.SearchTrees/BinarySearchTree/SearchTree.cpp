#include "SearchTree.hpp"
#include <bits/stdc++.h>

using namespace std;

int main(){
    SearchTree<Entry<int,int> > ST = SearchTree<Entry<int,int> >();
    for(int i=0; i < 10; i++){
        ST.insert(3,4);
    }
}