#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstdlib>
#define MAX 970
using namespace std;

/*
	time, ��Ƚ�� �����ϱ�
*/

class Laptop {
public:
	string model;
	int price;
	string cpu;
	int ram;
	int ssd;
	int weight;
	bool gpu; // ���� : 0, ���� : 1
	double monitor;

	Laptop() {
		this->model = "";
		this->price = 0;
		this->cpu = "";
		this->ram = 0;
		this->ssd = 0;
		this->weight = 0;
		this->gpu = false;
		this->monitor = 0;
	}
};

// for hashnode
class HashNode {
public:
	// hashkey
	int priceKey;
	// list������ idx
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

// for hashtable
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

	// hashtable ����
	void makeHash(Laptop a[]) {
		for (int i = 0; i < MAX - 1; i++)
			add(a[i], i);
	}

	// hashtable�� laptop �߰�
	void add(Laptop laptop, int idx) {

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

	// price ���ݰ� ���� ����� laptop�� originIdx ��ȯ
	int find(int price) {
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
};

// information for making hash
int getMinKey(Laptop a[]) { return a[0].price / 100000; }
int getMaxKey(Laptop a[]) { return a[MAX - 2].price / 100000; }
int getHashLength(Laptop a[]) { return getMaxKey(a) - getMinKey(a) + 1; }

void makeLaptopArr(Laptop list[], string fileName) {
	int position = 0; // Column number
	int aggIdx = 0; // Aggregate index number
	string str_buf;
	ifstream readFile;
	readFile.open(fileName);
	if (readFile.is_open()) {
		while (!readFile.eof()) {
			if (position == 8) {
				/*cout << list[aggIdx].model << endl;
				cout << aggIdx << endl;*/
				position = 0;
				aggIdx++;
			}
			string str;
			if (position == 7) {
				getline(readFile, str, '\n');
			}
			else {
				getline(readFile, str, ',');
			}
			/*cout << str << " postion : "<< position << endl;*/
			if (position == 0) list[aggIdx].model = str;
			else if (position == 1) list[aggIdx].cpu = str;
			else if (position == 2) list[aggIdx].ram = stoi(str);
			else if (position == 3) list[aggIdx].ssd = stoi(str);
			else if (position == 4) list[aggIdx].price = stoi(str);
			else if (position == 5) list[aggIdx].weight = stoi(str);
			else if (position == 6) list[aggIdx].monitor = stod(str);
			else if (position == 7) {
				if (str == "����") list[aggIdx].gpu = 0;
				else if (str == "����") list[aggIdx].gpu = 1;
			}
			position++;
		}
	}
	else {
		cout << "Error : File could not be opend.\n";
	}
}

int whatIndex(Laptop list[], int price)
{
	int min = getMinKey(list);
	int len = getHashLength(list);
	int idx = 0;
	HashTable ht(min, len);
	ht.makeHash(list);

	return ht.find(price);
}

void makeList(Laptop list[], Laptop coutlist[], int type, int coutidx, int idx)
{
	switch (type)
	{
	case 0:// weight <= 1.3, ��� cpu Ÿ�� ���, ����
		while (coutidx < 5)
		{
			for (int i = idx; i > 0; i--)
			{
				if ((list[i].weight <= 1300) &&
					(list[i].gpu == 0))
				{
					coutlist[coutidx++] = list[i];
				}
			}
		}
		break;
	case 1:// weight <= 2.5, (3, 5, 7, 9) ���, ����, ssd 128 <
		for (int i = 0; i < MAX - 1; i++)
		{
			if ((list[i].weight <= 2500) &&
				(list[i].gpu == 0) &&
				(list[i].cpu.at(0) == 'i') &&
				(list[i].ssd > 128))
			{
			}
		}
		break;
	case 2:// weight ���Ѿ���, (7, 9) ���, ����, ssd 256 <
		for (int i = 0; i < MAX - 1; i++)
		{
			if ((list[i].gpu == 1) &&
				(list[i].cpu == "i7-11����" || list[i].cpu == "i9-11����") &&
				(list[i].ssd > 256) && list[i].monitor > 15)
			{
			}
		}
		break;
	}
}
// For quick sort
inline void swap(Laptop a[], int i, int j)
{
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
		while (i <= r && a[i].price <= a[pivot].price) i++;
		while (j > l && a[j].price >= a[pivot].price) j--;
		if (i >= j) break;
		swap(a, i, j);
	}
	swap(a, j, pivot);
	quicksort(a, l, j - 1);
	quicksort(a, j + 1, r);
}

int main() {
	// file �ҷ��ͼ� ����Ʈ�� ����
	Laptop list[MAX];
	//int n = MAX - 1;
	int type;
	int wishPrice;
	int move = 0; int compare = 0; // -> �ڷ� �̵�, ���� �� ���� 
	//Laptop list �����
	makeLaptopArr(list, "Real_Data_For_Project_Laptop_ver_2.csv");
	// �뵵�� ��ȣ ���� �Է¹ޱ� 
	cout << "���Ͻô� ��Ʈ�� Ÿ���� �Է����ּ���.\n"
		<< "0.�繫��  1.���߿�   2.���ֿ̹�\n";
	cin >> type;
	/********************����***********************/
	quicksort(list, 0, MAX - 2);
	cout << "���Ͻô� ������ �Է����ּ���(�� ����) : ";
	cin >> wishPrice;
	// �ʹ� ���� �ݾ� (����� ��Ʈ���� ���� ���) ���� ó��
	while (wishPrice < 273260) {
		cout << "�Է��Ͻ� �ݾ��� �ʹ� ���� �ݾ׿� �´� ��Ʈ���� �����ϴ�.\n�ٽ� �Է����ּ���.\n";
		cout << "���Ͻô� ������ �Է����ּ���(�� ����) : ";
		cin >> wishPrice;
	}

	/********************Ž��***********************/
	// ����� ���ݴ� ó�� ������ �ε��� 
	int idx = whatIndex(list, wishPrice);

	Laptop coutlist[7];
	int coutidx = 0;
	/********************���͸�***********************/
	makeList(list, coutlist, type, coutidx, idx);

	// ���
	cout << "            ��Ʈ�� ��õ ����Ʈ           " << endl;
	cout << "-----------------------------------------" << endl;
	for (int i = 0; i < coutidx; i++) {
		cout << "model : " << coutlist[i].model
			<< ", price : " << coutlist[i].price
			<< ", cpu : " << coutlist[i].cpu
			<< ", ram : " << coutlist[i].ram << "gb";

		if (coutlist[i].ssd >= 1000) cout << ", ssd : " << coutlist[i].ssd << "tb";
		else cout << ", ssd : " << coutlist[i].ssd << "gb";

		if (coutlist[i].weight >= 1000) cout << ", weight : " << coutlist[i].weight << "g";
		else cout << ", weight : " << (double)(coutlist[i].weight) / 1000 << "kg ";

		cout << ", monitor : " << coutlist[i].weight << "��ġ"
			<< ", gpu : ";
		if (coutlist[i].gpu == 0) cout << "����";
		else cout << "����";
	}

	return 0;
}
