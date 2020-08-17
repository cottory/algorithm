#define Tuple tuple<int,int,int>
#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <queue>
using namespace std;

const int DIR_SIZE = 8;
int dy[] = {-2,-2,-1,1, 2,2,1,-1};
int dx[] = {-1,1,2,2, 1,-1,-2,-2};

int T,L,stY,stX,enX,enY;

bool isSafe(int y, int x)
{
    return (0 <= y && y < L && 0 <= x && x < L);
}
int main(void) {

    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> T;

    while (T--)
    {
        cin >> L;
        cin >> stY >> stX >> enY >> enX;

        vector<vector<bool>> trip(L,vector<bool>(L,0));
        queue<Tuple> q;
        q.push(make_tuple(stY,stX,0));
        
        while (!q.empty())
        {
            Tuple now = q.front(); q.pop();
            int now_y,now_x,now_cnt;
            tie(now_y,now_x,now_cnt) = now;
            
            if (now_y == enY && now_x == enX) {
                cout << now_cnt << "\n";
                break;
            }

            for (int dir = 0; dir < DIR_SIZE; ++dir)
            {   
                int ny = now_y + dy[dir];
                int nx = now_x + dx[dir];

                if (!isSafe(ny,nx) || (trip[ny][nx]))
                    continue;
                
                trip[ny][nx] = true;
                q.push(make_tuple(ny,nx,now_cnt + 1));
            }
        }
    }
    
    return 0;
}