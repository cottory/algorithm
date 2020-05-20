#include <iostream>
#include <cstring>
using namespace std;

int T, N;
int dp[11];

int func(int n) {
    if (dp[n] != -1)
        return dp[n];

    int ret = func(n-1) + func(n-2) + func(n-3);
    return dp[n] = ret;
}
int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin >> T;
    for (int i = 0; i < T; ++i) {
        memset(dp, -1, sizeof(dp));
        dp[1] = 1;
        dp[2] = 2;
        dp[3] = 4;
        cin >> N;
        cout << func(N) << "\n";
    }
    return 0;
}