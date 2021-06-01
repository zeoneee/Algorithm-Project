#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#define MAX 970
#define black 0
#define red 1

using namespace std;

int compare = 0;

class Laptop {
public:
	string model;
	int price;
	string cpu;
	int ram;
	int ssd;
	int weight;
	bool gpu; // 내장 : 0, 외장 : 1
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

Laptop* sorted = new Laptop[2000];

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
				if (str == "내장") list[aggIdx].gpu = 0;
				else if (str == "외장") list[aggIdx].gpu = 1;
			}
			position++;
		}
	}
	else {
		cout << "Error : File could not be opend.\n";
	}
}

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

// 가격 정렬
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

// RED-BLACK
class RBtree {
private:
	struct node {
		Laptop key;
		int tag;
		int Info;
		struct node* l, * r;
		node(Laptop k, int i, int t, struct node* ll, struct node* rr) {
			copy(key, k);
			Info = i; tag = t; l = ll; r = rr;
		}
	};
	struct node* head, * tail, * x, * p, * g, * gg, * z;

public:

	RBtree() {
		Laptop null;
		z = new node(null, -1, black, 0, 0);  // NULL노드
		z->l = z; z->r = z;
		head = new node(null, -1, black, z, z); // 실제 info는 0부터 시작 
	}

	void insert(Laptop k, int info, int& compare) {
		x = head; p = head; g = head;
		while (x != z) {
			gg = g; g = p; p = x;
			x = (k.price < x->key.price) ? x->l : x->r; compare++;
			if (x->l->tag && x->r->tag) split(k, compare);   // x가 4노드라면 split 
		}
		x = new node(k, info, red, z, z);
		if (k.price < p->key.price) p->l = x; else p->r = x; compare++;
		split(k, compare); head->r->tag = black; // 일단 모두 적링크로 부여하고 한번 더 split
	}

	struct node* rotate(Laptop k, struct node* y, int& compare) {
		struct node* high, * low;
		high = (k.price < y->key.price) ? y->l : y->r; compare++;
		if (k.price < high->key.price) { low = high->l; high->l = low->r; low->r = high; }
		else { low = high->r; high->r = low->l; low->l = high; }
		compare++;
		if (k.price < y->key.price) y->l = low; else y->r = low;
		compare++;
		return low;
	}

	void split(Laptop k, int& compare) {
		x->tag = red; x->l->tag = black; x->r->tag = black;
		if (p->tag) {
			g->tag = red;
			if (k.price < g->key.price != k.price < p->key.price) p = rotate(k, g, compare);
			compare++;
			x = rotate(k, gg, compare);
			x->tag = black;
		}
	}

	int search(int price, int& compare) {

		// 값 중복되는경우 
		// 찾는 가격의 금액대가 안나올경우 
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
		if (x->l == z && x->r == z) { // 자식노드 없는 경우  
			if (price == x->key.price) {
				return x->Info;
			}
			else {
				return x->Info + 1;
			}
		}
		else if (x->l != NULL) { // 왼쪽 자식만 있는 경우
			if (price == x->key.price) {
				return x->Info;
			}
			else if (price < x->key.price) x = x->l;
			else return x->Info + 1;

		}
		else {	// 오른쪽 자식만 있는 경우 
			if (price == x->key.price) {
				return x->Info;
			}
			else if (price < x->key.price) return x->Info;
			else x = x->r;
		}
	}
};


int whatIndex(Laptop list[], int price)
{
	// 흑적나무
	// 탐색 알고리즘으로 입력된 금액보다 높은 가격이 나오는 첫 index
	int info = 0;
	RBtree T;
	for (int i = 0; i < MAX - 1; i++) {
		T.insert(list[i], info++, compare);
	}
	return T.search(price, compare);
}

