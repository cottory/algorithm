#define first COST
#define second DST
#define pii pair<int,int>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int N, M, obj_src, obj_dst;
const int IMPOSSIBLE = 987654321;
vector<vector<pii>> graph;


int djisktra(int src, int dst) {
    vector<int> dist(N,IMPOSSIBLE);
    dist[src] = 0;

    priority_queue<pii> pq;
    pq.push({0,src});

    while (!pq.empty()) {
        
        pii now = pq.top(); pq.pop();
        now.COST = -now.COST;

        if (dist[now.DST] < now.COST) 
            continue;
        
        for (int i = 0; i < graph[now.DST].size(); ++i) {
            int nxt = graph[now.DST][i].first;
            
            if (now.COST + graph[now.DST][i].second < dist[nxt]) {
                dist[nxt] = now.COST + graph[now.DST][i].second;
                pq.push({-dist[nxt], nxt});
            }
        }
        
    }
        
    return dist[dst];
}
int main(void) {

    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> M;
    graph.resize(N);
    
    for (int src,dst,cost,i = 0; i < M; ++i) {
        cin >> src >> dst >> cost;
        src--; dst--;
        graph[src].push_back({dst,cost});
    }

    cin >> obj_src >> obj_dst;
    obj_src--; obj_dst--;
    
    cout << djisktra(obj_src, obj_dst);
    return 0;
}