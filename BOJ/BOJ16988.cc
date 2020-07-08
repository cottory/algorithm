#define Y first
#define X second
#define pii pair<int,int>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int dy[] = {-1,1,0,0};
int dx[] = {0,0,-1,1};

int N,M,answer;
vector<int> pick, used;
vector<pii> candidate;
vector<vector<bool>> visited, trip;
vector<vector<int>> board;

bool safe(int y, int x) {
    return (0 <= y && y < N && 0 <= x && x < M);
}

vector<pii> bfs(int y, int x) {

    //컴포넌트 나누기
    vector<pii> ret;
    queue<pii> q;

    q.push({y,x});
    ret.push_back({y,x});

    while (!q.empty()) {
        pii now = q.front(); q.pop();
        
        for (int dir = 0; dir < 4; ++dir) {
            int ny = now.Y + dy[dir];
            int nx = now.X + dx[dir];

            if (!safe(ny,nx)) continue;
            if (trip[ny][nx]) continue;
            if (board[ny][nx] != 2) continue;
            
            trip[ny][nx] = true;
            ret.push_back({ny,nx});
            q.push({ny,nx});
        }
    }

    return ret;
}

int calculate(int y, int x) {

    //그냥 0좌표 개수만 세면 된다.
    int ans = 0;
    vector<pii> ret = bfs(y,x);
    for (pii pos : ret) {
        for (int dir = 0; dir < 4; ++ dir) {
            int ny = pos.Y + dy[dir];
            int nx = pos.X + dx[dir];
            if (!safe(ny,nx)) continue;
            if (board[ny][nx] == 0) ans += 1;
        }
    }

    if (ans == 0) {
        return ret.size();
    }
    else {
        return 0;
    }
} 
int solve(vector<int>& newStones) {
    int ret = 0;

    //1-1. newStones => 내돌로 바꾸기
    for (int idx : newStones) {
        pii pos = candidate[idx];
        board[pos.Y][pos.X] = 1;
    }

    //solve logic
    for (int idx : newStones) {
        pii pos = candidate[idx];
        for (int dir = 0; dir < 4; ++dir) {
            int ny = pos.Y + dy[dir];
            int nx = pos.X + dx[dir];
            if (!safe(ny,nx)) continue;
            if (trip[ny][nx]) continue;
            if (board[ny][nx] != 2) continue;
            trip[ny][nx] = true;
            ret += calculate(ny,nx);
        }
    }

    //1-2. 돌 원상태로 복귀시키기
    for (int idx : newStones) {
        pii pos = candidate[idx];
        board[pos.Y][pos.X] = 0;
    }

    return ret;
}

void combination(int idx, int r) {
    if (r == 2) {
        //used pick
        trip.clear();
        trip.resize(N, vector<bool>(M,false));
        answer = max(answer,solve(pick));
        return;
    }

    if (idx == candidate.size()) {
        return;
    }

    if (!used[idx]) {
        used[idx] = true;
        pick.push_back(idx);
        combination(idx + 1, r + 1);
        pick.pop_back();
        used[idx] = false;
    }   
    
    combination(idx + 1, r);
    return;
}
int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> M;

    board.resize(N, vector<int>(M,0));
    visited.resize(N, vector<bool>(M,false));

    for (int i = 0; i < N; ++i)  
    for (int j = 0; j < M; ++j) {
        cin >> board[i][j];
    }

    for (int i = 0; i < N; ++i)  
    for (int j = 0; j < M; ++j) {
        if (board[i][j] == 2) {
            for (int dir = 0; dir < 4; ++dir) {
                int ny = i + dy[dir];
                int nx = j + dx[dir];
                if (!safe(ny,nx)) continue;
                if (visited[ny][nx]) continue;
                if (board[ny][nx] != 0) continue;

                visited[ny][nx] = true;
                candidate.push_back({ny,nx});
            }
        }
    }

    used.resize(candidate.size(), false);

    combination(0,0);
    cout << answer << "\n";
    return 0;
}