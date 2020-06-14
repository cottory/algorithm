#include <string>
#include <vector>
#include <cstring>
using namespace std;
typedef long long ll;

vector<ll> dp;
const ll DIV = 1234567;

ll func(ll n) {
    if (dp[n] != -1) return dp[n];
    return dp[n] = ((func(n-1) % DIV) + (func(n-2) % DIV)) % DIV;
}

long long solution(int n) {
    long long answer = 0;
    dp.resize(n+1,-1);
    dp[1] = 1;
    dp[2] = 2;
    answer = func(n);
    return answer;
}