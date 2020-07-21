#include <vector>
using namespace std;
const int mod = 1000000007;

int solution(int n) {
    int answer = 0;
    vector<int> dp(n+1,0);
    dp[1] = 1;
    dp[2] = 2;

    if (n > 2) {
        for (int i = 3; i <= n; ++i) {
            dp[i] = (dp[i-1] % mod)  + (dp[i-2] % mod);
            dp[i] %= mod;
        }
    }
    
    return answer = dp[n];
}