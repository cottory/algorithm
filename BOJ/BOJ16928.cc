#define POS first
#define CNT second
#define pii pair<int,int>
#include <iostream>
#include <vector>
#include <queue>
#include <map>
using namespace std;

const int dy[] = {-1,1,0,0};
const int dx[] = {0,0,-1,1};
const int dice[] = {1,2,3,4,5,6};
const int DICE_SIZE = 6;

int N, M;
vector<bool> trip;
map<int,int> ladder, snake;

bool safe(int pos) {
    return (1 <= pos && pos <= 100);
}
int bfs() {

    queue<pii> q;
    trip.resize(101, false);
    trip[1] = true;
    q.push({1,0});

    while (!q.empty()) {

        const pii now = q.front(); q.pop();
        if (now.POS == 100) {
            return now.CNT;
        }
        for (int dir = 0; dir < DICE_SIZE; ++dir) {
            const int nxt = now.POS + dice[dir];

            if (!safe(nxt)) continue;
            if (trip[nxt]) continue;
            
            trip[nxt] = true;
            
            if (ladder.find(nxt) != ladder.end()) {
                const int nnxt = ladder[nxt];
                trip[nnxt] = true;
                q.push({nnxt,now.CNT + 1});
            }
            else if (snake.find(nxt) != snake.end()) {
                const int nnxt = snake[nxt];
                trip[nnxt] = true;
                q.push({nnxt,now.CNT + 1});
            }
            else {
                q.push({nxt,now.CNT + 1});
            }
        }
    }

    return -1;
}
int main(void) {
   
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> M;

    for (int x,y,loop = 0; loop < N; ++loop) {
        cin >> x >> y;
        ladder[x] = y;
    }    
    
    for (int u,v,loop = 0; loop < M; ++loop) {
        cin >> u >> v;
        snake[u] = v;
    }   

    cout << bfs() << "\n";
    return 0;
}