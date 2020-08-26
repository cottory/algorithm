#define ll long long
#include <iostream>
#include <cstring>
using namespace std;

const ll MOD = 1000000000;
const int NMAX = 100 + 5;

ll N;
ll dp[NMAX][10][1<<11];

ll func(ll pos, ll num, ll state)
{
    if (num < 0 || num > 9)
        return 0;

    if (pos == 1)
    {
        if ((state | (1 << num)) == ((1 << 10) -1))
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    if (dp[pos][num][state] != -1)
        return dp[pos][num][state];

    ll nxtState = state | (1<<num);
    return dp[pos][num][state] = (func(pos-1,num-1,nxtState) + func(pos-1,num+1,nxtState)) % MOD;
}
int main(void) {

    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> N;

    memset(dp, -1, sizeof(dp));
    ll result = 0;
    ll initState = 0;
    for (int num = 1; num < 10; ++num)
    {
        result = (result + func(N, num, initState)) % MOD;
    }

    cout << result << "\n";
    return 0;
}