#define WEIGHT first
#define NODE second
#define INF 587654321
#define pii pair<int,int>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int N, E, N1,N2;
vector<vector<pii>> graph;

int dijkstra(int src, int dst) {
    int ret = 0;
    vector<int> dist(N,INF);
    priority_queue<pii> pq;    
    dist[src] = 0;
    pq.push({0,src});

    while (!pq.empty()) {
        pii now = pq.top(); pq.pop();
        now.WEIGHT = -now.WEIGHT;

        if (now.WEIGHT > dist[now.NODE])
            continue;

        for (int i = 0; i < graph[now.NODE].size(); ++i) {
            int nxt = graph[now.NODE][i].first;
            int w = graph[now.NODE][i].second;

            if (now.WEIGHT + w < dist[nxt]) {
                dist[nxt] = now.WEIGHT + w;
                pq.push({-dist[nxt],nxt});
            }
        }      
    }

    return dist[dst];
}   
int main(void) {

    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> E;
    graph.resize(N);
    
    for (int i = 0; i < E; ++i) {
        int a,b,c;
        cin >> a >> b >> c;
        a--; b--;
        
        graph[a].push_back(make_pair(b,c));
        graph[b].push_back(make_pair(a,c));
    }

    cin >> N1 >> N2;
    N1--; N2--;

    int answer = min(dijkstra(0,N1) + dijkstra(N1,N2) + dijkstra(N2,N-1), dijkstra(0,N2) + dijkstra(N2,N1) + dijkstra(N1,N-1));

    if (answer >= INF) cout << -1 << "\n";
    else cout << answer << "\n";

    return 0;
}