#include <bits/stdc++.h>
using namespace std;


typedef int Elem;
class ArrayVector{
public:
    ArrayVector();
    int size() const;
    bool empty() const;
    Elem& operator[](int i);
    Elem& at(int i);
    void erase(int i);
    void insert(int i, const Elem& e);
    void reserve(int N);
private:
    int capacity;  // 배열 용량
    int n;         // 원소 갯수
    Elem *A;        // 배열
};

ArrayVector::ArrayVector():capacity(0), n(0), A(nullptr){} // 생성자
int ArrayVector::size() const {  
    return n;
}
bool ArrayVector::empty() const{
    return size() ==0;
}
Elem& ArrayVector::operator[](int i){ // 원소의 인덱스
    return A[i];
}
Elem& ArrayVector::at(int i){ //~ 에있는원소
    if(i <0 || i >= n) throw invalid_argument("illegal index");
    return A[i];
}
void ArrayVector::erase(int i){
    for(int j= i+1; j< n; j++){ // 원소를 왼쪽으로 shift함
        A[j-1] = A[j];
    }
    n--;
}

void ArrayVector::reserve(int N){
    if( capacity >= N) return;  
    Elem* B = new Elem[N];      // 큰 배열을 생성
    for(int j=0; j < n; j++){   // 카피 
        B[j] = A[j];
    }
    if(A!= nullptr) delete [] A; // 원래배열 삭제
    A = B;                      // 원래배열을 새배열로 치환
    capacity = N;               // 새로운 capcaity로 설정
}

void ArrayVector::insert(int i, const Elem& e){
    if(n >= capacity){
        reserve(max(1,2*capacity));
    }
    for(int j= n-1; j>= i; j--){
        A[j+1] =A[j];           // 오른쪽으로 shift
    }
    A[i] = e;                   // 값배정
    n++;
}




int main(){
    ArrayVector v;
    for(int i=0; i < 10 ;i++)
        v.insert(0,i);
    for(int i=0; i < 10 ;i++){
        cout << v.at(0);
        v.erase(0);
    }
    cout << endl;
    cout << v.size();

}