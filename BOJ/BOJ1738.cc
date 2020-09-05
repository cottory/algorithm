#define ll long long
#define Pair pair<int,ll>
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
using namespace std;

const ll IMPOSSIBLE = -987654321;
int N,M;

vector<vector<Pair>> graph;
vector<vector<int>> reverseGraph;
vector<bool> visited;
int main(void) {

    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> M;
    graph.resize(N);
    reverseGraph.resize(N);
    visited.resize(N,false);

    for (int loop = 0; loop < M; ++loop)
    {
        int src, dst;
        ll money;
        cin >> src >> dst >> money;
        src--; dst--;

        graph[src].push_back(make_pair(dst,money));
        reverseGraph[dst].push_back(src);
    }

    //revesre BFS
    queue<int> q;
    q.push(N-1);
    visited[N-1] = true;

    while (!q.empty())
    {
        int now = q.front(); q.pop();

        for (int nxt : reverseGraph[now])
        {
            if (visited[nxt]) continue;

            visited[nxt] = true;
            q.push(nxt);
        }
    }

    //bellman-ford
    bool isCycle = false;
    vector<ll> dist, prev;
    dist.resize(N,IMPOSSIBLE);
    prev.resize(N,0);

    dist[0] = 0;

    for (int loop = 0; loop < N; ++loop)
    {
        for (int node = 0; node < N; ++node)
        {
            for (Pair adj : graph[node])
            {
                int nxtNode = adj.first;
                ll nxtMoney = adj.second;

                if (dist[node] != IMPOSSIBLE && dist[nxtNode] < dist[node] + nxtMoney)
                {
                    dist[nxtNode] = dist[node] + nxtMoney;
                    prev[nxtNode] = node;

                    if (loop == N-1 && visited[nxtNode]) 
                    {
                        isCycle = true;
                    }
                }
            }
        }
    }

    if (isCycle) cout << -1 << "\n";
    else
    {
        stack<int> answer;
        
        int node = N-1;
        while (node != 0)
        {
            answer.push(node+1);
            node = prev[node];
        }

        answer.push(1);

        while (!answer.empty())
        {
            cout << answer.top() << " ";
            answer.pop();
        }
    }

    return 0;
}