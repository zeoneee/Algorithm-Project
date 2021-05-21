#include <iostream>
using namespace std;

/*
	DB 가격 순으로 정렬 -> 용도로 필터링 -> 남은 리스트에서 input가격과의 차이 세팅
	-> 절대값 순으로 정렬(알고리즘 달리) (입력받은 가격대에서 출력하기 위함)
	-> 0을 기준으로 가격차의 절대값이 작은 것 중 싼거 5개, 비싼거 2개 출력
*/

class Laptop {
public:
	string model;
	int price;
	string cpu;
	int ram;
	int ssd;
	double weight;
	bool gpu; // 내장 : 0, 외장 : 1
	double monitor;
};


void SelectType(Laptop cams[], Laptop selectCams[], int type, int n) { // n = 노트북 수 
	int idx = 0;
	switch (type) {
	case 1:	// 문서작업용 
		for (int i = 0; i < n; i++) {
			if (cams[i].gpu == 0 && cams[i].ram <= 8 && cams[i].ssd <= 256 && cams[i].weight < 1200)
				selectCams[idx++] = cams[i];
		}
	case 2: // 개발용
		for (int i = 0; i < n; i++) {
			if (cams[i].gpu == 0 && cams[i].ram <= 16 && cams[i].ssd < 1000 && 1200 < cams[i].weight < 2200)
				selectCams[idx++] = cams[i];
		}
	case 3: // 게이밍 용 
		for (int i = 0; i < n; i++) {
			if (cams[i].gpu == 1 && 16 <= cams[i].ram && 512 <= cams[i].ssd)
				selectCams[idx++] = cams[i];
		}
	}
}

int main() {

	Laptop cams[1000];
	Laptop selectCams[100]; // 용도로 필터링 된 노트북  
	int wishPrice; 
	int type;

	// cams에 데이터 저장 


	// 용도와 선호 가격 입력받기 
	cout << "원하시는 노트북의 용도를 입력해주세요" << endl << "1. 문서작업용 2. 개발용 3. 게이밍용" << endl;
	cin >> type;
	cout << "원하는 가격을 입력해주세요(원 단위) : ";
	cin >> wishPrice;

	// wishPrice 예외처리 


	
	// 용도로 필터링 
	SelectType(cams, selectCams, type, 1000);
	
	 
	// 필터링 된 노트북들의 가격과 원하는 가격대 비교
	for (int i = 0; i < 100; i++) { // 10 : 필터링 된 노트북 수 
		selectCams[i].price = wishPrice - selectCams[i].price;
	}
	
	// 필터링 된 노트북들을 가격 순으로 정렬



	// 출력 
	cout << "            노트북 추천 리스트           " << endl;
	cout << "-----------------------------------------" << endl;
	for (int i = 0; i < 10; i++) {
		cout << "Model : " << selectCams[i].model
			<< ", Price : " << selectCams[i].price
			<< ", CPU : " << selectCams[i].cpu
			<< ", RAM : " << selectCams[i].ram << "GB"
			<< ", SSD : " << selectCams[i].price << "원"
			<< ", Weight : " << selectCams[i].price << "g"
			<< ", Monitor : " << selectCams[i].weight << "인치"
			<< ", GPU : ";
		if (selectCams[i].gpu == 0) cout << "내장";
		else cout << "외장";
	}
}

/*
	gpu , ram , ssd, cpu / weight, monitor
	ram : 4, 8, 16, 32
	ssd : 128, 256, 512, 1000, 2000, 4000,
	cpu : 잘몰라서 pass
	weight : < 1.2 / 1.2 < 2.2 / 2.2~
	monitor : 14, 15.. 보류

	사무용 : gpu = 0. ram <=8 , ssd <= 256, weight < 1.2
	개발용 : gpu = 0, ram <=16, ssd <1000, 1.2< weight < 2.2
	게이밍 용 : gpu = 1, 16<= ram <= 32 , ssd >= 512 weight는 상관 x
*/
