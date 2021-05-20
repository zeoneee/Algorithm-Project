#include <iostream>
using namespace std;

/*
	DB 가격 순으로 정렬 -> 용도로 필터링 -> 남은 리스트에서 input가격과의 차이 세팅
	-> 절대값 순으로 정렬(알고리즘 달리) (입력받은 가격대에서 출력하기 위함)
	-> 0을 기준으로 가격차의 절대값이 작은 것 중 싼거 5개, 비싼거 2개 출력
*/

class Notebook {
public:
	string name;
	int price;
	int cpu;
	int ram;
	int ssd;
	double weight;
	bool gpu; // 내장 : 0, 외장 : 1
	// 화면크기 
};

int main() {

	// 모델명, 가격, cpu, ram, ssd, 무게, 화면크기, gpu(내장/외장)
	// csv 파일 형식 

	Notebook cams[1200];
	Notebook selectCams[10]; // 용도로 필터링 된 노트북  
	int wishPrice; 

	// cams에 데이터 저장 


	// 가격 입력받기 
	cout << "원하는 가격을 입력해주세요(원 단위) : ";
	cin >> wishPrice;

	// 가격순으로 정렬 : 퀵정렬 이용 (데이터 양이 많으므로) 
	
	// 용도로 필터링 : 
	
	 
	// 필터링 된 노트북들의 가격과 원하는 가격대 비교
	for (int i = 0; i < 10; i++) { // 10 : 필터링 된 노트북 수 
		selectCams[i].price = wishPrice - selectCams[i].price;
	}
	
	// 필터링 된 노트북들을 가격 순으로 정렬 : 힙이든 뭐든 내가 정렬 


	// 출력 
	cout << "노트북 추천 리스트" << endl;
	cout << "------------------" << endl;
	for (int i = 0; i < 10; i++) {
		cout << "모델명 : " << selectCams[i].name << ", 가격 : " << selectCams[i].price;
	}
	

}