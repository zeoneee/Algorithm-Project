#include <iostream>
using namespace std;

/*
	DB ���� ������ ���� -> �뵵�� ���͸� -> ���� ����Ʈ���� input���ݰ��� ���� ����
	-> ���밪 ������ ����(�˰��� �޸�) (�Է¹��� ���ݴ뿡�� ����ϱ� ����)
	-> 0�� �������� �������� ���밪�� ���� �� �� �Ѱ� 5��, ��Ѱ� 2�� ���
*/

class Notebook {
public:
	string name;
	int price;
	int cpu;
	int ram;
	int ssd;
	double weight;
	bool gpu; // ���� : 0, ���� : 1
	// ȭ��ũ�� 
};

int main() {

	// �𵨸�, ����, cpu, ram, ssd, ����, ȭ��ũ��, gpu(����/����)
	// csv ���� ���� 

	Notebook cams[1200];
	Notebook selectCams[10]; // �뵵�� ���͸� �� ��Ʈ��  
	int wishPrice; 

	// cams�� ������ ���� 


	// ���� �Է¹ޱ� 
	cout << "���ϴ� ������ �Է����ּ���(�� ����) : ";
	cin >> wishPrice;

	// ���ݼ����� ���� : ������ �̿� (������ ���� �����Ƿ�) 
	
	// �뵵�� ���͸� : 
	
	 
	// ���͸� �� ��Ʈ�ϵ��� ���ݰ� ���ϴ� ���ݴ� ��
	for (int i = 0; i < 10; i++) { // 10 : ���͸� �� ��Ʈ�� �� 
		selectCams[i].price = wishPrice - selectCams[i].price;
	}
	
	// ���͸� �� ��Ʈ�ϵ��� ���� ������ ���� : ���̵� ���� ���� ���� 


	// ��� 
	cout << "��Ʈ�� ��õ ����Ʈ" << endl;
	cout << "------------------" << endl;
	for (int i = 0; i < 10; i++) {
		cout << "�𵨸� : " << selectCams[i].name << ", ���� : " << selectCams[i].price;
	}
	

}