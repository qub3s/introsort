#include <iostream>
#include<cstdlib>
#include<concepts>
using namespace std;

template <typename T>
concept order = requires (T a, T b) { {a < b}; };


// The compareto method has to provide a total order ( wikipedia.org/wiki/Total_order )
template <typename T>
bool compareto(T a, T b) requires order<T>{
    return a < b;
}

// Implemenation of insertionsort
template <typename T>
void insertionsort(T* list, int length)requires order<T>{
    int i = 1;
    T valuetosort;
    while( i < length ){
        valuetosort = list[i];
        int j = i;
        while( j > 0 && list[j-1] > valuetosort ){
            list[j] = list[j-1];
            j = j - 1;
        }
        list[j] = valuetosort;
        i = i+1;
    }
}

// Implementation of Quicksort-3, on very large lists it might be worth is to replace this with Quicksort-9
// takes: list pointer; first element (prob 0); length of list -1
template <typename T>
void quicksort3(T* list, int lo, int up){
    // ---------------------------------------------------
    // cancel conditions
    if( !( lo < up ) ){
        return;
    }
    
    if( up - lo == 0 ){
        return;
    }

    if(up - lo == 1){
        if( compareto( list[up], list[lo] ) ){
            T temp = list[lo];
            list[lo] = list[up];
            list[up] = temp;
        }
        return;
    }     
    // ---------------------------------------------------
    // finding the pivot Element ( middle of 3 )
    T lov = list[lo];
    T upv = list[up];
    int miv = lo + ( up - lo )/2;
    T a = list[miv];
    T pivot;

    if( compareto(lov,upv) ){
        pivot = lov;
    }
    else{
        pivot = upv;
    }

    if( compareto(pivot, list[miv] ) ){
        T temp = list[ miv ];
        list[ miv ] = list[ up ];
        list[ up ] = temp;
        pivot = temp;
    }

    // ---------------------------------------------------
    // Sort the array

    int le = lo - 1;
    int ri = up + 1;
    
    while(true){
        le = le + 1;
        // find element from the left to swap
        while ( compareto(list[le],pivot) ){
            le = le + 1;
        }

        ri = ri - 1;
        // find element form the right to swap
        while ( compareto(pivot,list[ri]) ){
            ri = ri - 1;
        }

        // If the pointers meet stop
        if( le >= ri ){
           break;
        }

        // swap the elements
        T temp = list[ri];
        list[ri] = list[le];
        list[le] = temp;
    }
    // if difference between lo and ri in smaller than x then use insertionsort

    // check if the restlists are bigger than x
    quicksort3(list,lo,ri);             // use quicksort on the lower part of the array
    quicksort3(list,ri+1,up);           // use quicksort on the upper part of the array
    return;
    }


// Implementation of Heapsort
template <typename T>
void printlist( T* list, int length){
    cout << "\n";
    for(int i = 0; i < length; i++){
        cout << list[i] << " ";
    }
    cout << "\n";
}

int main(){
    srand(time(0));
    int length = 100;
    double list[length];

    for(int i = 0; i < length; i++){
        list[i] = rand()%1000+0.5;
    }

    int arr[4]={123,1,2,3};
    int arr1[4]={0,1,2,3};
    printlist(list,length);
    quicksort3(list,0,length-1);
    printlist(list,length);
    return 0;
}

