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
	case 0:// weight <= 1.3, ��� cpu Ÿ�� ���, ����
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
	case 1:// weight <= 2.5, (3, 5, 7, 9) ���, ����, ssd 128 <
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
	case 2:// weight ���Ѿ���, (7, 9) ���, ����, ssd 256 <
		for (int i = idx - 1; i >= 0; i--)
		{
			if (coutidx == 5)
				break;
			if ((list[i].gpu == 1) &&
				(list[i].cpu == "i7-11����" || list[i].cpu == "i9-11����") &&
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
				(list[i].cpu == "i7-11����" || list[i].cpu == "i9-11����") &&
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
		if (coutlist[i].gpu == 0) cout << "����\n";
		else cout << "����\n";
	}
	cout << endl;
}

int main() {
	// file �ҷ��ͼ� ����Ʈ�� ����
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
	
	double heapsort;
	double quicksort;
	double mergesort;

	int coutidx1 = 0, coutidx2 = 0, coutidx3 = 0;
	int idx1, idx2, idx3;

	int type = -1;
	int wishPrice = 0;
	int move = 0; int compare = 0; // -> �ڷ� �̵�, ���� �� ���� 

	//Laptop list �����

	makeLaptopArr(list1, "Real_Data_For_Project_Laptop_ver_2.csv");
	makeLaptopArr(list2, "Real_Data_For_Project_Laptop_ver_2.csv");
	makeLaptopArr(list3, "Real_Data_For_Project_Laptop_ver_2.csv");
	


	// �뵵�� ��ȣ ���� �Է¹ޱ� 
	cout << "���Ͻô� ��Ʈ�� Ÿ���� �Է����ּ���.\n"
		<< "0.�繫��  1.���߿�   2.���ֿ̹�\n";
	cin >> type;

	/********************����***********************/
	
	start = clock();
	heapsort(list1, MAX - 1);
	end = clock();
	heapsort = (double)(end - start);

	start = clock();
	quicksort(list2, 0, MAX - 2);
	end = clock();
	quicksort = (double)(end - start);

	start = clock();
    mergesort(list3, 0, MAX - 2, compare, move);
	end = clock();
	mergesort = (double)(end - start);

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

	
	/********************���͸�***********************/
	coutidx1 = makeList(list1, coutlist1, type, coutidx1, idx1);
	coutidx2 = makeList(list2, coutlist2, type, coutidx2, idx2);
	coutidx3 = makeList(list3, coutlist3, type, coutidx3, idx3);

	// ���
	print(coutlist1, coutidx1);
	print(coutlist2, coutidx2);
	print(coutlist3, coutidx3);

	cout << "���� �� ���� �ð�" << endl;
	cout << heapsort << "(heap), " << quicksort << "(quick), " << mergesort << "(merge)" << endl;
	cout << " ���� Ž�� �ð�" << endl;
	cout << bssearch << "(binary search), " << hashsearch << "(hash), " << rbsearch << "(red-black)" << endl;
	return 0;
}