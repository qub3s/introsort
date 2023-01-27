#include <iostream>
#include <cstdlib>
#include <cmath>
#include <concepts>
#include <bits/stdc++.h>

#define QUICKSORT_INSERT_LIMIT 16 

using namespace std;

template <typename T>
concept order = requires (T a, T b) { {a < b}; };

// The compareto method has to provide a total order ( wikipedia.org/wiki/Total_order )
// uses pointers of the elements
template <typename T>
bool compareto(T* a, T* b) requires order<T>{
    return *a < *b;
}

// The swap of 2 Elements
// pointer pointing on the 2 elemntes
template <typename T>
void swap(T* a, T* b) requires order<T>{
    T temp = *a;
    *a = *b;
    *b = temp;
    return;
}

// Implemenation of insertionsort
// pointer, to the start of the list, and to the last element
template <typename T>
void insertionsort(T* list, T* end)requires order<T>{
    int i = 1;
    T valuetosort;
    while( list+i <= end ){
        valuetosort = list[i];
        int j = i;
        while( j > 0 && compareto(&valuetosort, &list[j-1]) ){
            list[j] = list[j-1];
            j = j - 1;
        }
        list[j] = valuetosort;
        i = i+1;
    }
}

// Implementation of Quicksort-3, on very large lists it might be worth is to replace this with Quicksort-9
// takes: list pointer; first element (prob 0); length of list -1
// returns the position of the 
template <typename T>
T* quicksort3(T* lo, T* up)requires order<T>{
    // ---------------------------------------------------
    // cancel conditions
    if( !( lo < up ) ){
        return NULL;
    }
    
    if( up - lo == 0 ){
        return NULL;
    }

    if(up - lo == 1){
        if( compareto( up, lo ) ){
            swap(up,lo);
        }
        return NULL;
    }     
    // ---------------------------------------------------
    // finding the pivot Element ( middle of 3 )
    int miv = ( up - lo )/2;
    T pivot;

    if( compareto(lo,up) ){
        pivot = *lo;
    }
    else{
        pivot = *up;
    }

    if( compareto( &pivot, &lo[miv] ) ){
        pivot = lo[miv];
    }

    // ---------------------------------------------------
    // Sort the array

    T* le = lo;
    T* ri = up;
    while(true){
        // find element from the left to swap
        while ( compareto(le, &pivot) && le < ri ){
            le = le + 1;
        }

        // find element form the right to swap
        while ( compareto( &pivot, ri) && le < ri){
            ri = ri - 1;
        }

        // If the pointers meet stop
        if( le >= ri ){
           break;
        }

        // swap the elements
        swap(ri,le);
        ri = ri - 1;
        le = le + 1;
    }
    return ri;
}


template <typename T>
void reheap(T* list, int n, int i)requires order<T>{
    int largest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;

    if (l < n && compareto(&list[largest], &list[l]) ){
        largest = l;
    }

    if (r < n && compareto( &list[largest], &list[r]) ){
        largest = r;
    }
    
    if (largest != i){
        T swap = list[i];
        list[i] = list[largest];
        list[largest] = swap;

        reheap(list, n, largest);
    }
}

// Implementation of Heapsort
template <typename T>
void heapsort(T* list, int n)requires order<T>{
    for (int i = n / 2 - 1; i >= 0; i--)
        reheap(list, n, i);

    for (int i=n-1; i>=0; i--)
    {
        T temp = list[0];
        list[0] = list[i];
        list[i] = temp;

        reheap(list, i, 0);
    }
}

template <typename T>
void introsortrun(T* lo, T* up,int depth,int heaplimit)requires order<T>{
    if( (up-lo) < QUICKSORT_INSERT_LIMIT ){
        insertionsort(lo, up);
        return;
    }

    if( depth > heaplimit ){
        heapsort(lo,up-lo);
        return;
    }

    T* pivpos = quicksort3(lo,up);
    if(pivpos != NULL){
        introsortrun(lo,pivpos,depth+1, heaplimit+1);
        introsortrun(pivpos+1,up,depth+1, heaplimit+1);
    }
}

template <typename T>
void introsort(T* lo, T* up)requires order<T>{
    int heaplimit = 2 * log2(up-lo);
    introsortrun(lo,up,0,heaplimit);
}

template <typename T>
void printlist(T* list, int length){
    cout << "\n";
    for(int i = 0; i < length; i++){
        cout << list[i] << " ";
    }
    cout << "\n";
}

int main(){
    srand(time(0));
    int length = 1000000;
    int times = 100;
    double list[length];

    for(int x = 0; x < times; x++){

        for(int i = 0; i < length; i++){
            list[i] = rand()%length;
        }

        introsort(list,list+length-1);
        cout << x << "\n";
    }
    return 0;
}

