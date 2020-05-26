#define BOARD_SIZE 5
#include <iostream>
#include <string>
#include <set>
using namespace std;

int dy[] = {-1,1,0,0};
int dx[] = {0,0,-1,1};
int board[5][5];
set<string> visit;

bool safe(int y, int x) {
    return (0<=y&&y<5&&0<=x&&x<5);
}

void dfs(int y, int x, int cnt, string ret) {
    
    if (cnt == 6) {
        if (!visit.count(ret)) 
            visit.insert(ret);

        return;
    }

    for (int dir = 0; dir < 4; ++dir) {
        int ny = y + dy[dir];
        int nx = x + dx[dir];

        if (safe(ny,nx)) {
            char nxt = board[ny][nx] + '0';
            string nxt_str = ret + nxt;
            dfs(ny,nx,cnt+1,nxt_str);
        }
    }
}
int main(void) {

    for (int i = 0; i < BOARD_SIZE; ++i)
    for (int j = 0; j < BOARD_SIZE; ++j)
        cin >> board[i][j];

    for (int i = 0; i < BOARD_SIZE; ++i)
    for (int j = 0; j < BOARD_SIZE; ++j) {
        string st = to_string(board[i][j]);
        dfs(i,j,1,st);
    }
    
    cout << visit.size() << "\n";
    return 0;
}