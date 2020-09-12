#include <iostream>
#include <vector>
using namespace std;

const int INF = 987654321;
int N, M;
vector<vector<int>> dist;

int main(void) {

    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> M;
    dist.resize(N,vector<int>(N,INF));

    for (int i = 0; i < M; ++i)
    {
        int src,dst;
        cin >> src >> dst;
        src--;dst--;

        dist[src][dst] = 1;
        dist[dst][src] = 1;
    }

    for (int middle = 0; middle < N; ++middle)
    {
        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                if (dist[i][j] > dist[i][middle] + dist[middle][j])
                {
                    dist[i][j] = dist[i][middle] + dist[middle][j];
                }
            }
        }
    }

    int ans_idx,ans = INF;

    for (int i = 0; i < N; ++i)
    {
        int candidate = 0;
        for (int nxt = 0; nxt < N; ++nxt)
        {
            if (i == nxt) 
                continue;

            candidate += dist[i][nxt];
        }

        if (candidate < ans)
        {
            ans = candidate;
            ans_idx = i;
        }
    }

    cout << ans_idx + 1 << "\n";
    return 0;
}