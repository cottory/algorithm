#include <iostream>
#include <cstring>
#include <string>
using namespace std;

string s;

const int sSize = 51;
const int stateSize = 4;
bool visited[sSize][sSize][sSize][sSize][stateSize][stateSize];
char answer[55];
int aNum, bNum, cNum;
bool solve(int begin, int aCnt, int bCnt, int cCnt, char before, char beforeBefore)
{
    if (aCnt == 0 && bCnt == 0 && cCnt == 0)
    {
        return true;
    }

    if (visited[begin][aCnt][bCnt][cCnt][(before - 32) % 4][(beforeBefore - 32) % 4]) return false;

    visited[begin][aCnt][bCnt][cCnt][(before - 32) % 4][(beforeBefore - 32) % 4] = true;

    if (aCnt > 0)
    {
        answer[begin] = 'A';
        if (solve(begin + 1, aCnt - 1, bCnt, cCnt, 'A', before)) return true;
    }

    if (bCnt > 0 && before != 'B')
    {
        answer[begin] = 'B';
        if (solve(begin + 1, aCnt, bCnt - 1, cCnt, 'B', before)) return true;
    }

    if (cCnt > 0 && before != 'C' && beforeBefore != 'C')
    {
        answer[begin] = 'C';
        if (solve(begin + 1, aCnt, bCnt, cCnt - 1, 'C' , before)) return true;
    }
    
    return false;
}
int main(void) {

    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> s;

    for (int i = 0; i < s.length(); ++i)
    {
        if (s[i] == 'A')
        {
            aNum += 1;
        }
        else if (s[i] == 'B')
        {
            bNum += 1;
        }
        else
        {
            cNum += 1;
        }
    }

    if (solve(0, aNum, bNum, cNum, ' ', ' '))
    {
        for (int i = 0; i < s.length(); ++i)
            cout << answer[i];
        cout << "\n";
    }
    else 
    {
        cout << -1 << "\n";
    }

    return 0;
}