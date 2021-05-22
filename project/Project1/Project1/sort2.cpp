#include <iostream>
#define MAX 1000
#define RESMAX 7

using namespace std;

class Laptop {
    public:
        string name;
        int price;
        string cpu;
        string gpu;
        int ssd;
        double weight;
};

// list에 존재하는 idx1과 idx2를 swap
void swapLaptop(Laptop* list, int idx1, int idx2){
    Laptop temp = list[idx1];
    list[idx1] = list[idx2];
    list[idx2] = temp;
}

// 가격순으로 정렬
void sortPrice(Laptop* list){

}

// 알맞는 노트북 리스트 반환
Laptop* showLaptopList(Laptop* list, int price, int usage){

}

int main(){

    // 노트북 리스트, 희망 가격
    Laptop list[MAX];
    Laptop* result;
    int setPrice;
    int usage;

    cout << "Set Price : ";
    cin >> setPrice;

    cout << "Set Usage 1. 사무용 2. 작업용 3. 게이밍 : ";
    cin >> usage;
    
    // 노트북 리스트를 가격 순으로 정렬

    sortPrice(list);

    // 결과 리스트 반환 후 출력

    result = showLaptopList(list, setPrice, usage);

    cout << "------ 추천 제품 ------" << endl;
    
    for (int i=0; i < RESMAX ; i++){

        cout << result[i].name << " ";
        cout << result[i].cpu << " ";
        cout << result[i].gpu << " ";

        if(result[i].ssd >= 1000)
            cout << (result[i].ssd) / 1000 << "TB ";
        else
            cout << result[i].ssd << "GB ";

        if(result[i].weight >= 1000)
            cout << (result[i].weight) / 1000 << "Kg ";
        else
            cout << result[i].weight << "g ";

        cout << result[i].price << endl;
    }

    return 0;
}