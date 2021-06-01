#include "Laptop.h"

// 승혁
int whatIndex_bs(Laptop list[], int price);

// 찬호

int whatIndex_hash(Laptop list[], int price);

class HashNode {
public:
	// hashkey
	int priceKey;
	// list에서의 idx
	int originIdx;
	Laptop laptop;
	HashNode* next;

	HashNode() { priceKey = 0; originIdx = 0; next = NULL; }
	HashNode(int _priceKey, Laptop _laptop) {
		priceKey = _priceKey;
		laptop = _laptop;
		next = NULL;
	}
};

class HashTable {
public:
	int size;
	HashNode* nodelist;

	HashTable(int min, int len) {
		int temp = min;

		size = len;
		nodelist = new HashNode[len];
		for (int i = 0; i < len; i++)
			nodelist[i].priceKey = temp++;
	}

	// hashtable 생성
	void makeHash(Laptop a[]); 

	// hashtable에 laptop 추가
	void add(Laptop laptop, int idx);

	// price 가격과 가장 가까운 laptop의 originIdx 반환
	int find(int price);
};

int getMinKey(Laptop a[]);
int getMaxKey(Laptop a[]);
int getHashLength(Laptop a[]);

// 지현
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

class RBtree {
private: 
	typedef struct node{
		Laptop key;
		int tag;
		int Info;
		struct node* l,* r;
		node(Laptop k, int i, int t, struct node* ll, struct node* rr) {
			copy(key, k);
			Info = i; tag = t; l = ll; r = rr;
		}
	}node;
	struct node* head, * tail, * x, * p, * g, * gg, * z;
public:
	RBtree();
	void insert(Laptop k, int info, int& compare);
	//node* rotate(Laptop k, struct node* y, int& compare);
	node* rotate(Laptop k, struct node* y, int& compare) {
		struct node* high, * low;
		high = (k.price < y->key.price) ? y->l : y->r; compare++;
		if (k.price < high->key.price) { low = high->l; high->l = low->r; low->r = high; }
		else { low = high->r; high->r = low->l; low->l = high; }
		compare++;
		if (k.price < y->key.price) y->l = low; else y->r = low;
		compare++;
		return low;
	}
	void split(Laptop k, int& compare);
	int search(int price, int& compare);
};

int whatIndex_rb(Laptop list[], int price);
