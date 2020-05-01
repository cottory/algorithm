#include <string>
#include <set>
#include <vector>
#include <iostream>
using namespace std;

bool isCandidateKey(vector<int>& keyList, int candidateKey)
{
    for (int key : keyList)
    {
        if ((key & candidateKey) == key) 
            return false;
    }
    return true;
}
int solve(vector<vector<string>>& relation, vector<int>& ans)
{
    vector<int> ret;
    int tuple_size = relation.size();
    int col_size = relation[0].size();

    for (int state = 0; state < (1 << col_size); ++state)
    {
        set<string> strSet;

        for (int i = 0; i < tuple_size; ++i)
        {
            string str = "";

            for (int loop = 0; loop < col_size; ++loop)
            {
                if (state & (1 << loop)) 
                {
                    str += relation[i][loop];
                }
            }

            if (!strSet.count(str))
                strSet.insert(str);
        }

        if (strSet.size() == tuple_size && (isCandidateKey(ans, state)))
        {
            ans.push_back(state);
        }
    }

    return ans.size();
}

int solution(vector<vector<string>> relation) {
    int answer = 0;
    vector<int> ans;
    answer = solve(relation, ans);

    return answer;
}