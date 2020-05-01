#define GREEN 1
#define RED 2
#define Y first
#define X second
#define pii pair<int,int>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#include <string>
using namespace std;

typedef struct tok {
    int y, x, color, t;
    tok(int _y, int _x, int col, int _t) : y(_y), x(_x), color(col), t(_t) {}
}tok;

int dy[] = {-1,1,0,0};
int dx[] = {0,0,-1,1};

int ans,N, M, G, R;
vector<vector<int>> board;
vector<pii> candidate_list;

bool isSafe(int y, int x)
{
    return (0 <= y && y < N && 0 <= x && x < M);
}
int bfs(vector<vector<int>> _board, vector<tok> seedList)
{
    int ans = 0;
    queue<tok> q;
    //pii => first: color, second: time
    vector<vector<pii>> trip(N, vector<pii>(M, {0,99999}));

    for (tok info : seedList) 
    {
        q.push(tok(info.y,info.x, info.color, 0));
        trip[info.y][info.x] = {info.color, -1};
    }

    while (!q.empty())
    {
        int loop = q.size();

        while (loop--)
        {
            tok now = q.front(); q.pop();

            if (_board[now.y][now.x] == 0) continue;

            for (int dir = 0; dir < 4; ++dir)
            {
                int ny = now.y + dy[dir];
                int nx = now.x + dx[dir];

                if (!isSafe(ny,nx)) continue;
                if (_board[ny][nx] == 0) continue;
                if (trip[ny][nx].second < now.t + 1) continue;


                if (trip[ny][nx].second != now.t + 1)
                {
                   _board[ny][nx] = now.color;
                   q.push(tok(ny,nx,now.color, now.t + 1));
                   trip[ny][nx].first = now.color;
                   trip[ny][nx].second = now.t + 1;          
                }
                else 
                {
                    if (trip[ny][nx].first == GREEN && now.color == RED) 
                    {
                        ans += 1;
                        _board[ny][nx] = 0;
                    }
                    else if (trip[ny][nx].first == RED && now.color == GREEN)
                    {
                        ans += 1;
                        _board[ny][nx] = 0;
                    }
                }                                   
            }
        }
    }

    return ans;
}

int solve(vector<int>& order)
{
    vector<vector<int>> new_board = board;
    vector<tok> new_list;

    for (int i = 0; i < order.size(); ++i)
    {
        pii now = candidate_list[i];

        if (order[i] == 0)
        {
            new_board[now.Y][now.X] = 3;
        }
        else if (order[i] == 1)
        {
            new_board[now.Y][now.X] = 1;
            new_list.push_back(tok(now.Y, now.X, GREEN, -1));
        }
        else 
        {
            new_board[now.Y][now.X] = 2;
            new_list.push_back(tok(now.Y, now.X, RED, -1));
        }
    }

    return bfs(new_board, new_list);
}

int main(void) 
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> M >> G >> R;
    board.resize(N,vector<int>(M,0));
    
    for (int i = 0; i < N; ++i)
    for (int x, j = 0; j < M; ++j)
    {
        cin >> x;
        if (x == 2)
        {
            candidate_list.push_back({i,j});
            board[i][j] = x;
        }
        else if (x == 1) 
        {
            board[i][j] = 3;
        }
        else
        {
            board[i][j] = x;
        }
    }

    vector<int> order;
    for (int i = 0; i < G; ++i) order.push_back(1);
    for (int i = 0; i < R; ++i) order.push_back(2);

    int clSize = candidate_list.size();
    int oSize = order.size();

    if (clSize > oSize)
    {
        for (int loop = 0; loop < (clSize - oSize); ++loop)
            order.push_back(0);
    }

    sort(order.begin(), order.end());

    do {
        ans = max(ans,solve(order));
    } while(next_permutation(order.begin(), order.end()));
    
    cout << ans << "\n";
    return 0;
}