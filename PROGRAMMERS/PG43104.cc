#include <string>
#include <vector>
using namespace std;

typedef long long ll;

vector<ll> dp;

ll solution(int N) {
    ll answer = 0;

    dp.resize(N+2,-1);
    dp[0] = 1;
    dp[1] = 1;

    for (int i = 2; i < N+2; ++i) 
        dp[i] = dp[i-1] + dp[i-2];

    if (N == 1) answer = 4;
    else if (N == 2) answer = 6;
    else answer = 2 * (dp[N] + dp[N-1]);

    return answer;
}