#define TYPE first
#define AMOUNT second
#define Pair pair<int,int>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

const int EMPTY = 0;
const int LEFF = 1;
const int TROLL = 2;
int N;
bool ans;
vector<vector<int>> map;
vector<Pair> blockInfo;
vector<bool> visited;

void dfs(int node, int money)
{
    if (ans)
        return;

    if (node == N-1)
    {
        ans = true;
        return;
    }
    else
    {
        for (int idx : map[node])
        {   
            if (!visited[idx]) 
            {
                visited[idx] = true;
                Pair nxt = blockInfo[idx];

                if (nxt.TYPE == EMPTY)
                {
                    dfs(idx, money);
                }
                else if (nxt.TYPE == TROLL)
                {
                    if (money >= nxt.AMOUNT)
                    {
                        dfs(idx, money - nxt.AMOUNT);
                    }                
                }
                else 
                {
                    dfs(idx, max(money,nxt.AMOUNT));
                }

                visited[idx] = false;
            }
        }
    }
}

int main(void) 
{
    ios::sync_with_stdio(0);

    while (true)
    {
        cin >> N;

        if (N == 0)
        {
            break;
        }
        else
        {
            ans = false;

            for (int i = 0; i < map.size(); ++i)
                map[i].clear();
            
            map.clear();
            blockInfo.clear();
            visited.clear();

            map.resize(N);
            visited.resize(N,false);

            string str;
            getline(cin,str);

            for (int loop = 0; loop < N; ++loop)
            {
                string token;
                getline(cin,str);
                    
                vector<string> info;
                stringstream ss(str);
                
                while (getline(ss,token, ' '))
                {
                    info.push_back(token);
                }

                int type,amount;
                //info[0] == TYPE
                //info[1] == COUNT
                amount = stoi(info[1]);

                if (info[0].compare("E") == 0)
                {
                    type = EMPTY;
                }
                else if (info[0].compare("L") == 0)
                {
                    type = LEFF;
                }
                else 
                {
                    type = TROLL;
                }

                blockInfo.push_back({type,amount});


                if (info.size() <= 2)
                {

                }
                else
                {
                    for (int idx = 2; idx < (int)info.size() - 1; ++idx)
                    {
                        int nxt = stoi(info[idx]);
                        nxt--;
                        map[loop].push_back(nxt);
                    }
                }
            }

            visited[0] = true;
            dfs(0,0);

            if (ans)
                cout << "Yes\n";
            else
                cout << "No\n";

        }   
    }

    return 0;
}