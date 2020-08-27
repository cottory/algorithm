#define ll long long
#define Pair pair<ll,ll>
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const int NODE_SIZE = 2505;
const int LITER_MAX = 2505;

int N,M;
ll answer, literCost[NODE_SIZE], dp[NODE_SIZE][LITER_MAX];
vector<vector<Pair>> graph;

ll djikstra()
{
    //누적 cost, 목적node, 현재 방문한 주유소 중 최저가격
    priority_queue<pair<ll, Pair>> pq; 

    pq.push(make_pair(0, make_pair(0, literCost[0])));

    while (!pq.empty())
    {
        ll totalCost = pq.top().first;
        ll here = pq.top().second.first;
        ll minOilPrice = pq.top().second.second;
        pq.pop();
        totalCost = -totalCost;

        if (here == N-1) 
        {
            return totalCost;
        }

        //here까지 오는데 최저 가격이 minOilPrice 였다.
        if (dp[here][minOilPrice] != -1)
            continue;

        dp[here][minOilPrice] = totalCost;

        for (auto nxt : graph[here])
        {
            //vector<Pair>
            ll nxtNode = nxt.first;
            ll dist = nxt.second;

            if (dp[nxtNode][minOilPrice] != -1)
                continue;

            pq.push({ -(totalCost + (minOilPrice * dist)), {nxtNode, min(minOilPrice, literCost[nxtNode])} });
        }
    }
}

int main(void) {

    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> M;

    for (int i = 0; i < N; ++i)
        cin >> literCost[i];

    graph.resize(N+1);

    for (int i = 0; i < M; ++i)
    {
        int src,dst,dist;
        cin >> src >> dst >> dist;
        src--; dst--;
        graph[src].push_back(make_pair(dst,dist));
        graph[dst].push_back(make_pair(src,dist));
    }

    memset(dp,-1,sizeof(dp));
    cout << djikstra() << endl;
    return 0;
}