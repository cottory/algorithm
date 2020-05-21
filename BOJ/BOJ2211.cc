#define WEIGHT first
#define NODE second
#define INF 987654321
#define pii pair<int,int>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int N, M;
vector<vector<pii> > graph;
priority_queue<pii> pq;

vector<pii> dij() {

    vector<pii> ret;
    vector<pii> dist(N, make_pair(INF,0));
    dist[0] = {0,0};
    pq.push({0,0}); //WEIGHT, NODE

    while (!pq.empty()) {
        
        pii now = pq.top(); pq.pop();
        now.WEIGHT = -now.WEIGHT;

        if (now.WEIGHT > dist[now.NODE].WEIGHT)
            continue;

        for (int loop = 0; loop < graph[now.NODE].size(); ++loop) {
            int nxt = graph[now.NODE][loop].first;
            int weight = graph[now.NODE][loop].second;

            if (now.WEIGHT + weight < dist[nxt].WEIGHT) {
                dist[nxt].WEIGHT = now.WEIGHT + weight;
                dist[nxt].second = now.NODE;
                pq.push({-dist[nxt].WEIGHT, nxt});
            }   
        }
    }

    for (int i = 0; i < dist.size(); ++i) {
        ret.push_back(make_pair(i,dist[i].NODE));
    }
    return ret;
}
int main(void) {

    vector<pii> ret;
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> M;
    graph.resize(N);

    for (int a,b,c,i = 0; i < M; ++i) {
        cin >> a >> b >> c;
        a--; b--;
        graph[a].push_back({b,c});
        graph[b].push_back({a,c});
    }

    ret = dij();

    cout << (int)ret.size() - 1 << "\n";
    for (pii node : ret) {
        if (node.first == 0 && node.second == 0) continue;
        else {
            cout << node.first + 1 << " " << node.second + 1 << "\n";
        }
    }
    
    return 0;
}