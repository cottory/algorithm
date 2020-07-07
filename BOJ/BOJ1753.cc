#define W first
#define NODE second
#define pii pair<int,int>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int V,E;
const int INF = 987654321;
vector<vector<pii>> graph;
priority_queue<pii> pq;

vector<int> dijskstra(int start) {
    vector<int> dist(V,INF);
    dist[start] = 0;
    pq.push({0,start});
    
    while (!pq.empty()) {
        pii now = pq.top(); pq.pop();
        now.W = -now.W;
        
        if (now.W > dist[now.second])
            continue;

        for (int i = 0; i < graph[now.NODE].size(); ++i) {
            int nxtNode = graph[now.NODE][i].first;
            int nxtWeight = now.W + graph[now.NODE][i].second;

            if (nxtWeight < dist[nxtNode]) {
                dist[nxtNode] = nxtWeight;
                pq.push({-nxtWeight,nxtNode});
            }
        }
    }

    return dist;
}
int main(void) {

    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int start;
    cin >> V >> E;
    cin >> start;
    start--;
    graph.resize(V);

    for (int i = 0; i < E; ++i) {
        int src,dst,w;
        cin >> src >> dst >> w;
        src--; dst--;
        graph[src].push_back({dst,w});
    }

    vector<int> ret = dijskstra(start);

    for (int weight : ret) {
        if (weight == INF) cout << "INF\n";
        else cout << weight << "\n";
    }

    return 0;
}