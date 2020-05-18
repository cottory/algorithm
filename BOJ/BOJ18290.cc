#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int N, M, K;
vector<int> pick;
vector<bool> used;
vector<vector<int>> board;

int ans = -987654321;
int dy[] = {-1,1,0,0};
int dx[] = {0,0,-1,1};

bool safe(int y, int x) {
    return (0<=y&&y<N&&0<=x&&x<M);
}
bool isAdj() {
    for (int i = 0; i < K; ++i)
    for (int j = 0; j < K; ++j) {
        if (i == j) continue;
        int y = pick[i] / M;
        int x = pick[i] % M;

        int y2 = pick[j] / M;
        int x2 = pick[j] % M;
        
        for (int dir = 0; dir < 4; ++dir) {
            int ny = y + dy[dir];
            int nx = x + dx[dir];
            if (!safe(ny,nx)) continue;
            if (y2 == ny && x2 == nx) return true;
        }

    }

    return false;
}
void combination(int n, int k) {

    if (k == K) {
        //solve
        int sum = 0;
        
        if (isAdj()) return;

        for (int i = 0; i < K; ++i) {
            int y = pick[i] / M;
            int x = pick[i] % M;
            sum += board[y][x];
        }

        ans = max(ans,sum);
        return;
    }

    if (n == N*M) 
        return;

    int now = n;
    
    if (!used[now]) {
        used[now] = true;
        pick.push_back(now);
        combination(n+1,k+1);
        pick.pop_back();
        used[now] = false;
    }

    combination(n+1,k);
}
int main(void) {

    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> M >> K;
    board.resize(N, vector<int>(M,0));
    used.resize(N*M, false);

    for (int i = 0; i < N; ++i)
    for (int j = 0; j < M; ++j)
        cin >> board[i][j];

    combination(0,0);

    cout << ans << "\n";
    return 0;
}