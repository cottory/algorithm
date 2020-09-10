#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int IMPOSSIBLE = 987654321;
vector<vector<int>> weaks;

int solve(vector<int> members)
{
    int answer = IMPOSSIBLE;
    int mSize = members.size();

    for (vector<int> weak : weaks)
    {
        bool isPossible = true;
        int memberIdx = 0;
        int memberCoverSt = weak[0];
        int memberCoverEn = memberCoverSt + members[memberIdx];

        for (int i = 0; i < weak.size(); ++i)
        {
            if (memberCoverEn >= weak[i]) 
            {
                continue;
            }
            else
            {
                //memberConverEn < weak[i]ÀÎ »óÈ²
                memberIdx += 1;

                if (memberIdx >= mSize) 
                {
                    isPossible = false;
                    break;
                }

                memberCoverSt = weak[i];
                memberCoverEn = memberCoverSt + members[memberIdx];
            }
        }   

        if (isPossible == true)
            answer = min(answer,memberIdx + 1);
    }

    return answer;
}

int solution(int n, vector<int> weak, vector<int> dist) {

    int answer = IMPOSSIBLE;
    int wSize = weak.size();

    for (int idx = 0; idx < wSize; ++idx)
    {
        vector<int> candidate;
        for (int st = idx; st < idx + wSize; ++st)
        {
            if (st >= wSize) 
                candidate.push_back(weak[st % wSize] + n);
            else
                candidate.push_back(weak[st]);
        }

        weaks.push_back(candidate);
    }

    for (int state = 0; state < (1 << dist.size()); ++state)
    {
        int now = state;
        
        vector<int> candidate;
        for (int loop = 0; loop < dist.size(); ++loop)
        {
            if (now & (1 << loop)) 
            {
                candidate.push_back(dist[loop]);
            }
        }

        if (candidate.size() != 0)
        {
            sort(candidate.begin(), candidate.end());

            do 
            {
                answer = min(answer, solve(candidate));
            } while(next_permutation(candidate.begin(), candidate.end()));
        }
    }

    if (answer == IMPOSSIBLE)
    {
        answer = -1;
    }
    
    return answer;
}