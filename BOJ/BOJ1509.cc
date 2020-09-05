#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
using namespace std;

int dp[2505][2505];
int dp2[2505];
string S,str;
int isPalin(int st, int en)
{
    if (st >= en) return 1;
    int& ret = dp[st][en];
    if (ret != -1) return ret;
    
    if (S[st] != S[en]) return ret = 0;
    else return ret = isPalin(st+1,en-1);
}
int main(void) {

    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    
    cin >> str;
    S = '#';
    S += str;

    memset(dp, -1, sizeof(dp));

    for (int i = 1; i <= str.size(); ++i)
    {
        dp2[i] = dp2[i-1] + 1;
        for (int j = 1; j <= i; ++j)
        {
            if (isPalin(j,i))
                dp2[i] = min(dp2[i], dp2[j-1] + 1);
        }
    }
    
    cout << dp2[str.size()] << endl;
    return 0;
}