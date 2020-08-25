#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
const int INF = 987654321;
const int NMAX = 17;

int N,P;
int initOnCnt, initState;
int dp[NMAX][1 << NMAX];
vector<vector<int>> graph;
int solve(int cnt, int state)
{
    //기저 사례
    if (cnt >= P)   
        return 0;

    if (dp[cnt][state] != -1)
        return dp[cnt][state];

    int ret = INF;

    for (int i = 0; i < N; ++i)
    {
        if (state & (1 << i))
        {
            for (int j = 0; j < N; ++j)
            {
                if ((state & (1 << j)) == 0)
                {
                    ret = min(ret, solve(cnt+1, (state | (1 << j))) + graph[i][j]);
                }
            }
        }
    }

    return dp[cnt][state] = ret;
}
int main(void) 
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;
    graph.resize(N+1,vector<int>(N+1,0));

    memset(dp,-1,sizeof(dp));

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            cin >> graph[i][j];
        }
    }

    string str;
    cin >> str;
    for (int i = 0; i < str.size(); ++i)
    {
        if (str[i] == 'Y')
        {
            initState = initState | (1 << i);
            initOnCnt += 1;
        }
    }

    cin >> P;

    int ans = solve(initOnCnt, initState);
    if (ans == INF) cout << -1 << "\n";
    else cout << ans << "\n";

    return 0;
}