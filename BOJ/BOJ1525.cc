#define UP 0
#define DOWN 1
#define RIGHT 2
#define LEFT 3
#define PAIR pair<int,int>
#define NUMBER first
#define SWAP_CNT second
#include <iostream>
#include <set>
#include <queue>
#include <string>
#include <algorithm>
using namespace std;

int dir[] = {-3,3,1,-1};
const int BOARD_SIZE = 3;
const int DIR_SIZE = 4;
const int ANSWER = 123456789;
set<int> visited;

bool isSafe(int idx) {
    return (0 <= idx && idx < BOARD_SIZE*BOARD_SIZE);
}
int main(void) {

    ios::sync_with_stdio(0);
    cin.tie(nullptr);   
    cout.tie(nullptr);

    int ans = -1;
    string str = "";

    for (int i = 0; i < BOARD_SIZE; ++i) 
    {
        for (int x,j = 0; j < BOARD_SIZE; ++j)
        {
            cin >> x;
            if (x == 0) {
                x = 9;
            }
            
            str += to_string(x);
        }
    }
    
    queue<PAIR> q;
    q.push({stoi(str), 0});
    visited.insert(stoi(str));

    while (!q.empty())
    {
        PAIR now = q.front(); q.pop();

        if (now.NUMBER == ANSWER) {
            ans = now.SWAP_CNT;
            break;
        }

        //9 포지션 구하기
        string nowString = to_string(now.NUMBER);
        int now_idx = nowString.find('9');

        for (int d = 0; d < DIR_SIZE; ++d)
        {
            if (d == RIGHT && (now_idx == 2 || now_idx == 5 || now_idx == 8)) 
                continue;
            else if (d == LEFT && (now_idx == 0 || now_idx == 3 || now_idx == 6))
                continue;

            int nxt_idx = now_idx + dir[d];

            if (!isSafe(nxt_idx)) 
                continue;
            
            nowString = to_string(now.NUMBER);
            swap(nowString[now_idx],nowString[nxt_idx]);
            
            int nxt_number = stoi(nowString);
            
            if (visited.find(nxt_number) != visited.end()) 
                continue;

            visited.insert(nxt_number);
            q.push({nxt_number, now.SWAP_CNT + 1});
        }
    }

    cout << ans << "\n";
    return 0;
}