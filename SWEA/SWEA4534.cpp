#define MOD 1000000007 
#define BLACK 0
#define WHITE 1
#define MAXV 100005
#define ll long long
#include<iostream>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;

int N;
ll ans, dp[MAXV][2];

ll solve(vector<vector<int> > &graph, int node, int color, int parent)
{
    if (dp[node][color] != -1)
        return dp[node][color];

    ll ret = 1;
    
    for (int nxt : graph[node])
    {
        if (parent == nxt) 
            continue;

        if (color == WHITE) 
        {
            ret *= (solve(graph, nxt, BLACK, node) + solve(graph, nxt, WHITE, node));
        }
        else if (color == BLACK) 
        {
            ret *= solve(graph, nxt, WHITE, node);
        }
        ret %= MOD;
    }

    return dp[node][color] = ret;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	
	cin>>T;

	for(test_case = 1; test_case <= T; ++test_case)
	{
        memset(dp, -1, sizeof(dp));
        scanf("%d", &N);

        vector<vector<int> > graph(N);

        for (int src,dst,loop = 0; loop < N-1; ++loop)
        {
            scanf("%d%d",&src,&dst);
            src--; dst--;
            graph[src].push_back(dst);
            graph[dst].push_back(src);
        }

        ans = (solve(graph, 0, BLACK, -1) + solve(graph, 0, WHITE, -1)) % MOD;
        printf("#%d %lld\n", test_case, ans);
	}
	return 0;
}