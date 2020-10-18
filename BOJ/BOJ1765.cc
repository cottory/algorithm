#include <iostream>
#include <vector>
using namespace std;

int N,M,ans;
vector<vector<int>> friends,enemys;
vector<bool> isHaveTeams;

void dfs(int node)
{
    //search friends
    for (int i = 0; i < friends[node].size(); ++i)
    {
        int myFriend = friends[node][i];
        if (!isHaveTeams[myFriend])
        {
            isHaveTeams[myFriend] = true;
            dfs(myFriend);
        }
    }

    //search enemys
    for (int i = 0; i < enemys[node].size(); ++i)
    {
        int myEnemy = enemys[node][i];
        for (int j = 0; j < enemys[myEnemy].size(); ++j)
        {
            int myFriend = enemys[myEnemy][j];
            if (!isHaveTeams[myFriend])
            {
                isHaveTeams[myFriend] = true;
                dfs(myFriend);
            }
        }
    }

}
int main(void)
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> N >> M;
    friends.resize(N);
    enemys.resize(N);
    isHaveTeams.resize(N,false);

    for (int i = 0; i < M; ++i)
    {
        char relation;
        int a,b;
        cin >> relation >> a >> b;
        a--; b--;

        if (relation == 'F')
        {
            friends[a].push_back(b);
            friends[b].push_back(a);
        }
        else
        {
            enemys[a].push_back(b);
            enemys[b].push_back(a);
        }
    }

    for (int i = 0; i < N; ++i)
    {
        if (!isHaveTeams[i])
        {
            isHaveTeams[i] = true;
            ans += 1;
            dfs(i);
        }
    }

    cout << ans;

    return 0;
}