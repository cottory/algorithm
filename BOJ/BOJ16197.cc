#define Y first
#define X second
#define pii pair<int,int>
#include <iostream>
#include <vector>
#include <string>
#include <queue>
using namespace std;

typedef struct token {
    int y1,x1,y2,x2,cnt;
    token(int yy1, int xx1, int yy2, int xx2, int ccnt) 
    :  y1(yy1), x1(xx1), y2(yy2), x2(xx2), cnt(ccnt) {}
}token;

int dy[] = {-1,1,0,0};
int dx[] = {0,0,-1,1};

int N, M;
vector<string> vs;
vector<pii> coin;
bool trip[20][20][20][20];

bool safe(int y, int x) {
    return (0<=y&&y<N&&0<=x&&x<M);
}

int bfs() {

    int ret = -1;

    queue<token> q;
    
    q.push(token(coin[0].Y,coin[0].X,coin[1].Y,coin[1].X,0));

    while (!q.empty()) {
        token now = q.front(); q.pop();
        
        if (now.cnt > 10) {
            ret = -1;
            break;
        }
        
        int cnt = 0;
        if (safe(now.y1,now.x1)) cnt += 1;
        if (safe(now.y2,now.x2)) cnt += 1;

        if (cnt == 1) {
            ret = now.cnt;
            break;
        }
        else if (cnt == 2) {
            for (int dir = 0; dir < 4; ++dir) {
                int ny1 = now.y1 + dy[dir];
                int nx1 = now.x1 + dx[dir];
                int ny2 = now.y2 + dy[dir];
                int nx2 = now.x2 + dx[dir];   

                if (safe(ny1,nx1) && vs[ny1][nx1] == '#') {
                    ny1 -= dy[dir];
                    nx1 -= dx[dir];
                }
                if (safe(ny2,nx2) && vs[ny2][nx2] == '#') {
                    ny2 -= dy[dir];
                    nx2 -= dx[dir];
                }

                if (safe(ny1,nx1) && safe(ny2,nx2) && !trip[ny1][nx1][ny2][nx2]) {
                    trip[ny1][nx1][ny2][nx2] = true;
                    q.push(token(ny1,nx1,ny2,nx2,now.cnt + 1));
                }
                else if (safe(ny1,nx1) || safe(ny2,nx2)) {
                    q.push(token(ny1,nx1,ny2,nx2,now.cnt + 1));
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

    cin >> N >> M;
    vs.resize(N);

    for (int i = 0; i < N; ++i)
        cin >> vs[i];

    for (int i = 0; i < N; ++i)
    for (int j = 0; j < M; ++j)
        if (vs[i][j] == 'o') 
            coin.push_back(make_pair(i,j));

    cout << bfs() << "\n";
    
    return 0;
}