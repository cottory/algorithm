#define Tuple tuple<int,int,int>
#include <vector>
#include <queue>
#include <iostream>
#include <tuple>
#include <algorithm>
using namespace std;

int dy[] = {-1,1,0,0};
int dx[] = {0,0,-1,1};

const int DIR_SIZE = 4;
int N,M;
vector<string> map;
vector<vector<bool>> trip;

bool isSafe(int y, int x)
{
    return (0 <= y && y < N && 0 <= x && x < M);
}

int bfs(int y, int x)
{
    int ret = -1;
    queue<Tuple> q;
    trip[y][x] = true;
    q.push(make_tuple(y,x,0));

    while (!q.empty())
    {
        Tuple now = q.front(); q.pop();
        int cur_y,cur_x,cur_dist;
        tie(cur_y,cur_x,cur_dist) = now;
        
        ret = max(ret,cur_dist);

        for (int dir = 0; dir < DIR_SIZE; ++dir)
        {
            int ny = cur_y + dy[dir];
            int nx = cur_x + dx[dir];

            if (isSafe(ny,nx) && !trip[ny][nx] && map[ny][nx] == 'L')
            {
                trip[ny][nx] = true;
                q.push(make_tuple(ny, nx, cur_dist + 1));
            }
        }
    }

    return ret;
}
int main(void) {

    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> M;
    map.resize(N);
    trip.resize(N,vector<bool>(M,false));

    for (int i = 0; i < N; ++i)
    {
        cin >> map[i];
    }

    int ans = -1;

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < M; ++j)
        {
            if (map[i][j] == 'L')
            {
                for (int i = 0; i < N; ++i)
                {
                    fill(trip[i].begin(), trip[i].end(), false);    
                }

                ans = max(ans, bfs(i,j));
            }
        }
    }

    cout << ans << "\n";

    return 0;
}