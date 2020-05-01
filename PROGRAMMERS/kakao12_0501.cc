#include <string>
#include <vector>
#include <stack>
using namespace std;

//10: A
//11: B
//12: C
//13: D
//14: E
//15: F
string convert_str = "ABCDEF";

string split_str(string target, int t, int m, int p)
{
    string answer = "";

    for (int idx = 0; idx < target.size(); idx += m)
    {  
       if (answer.size() == t) 
        break;

       string sub_str = target.substr(idx, m);

       answer += sub_str[p-1];
    }

    return answer;
}

char convert(int num)
{
    num %= 10;
    return convert_str[num];
}
string get_target_string(int n, int t, int m)
{
    string ret = "0";
    int loop = m * t;

    for (int num = 0; num <= loop; ++num)
    {
        stack<char> sc;

        int now = num;
        while (now)
        {
            int nxt = now % n;

            if (nxt > 9) {
                sc.push(convert(nxt));
            }
            else {
                char nxt_c = nxt + '0';
                sc.push(nxt_c);
            }

            now /= n;
        }

        while (!sc.empty())
        {
            ret += sc.top();
            sc.pop();
        }
    }

    return ret;
}
string solution(int n, int t, int m, int p) {
    string target_string, answer = "";
    target_string = get_target_string(n, t, m);
    answer = split_str(target_string, t, m, p);

    return answer;
}