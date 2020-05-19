#define SUM first
#define CNT second
#define pii pair<int,int>
#include <iostream>
#include <queue>
#include <set>
#include <vector>
#include <cstring>
using namespace std;

int num[] = {1,5,10,50};
int N;
queue<pii> q;
set<int> num_list;
int used[1005][25];
int bfs() {
    
    q.push({0,0});

    while (!q.empty()) {
        pii now = q.front(); q.pop();

        if (now.CNT == N) {
            num_list.insert(now.SUM);
        }
        else {
            for (int state = 0; state < 4; ++state) {
                int nxt = now.SUM + num[state];
                if (!used[nxt][now.CNT+1]) {
                    used[nxt][now.CNT+1] = 1;
                    q.push({nxt, now.CNT + 1});
                }
            }
        }
    }

    return (int)num_list.size();    
}

int main(void) {

    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;
    memset(used, 0, sizeof(used)); 
    cout << bfs() << "\n";
    return 0;
}