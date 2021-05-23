#include <iostream>
#include <vector>
#include <fstream>
#include <string>
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

int whatIndex(vector<Laptop> mList, int price)
{
	// ��������, 2-3-4����, ��������
	// ���� : ����, 2-3-4���� : ��ȣ, �������� : ���� 

	int index = 0;
	// Ž�� �˰������� �Էµ� �ݾ׺��� ���� ������ ������ ù index
	return index;
}

void makeList(Laptop list[], vector<Laptop> mList, int type, int n)
{


	switch (type)
	{
	case 0:// weight <= 1.3, ��� cpu Ÿ�� ���, ����
		for (int i = 0; i < n; i++)
		{
			if ((list[i].weight <= 1300) &&
				(list[i].gpu == 0))
			{
				mList.push_back(list[i]);
			}
		}
		break;
	case 1:// weight <= 2.5, (3, 5, 7, 9) ���, ����, ssd 128 <
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
	case 2:// weight ���Ѿ���, (7, 9) ���, ����, ssd 256 <
		for (int i = 0; i < n; i++)
		{
			if ((list[i].gpu == 1) &&
				(list[i].cpu == "i7-11����" || list[i].cpu == "i9-11����") &&
				(list[i].ssd > 256) && list[i].monitor > 15)
			{
				mList.push_back(list[i]);
			}
		}
		break;
	}
}


int main() {

	// file �ҷ��ͼ� ����Ʈ�� ����
	Laptop list[969];
	vector<Laptop> mList;
	int n = 969;
	int type;
	int wishPrice;

	int move = 0; int compare = 0; // -> �ڷ� �̵�, ���� �� ���� 

	//Laptop list �����
	makeLaptopArr(list, "Real_Data_For_Project_Laptop_ver_2.csv");

	// �뵵�� ��ȣ ���� �Է¹ޱ� 
	cout << "���Ͻô� ��Ʈ�� Ÿ���� �Է����ּ���.\n"
		<< "0.�繫��  1.���߿�   2.���ֿ̹�";
	cin >> type;

	// �뵵�� ���͸� 
	makeList(list, mList, type, n);

	cout << "���Ͻô� ������ �Է����ּ���(�� ����) : ";
	cin >> wishPrice;

	// �ʹ� ���� �ݾ� (����� ��Ʈ���� ���� ���) ���� ó��
	while (wishPrice < 273260) {
		cout << "�Է��Ͻ� �ݾ��� �ʹ� ���� �ݾ׿� �´� ��Ʈ���� �����ϴ�.\n�ٽ� �Է����ּ���.\n";
		cout << "���Ͻô� ������ �Է����ּ���(�� ����) : ";
		cin >> wishPrice;
	}



	// ���� �� ������ �˰���
	// -> ���� heap, quick, merge

	// heap : ����, quick : ��ȣ, merge : ���� -> ���� Ȯ�� 



	// ����� ���ݴ� ó�� ������ �ε��� 
	int idx = whatIndex(mList, wishPrice);

	Laptop coutList[7];

	for (int i = 0; i < 7; i++)
	{ // index�� �ּ�ġ�̰ų� �ִ�ġ�� ������ ��� ���� ó�� �ʿ�
		coutList[i] = mList[idx - 5];
		idx++;
	}


	// Ž���Լ�, �����Լ� �ð�, �ڷ��̵� Ƚ��, �� Ƚ�� �� ��� 
	// -> ������ ���ϱ� 


	// ���
	cout << "            ��Ʈ�� ��õ ����Ʈ           " << endl;
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

		cout << ", Monitor : " << coutList[i].weight << "��ġ"
			<< ", GPU : ";
		if (coutList[i].gpu == 0) cout << "����";
		else cout << "����";
	}

	return 0;
}