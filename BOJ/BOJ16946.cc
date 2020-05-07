#define Y first
#define X second
#define pii pair<int,int>
#define BLOCK 987654321
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <queue>
using namespace std;

int dy[] = {-1,1,0,0};
int dx[] = {0,0,-1,1};

int N, M;
vector<string> vs;
vector<vector<int> > ans;
vector<vector<pii> > board;
vector<vector<bool> > trip;

bool isSafe(int y, int x)
{
    return (0 <= y && y < N && 0 <= x && x < M);
}
vector<pii> bfs(int y, int x)
{
    vector<pii> ret;
    queue<pii> q;
    q.push({y,x});
    ret.push_back({y,x});

    while (!q.empty())
    {
        pii now = q.front(); q.pop();
        
        for (int dir = 0; dir < 4; ++dir)
        {
            int ny = now.Y + dy[dir];
            int nx = now.X + dx[dir];

            if (!isSafe(ny,nx)) continue;
            if (trip[ny][nx]) continue;
            if (board[ny][nx].first == BLOCK) continue;

            trip[ny][nx] = true;
            q.push({ny,nx});
            ret.push_back({ny,nx});
        }
    }

    return ret;
}
void getComponent()
{
    vector<vector<pii> > candidate;
    
    for (int i = 0; i < N; ++i)
    for (int j = 0; j < M; ++j)
    {
        if (!trip[i][j] && board[i][j].first == 0)
        {
            trip[i][j] = true;
            candidate.push_back(bfs(i,j));
        }
    }

    //board 갱신
    for (int loop = 0; loop < candidate.size(); ++loop)
    {
        int cnt = candidate[loop].size();

        for (pii pos : candidate[loop])
        {
            board[pos.Y][pos.X] = {cnt, loop};
        }
    }

    return;
}

vector<vector<int> > solve()
{
    vector<vector<int> > ret(N,vector<int>(M,0));

    for (int i = 0; i < N; ++i)
    for (int j = 0; j < M; ++j)
    {
        if (board[i][j].first == BLOCK)
        {
            set<int> used;

            int cnt = 0;
            for (int dir = 0; dir < 4; ++dir)
            {
                int ny = i + dy[dir];
                int nx = j + dx[dir];

                if (isSafe(ny, nx) && (board[ny][nx].first != BLOCK) && !used.count(board[ny][nx].second))
                {
                    used.insert(board[ny][nx].second);
                    cnt += board[ny][nx].first;
                }
            }

            ret[i][j] = (cnt + 1) % 10;
        }
    }

    return ret;
}

void print(vector<vector<int> > v)
{
    for (int i = 0; i < v.size(); ++i)
    {
        for (int j = 0; j < v[i].size(); ++j)
        {
            cout << v[i][j];
        }
        cout << "\n";
    }
}
int main(void)
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    cin >> N >> M;

    for (int i = 0; i < N; ++i)
    {
        string s;
        cin >> s;
        vs.push_back(s);
    }

    board.resize(N,vector<pii>(M,{0, -1}));
    ans.resize(N,vector<int>(M,0));
    trip.resize(N,vector<bool>(M,false));

    for (int i = 0; i < N; ++i)
    for (int j = 0; j < M; ++j)
    {
        int val = vs[i][j] - '0';
        if (val)
            board[i][j] = {BLOCK, -1};
        else    
            board[i][j] = {0,-1};
    }

    getComponent();
    ans = solve();
    print(ans);
    
    return 0;
}