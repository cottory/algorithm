#include <iostream>
#include <cstring>
using namespace std;

int dp[31][31];

int func(int n, int r)
{
    //기저 사례
    if (n == r || r == 0 || n == 0)
        return 1;

    if (dp[n][r] != -1)
        return dp[n][r];

    return dp[n][r] = func(n-1,r) + func(n-1,r-1);
}
int main(void) {

    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t;
    cin >> t;

    while (t--)
    {
        memset(dp,-1,sizeof(dp));
        int n,m;
        cin >> n >> m;
        cout << func(m,n) << "\n";
    }
    
    return 0; 
}