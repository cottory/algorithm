#define BLACK 0
#define WHITE 1
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

int N,M;
vector<string> vs;
vector<vector<int>> board;
int compare_block(int y, int x) {
    int minv, ret = 0;

    int ref[8][8];
    memset(ref, 0x0, sizeof(ref));
    for (int i = 0; i < 8; ++i) 
    for (int j = 0; j < 8; ++j) 
        if ((i + j) % 2) ref[i][j] = 1;

    for (int i = 0; i < 8; ++i) 
    for (int j = 0; j < 8; ++j)
        if (board[y+i][x+j] != ref[i][j])
            ret += 1;

    minv = ret;

    for (int i = 0; i < 8; ++i)
        fill(ref[i], ref[i] + 8, 1);
 
    for (int i = 0; i < 8; ++i)
    for (int j = 0; j < 8; ++j) 
        if ((i + j) % 2) ref[i][j] = 0;

    ret = 0;
    for (int i = 0; i < 8; ++i) 
    for (int j = 0; j < 8; ++j)
        if (board[y+i][x+j] != ref[i][j])
            ret += 1;

    return min(minv,ret);
}

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> M;
    board.resize(N,vector<int>(M,0));

    for (int i = 0; i < N; ++i) {
        string block;
        cin >> block;
        vs.push_back(block);
    }

    for (int i = 0; i < N; ++i)
    for (int j = 0; j < M; ++j) {
        if (vs[i][j] == 'B') board[i][j] = BLACK;
        else board[i][j] = WHITE;
    }
    
    int ans = 987654321;
    for (int i = 0; i <= N - 8; ++i)
    for (int j = 0; j <= M - 8; ++j) {
        int ret = compare_block(i,j);
        ans = min(ans,ret);
    }

    cout << ans << "\n";
    return 0;
}