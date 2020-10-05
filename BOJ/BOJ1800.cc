#define Pair pair<int,int>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <tuple>
using namespace std;

const int INF = 987654321;
int N,P,K,ans,maxv;
vector<vector<Pair>> graph;

bool djikstra(int value)
{
    vector<int> dist(N,INF);
    dist[0] = 0;
    priority_queue<Pair> pq;
    pq.push({0,0});
    
    while (!pq.empty())
    {
        Pair now = pq.top(); pq.pop();
        int nowCost,nowNode;
        tie(nowCost,nowNode) = now;
        nowCost = -nowCost;

        if (dist[nowNode] < nowCost)
            continue;

        for (Pair nxt : graph[nowNode])
        {
            int nxtNode,nxtCost;
            tie(nxtNode,nxtCost) = nxt;
            
            if (dist[nxtNode] > nowCost + (nxtCost > value))
            {
                dist[nxtNode] = nowCost + (nxtCost > value);
                pq.push({-dist[nxtNode], nxtNode});
            }
        }
    }

    return dist[N-1] <= K;
}

int main(void) {

    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    cin >> N >> P >> K;
    graph.resize(N);

    for (int loop = 0; loop < P; ++loop)
    {
        int com1, com2, cost;
        cin >> com1 >> com2 >> cost;
        com1--;
        com2--;
        graph[com1].push_back({com2,cost});
        graph[com2].push_back({com1,cost});
    }

    int mid,minv = 0;
    maxv = 1000001;
    ans = INF;

    while (minv < maxv)
    {
        mid = (minv + maxv) / 2;

        if (djikstra(mid))
        {
            maxv = mid;
            ans = min(ans,mid);
        }
        else
        {
            minv = mid + 1;
        }
    }

    if (ans == INF)
        cout << -1 << endl;
    else
        cout << ans << "\n";

    return 0;
}