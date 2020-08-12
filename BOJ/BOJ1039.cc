#define NUMBER first
#define COUNT second
#define psi pair<string,int>
#include <iostream>
#include <string>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;

int K,nSize;
string N;
int visited[11][1000005];
queue<psi> q;

bool isPossible(string num)
{
    if (num[0] == '0')
        return false;

    if (num.size() == 2 && num[1] == '0')
        return false;
    
    return true;
}
int bfs()
{
    int ans = -1;
    q.push({N,0});

    while (true) 
    {
        int loop = q.size();
        memset(visited,0,sizeof(visited));

        if (loop == 0)
            break;

        while (loop--)
        {
            psi now = q.front(); q.pop();

            if (now.COUNT == K) {
                ans = max(ans,stoi(now.NUMBER));
            }
            else 
            {
                for (int i = 0; i < nSize-1; ++i)
                {
                    for (int j = i + 1; j < nSize; ++j)
                    {
                        string nxt = now.NUMBER;
                        swap(nxt[i],nxt[j]);

                        if (!isPossible(nxt))
                            continue;

                        int nxtNumber = stoi(nxt);
                        if (visited[now.COUNT + 1][nxtNumber]) 
                            continue;

                        visited[now.COUNT + 1][nxtNumber] = 1;
                        q.push({nxt,now.COUNT + 1});
                    }
                }   
            }

        }
    }

    return ans;
}

int main(void) {
    
    cin >> N >> K;
    nSize = N.size();
    
    cout << bfs() << "\n";
        
    return 0;
}