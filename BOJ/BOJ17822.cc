#define Y first
#define X second
#define pii pair<int,int>
#define NOT_USED 987654321
#define CLOCK 0
#define COUNTER_CLOCK 1
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int dy[] = {-1,1,0,0};
int dx[] = {0,0,-1,1};

int N,M,T, number_count;
vector<vector<int>> circles;

bool isSafe(int y, int x) {
    return (0 <= y && y < N && 0 <= x && x < M);
}

vector<int> rotate(vector<int> before, int dir, int k) {
    vector<int> ret = before;

    if (dir == CLOCK) {
        for (int i = 0; i < M; ++i) 
            ret[(i + k) % M] = before[i];
    }
    else {
        for (int i = 0; i < M; ++i) 
            ret[((i - k + M)) % M] = before[i];
    }

    return ret;
} 

int bfs(vector<vector<bool> >& trip, int y, int x, int number) {

    int cnt = 1;
    queue<pii> q;
    q.push({y,x});
    
    while (!q.empty()) {
        pii now = q.front(); q.pop();

        for (int dir = 0; dir < 4; ++dir) {
            int ny = now.Y + dy[dir];
            int nx = (now.X + dx[dir] + M) % M;

            if (isSafe(ny,nx) && !trip[ny][nx] && circles[ny][nx] == number) {
                trip[ny][nx] = true;
                cnt += 1;
                circles[ny][nx] = NOT_USED;
                q.push({ny,nx});
            }
        }
    }

    if (cnt > 1) 
        circles[y][x] = NOT_USED;

    return cnt;
}

bool isAdj() {

    bool ret = false;
    vector<vector<bool> > trip(N,vector<bool>(M,false));
    
    for (int i = 0; i < N; ++i)
    for (int j = 0; j < M; ++j) {
        if (!trip[i][j] && (circles[i][j] != NOT_USED)) {
            trip[i][j] = true;
            int compoSize = bfs(trip, i,j,circles[i][j]);
            
            if (compoSize > 1) {
                ret = true;
                number_count -= compoSize;
            }
        }
    }

    return ret;
}

void calculate() {

    int sum = 0;
    int cnt = 0;
    double aver;

    for (int i = 0; i < N; ++i) 
    for (int j = 0; j < M; ++j) {
        if (circles[i][j] != NOT_USED) {
            cnt += 1;
            sum += circles[i][j];
        }
    }    

    aver = sum / (double)cnt;

    for (int i = 0; i < N; ++i) 
    for (int j = 0; j < M; ++j) {
        double num = (double)circles[i][j];
        if (num != (double)NOT_USED) {
            if (num > aver) 
                circles[i][j] -= 1;
            else if (num < aver)
                circles[i][j] += 1;
        }
    }    

    return;    
}

void solve(int x, int d, int k) {

    for (int i = 1; i <= N; ++i) {
        if (i % x == 0) {
            circles[i-1] = rotate(circles[i-1], d, k);
        }
    }

    //원판의 수가 남아있는지
    if (number_count) {

        if (!isAdj()) 
            calculate();
    }
}

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    cin >> N >> M >> T;

    circles.resize(N, vector<int>(M, 0));
    for (int i = 0; i < N; ++i)
    for (int x,j = 0; j < M; ++j) {
        cin >> x;
        circles[i][j] = x;
    }

    number_count = N*M;

    while (T--) {
        int x, d, k;
        cin >> x >> d >> k;
        solve(x,d,k);
    }

    int answer = 0;
    for (int i = 0; i < N; ++i)
    for (int j = 0; j < M; ++j)
    {
        if (circles[i][j] != NOT_USED)
            answer += circles[i][j];
    }

    cout << answer << "\n";
    return 0;
}