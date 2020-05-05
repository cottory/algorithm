#include <string>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

set<int> s;

bool is_matching(string target, string banned)
{
    int tSize = target.length();
    int bSize = banned.length();
    if (tSize != bSize) return false;

    for (int idx = 0; idx < bSize; ++idx)
    {
        if ((banned[idx] != '*') && (target[idx] != banned[idx])) 
            return false;
    }

    return true;
}
int solution(vector<string> user_id, vector<string> banned_id) {
    int answer = 0;
    int uSize = user_id.size();
    
    vector<int> order;

    for (int loop = 0; loop < uSize; ++loop)
        order.push_back(loop);

    do {

        int state = 0;
        int cnt = 0;

        for (int idx = 0; idx < banned_id.size(); ++idx)
        {
            if (is_matching(user_id[order[idx]], banned_id[idx]))
            {
                cnt += 1;
                state += (1 << order[idx]);
            }
        }

        if (cnt == banned_id.size())
        {
            if (!s.count(state))
                s.insert(state);
        }

    } while (next_permutation(order.begin(), order.end()));

    answer = s.size();
    return answer;
}