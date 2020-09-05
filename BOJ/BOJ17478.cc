#include <iostream>
using namespace std;


void generatHyphen(int cnt)
{
    for (int i = 0; i < (4 * cnt); ++i)
        cout << "_";
    return;
}
void solve(int cnt, int cntMax)
{
    if (cnt == cntMax)
    {
        generatHyphen(cnt);
        cout << "\"����Լ��� ������?\"" << "\n";
        generatHyphen(cnt);
        cout << "\"����Լ��� �ڱ� �ڽ��� ȣ���ϴ� �Լ����\"" << "\n";
        generatHyphen(cnt);
        cout << "��� �亯�Ͽ���." << "\n";
        return;
    }

    generatHyphen(cnt); 
    cout << "\"����Լ��� ������?\"" << "\n";
    generatHyphen(cnt);
    cout << "\"�� ����. �������� �� �� ����⿡ �̼��� ��� ������ ����� ������ �־���." << "\n";
    generatHyphen(cnt);
    cout << "���� ������� ��� �� ���ο��� ������ ������ �߰�, ��� �����Ӱ� ����� �־���." << "\n";
    generatHyphen(cnt);
    cout << "���� ���� ��κ� �ǾҴٰ� �ϳ�. �׷��� ��� ��, �� ���ο��� �� ���� ã�ƿͼ� ������.\"" << "\n";

    solve(cnt + 1, cntMax);

    generatHyphen(cnt);
    cout << "��� �亯�Ͽ���." << "\n";
}

int main(void) {

    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N;
    cin >> N;

    cout << "��� �� ��ǻ�Ͱ��а� �л��� ������ �������� ã�ư� ������." << "\n";
    solve(0, N);
    return 0;
}