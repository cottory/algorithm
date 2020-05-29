#define SLOW 0
#define FAST 1
#define DIST first
#define NODE second
#define ll long long
#define pii pair<int,int>
#define pli pair<ll,int>
#define tlii tuple<ll,int,int>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <tuple>
using namespace std;

int N,M;
vector<vector<pii>> graph;
vector<ll> dist, dp[2]; //여우 길, 늑대 길

void wolf_dij() {
    dp[0].resize(N,__LONG_LONG_MAX__);
    dp[1].resize(N,__LONG_LONG_MAX__);

    dp[0][0] = 0;
    priority_queue<tlii> pq;
    pq.push(make_tuple(0,0,FAST));

    while (!pq.empty()) {
        tlii now = pq.top(); pq.pop();
        ll w = -get<0>(now);
        int node = get<1>(now);
        int state = get<2>(now);

        if (w > dp[(state+1)%2][node])
            continue;
        
        for (int i = 0; i < graph[node].size(); ++i) {
            int nxt = graph[node][i].first;
            ll weight = graph[node][i].second;

            if (state == FAST) weight /= 2;
            else if (state == SLOW) weight *= 2;

            if (w + weight < dp[state][nxt]) {
                dp[state][nxt] = w + weight;
                pq.push(make_tuple(-dp[state][nxt], nxt, (state + 1) % 2));
            }
        }
    }

    return;
}

void fox_dij() {
    dist.resize(N,__LONG_LONG_MAX__);
    dist[0] = 0;
    priority_queue<pli> pq;
    pq.push({0,0});

    while (!pq.empty()) {
        pli now = pq.top(); pq.pop();
        now.DIST = -now.DIST;

        if (now.DIST > dist[now.NODE])
            continue;
                
        for (int i = 0; i < graph[now.NODE].size(); ++i) {
            int nxt = graph[now.NODE][i].first;
            ll w = graph[now.NODE][i].second;
            
            if (now.DIST + w < dist[nxt]) {
                dist[nxt] = now.DIST + w;
                pq.push({-dist[nxt], nxt});
            }
        }
    }

    return;
}
int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> N >> M;
    graph.resize(N);

    for (int a,b,d,i = 0; i < M; ++i)
    {
        cin >> a >> b >> d;
        d *= 2;
        a--; b--;
        graph[a].push_back({b,d});
        graph[b].push_back({a,d});
    }
    
    fox_dij(); //여우 case
    wolf_dij(); //늑대 case

    int ans = 0;
    for (int i = 1; i < N; ++i) {
        if (dist[i] < min(dp[SLOW][i],dp[FAST][i]))
            ans += 1;
    }

    cout << ans << "\n";
    return 0;
}