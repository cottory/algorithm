#include <iostream>
#include <string>
using namespace std;

const int NMAX = 30 + 5;
int N,K;

bool trip[NMAX][NMAX][NMAX][NMAX*NMAX/2];
char ans[NMAX];
bool solve(int nCnt, int a, int b, int kCnt)
{
    if (nCnt == N)
    {
        if (kCnt == K) return true;
        else return false;
    }

    if (trip[nCnt][a][b][kCnt]) return false;
    trip[nCnt][a][b][kCnt] = true;

    ans[nCnt] = 'A';
    if (solve(nCnt + 1, a + 1, b, kCnt)) return true;

    ans[nCnt] = 'B';
    if (solve(nCnt + 1, a, b + 1, kCnt + a)) return true;

    ans[nCnt] = 'C';
    if (solve(nCnt + 1, a, b, kCnt + a + b)) return true;
    
    return false;
}

int main(void) {

    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    
    cin >> N >> K;

    if (solve(0,0,0,0))
        cout << ans << "\n";
    else
        cout << - 1 << "\n";

    return 0;
}