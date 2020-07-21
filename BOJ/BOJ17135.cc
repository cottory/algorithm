#define pii pair<int,int>
#define tiii tuple<int,int,int>
#define Y first
#define X second
#define ENEMY 1
#define ARCHER 2
#include <tuple>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

//왼쪽, 거리 순으로 PQ
int N,M,D, enemy_count, ans;
vector<int> order;
vector<vector<int>> board;

bool isSafe(int y, int x) {
    return (0 <= y && y < N && 0 <= x && x < M);
}
int solve(vector<vector<int>> _board, vector<int>& archer_pos) {

    int ret = 0;
    int total = enemy_count;

    //shoot
    while (total > 0) {
        
        queue<pii> q;
        vector<vector<bool>> used(N+1,vector<bool>(M,false));

        for (int pos : archer_pos) {
            int ay = N;
            int ax = pos;
            priority_queue<tiii> pq;

            for (int h = 1; h <= D; ++h) 
            for (int w = -D; w < D; ++w) {
                if (h + abs(w) > D) continue;
                else if (!isSafe(ay-h,ax+w)) continue;
                
                if (_board[ay-h][ax+w] == ENEMY) {
                    pq.push(make_tuple(-(h+abs(w)), -(ax+w), ay-h));
                }
            } 

            if (!pq.empty()) {
                tiii kill_pos = pq.top(); pq.pop();
                int x = get<1>(kill_pos);
                x = -x;

                int y = get<2>(kill_pos);
                q.push(make_pair(y,x)); 

                //cnt
                if (!used[y][x]) {
                    used[y][x] = true;
                    ret += 1;
                    total -= 1;
                }
            }
        }

        while (!q.empty()) {
            pii now = q.front(); q.pop();
            _board[now.Y][now.X] = 0;
        }

        //board_down
        vector<vector<int>> _board_copy(N+1,vector<int>(M, 0));
        
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                if (i == N-1 && _board[i][j] == ENEMY) {
                    total--;
                }
                else {
                    _board_copy[i+1][j] = _board[i][j];    
                }
            }
        }

        _board = _board_copy;        
    }
    
    return ret;
}
int main(void) {

    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    cin >> N >> M >> D;

    board.resize(N+1,vector<int>(M, ARCHER));

    for (int i = 0; i < N; ++i)
    for (int x,j = 0; j < M; ++j) {
        cin >> x;
        
        if (x == ENEMY) 
            enemy_count += 1;

        board[i][j] = x;
    }

    if (M > 3)
        order.resize(M-3,0);

    for (int i = 0; i < 3; ++i)
        order.push_back(1);

    do {
        vector<vector<int>> board_cpy = board;
        vector<int> archer_pos;

        for (int i = 0; i < order.size(); ++i) {
            if (order[i]) {
                archer_pos.push_back(i);
            }
        }
        
        ans = max(ans,solve(board_cpy, archer_pos));
        
    } while(next_permutation(order.begin(), order.end()));

    cout << ans << "\n";

    return 0;
}