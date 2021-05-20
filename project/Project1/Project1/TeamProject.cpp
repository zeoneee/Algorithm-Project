#include <iostream>
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

int whatIndex(Laptop list[], int price)
{
    int index = 0;
    // 탐색 알고리즘으로 입력된 금액보다 높은 가격이 나오는 첫 index
    return index;
}

void makeList(Laptop list[],  int type, int n)
{
    Laptop mlist[1000];
    int mindex = 0;

    switch (type)
    {
    case 0:// weight <= 1.3, 모든 cpu 타입 허용, 내장
        for (int i = 0; i < n; i++)
        {
            if ((list[i].weight <= 1.3) &&
                (list[i].gpu == "내장"))
            {
                mlist[mindex++] = list[i];
            }
        }
        break;
    case 1:// weight <= 2.5, (3, 5, 7, 9) 허용, 내장, ssd 128 <
        for (int i = 0; i < n; i++)
        {
            if ((list[i].weight <= 2.5) &&
                (list[i].gpu == "내장") &&
                (list[i].cpu.at(0) == 'i') &&
                (list[i].ssd > 128))
            {
                mlist[mindex++] = list[i];
            }
        }
        break;
    case 2:// weight 제한없음, (7, 9) 허용, 외장, ssd 256 <
        for (int i = 0; i < n; i++)
        {
            if ((list[i].gpu == "외장") &&
                (list[i].cpu == "i7-11세대" || list[i].cpu == "i9-11세대") &&
                (list[i].ssd > 256))
            {
                mlist[mindex++] = list[i];
            }
        }
        break;
    }

    // 가격 순 재정렬 알고리즘
}

int main(void)
{
    // file 불러와서 리스트에 저장
    Laptop list[1000];
    int n = 1000;

    int s = 0;
    cout << "원하시는 노트북 타입을 입력해주세요.\n"
        << "0.사무용  1.개발용   2.게이밍용";
    cin >> s;
    makeList(list, s, n);

    int getPrice = 0;
    cout << "생각하시는 금액을 적어주세요.";
    cin >> getPrice;

    int index = 0;
    index = whatIndex(list, getPrice);
    // 너무 낮은 금액 (출력할 노트북이 없을 경우) 예외 처리

    Laptop coutList[7];

    for (int i = 0; i < 7; i++)
    { // index가 최소치이거나 최대치에 근접한 경우 예외 처리 필요
        coutList[i] = list[index-5];
        index++;
    }

    int cn = 7; // 총 결과 갯수 (index에 따라 변동)
    // ※가격에 따라 결과 출력 갯수가 변동되는 방법?

    for (int i = 0; i < cn; i++)
    {
        cout << coutList[i].name << " : \\"
            << coutList[i].price << ", "
            << coutList[i].cpu << ", "
            << coutList[i].gpu << ", "
            << coutList[i].ssd << "GB, "
            << coutList[i].weight << "kg" << endl;
    }

    return 0;
}
