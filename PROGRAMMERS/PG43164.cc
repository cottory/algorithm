#define SRC first
#define DST second
#define pss pair<string,string>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <iostream>
using namespace std;

vector<pss> ticketList;
vector<string> ans;
vector<bool> used;
bool isFindAnswer = false;

void dfs(vector<string> result, string airport, int ticketCount) 
{
    if (ticketCount == ticketList.size())
    {
        isFindAnswer = true;
        ans = result;
        return;
    }

    for (int i = 0; i < ticketList.size(); ++i)
    {
        if (used[i]) 
            continue;

        if (ticketList[i].SRC.compare(airport) == 0)
        {
            used[i] = true;
            vector<string> newResult = result;
            newResult.push_back(ticketList[i].DST);
            dfs(newResult, ticketList[i].DST, ticketCount + 1);

            if (!isFindAnswer) {
                used[i] = false;
            }
            else
                return;
        }       
    }
    return;
}

vector<string> solution(vector<vector<string>> tickets) {
    vector<string> answer;
    
    for (int i = 0; i < tickets.size(); ++i)
    {
        string src = tickets[i][0];
        string dst = tickets[i][1];
        ticketList.push_back({src,dst});
    }

    used.resize(tickets.size(), false);
    sort(ticketList.begin(), ticketList.end());

    vector<string> vs;
    dfs(vs, "ICN", 0);

    answer.push_back("ICN");
    for (string port : ans) {
        answer.push_back(port);
    }

    return answer;
}