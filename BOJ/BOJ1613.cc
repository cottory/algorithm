#include <iostream>
#include <vector>
using namespace std;

int N,K,S;
vector<vector<int>> eventTable;
vector<int> ans;

void floyd()
{
    for (int candidate = 0; candidate < N; ++candidate)
    {
        for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
        {
            if (eventTable[i][candidate] && eventTable[candidate][j])
                eventTable[i][j] = 1;
        }
    }
}
int main(void) {

    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> K;
    eventTable.resize(N, vector<int>(N,0));

    for (int before,after,i = 0; i < K; ++i)
    {
        cin >> before >> after;
        before--; after--;
        eventTable[before][after] = 1;
    }

    //floyd
    floyd();

    cin >> S;

    for (int event1, event2, loop = 0; loop < S; ++loop)
    {
        cin >> event1 >> event2;
        event1--; event2--;

        if (eventTable[event1][event2]) 
        {
            ans.push_back(-1);
        }
        else if (eventTable[event2][event1]) 
        {
            ans.push_back(1);
        }
        else
        {
            ans.push_back(0);
        }
    }

    for (int num : ans)
    {
        cout << num << "\n";
    }

    return 0;
}