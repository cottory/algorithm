#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

const int DIR_SIZE = 4;
const int dy[] = {-1,1,0,0};
const int dx[] = {0,0,-1,1};

int R,C,K,ans;
vector<string> map;
vector<vector<bool>> visited;

bool isSafe(int y, int x)
{
    return (0 <= y && y < R && 0 <= x && x < C);
}

void dfs(int y, int x, int cnt)
{
    if (cnt > K)
    {
        return;
    }
    else if (y == 0 && x == C-1 && cnt == K)
    {
        ans += 1;
        return;
    }

    for (int dir = 0; dir < DIR_SIZE; ++dir)
    {
        int ny = y + dy[dir];
        int nx = x + dx[dir];

        if (!isSafe(ny,nx)) continue;
        else if (map[ny][nx] == 'T') continue;
        else if (visited[ny][nx]) continue;

        visited[ny][nx] = true;
        dfs(ny,nx,cnt+1);
        visited[ny][nx] = false;
    }

}

int main(void)
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> R >> C >> K;

    for (int i = 0; i < R; ++i)
    {
        string str;
        cin >> str;
        map.push_back(str);
    }

    visited.resize(R,vector<bool>(C,false));
    visited[R-1][0] = true;
    dfs(R-1,0,1);

    cout << ans << "\n";
    return 0;
}