#define ll long long
#define COST first
#define NODE second
#define pll pair<ll,ll>
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

ll N, M, D, E, ans;
const ll IMPOSSIBLE = __LONG_LONG_MAX__;
vector<ll> h,dist_from_house,dist_to_school;
vector<vector<pll>> graph;

vector<ll> dijkstra(int target_node) 
{
    vector<ll> dist(N,IMPOSSIBLE);
    priority_queue<pll> pq;
    pq.push(make_pair(0,target_node));
    dist[target_node] = 0;

    while (!pq.empty())
    {
        pll now = pq.top(); pq.pop();
        now.COST = -now.COST;

        if (now.COST > dist[now.NODE])
            continue;

        for (int i = 0; i < graph[now.NODE].size(); ++i)
        {

            ll nxt_node = graph[now.NODE][i].first;
            ll nxt_cost = now.COST + graph[now.NODE][i].second;

            if (h[nxt_node] <= h[now.NODE]) continue;
            
            if (dist[nxt_node] > nxt_cost) 
            {
                dist[nxt_node] = nxt_cost;
                pq.push(make_pair(-nxt_cost,nxt_node));
            }
        }
    }
        
    return dist;
}

int main(void) {

    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> M >> D >> E;
    for (int x,i = 0; i < N; ++i) {
        cin >> x;
        h.push_back(x);
    }

    graph.resize(N);

    for (int src,dst,w,i = 0; i < M; ++i)
    {
        cin >> src >> dst >> w;
        src--; dst--;
        graph[src].push_back(make_pair(dst,w));
        graph[dst].push_back(make_pair(src,w));
    }

    dist_from_house = dijkstra(0);
    dist_to_school = dijkstra(N-1);

    ans = -__LONG_LONG_MAX__;
    
    for (int i = 0; i < N; ++i)
    {
        if (i == 0 || i == N - 1) 
            continue;

        if (dist_from_house[i] == IMPOSSIBLE || dist_to_school[i] == IMPOSSIBLE)
            continue;

        ll plusValue, minusValue;
        plusValue = h[i]*E;
        minusValue = (dist_from_house[i] + dist_to_school[i]) * D;
        ans = max(ans, (plusValue - minusValue));
    }
    
    if (ans == -__LONG_LONG_MAX__) {
        cout << "Impossible\n";
    }
    else {
        cout << ans << "\n";
    }
    
    return 0;
}