#define JIHOON 0
#define FIRE 1
#define tiiii tuple<int,int,int, int>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <queue>
#include <tuple>
using namespace std;

int dy[] = {-1,1,0,0};
int dx[] = {0,0,-1,1};

int R, C;
vector<string> map;
vector<vector<bool>> trip_fire, trip_jihoon;
queue<tiiii> q;

bool finished(int y, int x) {
    return (y == 0 || y == C - 1 || x == 0 || x == R- 1);
}
bool safe(int y, int x) {
    return (0 <= y && y < C && 0 <= x && x < R);
}
int bfs(int jy, int jx) {
    
    int ret = -1;
    q.push(make_tuple(jy,jx,0,JIHOON));
    trip_jihoon[jy][jx] = true;

    while (!q.empty()) {
        int loop = q.size();

        while (loop--) {
            tiiii now = q.front(); q.pop();
            int y = get<0>(now);
            int x = get<1>(now);
            int count = get<2>(now);
            int state = get<3>(now);

            if (state == JIHOON && finished(y,x)) {
                ret = count + 1;
                return ret;
            }

            for (int dir = 0; dir < 4; ++dir) {
                int ny = y + dy[dir];
                int nx = x + dx[dir];

                if (!safe(ny,nx)) continue;
                if (map[ny][nx] == '#') continue;
                
                if (state == FIRE) {
                    if (!trip_fire[ny][nx]) {
                        trip_fire[ny][nx] = true;
                        q.push(make_tuple(ny,nx,count+1,FIRE));
                    }
                }
                else {
                    if (trip_jihoon[ny][nx]) continue;
                    if (trip_fire[ny][nx]) continue;
                    trip_jihoon[ny][nx] = true;
                    q.push(make_tuple(ny,nx,count+1,JIHOON));
                }
            }
        }
    }

    return ret;
}

int main(void) {

    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> C >> R;

    map.resize(C);
    trip_fire.resize(C,vector<bool>(R, false));
    trip_jihoon.resize(C,vector<bool>(R, false));
    
    for (int i = 0; i < C; ++i) {
        string str;
        cin >> map[i];
    }

    int jy,jx;
    
    for (int i = 0; i < C; ++i)
    for (int j = 0; j < R; ++j) {
        if (map[i][j] == 'J') {
            jy = i;
            jx = j;
            map[i][j] = '.';
        }
        else if (map[i][j] == 'F') {
            q.push(make_tuple(i,j,0,FIRE));
            trip_fire[i][j] = true;
        }
    }

    int ans = bfs(jy,jx);
    if (ans == -1) 
        cout << "IMPOSSIBLE\n";
    else
        cout << ans << "\n";
    
    return 0;
}