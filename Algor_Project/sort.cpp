#include "sort.h"

Laptop* sorted = new Laptop[2000]; // merge

// ½ÂÇõ
void swap(Laptop a[], int i, int j) {
	Laptop temp;
	temp = a[j];
	// move++;
	a[j] = a[i];
	// move++;
	a[i] = temp;
}

void MakeHeap(Laptop a[], int Root, int LastNode) {
	int Parent, LeftSon, RightSon, Son; Laptop RootValue;
	Parent = Root;
	RootValue = a[Root];
	LeftSon = 2 * Parent + 1;
	//move++;
	RightSon = LeftSon + 1;
	//move++;
	while (LeftSon < LastNode) {
		//comp++;
		if (RightSon <= LastNode && a[LeftSon].price < a[RightSon].price) {
			Son = RightSon;
		}
		else
		{
			Son = LeftSon;
		}
		if (RootValue.price < a[Son].price) {
			//move++;
			a[Parent] = a[Son];
			Parent = Son;
			LeftSon = Parent * 2 + 1;
			RightSon = LeftSon + 1;
		}
		else break;
		//comp++;
	}
	a[Parent] = RootValue;
}

void heapsort(Laptop a[], int N) {
	int i;
	for (i = N / 2; i >= 1; i--)
	{
		MakeHeap(a, i - 1, N - 1);
	}
	for (i = N - 1; i >= 1; i--)
	{
		//comp++;
		//move++;
		swap(a, 0, i);
		MakeHeap(a, 0, i - 1);
	}
}

// ÂùÈ£
// For quick sort
inline void swap(Laptop a[], int i, int j)
{
	//move += 3;
	Laptop t = a[i];
	a[i] = a[j];
	a[j] = t;
}

void quicksort(Laptop a[], int l, int r)
{
	if (l >= r)
		return;
	int pivot = l;
	int i = pivot + 1;
	int j = r;
	int temp;
	while (i <= j) {
		while (i <= r && a[i].price <= a[pivot].price) {
			i++; 
			//compare++;
		}
		while (j > l && a[j].price >= a[pivot].price) {
			j--;
			//compare++;
		}
		if (i >= j) break;
		swap(a, i, j);
	}
	swap(a, j, pivot);
	quicksort(a, l, j - 1);
	quicksort(a, j + 1, r);
}

// ÁöÇö
void copy(Laptop& a, Laptop& b) {
	a.model = b.model;
	a.price = b.price;
	a.cpu = b.cpu;
	a.ram = b.ram;
	a.ssd = b.ssd;
	a.weight = b.weight;
	a.gpu = b.gpu;
	a.monitor = b.monitor;
}

// °¡°Ý Á¤·Ä
void merge(Laptop* a, int l, int mid, int r, int& compare, int& move) {
	int i, j, k, n;
	i = l; j = mid + 1; k = l;
	while (i <= mid && j <= r) {
		if (a[i].price <= a[j].price) {
			compare++;
			copy(sorted[k++], a[i++]);
			move++;
		}
		else {
			compare++;
			copy(sorted[k++], a[j++]);
			move++;
		}
	}
	if (i > mid) {
		for (n = j; n <= r; n++) { copy(sorted[k++], a[n]); move++; }
	}
	else {
		for (n = i; n <= mid; n++) { copy(sorted[k++], a[n]); move++; }
	}
	for (n = l; n <= r; n++) { copy(a[n], sorted[n]); move++; }
}

void mergesort(Laptop* a, int l, int r, int& compare, int& move) {
	int mid;
	if (l < r) {
		mid = (l + r) / 2;
		mergesort(a, l, mid, compare, move);
		mergesort(a, mid + 1, r, compare, move);
		merge(a, l, mid, r, compare, move);
	}
}
