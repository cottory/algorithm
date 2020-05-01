#define STATE_SIZE 4
#define vi vector<int>
#define vvi vector<vector<int>>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef struct Sticker {
    vector<vector<int>> board[4];   //0, 90, 180, 270
}Sticker;

int N, M, K;
queue<Sticker> stickerList;
vector<vector<int> > map;
vector<vector<bool>> used;

vector<vector<int> > rotate(vector<vector<int>> before)
{
    int r,c;
    vector<vector<int> > ret;

    r = before.size();
    c = before[0].size();
    
    ret.resize(c, vi(r,0));
    
    for (int i = 0; i < r; ++i)
    for (int j = 0; j < c; ++j)
        ret[j][r-1-i] = before[i][j];

    return ret;
}

bool isSafe(int y, int x)
{
    return (0 <= y && y < N && 0 <= x && x < M);
}

void put_sticker(Sticker s, int y, int x, int state)
{
    vvi now = s.board[state];
    
    for (int i = 0; i < now.size(); ++i)
    {
        for (int j = 0; j < now[i].size(); ++j)
        {
            int ny = y + i;
            int nx = x + j;
            if (now[i][j])
                used[ny][nx] = true;
        }
    }
}
bool isPossible(Sticker s, int y, int x, int state)
{
    vvi now = s.board[state];
    
    for (int i = 0; i < now.size(); ++i)
    {
        for (int j = 0; j < now[i].size(); ++j)
        {
            int ny = y + i;
            int nx = x + j;
            if (!isSafe(ny,nx)) return false;
            if (used[ny][nx] && now[i][j]) return false;
        }
    }

    return true;
}

void solve()
{
    while (!stickerList.empty())
    {
        Sticker now = stickerList.front(); 
        stickerList.pop();
    
        bool isPut = false;
    
        for (int state = 0; state < STATE_SIZE; ++state)
        {
            for (int i = 0; i < N; ++i)
            {
                for (int j = 0; j < M; ++j)
                {
                    if(!used[i][j] || (used[i][j] && !now.board[state][0][0]))
                    {
                        if (isPossible(now, i,j, state)) 
                        {
                            put_sticker(now,i,j,state);
                            isPut = true;
                            break;
                        }
                    }
                }

                if (isPut) break;
            }

            if (isPut) break;
        }
    }
}
int main(void)
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> M >> K;

    map.resize(N, vi(M, 0));
    used.resize(N, vector<bool>(M, false));

    for (int r,c,loop = 0; loop < K; ++loop)
    {
        Sticker s;
        cin >> r >> c;
        vvi tmp(r, vi(c,0));

        for (int i = 0; i < r; ++i)
            for (int j = 0; j < c; ++j)
                cin >> tmp[i][j];

        s.board[0] = tmp;

        for (int i = 1; i < STATE_SIZE; ++i)
        {
            vvi nxt = rotate(tmp);
            s.board[i] = nxt;
            tmp = nxt;
        }

        stickerList.push(s);
    }

    solve();

    int ans = 0;
    for (int i = 0; i < N; ++i) 
    for (int j = 0; j < M; ++j)
        if (used[i][j]) ans += 1;   

    cout << ans << "\n";
    return 0;
}