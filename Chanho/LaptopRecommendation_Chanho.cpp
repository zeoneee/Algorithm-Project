#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

/*
	time, 비교횟수 저장하기
*/

// Laptop
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

int whatIndex(vector<Laptop> mList, int price)
{
	// 이진나무, 2-3-4나무, 흑적나무
	// 이진 : 승혁, 2-3-4나무 : 찬호, 흑적나무 : 지현 

	int index = 0;
	// 탐색 알고리즘으로 입력된 금액보다 높은 가격이 나오는 첫 index
	Node* r234 = newnode();
	Node** root = &r234;
	for (int i = 0; i < mList.size(); i++)
		insert(root, mList[i]);

	search(*root, price);
	return index;
}

void makeList(Laptop list[], vector<Laptop> &mList, int type, int n)
{


	switch (type)
	{
	case 0:// weight <= 1.3, 모든 cpu 타입 허용, 내장
		for (int i = 0; i < n; i++)
		{
			if ((list[i].weight <= 1300) &&
				(list[i].gpu == 0))
			{
				mList.push_back(list[i]);
			}
		}
		break;
	case 1:// weight <= 2.5, (3, 5, 7, 9) 허용, 내장, ssd 128 <
		for (int i = 0; i < n; i++)
		{
			if ((list[i].weight <= 2500) &&
				(list[i].gpu == 0) &&
				(list[i].cpu.at(0) == 'i') &&
				(list[i].ssd > 128))
			{
				mList.push_back(list[i]);
			}
		}
		break;
	case 2:// weight 제한없음, (7, 9) 허용, 외장, ssd 256 <
		for (int i = 0; i < n; i++)
		{
			if ((list[i].gpu == 1) &&
				(list[i].cpu == "i7-11세대" || list[i].cpu == "i9-11세대") &&
				(list[i].ssd > 256) && list[i].monitor > 15)
			{
				mList.push_back(list[i]);
			}
		}
		break;
	}
}

// For quick sort
inline void swap(vector<Laptop> &a, int i, int j)
{
	Laptop t = a[i];
	a[i] = a[j];
	a[j] = t;
}

int partition(vector<Laptop> &a, int l, int r)
{
	int i, j=0;
	int v;
	if (r > l)
	{
		v = a[l].price;
		i = l;
		j = r + 1;
		for (;;)
		{
			while (a[++i].price < v)
				while (a[--j].price > v)
					if (i >= j)
						break;
			swap(a, i, j);
		}
		swap(a, j, l);
	}
	return j;
}

void quicksort(vector<Laptop> &a, int l, int r)
{
	int j;
	if (r > l)
	{
		j = partition(a, l, r);
		quicksort(a, l, j - 1);
		quicksort(a, j + 1, r);
	}
}

// For 2-3-4 tree
typedef struct nodes {
	Laptop keys[3];
	struct nodes* children[4];
	int n;
	bool leaf;
} Node;

void freetree(Node* x) {
	if (!x->leaf) {
		for (int i = 0; i < x->n; i++) {
			freetree(x->children[i]);
		}
	}
	free(x);
}

Node* newnode() {
	Node* x = new Node;
	x->n = 0;
	x->leaf = true;
	return x;
}

Node* insert(Node** root, Laptop newLap) {
	Node* r = *root;
	if (r->n == 3) {
		
		Node* a = newnode();
		a->children[0] = r;
		a->leaf = false;
		*root = a;
		splitChild(a, 0);
		return insertnonfull(a, newLap);
	}
	else {
		return insertnonfull(r, newLap);
	}
}

Node* insertnonfull(Node* x, Laptop newLap) {
	//find where to place value
	int i = 0;
	while (i < x->n && newLap.price > x->keys[i].price)
		i++;
	if (x->leaf) {
		int j;
		for (j = x->n; j > i; j--) {
			x->keys[j] = x->keys[j - 1];
		}
		x->keys[j] = newLap;
		x->n++;
		return x;
	}
	else {
		if (x->children[i]->n == 3) {
			// node is full split it
			splitChild(x, i);
			if (newLap.price > x->keys[i].price) {
				i++;
			}
		}
		return insertnonfull(x->children[i], newLap);
	}
}

