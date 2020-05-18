#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int dy[] = {-1,1,0,0,-1,-1,1,1};
int dx[] = {0,0,-1,1,-1,1,-1,1};
int R, C;

vector<vector<int>> board, parent;

bool safe(int y, int x) {
    return (0<=y&&y<R&&0<=x&&x<C);
}
int find(int number) {
    int y = number / C;
    int x = number % C;
    
    if (parent[y][x] == number) return number;
    else return parent[y][x] = find(parent[y][x]);
}

void print(vector<vector<int>> vvi) {
    for (int i = 0; i < vvi.size(); ++i) {
        for (int j = 0; j < vvi[i].size(); ++j) {
            cout << vvi[i][j] << " ";
        }
        cout << endl;
    }
}
int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> R >> C;
    board.resize(R,vector<int>(C,0));
    parent.resize(R,vector<int>(C,0));
    for (int i = 0; i < R; ++i)
    for (int j = 0; j < C; ++j)
        cin >> board[i][j];

    for (int i = 0; i < R; ++i)
    for (int j = 0; j < C; ++j) 
        parent[i][j] = (C*i) + j;

    for (int i = 0; i < R; ++i)
    for (int j = 0; j < C; ++j) {
        int minv = board[i][j], my = i,mx = j;

        for (int dir = 0; dir < 8; ++dir) {
            int ny = i + dy[dir];
            int nx = j + dx[dir];

            if (!safe(ny,nx)) continue;
            
            if (board[ny][nx] < minv) {
                minv = board[ny][nx];
                my = ny;
                mx = nx;
            }
        }

        parent[i][j] = (C*my) + mx;
    }

    for (int i = 0; i < R; ++i)
    for (int j = 0; j < C; ++j)
        find(i*C + j);
        
    for (int i = 0; i < R; ++i)
        fill(board[i].begin(), board[i].end(), 0);

    for (int i = 0; i < R; ++i)
    for (int j = 0; j < C; ++j) {
        int num = parent[i][j];
        int y = num / C;
        int x = num % C;
        board[y][x]++;
    }

    print(board);
    return 0;
}