void makeList(Laptop list[], Laptop coutlist[], int type, int coutidx, int idx)
{
	switch (type)
	{
	case 0:// weight <= 1.3, 모든 cpu 타입 허용, 내장
		while (coutidx < 5)
		{
			for (int i = idx; i > 0; i--)
			{
				if ((list[i].weight <= 1300) &&
					(list[i].gpu == 0))
				{
					//coutlist[coutidx++] = list[i];
					copy(coutlist[coutidx++], list[i]);
				}
			}
		}
		break;
	case 1:// weight <= 2.5, (3, 5, 7, 9) 허용, 내장, ssd 128 <
		while (coutidx < 5) {
			for (int i = 0; i < MAX; i++)
			{
				if ((list[i].weight <= 2500) &&
					(list[i].gpu == 0) &&
					(list[i].cpu.at(0) == 'i') &&
					(list[i].ssd > 128))
				{
					copy(coutlist[coutidx++], list[i]);
				}
			}
		}
		break;
	case 2:// weight 제한없음, (7, 9) 허용, 외장, ssd 256 <
		while (coutidx < 5) {
			for (int i = 0; i < MAX; i++)
			{
				if ((list[i].gpu == 1) &&
					(list[i].cpu == "i7-11세대" || list[i].cpu == "i9-11세대") &&
					(list[i].ssd > 256) && list[i].monitor > 15)
				{
					copy(coutlist[coutidx++], list[i]);
				}
			}
		}
		break;
	}
}

int main() {

	// file 불러와서 리스트에 저장
	Laptop list[MAX];
	int type;
	int wishPrice;

	int move = 0; int compare = 0; // -> 자료 이동, 가격 비교 변수 

	//Laptop list 만들기
	makeLaptopArr(list, "Real_Data_For_Project_Laptop_ver_2.csv");

	// 용도와 선호 가격 입력받기 
	cout << "원하시는 노트북 타입을 입력해주세요.\n"
		<< "0.사무용  1.개발용   2.게이밍용\n";
	cin >> type;

	if (type != 0 && type != 1 && type != 2) {
		cout << "잘못된 타입을 입력하셨습니다." << endl;
		return 0;
	}

	/********************정렬***********************/
	mergesort(list, 0, MAX - 2, compare, move);

	cout << "원하시는 가격을 입력해주세요(원 단위) : ";
	cin >> wishPrice;

	//너무 낮은 금액 (출력할 노트북이 없을 경우) 예외 처리
	while (wishPrice < 273260) {
		cout << "입력하신 금액이 너무 낮아 금액에 맞는 노트북이 없습니다.\n다시 입력해주세요.\n";
		cout << "원하시는 가격을 입력해주세요(원 단위) : ";
		cin >> wishPrice;
	}

	/********************탐색***********************/
	// 비슷한 가격대 처음 나오는 인덱스 
	int idx = whatIndex(list, wishPrice);
	cout << "idx: " << idx << endl;

	Laptop coutlist[5];
	int coutidx = 0;
	idx = 400;

	/********************필터링***********************/
	makeList(list, coutlist, type, coutidx, idx);

	/*/
	// 출력
	cout << "            노트북 추천 리스트           " << endl;
	cout << "-----------------------------------------" << endl;
	for (int i = 0; i < 10; i++) {
		cout << "model : " << list[i].model
			<< ", price : " << list[i].price
			<< ", cpu : " << list[i].cpu
			<< ", ram : " << list[i].ram << "gb";

		if (list[i].ssd >= 1000) cout << ", ssd : " << list[i].ssd << "tb";
		else cout << ", ssd : " << list[i].ssd << "gb";

		if (list[i].weight >= 1000) cout << ", weight : " << list[i].weight << "g";
		else cout << ", weight : " << (double)(list[i].weight) / 1000 << "kg ";

		cout << ", monitor : " << list[i].weight << "인치"
			<< ", gpu : ";
		if (list[i].gpu == 0) cout << "내장";
		else cout << "외장";

		cout << endl;
	}*/

	
	/*
	// 출력
	cout << "            노트북 추천 리스트           " << endl;
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

		cout << ", monitor : " << coutlist[i].weight << "인치"
			<< ", gpu : ";
		if (coutlist[i].gpu == 0) cout << "내장";
		else cout << "외장";
	}*/


	return 0;
}
