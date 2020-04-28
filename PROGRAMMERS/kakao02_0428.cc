#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int solution(string s) {
    int answer = 987654321;

    if (s.size() == 1) return 1;

    for (int len = 1; len <= s.size() / 2; ++len)
    {
        string ret = "";

        int idx = 0;
        for (idx; idx < s.size(); ++idx) 
        {            
            if (idx + len > s.size())
            {
                ret += s.substr(idx);
                break;
            }

            string target = s.substr(idx,len);

            int nxt, cnt = 0;
            for (nxt = idx; (nxt + len) <= s.size(); nxt += len)
            {
                if (target.compare(s.substr(nxt, len)) == 0)
                {
                    cnt += 1;
                }
                else
                {
                    break;
                }
            }
            
            idx = nxt - 1;

            if (cnt != 1)
                ret += to_string(cnt);
            
            ret += target;

        }
    
        answer = min(answer, (int)ret.length());
    }
    
    return answer;
}

int main(void) {

    string str;
    cin >> str;

    cout << solution(str) << "\n";

    return 0;
}