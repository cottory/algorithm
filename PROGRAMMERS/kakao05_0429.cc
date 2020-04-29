#define pdi pair<double, int>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> stage, userState;
vector<pdi> ans;

bool comp(pdi arg1, pdi arg2)
{
    if (arg1.first == arg2.first) {
        return arg1.second < arg2.second;
    }
    else return arg1.first > arg2.first;
}
vector<int> solution(int N, vector<int> stages) {
    vector<int> answer;

    stage.resize(N+2,0);
    userState.resize(N+2,0);

    for (int level : stages)
    {
        userState[level] +=1;
        
        for (int num = 1; num <= level; ++num)
        {
            stage[num] +=1;
        }
    }

    for (int level = 1; level < N + 1; ++level)
    {
        if (stage[level] == 0) {
            ans.push_back({0, level});
        }
        else {
            double ret = userState[level] / (double)stage[level];
            ans.push_back({ret, level});
        }
    }

    sort(ans.begin(), ans.end(), comp);

    for (pdi tmp : ans) 
    {
        answer.push_back(tmp.second);
    }
    
    return answer;
}