Node* search(Node* x, int price) {
	if (x->leaf) {
		return x;
	}

	int i = 0;
	while (i < x->n && price > x->keys[i].price) {
		i++;
	}
	if (price == x->keys[i].price) {
		return x;
	}
	else {
		return search(x->children[i], price);
	}
}

void splitChild(Node* x, int i) {
	
	Node* a = x->children[i];
	Node* b = newnode();

	for (int j = x->n; j > i; j--) {
		x->children[j + 1] = x->children[j];
		x->keys[j] = x->keys[j - 1];
	}
	// bring up the new key to i
	x->keys[i] = a->keys[1];
	x->children[i + 1] = b;
	x->n++;
	if (a->leaf) {
		b->leaf = true;
		
		for (int j = 0; j < 1; j++) {
			b->keys[j] = a->keys[j + 2];
			b->n++;
		}
		a->n = 1;
	}
	else {
		b->leaf = false;
		
		for (int j = 0; j < 1; j++) {
			b->keys[j] = a->keys[j + 2];
			b->children[j] = a->children[j + 2];
			b->n++;
		}
		b->children[1] = a->children[3];
		a->n = 1;
		
	}
	
}

void printNode(Node* x) {
	if (x == NULL) {
		printf("Sorry no node there.\n");
		return;
	}
	else if (x->n < 1) {
		printf("There are no keys in this node.\n");
		return;
	}
	int i;
	for (i = 0; i < x->n - 1; i++) {
		printf("%d ", x->keys[i].price);
	}
	printf("%d\n", x->keys[i].price);
}


int main() {

	// file 불러와서 리스트에 저장
	Laptop list[20];
	vector<Laptop> mList;
	int n = 20;
	int type;
	int wishPrice;

	int move = 0; int compare = 0; // -> 자료 이동, 가격 비교 변수 
	
	//Laptop list 만들기
	makeLaptopArr(list, "Real_Data_For_Project_Laptop_ver_2.csv");

	// 용도와 선호 가격 입력받기 
	cout << "원하시는 노트북 타입을 입력해주세요.\n"
		<< "0.사무용  1.개발용   2.게이밍용 : ";
	cin >> type;

	// 용도로 필터링 
	makeList(list, mList, type, n);

	cout << "원하시는 가격을 입력해주세요(원 단위) : ";
	cin >> wishPrice;

	// 너무 낮은 금액 (출력할 노트북이 없을 경우) 예외 처리
	while (wishPrice < 273260) {
		cout << "입력하신 금액이 너무 낮아 금액에 맞는 노트북이 없습니다.\n다시 입력해주세요.\n";
		cout << "원하시는 가격을 입력해주세요(원 단위) : ";
		cin >> wishPrice;
	}

	// 가격 순 재정렬 알고리즘
	// quick sort
	quicksort(mList, 0, n - 1);

	for (int i = 0; i++; i < 10) {
		cout << mList[i].price << " ";
	}
	cout << endl;
	// 비슷한 가격대 처음 나오는 인덱스 
	int idx = whatIndex(mList, wishPrice);

	Laptop coutList[7];

	for (int i = 0; i < 7; i++)
	{ // index가 최소치이거나 최대치에 근접한 경우 예외 처리 필요
		coutList[i] = mList[idx - 5];
		idx++;
	}


	// 탐색함수, 정렬함수 시간, 자료이동 횟수, 비교 횟수 비교 출력 
	// -> 다음에 정하기 


	// 출력
	cout << "            노트북 추천 리스트           " << endl;
	cout << "-----------------------------------------" << endl;
	for (int i = 0; i < 10; i++) {
		cout << "Model : " << coutList[i].model
			<< ", Price : " << coutList[i].price
			<< ", CPU : " << coutList[i].cpu
			<< ", RAM : " << coutList[i].ram << "GB";

		if (coutList[i].ssd >= 1000) cout << ", SSD : " << coutList[i].ssd << "TB";
		else cout << ", SSD : " << coutList[i].ssd << "GB";

		if (coutList[i].weight >= 1000) cout << ", Weight : " << coutList[i].weight << "g";
		else cout << ", Weight : " << (double)(coutList[i].weight) / 1000 << "Kg ";

		cout << ", Monitor : " << coutList[i].weight << "인치"
			<< ", GPU : ";
		if (coutList[i].gpu == 0) cout << "내장";
		else cout << "외장";
	}

	return 0;
}