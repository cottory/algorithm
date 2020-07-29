#define pis pair<int,string>
#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;

const int MOD = 10000;
const char dir[6] = {'D','S','L','R'};
int T;

int operation_D(int target)
{
    target *= 2;
    target = (target % MOD);
    return target;
}
int operation_S(int target)
{
    return target == 0 ? 9999 : target - 1;
}
int operation_L(int target)
{
    int ret = (target % 1000) * 10 + target / 1000;
    return ret;
}
int operation_R(int target)
{
    int ret = (target % 10) * 1000 + target / 10;
    return ret;
}
int calculate(int target, char cmd)
{
    switch (cmd) {
        case 'D':
            return operation_D(target);
        case 'S':
            return operation_S(target);
        case 'L':
            return operation_L(target);
        case 'R':
            return operation_R(target);
    }
}

string bfs(int source, int target) {

    queue<pis> q;
    int used[MOD];
    memset(used,0x0,sizeof(used));
    string ret;

    used[source] = 1; 
    q.push(make_pair(source,""));

    while (!q.empty())
    {
        pis now = q.front(); q.pop();
        
        if (now.first == target)
        {
            return now.second;
        }

        for (int d = 0; d < 4; ++d)
        {
            char direction = dir[d];
            int nxt = calculate(now.first,direction);

            if (!used[nxt]) 
            {
                used[nxt] = 1;
                string nxtState = now.second;
                nxtState += direction;
                q.push({nxt,nxtState});    
            }
        }
    }

    return ret;
}
int main(void) 
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> T;

    for (int test = 0; test < T; ++test)
    {
        int A, B;
        cin >> A >> B;
        cout<< bfs(A,B) << "\n";
    }

    return 0;
}