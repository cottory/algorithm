#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> v,dp;
int main(void) {

    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N;
    cin >> N;

    dp.resize(N+5,0);

    for (int x,i = 0; i < N; ++i)
    {
        cin >> x;
        v.push_back(x);
    }

    dp[N-1] = 1;

    for (int now = N-2; now >= 0; --now)
    {
        int result = 1;
        for (int nxt = now + 1; nxt < N; ++nxt)
        {
            if (v[now] > v[nxt])
            {
                result = max(result,dp[nxt] + 1);
            }
        }

        dp[now] = result;
    }

    int answer = -1;
    for (int i = 0; i < N; ++i)
        answer = max(answer,dp[i]);

    cout << N - answer << "\n";
    return 0;
}