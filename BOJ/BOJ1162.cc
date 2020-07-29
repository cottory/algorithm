#define tlii tuple<ll,int,int>
#define pii pair<int,int>
#define ll long long
#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <queue>
using namespace std;

const ll IMP = __LONG_LONG_MAX__;
int N,M,K;
vector<vector<pii>> graph;

vector<vector<ll>> dijkstra(int src, int dst) {
    
    vector<vector<ll>> dist(N, vector<ll>(K+1,IMP));
    priority_queue<tlii> pq;
    dist[src][0] = 0;
    pq.push({0,src,0});
    
    while (!pq.empty())
    {
        tlii now = pq.top(); pq.pop();
        ll nowCost;
        int nowNode, cnt;
        tie(nowCost,nowNode,cnt) = now;
        
        nowCost = -nowCost;
        
        if (dist[nowNode][cnt] < nowCost)
            continue;

        for (int i = 0; i < graph[nowNode].size(); ++i)
        {
            int nxtNode = graph[nowNode][i].first;
            ll nxtCost = nowCost + graph[nowNode][i].second;

            if (nxtCost < dist[nxtNode][cnt])
            {
                dist[nxtNode][cnt] = nxtCost;
                pq.push(make_tuple(-nxtCost,nxtNode,cnt));
            }

            if (cnt < K && nowCost < dist[nxtNode][cnt+1])
            {
                dist[nxtNode][cnt+1] = nowCost;
                pq.push(make_tuple(-nowCost,nxtNode,cnt+1));
            }
        }
    }

    return dist;
}

int main(void) {

    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> M >> K;
    graph.resize(N);

    for (int src,dst,w,i = 0; i < M; ++i)
    {
        cin >> src >> dst >> w;
        src--; dst--;
        graph[src].push_back({dst,w});
        graph[dst].push_back({src,w});
    }

    vector<vector<ll>> result = dijkstra(0,N-1);
    ll ans = __LONG_LONG_MAX__;

    for (int i = 0; i <= K; ++i) {
        ans = min(ans,result[N-1][i]);
    }

    cout << ans << "\n";
    return 0;
}