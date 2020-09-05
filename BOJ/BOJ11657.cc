#define ll long long
#define Pair pair<int,ll>
#include <iostream>
#include <vector>
using namespace std;

const ll INF = 987654321;
int N,M;

vector<vector<Pair> > graph;
vector<ll> bellmanFord()
{
    vector<ll> dist(N,INF);
    dist[0] = 0;

    for (int loop = 0; loop < N; ++loop)
    {
        for (int node = 0; node < N; ++node)
        {
            for (Pair adj : graph[node])
            {
                int nxtNode = adj.first;
                int nxtCost = adj.second;

                if (dist[node] != INF && dist[nxtNode] > dist[node] + nxtCost)
                {
                    dist[nxtNode] = dist[node] + nxtCost;

                    if (loop == N-1)
                        return { };
                }
            }
        }
    }

    return dist;
}

int main(void) {

    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> M;
    graph.resize(N);

    for (int loop = 0; loop < M; ++loop)
    {
        int src,dst,cost;
        cin >> src >> dst >> cost;
        src--; dst--;
        graph[src].push_back(make_pair(dst,cost));
    }
    
    vector<ll> ret = bellmanFord();

    if (ret.size() == 0) cout << -1 << "\n";
    else
    {
        for (int i = 1; i < ret.size(); ++i)
        {
            if (ret[i] == INF)
                cout << -1 << "\n";
            else
                cout << ret[i] << "\n";
        }
    }
    
    return 0;
}