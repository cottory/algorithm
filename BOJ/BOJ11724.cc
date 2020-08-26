#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int N, M;
vector<vector<int>> graph;
vector<bool> trip;

void bfs(int node)
{
    queue<int> q;
    q.push(node);

    while (!q.empty())
    {
        int now = q.front(); q.pop();

        for (int i = 0; i < graph[now].size(); ++i)
        {
            int nxt = graph[now][i];
            if (trip[nxt]) 
                continue;

            trip[nxt] = true;
            q.push(nxt);
        }
    }

    return;
}

int main(void)
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> M;
    graph.resize(N);
    trip.resize(N,false);

    for (int i = 0; i < M; ++i)
    {
        int src, dst;
        cin >> src >> dst;
        src--; dst--;
        graph[src].push_back(dst);
        graph[dst].push_back(src);
    }

    int answer = 0;

    for (int i = 0; i < N; ++i)
    {
        if (!trip[i])
        {
            trip[i] = true;
            bfs(i);
            answer += 1;
        }
    }

    cout << answer << "\n";
    return 0;
}