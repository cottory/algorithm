#define Tuple tuple<int,int,int>
#define QTuple tuple<int,int,int,int>
#include <iostream>
#include <queue>
#include <tuple>
#include <algorithm>
using namespace std;

const int DIR_SIZE = 6;
const int dz[] = {0,0,0,0,-1,1};
const int dy[] = {-1,1,0,0,0,0};
const int dx[] = {0,0,-1,1,0,0};

Tuple st;
int L,R,C;
const int BOARD_SIZE = 35;
char board[35][35][35];
bool trip[35][35][35];

bool isSafe(int z, int y, int x)
{
    return (0 <= z && z < L && 0 <= y && y < R && 0 <= x && x < C);
}
int bfs()
{
    queue<QTuple> q;
    int stZ = get<0>(st);
    int stY = get<1>(st);
    int stX = get<2>(st);

    q.push(make_tuple(stZ,stY,stX,0));
    trip[stZ][stY][stX] = true;

    while (!q.empty())
    {
        QTuple now = q.front(); q.pop();

        int z,y,x,time;
        tie(z,y,x,time) = now;

        if (board[z][y][x] == 'E')
            return time;

        for (int dir = 0; dir < DIR_SIZE; ++dir)
        {
            int nz = z + dz[dir];
            int ny = y + dy[dir];
            int nx = x + dx[dir];

            if (!isSafe(nz,ny,nx)) continue;
            if (trip[nz][ny][nx]) continue;
            if (board[nz][ny][nx] == '#') continue;

            trip[nz][ny][nx] = true;
            q.push(make_tuple(nz,ny,nx,time + 1));
        }
    }

    return -1;
}
int main(void) {
    
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    while (true)
    {
        cin >> L >> R >> C;

        if (!L && !R && !C)
            break;

        for (int i = 0; i < BOARD_SIZE; ++i)
        for (int j = 0; j < BOARD_SIZE; ++j)
            fill(board[i][j], board[i][j] + BOARD_SIZE, '.');
        
        for (int i = 0; i < BOARD_SIZE; ++i)
        for (int j = 0; j < BOARD_SIZE; ++j)
            fill(trip[i][j], trip[i][j] + BOARD_SIZE, false);

        for (int i = 0; i < L; ++i)
        for (int j = 0; j < R; ++j)
        for (int k = 0; k < C; ++k)
        {
            char c;
            cin >> c;
            board[i][j][k] = c;
            
            if (c == 'S')
            {
                int z,y,x;
                z = i;
                y = j;
                x = k;
                st = make_tuple(z,y,x);
            }
        }

        int ret = bfs();
        if (ret == -1)
            cout << "Trapped!\n";
        else
            cout << "Escaped in " << ret << " minute(s).\n";   
    }

    return 0;
}