#define EMPTY 0
#define WALL 1
#define VIRUS 2
#define Y first
#define X second
#define pii pair<int,int>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int dy[] = {-1,1,0,0};
int dx[] = {0,0,-1,1};

int N,M,ans;
vector<vector<int>> board;
vector<pii> virus, candidate;

vector<vector<int>> makeNewBoard(vector<int>& order) {
    vector<vector<int>> ret = board;

    for (int i = 0; i < order.size(); ++i) {
        if (order[i] == 0) continue;
        int y = candidate[i].Y;
        int x = candidate[i].X;
        ret[y][x] = WALL;
    }

    return ret;
}
bool safe(int y, int x) {
    return (0 <= y && y < N && 0 <= x && x < M);
}

int bfs(vector<vector<int>>& newBoard) {

    int ret = 0;
    vector<vector<bool>> trip(N,vector<bool>(M,false));
    queue<pii> q;
    
    for (int i = 0; i < virus.size(); ++i) {
        int y = virus[i].Y;
        int x = virus[i].X;
        trip[y][x] = true;
        q.push({y,x});
    }

    while (!q.empty()) {
        pii now = q.front(); q.pop();

        for (int dir = 0; dir < 4; ++dir) {
            int ny = now.Y + dy[dir];
            int nx = now.X + dx[dir];

            if (!safe(ny,nx)) continue;
            if (trip[ny][nx]) continue;

            if (newBoard[ny][nx] == EMPTY) {
                ret += 1;
                trip[ny][nx] = true;
                q.push({ny,nx});        
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
    board.resize(N,vector<int>(M,0));

    for (int i = 0; i < N; ++i)
    for (int x,j = 0; j < M; ++j) {
        cin >> x;
        if (x == EMPTY) {
            candidate.push_back({i,j});
        }
        else if (x == VIRUS) {
            virus.push_back({i,j});
        }
        board[i][j] = x;
    }

    vector<int> order;
    order.resize((int)candidate.size() - 3, 0);
    for (int loop = 0; loop < 3; ++loop) order.push_back(1);

    do {
        vector<vector<int>> newBoard = makeNewBoard(order);
        int cnt = bfs(newBoard);    //0 => 2로 바뀐 칸의 갯수 리턴
        int result = candidate.size() - cnt - 3;
        ans = max(ans,result);
    } while (next_permutation(order.begin(), order.end()));

    cout << ans << "\n";
    return 0;
}