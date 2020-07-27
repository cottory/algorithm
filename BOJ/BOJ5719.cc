#define pii pair<int,int>
#define WEIGHT first
#define NODE second
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int IMPOSSIBLE = 987654321;
int V,E;
int st,en;
vector<vector<pii>> graph;
vector<vector<int>> before;

void bfs(int node) 
{
    queue<int> q;
    q.push(node);

    while (!q.empty())
    {
        int now = q.front(); q.pop();

        for (int i = 0; i < before[now].size(); ++i)
        {
            int adj_node = before[now][i];

            for (int j = 0; j < graph[adj_node].size(); ++j)
            {
                int nxt = graph[adj_node][j].first;
                if (nxt == now)
                {
                    graph[adj_node][j].second = -1;
                    q.push(adj_node);
                }
            }
        }              
    }
    
    return;
}

int dijkstra(int src, int dst)
{
    vector<int> dist(V,IMPOSSIBLE);
    dist[src] = 0;
    priority_queue<pii> pq;
    pq.push({0,src});

    while (!pq.empty())
    {
        pii now = pq.top(); pq.pop();
        now.WEIGHT = -now.WEIGHT;

        if (dist[now.NODE] < now.WEIGHT)
            continue;
                
        for (int i = 0; i < graph[now.NODE].size(); ++i)
        {
            int nxt = graph[now.NODE][i].first;
            int nxtWeight = now.WEIGHT + graph[now.NODE][i].second;

            if (graph[now.NODE][i].second == -1)
                continue;

            if (nxtWeight < dist[nxt]) 
            {
                dist[nxt] = nxtWeight;
                pq.push({-dist[nxt], nxt});

                before[nxt].clear();
                before[nxt].push_back(now.NODE);
            }
            else if (nxtWeight == dist[nxt])
            {
                before[nxt].push_back(now.NODE);
            }            
        }
    }

    return dist[dst];
}

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    while (true)
    {
        cin >> V >> E;
        if (V == 0 && E == 0)
            break;

        graph.resize(V);
        before.resize(V);  
        
        cin >> st >> en;

        for (int src,dst,w,i = 0; i < E; ++i)
        {
            cin >> src >> dst >> w;
            graph[src].push_back({dst,w});
        }

        dijkstra(st,en);
        bfs(en);
        int ans = dijkstra(st,en);
        if (ans == IMPOSSIBLE) cout << -1 << "\n";
        else cout << ans << "\n";

        for (int i = 0; i < V; ++i)
        {
            graph[i].clear();
            before[i].clear();
        }
        
        graph.clear();
        before.clear();
    }
    
    return 0;
}