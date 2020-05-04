#define BLOCK_SIZE 3
#define Y first
#define X second
#define pii pair<int,int>
#include <string>
#include <vector>
#include <queue>
using namespace std;

typedef struct info{
    int y, x, type;
    info(int _y, int _x, int _type) : y(_y), x(_x), type(_type) {}
}info;

int N;
vector<vector<int> > map;
vector<info> infoList;
vector<bool> removed;

//Y,X
pii removed_pos[5][2] = {{{-1,0}, {-1,1}}, {{-1,0}, {-2,0}}, {{-1,0}, {-1,-1}}, {{-1,0}, {-2,0}}, {{-1,-1}, {-1,1}}};

int dy[5][3] = { {0,0,-1}, {0,-1,-2}, {0,0,-1}, {0,-1,-2} ,{0,0,-1}};
int dx[5][3] = { {1,-1,-1}, {-1,-1,-1}, {1,-1,1}, {1,1,1} ,{1,-1,0}};

int dy2[] = {-1,1,0,0};
int dx2[] = {0,0,-1,1};

bool isSafe(int y, int x)
{
    return (0 <= y && y < N && 0 <= x && x < N);
}

void removeBlock(int block_number, int y, int x)
{
    vector<vector<bool> > trip(N, vector<bool>(N, false));
    queue<pii> q;

    q.push({y,x});
    trip[y][x] = true;
    map[y][x] = 0;

    while (!q.empty())
    {
        pii now = q.front(); q.pop();

        for (int dir = 0; dir < 4; ++dir)
        {
            int ny = now.Y + dy2[dir];
            int nx = now.X + dx2[dir];

            if (!isSafe(ny,nx)) continue;
            if (map[ny][nx] != block_number) continue;
            if (trip[ny][nx]) continue;

            trip[ny][nx] = true;
            q.push({ny,nx});
            map[ny][nx] = 0;
        }
    }
}

bool is_Removed(info _block)
{
    int y = _block.y;
    int x = _block.x;
    int type = _block.type;

    for (int loop = 0; loop < 2; ++loop)
    {
        int ny = y + removed_pos[type][loop].Y;
        int nx = x +removed_pos[type][loop].X;

        for (int idx = ny; idx >= 0; --idx)
        {
            if (map[idx][nx]) return false;
        }
    }

    return true;
}

bool is_Target_Block(int _type, int y , int x)
{
    int num = map[y][x];
    for (int dir = 0; dir < BLOCK_SIZE; ++dir)
    {
        int ny = y + dy[_type][dir];
        int nx = x + dx[_type][dir];
        if (!isSafe(ny,nx)) return false;
        if (map[ny][nx] != num) return false;
    }
    return true;
}

int solution(vector<vector<int>> board) {
    int answer = 0;
    N = board.size();
    map = board;
    
    for (int i = 0; i < N; ++i)
    for (int j = 0; j < N; ++j)
    {
        if (map[i][j])
        {
            for (int block_type = 0; block_type < 5; ++block_type)
            {
                if (is_Target_Block(block_type, i, j))
                    infoList.push_back(info(i,j,block_type));
            }
        }
    }

    bool isEnd = false;
    removed.resize(infoList.size(), false);

    while (!isEnd)
    {
        isEnd = true;

        for (int i = 0; i < infoList.size(); ++i)
        {
            if (!removed[i] && is_Removed(infoList[i]))
            {
                info now = infoList[i];
                removed[i] = true;
                removeBlock(map[now.y][now.x], now.y, now.x);
                isEnd = false;
                answer += 1;
            }
        }
    }
    
    return answer;
}