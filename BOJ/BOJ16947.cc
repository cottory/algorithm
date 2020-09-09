#define Pair pair<int,int>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

int N;
vector<int> finished,dist;
vector<bool> isCycled,visited;
vector<vector<int> > graph;
queue<Pair> q;

void bfs()
{
    while (!q.empty())
    {
        Pair now = q.front(); q.pop();

        int node = now.first;
        int cnt = now.second;

        for (int i = 0; i < graph[node].size(); ++i)
        {
            int nxt = graph[node][i];
            if (isCycled[nxt] == false && visited[nxt] == false)
            {
                visited[nxt] = true;
                dist[nxt] = cnt + 1;
                q.push(make_pair(nxt,cnt+1));
            }
        }
    }
}

int main(void) {

    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;
    graph.resize(N);
    dist.resize(N,0);
    finished.resize(N,0);
    isCycled.resize(N, true);
    visited.resize(N,false);

    for (int i = 0; i < N; ++i)
    {
        int src, dst;
        cin >> src >> dst;
        src--; dst--;
        graph[src].push_back(dst);
        graph[dst].push_back(src);
        finished[src]++;
        finished[dst]++;
    }
    
    //싸이클 판단
    bool flag = true;

    while (flag)
    {
        flag = false;
        for (int i = 0; i < N; ++i)
        {
            if (finished[i] == 1 && (isCycled[i] == true))
            {
                flag = true;
                isCycled[i] = false;
                for (int nxt = 0; nxt < graph[i].size(); ++nxt)
                {
                    int nxtNode = graph[i][nxt];
                    finished[nxtNode]--;
                }
            }
        }
    }

    //bfs 초기화 작업
    for (int i = 0; i < N; ++i)
    {
        if (isCycled[i] == true)
        {
            for (int idx = 0; idx < graph[i].size(); ++idx)
            {
                int nxt = graph[i][idx];
                if (isCycled[nxt] == false && visited[nxt] == false)
                {
                    visited[nxt] = true;
                    dist[nxt] = 1;
                    q.push(make_pair(nxt,1));
                } 
            }
        }
    }

    //bfs
    bfs();

    for (int i = 0; i < N; ++i)
        cout << dist[i] << " ";

    return 0;
}