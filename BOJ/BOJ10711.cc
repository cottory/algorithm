#define DIR_SIZE 8
#define Y first
#define X second
#define pii pair<int,int>
#include <iostream>
#include <queue>
#include <vector>
#include <string>
using namespace std;

int dy[] = {-1,1,0,0,-1,-1,1,1};
int dx[] = {0,0,-1,1,-1,1,-1,1};

vector<string> map;
vector<vector<bool>> trip;
int N, M;
vector<pii> q1,q2;

bool safe(int y, int x) {
    return (0<=y && y<N && 0<=x && x<M);
}

int count(int y, int x) {

    int ret = 0;
    for (int dir = 0; dir < DIR_SIZE; ++dir) {
        int ny = y + dy[dir];
        int nx = x + dx[dir];
        if (safe(ny,nx) && map[ny][nx] == '.') 
            ret += 1;
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
        cin >> map[i];

    for (int i = 0; i < N; ++i)
    for (int j = 0; j < M; ++j) {
        if (map[i][j] != '.' && (count(i,j) >= (map[i][j] - '0'))) {
            trip[i][j] = true;
            q1.push_back({i,j});
        }
    }

    for (pii sand : q1) 
        map[sand.Y][sand.X] = '.';

    int cnt = 0;
    while (!q1.empty()) {

        cnt += 1;

        q2.clear();

        for (pii sand : q1) {

            for (int dir = 0; dir < DIR_SIZE; ++dir) {
                int ny = sand.Y + dy[dir];
                int nx = sand.X + dx[dir];
                if (safe(ny,nx) && map[ny][nx] != '.' && count(ny,nx) >= (map[ny][nx] - '0') && !trip[ny][nx]) {
                    trip[ny][nx] = true;
                    q2.push_back({ny,nx});
                }
            }    
        }

        for (pii sand : q2) {
            map[sand.Y][sand.X] = '.';
        }

        q1 = q2;
    }

    cout << cnt << "\n";    
    return 0;
}