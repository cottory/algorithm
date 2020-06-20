#define TIME first
#define POS second
#define pii pair<int,int>
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

int N,K;
vector<int> trip;
queue<pii> q;

bool safe(int n) {
    return (0 <= n && n <= 100000);
}
int bfs(int st, int en) {
    
    int ret = INT32_MAX;
    trip[st] = true;
    q.push(make_pair(0,st));

    while(!q.empty()) {
        pii now = q.front(); q.pop();

        if (now.POS == en) {
            ret = min(ret,now.TIME);
            continue;
        }

        if (safe(now.POS + 1) && now.TIME + 1 < trip[now.POS+1]) {
            trip[now.POS + 1] = now.TIME + 1;
            q.push(make_pair(now.TIME + 1, now.POS + 1));
        }
        if (safe(now.POS - 1) && now.TIME + 1 < trip[now.POS-1]) {
            trip[now.POS - 1] = now.TIME + 1;
            q.push(make_pair(now.TIME + 1, now.POS - 1));
        }
        if (safe(now.POS * 2) && now.TIME < trip[now.POS*2]) {
            trip[now.POS * 2] = now.TIME;
            q.push(make_pair(now.TIME, now.POS * 2));
        }
    }
    return ret;
}
int main(void) {

    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> K;
    trip.resize(100001,INT32_MAX);
    cout << bfs(N,K) << "\n";
    return 0;
}