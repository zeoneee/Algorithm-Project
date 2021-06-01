#include "Laptop.h"

void MakeHeap(Laptop a[], int Root, int LastNode);
void heapsort(Laptop a[], int N);
void swap(Laptop a[], int i, int j);

inline void swap(Laptop a[], int i, int j); 
void quicksort(Laptop a[], int l, int r);

void copy(Laptop& a, Laptop& b);
void merge(Laptop* a, int l, int mid, int r, int& compare, int& move);
void mergesort(Laptop* a, int l, int r, int& compare, int& move);