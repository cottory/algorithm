#define ll long long
#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
int N,M;
ll K;
vector<int> stones;
vector<bool> visited;
vector<vector<int>> component;
int graph[1000005][2];
int main(void) {

    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> M >> K;

    if (M <= 1) {
        cout << "YES\n";
        return 0;
    }

    stones.resize(N);
    visited.resize(N,false);
    memset(graph,0, sizeof(graph));

    for (int i = 0; i < N; ++i)
        cin >> stones[i];

    for (int x,y,i = 0; i < M; ++i) {
        cin >> x >> y;
        x--; y--;

        if (x > y) swap(x,y);

        if (x == 0 && y == N-1) {
            graph[x][0] = 1;
            graph[y][1] = 1;
        }
        else {
            graph[x][1] = 1;
            graph[y][0] = 1;
        }
    }

    for (int i = 0; i < N; ++i) {
        if (visited[i]) continue;

        vector<int> cmp;
        visited[i] = true;
        cmp.push_back(i);

        int nxt = 1;
        while (!visited[(i+nxt) % N] && !graph[(i+nxt) % N][0]) {
            cmp.push_back((i+nxt) % N);
            visited[(i+nxt) % N] = true;
            nxt += 1;
        }

        nxt = -1;
        while (!visited[(i+nxt + N) % N] && !graph[(i+nxt + N) % N][1]) {
            cmp.push_back((i+nxt + N) % N);
            visited[(i+nxt + N) % N] = true;
            nxt -= 1;
        }

        component.push_back(cmp);
    }

    ll total = 0;
    for (vector<int> cmp : component) {
        int minv = 987654321;
        for (int idx : cmp) 
            minv = min(stones[idx],minv);

        total += minv;
    }

    if (K >= total) cout << "YES\n";
    else cout << "NO\n";

    return 0;
}