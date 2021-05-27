#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

/*
	time, 비교횟수 저장하기
*/

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

void swap(Laptop a[], int i, int j) {
	Laptop temp;
	temp = a[j]; a[j] = a[i]; a[i] = temp;
}

void MakeHeap(Laptop a[], int Root, int LastNode) {
	int Parent, LeftSon, RightSon, Son; Laptop RootValue;
	Parent = Root;
	RootValue = a[Root];
	LeftSon = 2 * Parent + 1;
	RightSon = LeftSon + 1;
	while (LeftSon < LastNode) {
		if (RightSon <= LastNode && a[LeftSon].price < a[RightSon].price) {
			Son = RightSon;
		}
		else
		{
			Son = LeftSon;
		}
		if (RootValue.price < a[Son].price) {
			a[Parent] = a[Son];
			Parent = Son;
			LeftSon = Parent * 2 + 1;
			RightSon = LeftSon + 1;
		}
		else break;
	}
	a[Parent] = RootValue;
}

void heapsort(Laptop a[], int N) {
	int i;
	for (i = N / 2; i >= 1; i--) { MakeHeap(a, i - 1, N - 1); }
	for (i = N - 1; i >= 1; i--) { swap(a, 0, i); MakeHeap(a, 0, i - 1); }
}

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
	int start = 0;
	int end = mList.size() - 1;

	while (start <= end)
	{
		int mid = (start + end) / 2;

		if (start + 1 == end) // 좀 더 명확한 조건문 필요
			return end;
		else if (price == mList[mid].price)
			return mid;
		else if (price < mList[mid].price)
			end = mid - 1;
		else if (price > mList[mid].price)
			start = mid - 1;
	}
}

void makeList(Laptop list[], vector<Laptop> mList, int type, int n)
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


int main() {
	// file 불러와서 리스트에 저장
	Laptop list[969];
	vector<Laptop> mList;
	int n = 969;
	int type;
	int wishPrice;

	int move = 0; int compare = 0; // -> 자료 이동, 가격 비교 변수 

	//Laptop list 만들기
	makeLaptopArr(list, "Real_Data_For_Project_Laptop_ver_2.csv");

	// 용도와 선호 가격 입력받기 
	cout << "원하시는 노트북 타입을 입력해주세요.\n"
		<< "0.사무용  1.개발용   2.게이밍용\n";
	cin >> type;

	heapsort(list, n);

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

	// 비슷한 가격대 처음 나오는 인덱스 
	int idx = whatIndex(mList, wishPrice);

	Laptop coutlist[7];
	int coutidx = 0;
	int midx = mList.size();

	switch (idx)
	{
	case 0:
		for (int i = 0; i < 3; i++)
		{
			coutlist[coutidx++] = mList[i];
		}break;
	case 1:
		for (int i = 0; i < 4; i++)
		{
			coutlist[coutidx++] = mList[i];
		}break;
	case 2:
		for (int i = 0; i < 5; i++)
		{
			coutlist[coutidx++] = mList[i];
		}break;
	case 3:
		for (int i = 0; i < 6; i++)
		{
			coutlist[coutidx++] = mList[i];
		}break;
	case 4:
		for (int i = 0; i < 7; i++)
		{
			coutlist[coutidx++] = mList[i];
		}break;
	default:
		if (midx - idx <= 1)
		{
			for (int i = midx - 5; i < midx; i++)
			{
				coutlist[coutidx++] = mList[i];
			}
		}
		else
		{
			for (int i = idx - 5; i < idx + 2; i++)
			{
				coutlist[coutidx++] = mList[i];
			}
		}
		break;
	}

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
	}

	return 0;
}
