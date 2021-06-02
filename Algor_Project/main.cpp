#include "sort.h"
#include "search.h"
#include <vector>
#include <fstream>
#include <string>
#include <time.h>

#define MAX 970
using namespace std;

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

int makeList(Laptop list[], Laptop coutlist[], int type, int coutidx, int idx)
{
	vector<Laptop> temp;

	switch (type)
	{
	case 0:// weight <= 1.3, 모든 cpu 타입 허용, 내장
		for (int i = idx - 1; i >= 0; i--)
		{
			if (coutidx == 5)
				break;
			if ((list[i].weight <= 1300) &&
				(list[i].gpu == 0))
			{
				coutlist[coutidx++] = list[i];
			}
		}
		for (int i = 0; i < coutidx; i++)
		{
			temp.push_back(coutlist[i]);
		}
		for (int i = 0; i < coutidx; i++)
		{
			coutlist[i] = temp.back();
			temp.pop_back();
		}
		for (int i = idx; i < MAX-1; i++)
		{
			if (coutidx == 7)
				break;
			if ((list[i].weight <= 1300) &&
				(list[i].gpu == 0))
			{
				coutlist[coutidx++] = list[i];
			}
		}
		break;
	case 1:// weight <= 2.5, (3, 5, 7, 9) 허용, 내장, ssd 128 <
		for (int i = idx - 1; i >= 0; i--)
		{
			if (coutidx == 5)
				break;
			if ((list[i].weight <= 2500) &&
				(list[i].gpu == 0) &&
				(list[i].cpu.at(0) == 'i') &&
				(list[i].ssd > 128))
			{
				coutlist[coutidx++] = list[i];
			}
		}
		for (int i = 0; i < coutidx; i++)
		{
			temp.push_back(coutlist[i]);
		}
		for (int i = 0; i < coutidx; i++)
		{
			coutlist[i] = temp.back();
			temp.pop_back();
		}
		for (int i = idx; i < MAX-1; i++)
		{
			if (coutidx == 7)
				break;
			if ((list[i].weight <= 2500) &&
				(list[i].gpu == 0) &&
				(list[i].cpu.at(0) == 'i') &&
				(list[i].ssd > 128))
			{
				coutlist[coutidx++] = list[i];
			}
		}
		break;
	case 2:// weight 제한없음, (7, 9) 허용, 외장, ssd 256 <
		for (int i = idx - 1; i >= 0; i--)
		{
			if (coutidx == 5)
				break;
			if ((list[i].gpu == 1) &&
				(list[i].cpu == "i7-11세대" || list[i].cpu == "i9-11세대") &&
				(list[i].ssd > 256) && list[i].monitor > 15)
			{
				coutlist[coutidx++] = list[i];
			}
		}
		for (int i = 0; i < coutidx; i++)
		{
			temp.push_back(coutlist[i]);
		}
		for (int i = 0; i < coutidx; i++)
		{
			coutlist[i] = temp.back();
			temp.pop_back();
		}
		for (int i = idx; i < MAX-1; i++)
		{
			if (coutidx == 7)
				break;
			if ((list[i].gpu == 1) &&
				(list[i].cpu == "i7-11세대" || list[i].cpu == "i9-11세대") &&
				(list[i].ssd > 256) && list[i].monitor > 15)
			{
				coutlist[coutidx++] = list[i];
			}
		}
		break;
	}

	return coutidx;
}

void print(Laptop coutlist[], int coutidx) {
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
		if (coutlist[i].gpu == 0) cout << "내장\n";
		else cout << "외장\n";
	}
	cout << endl;
}

int main() {
	// file 불러와서 리스트에 저장
	Laptop list1[MAX];
	Laptop list2[MAX];
	Laptop list3[MAX];

	Laptop coutlist1[7];
	Laptop coutlist2[7];
	Laptop coutlist3[7];

	clock_t start;
	clock_t end;

	double bssearch;
	double hashsearch;
	double rbsearch;
	
	double heapsort_t;
	double quicksort_t;
	double mergesort_t;

	int coutidx1 = 0, coutidx2 = 0, coutidx3 = 0;
	int idx1, idx2, idx3;

	int type = -1;
	int wishPrice = 0;
	int move = 0; int compare = 0; // -> 자료 이동, 가격 비교 변수 

	//Laptop list 만들기

	makeLaptopArr(list1, "Real_Data_For_Project_Laptop_ver_2.csv");
	makeLaptopArr(list2, "Real_Data_For_Project_Laptop_ver_2.csv");
	makeLaptopArr(list3, "Real_Data_For_Project_Laptop_ver_2.csv");
	


	// 용도와 선호 가격 입력받기 
	cout << "원하시는 노트북 타입을 입력해주세요.\n"
		<< "0.사무용  1.개발용   2.게이밍용\n";
	cin >> type;

	/********************정렬***********************/
	
	start = clock();
	heapsort(list1, MAX - 1);
	end = clock();
	heapsort_t = (double)(end - start);

	start = clock();
	quicksort(list2, 0, MAX - 2);
	end = clock();
	quicksort_t = (double)(end - start);

	start = clock();
    mergesort(list3, 0, MAX - 2, compare, move);
	end = clock();
	mergesort_t = (double)(end - start);

	cout << "원하시는 가격을 입력해주세요(원 단위) : ";
	cin >> wishPrice;

	// 너무 낮은 금액 (출력할 노트북이 없을 경우) 예외 처리
	while (wishPrice < 273260) {
		cout << "입력하신 금액이 너무 낮아 금액에 맞는 노트북이 없습니다.\n다시 입력해주세요.\n";
		cout << "원하시는 가격을 입력해주세요(원 단위) : ";
		cin >> wishPrice;
	}

	/********************탐색***********************/
	// 비슷한 가격대 처음 나오는 인덱스 
	start = clock();
	idx1 = whatIndex_bs(list1, wishPrice);
	end = clock();
	bssearch = (double)(end - start);

	start = clock();
	idx2 = whatIndex_hash(list2, wishPrice);
	end = clock();
	hashsearch = (double)(end - start);

	start = clock();
	idx3 = whatIndex_rb(list2, wishPrice);
	end = clock();
	rbsearch = (double)(end - start);

	
	/********************필터링***********************/
	coutidx1 = makeList(list1, coutlist1, type, coutidx1, idx1);
	coutidx2 = makeList(list2, coutlist2, type, coutidx2, idx2);
	coutidx3 = makeList(list3, coutlist3, type, coutidx3, idx3);

	// 출력
	print(coutlist1, coutidx1);
	print(coutlist2, coutidx2);
	print(coutlist3, coutidx3);

	cout << "가격 순 정렬 시간" << endl;
	cout << heapsort_t << "(heap), " << quicksort_t << "(quick), " << mergesort_t << "(merge)" << endl;
	cout << " 가격 탐색 시간" << endl;
	cout << bssearch << "(binary search), " << hashsearch << "(hash), " << rbsearch << "(red-black)" << endl;
	cout << endl;
	cout << "가격 순 정렬 비교 횟수 " << endl;
	cout << "가격 탐색 비교 횟수 " << endl;
	return 0;
}
