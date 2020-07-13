#define vi vector<int>
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;
const int dir[] = {1,-1,1};

int N,K;
const int POS_MAX = 200005;
vector<int> visited;
bool safe(int pos) {
    return (0 <= pos && pos < POS_MAX);
}

pair<int,vi> bfs() {
    queue<pair<int,vi>> q;
    q.push(make_pair(N,vector<int>()));

    while(!q.empty()) {
        pair<int,vi> now = q.front(); q.pop();
        
        if (now.first == K) {
            return now;
        }
        
        for (int nxt,d = 0; d < 3; ++d) {
            
            if (d == 2) {
                nxt = now.first * 2;
            }
            else {
                nxt = now.first + dir[d];
            } 

            if (!safe(nxt)) continue;
            if (visited[nxt]) continue;

            visited[nxt] = true;
            vector<int> next_vec = now.second;
            next_vec.push_back(nxt);
            q.push(make_pair(nxt,next_vec));
        }
    }
}
int main(void) {

    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> N >> K;

    if (N <= K) {
        visited.resize(POS_MAX,false);
        pair<int,vi> ans = bfs();
        cout << ans.second.size() << "\n";
        cout << N << " ";
        for (int pos : ans.second) {
            cout << pos << " ";
        }
        cout << "\n";
    } else {
        //K < N
        vector<int> ans;
        for (int loop = 0; loop <= N - K; ++loop) {
            ans.push_back(N-loop);
        }
        
        cout << N - K << "\n";
        for (int pos : ans) {
            cout << pos << " ";
        }
        cout << "\n";
    }
    return 0;
}