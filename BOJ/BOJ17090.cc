#define Y first
#define X second
#define pii pair<int,int>
#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <cstring>
using namespace std;

const int BOARD_SIZE = 501;
int dy[] = {-1,0,1,0};
int dx[] = {0,1,0,-1};
const char direction[] = {'U','R','D','L'};

int N,M,ans;
vector<string> board;
int visited[BOARD_SIZE][BOARD_SIZE];
queue<pii> q;

bool safe(int y, int x) {
    return (0 <= y && y < N && 0 <= x && x < M); 
}

int main(void) {

    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> M;

    board.resize(N);

    for (int i = 0; i < N; ++i) {
        cin >> board[i];
    }

    //init
    for (int i = 0; i < N; ++i)
    for (int j = 0; j < M; ++j) {
        char c = board[i][j];
        for (int dir = 0; dir < 4; ++dir) {
            if (c != direction[dir]) continue;
            
            //c == direction[dir]
            int ny = i + dy[dir];
            int nx = j + dx[dir];
            if (!safe(ny,nx)) {
                visited[i][j] = 1;
                q.push({i,j});
            }
        }
    }

    ans = q.size();

    while (!q.empty()) {
        pii now = q.front(); q.pop();
        
        for (int dir = 0; dir < 4; ++dir) {
            int by = now.Y + dy[dir];   //before_y
            int bx = now.X + dx[dir];   //before_x
            
            if (!safe(by,bx)) continue;
            if (visited[by][bx]) continue;

            char c = board[by][bx];
            
            for (int dir_2 = 0; dir_2 < 4; ++dir_2) {
                if (c != direction[dir_2]) continue;
                
                //c == direction[dir_2]
                int ny = by + dy[dir_2];
                int nx = bx + dx[dir_2];
                if (ny == now.Y && nx == now.X) {
                    visited[by][bx] = 1;
                    q.push({by,bx});
                    ans += 1;
                }
            }
        }
    }

    cout << ans << "\n";
    return 0;
}