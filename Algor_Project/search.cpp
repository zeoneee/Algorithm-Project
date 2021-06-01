#include "search.h"
#define MAX 970
#define black 0 // rbtree
#define red 1

// ����
int whatIndex_bs(Laptop list[], int price)
{
	int start = 0;
	int end = MAX - 2;
	int i = 0;

	if (price > list[end].price)
		return end;
	while (start <= end)
	{
		i++;
		printf("%dȸ�� Ž�� start=%d, end=%d\n", i, start, end);
		int mid = (start + end) / 2;
		if (list[start].price == list[end].price)
		{
			if (price < list[start].price)
			{
				int temp = list[start].price;
				while ((temp != list[start].price) && start != 0)
				{
					start--;
				}
				return start;
			}
			else if (price > list[end].price)
			{
				int temp = list[end].price;
				while ((temp != list[end].price) && end != MAX)
				{
					end++;
				}
				return end;
			}
		}
		if (start + 3 == end)
		{
			if (price < list[start].price)
				return start;
			else if (price >= list[start].price
				&& price < list[start + 1].price)
				return start + 1;
			else if (price >= list[start + 1].price
				&& price < list[start + 2].price)
				return start + 2;
			else if (price >= list[end - 1].price
				&& price < list[end].price)
				return end;
			else
				return end + 1;
		}
		else if (start + 2 == end)
		{
			if (price < list[start].price)
				return start;
			else if (price >= list[start].price
				&& price < list[mid].price)
				return mid;
			else if (price >= list[mid].price
				&& price < list[end].price)
				return end;
			else
				return end + 1;
		}
		else if (start + 1 == end)
		{
			if (price < list[start].price)
				return start;
			else if (price >= list[start].price
				&& price < list[end].price)
				return end;
			else
				return end + 1;
		}
		else if (price == list[mid].price)
			return mid;
		else if (price < list[mid].price)
		{
			end = mid - 1;
		}
		else if (price > list[mid].price)
		{
			start = mid - 1;
		}
	}
}


// ��ȣ
int whatIndex_hash(Laptop list[], int price) {
	int min = getMinKey(list);
	int len = getHashLength(list);
	int idx = 0;
	HashTable ht(min, len);
	ht.makeHash(list);

	return ht.find(price);
}


void HashTable::makeHash(Laptop a[]) {
	for (int i = 0; i < MAX - 1; i++)
		add(a[i], i);
}

void HashTable::add(Laptop laptop, int idx) {

	HashNode* tempNode = new HashNode;
	HashNode* cursor = NULL;
	tempNode->priceKey = (laptop.price / 100000);
	tempNode->originIdx = idx;
	tempNode->laptop = laptop;

	for (int i = 0; i < size; i++) {
		if (nodelist[i].priceKey == tempNode->priceKey) {
			cursor = &nodelist[i];
			while (cursor->next != NULL)
				cursor = cursor->next;

			cursor->next = tempNode;
			break;
		}
	}
}

int HashTable::find(int price) {
	int findKey = price / 100000;
	HashNode* cursor = NULL;

	for (int i = 0; i < size; i++) {
		if (nodelist[i].priceKey == findKey) {
			cursor = &nodelist[i];
			break;
		}
	}

	while (cursor->laptop.price == 0 ||
		(cursor->next != NULL
			&& abs(cursor->laptop.price - price) > abs(cursor->next->laptop.price - price)))
		cursor = cursor->next;

	return cursor->originIdx;

}

int getMinKey(Laptop a[]) { return a[0].price / 100000; }
int getMaxKey(Laptop a[]) { return a[MAX - 2].price / 100000; }
int getHashLength(Laptop a[]) { return getMaxKey(a) - getMinKey(a) + 1; }


// ����
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

RBtree::RBtree() {
	Laptop null;
	z = new node(null, -1, black, 0, 0);  // NULL���
	z->l = z; z->r = z;
	head = new node(null, -1, black, z, z); // ���� info�� 0���� ���� 
}

void RBtree::insert(Laptop k, int info, int& compare) {
	x = head; p = head; g = head;
	while (x != z) {
		gg = g; g = p; p = x;
		x = (k.price < x->key.price) ? x->l : x->r; compare++;
		if (x->l->tag && x->r->tag) split(k, compare);   // x�� 4����� split 
	}
	x = new node(k, info, red, z, z);
	if (k.price < p->key.price) p->l = x; else p->r = x; compare++;
	split(k, compare); head->r->tag = black; // �ϴ� ��� ����ũ�� �ο��ϰ� �ѹ� �� split
}

/*
node* RBtree::rotate(Laptop k, struct node* y, int& compare) {
	struct node* high, * low;
	high = (k.price < y->key.price) ? y->l : y->r; compare++;
	if (k.price < high->key.price) { low = high->l; high->l = low->r; low->r = high; }
	else { low = high->r; high->r = low->l; low->l = high; }
	compare++;
	if (k.price < y->key.price) y->l = low; else y->r = low;
	compare++;
	return low;
}
*/

void RBtree::split(Laptop k, int& compare) {
	x->tag = red; x->l->tag = black; x->r->tag = black;
	if (p->tag) {
		g->tag = red;
		if (k.price < g->key.price != k.price < p->key.price) p = rotate(k, g, compare);
		compare++;
		x = rotate(k, gg, compare);
		x->tag = black;
	}
}

int RBtree::search(int price, int& compare) {
	// �� �ߺ��Ǵ°�� 
		// ã�� ������ �ݾ״밡 �ȳ��ð�� 
	struct node* x = head->r;
	z->key.price = price;
	while (x->r != z && x->l != z) {
		compare++;
		if (price == x->key.price) {
			return x->Info;
		}
		else {
			x = (price < x->key.price) ? x->l : x->r;
		}
	}
	compare++;
	if (x->l == z && x->r == z) { // �ڽĳ�� ���� ���  
		if (price == x->key.price) {
			return x->Info;
		}
		else {
			return x->Info + 1;
		}
	}
	else if (x->l != NULL) { // ���� �ڽĸ� �ִ� ���
		if (price == x->key.price) {
			return x->Info;
		}
		else if (price < x->key.price) x = x->l;
		else return x->Info + 1;

	}
	else {	// ������ �ڽĸ� �ִ� ��� 
		if (price == x->key.price) {
			return x->Info;
		}
		else if (price < x->key.price) return x->Info;
		else x = x->r;
	}
}

int whatIndex_rb(Laptop list[], int price) {
	// ��������
	// Ž�� �˰������� �Էµ� �ݾ׺��� ���� ������ ������ ù index
	int info = 0;
	RBtree T;
	for (int i = 0; i < MAX - 1; i++) {
		T.insert(list[i], info++, compare);
	}
	return T.search(price, compare);
}
