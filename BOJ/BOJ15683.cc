#define VISITED 9999
#define tiii tuple<int,int,int>
#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
using namespace std;

const int DIRECTION_SiZE = 4;
const int dy[] = {-1,0,1,0};
const int dx[] = {0,1,0,-1};

int N, M, zeroCnt;
vector<tiii> cctv;
vector<vector<int>> board;

bool safe(int y, int x) {
    return (0 <= y && y < N && 0 <= x && x < M);
} 

int func(vector<vector<int>>& tmp_board, int y, int x, int dir) {
    int ret = 0;
    dir %= DIRECTION_SiZE;

    int ny = y;
    int nx = x;
    
    while (safe(ny + dy[dir], nx + dx[dir]) && (tmp_board[ny + dy[dir]][nx + dx[dir]] != 6)) {
        ny += dy[dir];
        nx += dx[dir];
        if (tmp_board[ny][nx] == 0) {
            ret += 1;
            tmp_board[ny][nx] = VISITED;
        }
    }

    return ret;
}

int beam(vector<vector<int>>& tmp_board, const int y, const int x, const int number, const int dir) {

    int ret = 0;
    if (number == 1) {
        ret += func(tmp_board, y, x, dir);        
    }
    else if (number == 2) {
        ret += func(tmp_board, y, x, dir);      
        ret += func(tmp_board, y, x, dir + 2);      
    }
    else if (number == 3) {
        ret += func(tmp_board, y, x, dir);      
        ret += func(tmp_board, y, x, dir + 1);  
    }
    else if (number == 4) {
        ret += func(tmp_board, y, x, dir);      
        ret += func(tmp_board, y, x, dir + 1);      
        ret += func(tmp_board, y, x, dir + 3);  
    }
    else {
        for (int loop = 0; loop < 4; ++loop) {
            ret += func(tmp_board, y, x, dir + loop);  
        }
    }
    
    return ret;
}
int solve(vector<vector<int>>& tmp_board, vector<int>& dirVector) {

    int ret = 0;
    for (int idx = 0; idx < dirVector.size(); ++idx) {
        tiii now = cctv[idx];
        int dir = dirVector[idx];

        int y = get<0>(now);
        int x = get<1>(now);
        int cctv_type = get<2>(now);
        ret += beam(tmp_board, y,x,cctv_type,dir);
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
    for (int num,j = 0; j < M; ++j) {
        cin >> num;
        if (1 <= num && num <=5) {
            cctv.push_back(make_tuple(i,j,num));
        }
        else if (num == 0) {
            zeroCnt += 1;
        }

        board[i][j] = num;
    }

    int ans = 987654321;
    const int CSIZE = cctv.size();
    for (int state = 0; state < (1 << (2*CSIZE)); ++state) {

        int now = state;
        vector<int> dirVector;
        vector<vector<int>> tmp_board;
        tmp_board = board;

        dirVector.clear();
        for (int i = 0; i < CSIZE; ++i) {
            int dir = now % DIRECTION_SiZE;
            dirVector.push_back(dir);
            now /= DIRECTION_SiZE;
        }    

        int result = solve(tmp_board, dirVector);
        ans = min(ans, zeroCnt - result);
    }

    cout << ans << "\n";
    return 0;
}