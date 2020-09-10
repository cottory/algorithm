#define Pair pair<int,int>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

const int INF = 987654321;
int N,M,W;
vector<int> components;
vector<bool> visited;
vector<vector<Pair>> graph;

bool bellmanFord(int node) {
    
    vector<int> dist(N,INF);
    dist[node] = 0;

    for (int loop = 0; loop < N; ++loop)
    {
        for (int now = 0; now < N; ++now)
        {
            for (auto nxt : graph[now])
            {
                int nxtNode = nxt.first;
                int nxtWeight = nxt.second;

                if (dist[nxtNode] > dist[now] + nxtWeight)
                {
                    dist[nxtNode] = dist[now] + nxtWeight;
                    if (loop == N-1)
                        return true;
                }
            }
        }
    }

    return false;
}

int bfs(int node)
{
    queue<int> q;
    q.push(node);

    while (!q.empty())
    {
        int now = q.front(); q.pop();

        for (auto nxt : graph[now])
        {
            int nxtNode = nxt.first;

            if (visited[nxtNode]) 
                continue;

            visited[nxtNode] = true;
            q.push(nxtNode);
        }
    }

    return node;
}
int main(void) {

    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    bool result;
    int testCase;

    cin >> testCase;

    while (testCase--)
    {
        result = false;
        visited.clear();
        components.clear();
        
        for (int i = 0; i < graph.size(); ++i)
            graph[i].clear();
        
        graph.clear();

        cin >> N >> M >> W;

        graph.resize(N);
        visited.resize(N,false);

        for (int src,dst,w,i = 0; i < M; ++i)
        {
            cin >> src >> dst >> w;
            src--; dst--;
            graph[src].push_back({dst,w});
            graph[dst].push_back({src,w});
        }

        for (int src,dst,w,i = 0; i < W; ++i)
        {
            cin >> src >> dst >> w;
            src--; dst--;
            graph[src].push_back({dst,-w});
        }

        //ÄÄÆ÷³ÍÆ® °¹¼ö Ã£±â
        for (int i = 0; i < N; ++i) {
            if (visited[i] == false) 
            {
                visited[i] = true;
                int node = bfs(i);
                components.push_back(node);
            }
        }

        for (int entryPoint : components)
        {
            if (bellmanFord(entryPoint))
            {
                result = true;
                break;
            }
        }

        if (result) cout << "YES\n";
        else cout << "NO\n";
    }

    return 0;
}