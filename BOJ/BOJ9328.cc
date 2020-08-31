#define Y first
#define X second
#define Pair pair<int,int>
#include <iostream>
#include <cstring>
#include <vector>
#include <string>
#include <cctype>
#include <queue>
using namespace std;

int dy[] = {-1,1,0,0};
int dx[] = {0,0,-1,1};

int T,W,H,docCount;
vector<string> board;
bool trip[102][102];
bool key[26];

queue<Pair> q;

bool isSafe(int y, int x) {
    return (0 <= y && y < H + 2 && 0 <= x && x < W + 2);
}
void bfs(int stY, int stX)
{
    q.push(make_pair(stY,stX));
    trip[stY][stX] = true;

    while (!q.empty())
    {
        Pair now = q.front(); q.pop();

        if (!isSafe(now.Y,now.X)) continue;
        else if (board[now.Y][now.X] == '*') continue;
        else if ('A' <= board[now.Y][now.X] && board[now.Y][now.X] <= 'Z') continue;

        if (board[now.Y][now.X] == '$')
        {
            docCount += 1;
            board[now.Y][now.X] = '.';
        }
        else if ('a' <= board[now.Y][now.X] && board[now.Y][now.X] <= 'z')
        {
            int offset = board[now.Y][now.X] - 'a';

            if (key[offset] == false)
            {
                key[offset] = true;

                for (int i = 0; i < H+2; ++i)
                {
                    for (int j = 0; j < W+2; ++j)
                    {
                        char target = (char)toupper(board[now.Y][now.X]);
                        if (board[i][j] == target)
                        {
                            board[i][j] = '.';

                            while (!q.empty())
                                q.pop();
                            
                            memset(trip,0,sizeof(trip));
                            trip[now.Y][now.X] = true;
                            q.push(make_pair(now.Y,now.X));
                            continue;
                        }
                    }
                }
            }

            board[now.Y][now.X] = '.';
        }

        for (int dir = 0; dir < 4; ++dir)
        {
            int ny = now.Y + dy[dir];
            int nx = now.X + dx[dir];
            if (!isSafe(ny,nx)) continue;
            if (trip[ny][nx]) continue;
            trip[ny][nx] = true;
            q.push(make_pair(ny,nx));
        }
    }

    return;
}
int main(void) {

    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> T;

    while (T--)
    {
        docCount = 0;
        cin >> H >> W;
        board.resize(H + 5);
        memset(trip,0,sizeof(trip));
        memset(key,0,sizeof(key));
        
        string wall = "";
        for (int i = 0; i < W + 2; ++i)
            wall += ".";

        board[0] = wall;

        for (int i = 1; i <= H; ++i)
        {
            string str;
            cin >> str;
            string inner_wall = ".";
            inner_wall += str;
            inner_wall += ".";
            board[i] = inner_wall;
        }

        board[H+1] = wall;

        string keys;
        cin >> keys;

        if (keys.compare("0") != 0)
        {
            for (int i = 0; i < keys.size(); ++i)
            {
                int offset = keys[i] - 'a';   
                key[offset] = true;
                char door = (char)toupper(keys[i]);

                for (int i = 0; i < H + 2; ++i)
                {
                    for (int j = 0; j < W + 2; ++j)
                    {
                        if (board[i][j] == door)
                        {
                            board[i][j] = '.';
                        }
                    }
                }
            }
        }   

        bfs(0,0);
        cout << docCount << "\n";
        board.clear();
    }

    return 0;
}