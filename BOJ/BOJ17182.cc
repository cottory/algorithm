#define Pair pair<int,int>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <tuple>
using namespace std;

const int INF = 987654321;
int N,K;
vector<vector<int>> graph;

int calculate(vector<int>& travelOrder)
{
    int ret = 0;
    for (int i = 0; i < N-1; ++i)
    {
        int src = travelOrder[i];
        int dst = travelOrder[i+1];
        ret += graph[src][dst];
    }
    
    return ret;
}

int main(void)
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> K;
    graph.resize(N,vector<int>(N,INF));

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            cin >> graph[i][j];
        }
    }

    //floyd
    for (int mid = 0; mid < N; ++mid)
    {
        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                if (graph[i][j] > graph[i][mid] + graph[mid][j])
                {
                    graph[i][j] = graph[i][mid] + graph[mid][j];
                }
            }
        }
    }

    vector<int> order(N);
    for (int i = 0; i < N; ++i)
        order[i] = i;

    int ans = INF;

    do {

        if (order[0] == K) {
            ans = min(ans,calculate(order));
        }

    } while (next_permutation(order.begin(), order.end()));

    cout << ans << endl;

    return 0;
}