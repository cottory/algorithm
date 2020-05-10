#define IMPOSSIBLE 987654321
#define EDGE first
#define NODE second
#define pii pair<int,int>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int _N;
vector<vector<int> > graph;

bool dij(int dst, int K)
{
    int ret = 0;
    vector<int> dist(_N, IMPOSSIBLE);
    priority_queue<pii> pq;

    pq.push({0,0});
    dist[0] = 0;

    while (!pq.empty())
    {
        pii now = pq.top(); pq.pop();

        if (now.EDGE > dist[now.NODE]) 
            continue;

        for (int nxt = 0; nxt < _N; ++nxt)
        {
            if (now.NODE != nxt && graph[now.NODE][nxt] != IMPOSSIBLE)
            {
                int candidate = graph[now.NODE][nxt] + (-now.EDGE);
                if (candidate < dist[nxt]) {
                    dist[nxt] = candidate;
                    pq.push({-candidate, nxt});
                }
            }
        }
    }

    return dist[dst] <= K ? true : false;
}
int solution(int N, vector<vector<int> > road, int K) {
    int answer = 1;

    _N = N;
    graph.resize(N,vector<int>(N, IMPOSSIBLE));

    for (vector<int> info : road)
    {
        int src, dst, w;
        src = info[0];
        dst = info[1];
        w = info[2];
        src--, dst--;

        graph[src][dst] = min(graph[src][dst], w);
        graph[dst][src] = min(graph[dst][src], w);
    }

    for (int nxt = 1; nxt < N; ++nxt)
    {
        if (dij(nxt, K))
            answer += 1;
    }
    
    return answer;
}