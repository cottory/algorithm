#include <string>
#include <vector>
#include <stack>
using namespace std;

// ( : left 
// ) : right
bool isBalanced(string str)
{
    if (str.compare("") == 0) return false;

    int left = 0, right = 0;
    
    for (char c : str)
    {
        if (c == '(') left++;
        else right++;
    }

    return left == right ? true : false;
}

bool isAnswer(string str)
{
    if (!isBalanced(str)) return false;

    if (str[0] == ')') return false;
    else
    {
        stack<char> s;
        
        for (char c : str)
        {
            if (c == '(')
            {
                s.push(c);
            }
            else 
            {
                if (!s.empty()) 
                {
                    s.pop();
                }
                else 
                    return false;
            }
        }

        if (s.empty()) return true;
        else return false;
    }
}

string solve(string str)
{
    //1
    if (str.compare("") == 0) return "";
    else 
    {
        string u = "";
        string v = "";
        
        //2. u와 v로 쪼개기
        for (int i = 2; i <= str.length(); i += 2)
        {
            u = str.substr(0, i);
            
            if (i != str.length())
                v = str.substr(i);

            if (isBalanced(u))
            {
                break;
            }
            else {
                //u가 균형잡힌 문자열이 아니라면, 이전에 쪼갰던 v를 빈 문자열로 초기화
                v = "";
            }
        }

        //3.
        if (isAnswer(u))
        {
            return u += solve(v);
        }
        else 
        {
            //4. u가 올바른 괄호 문자열이 아닌 경우

            string ret = "(";   //4-1
            ret += solve(v);    //4-2
            ret += ")"; //4-3

            string new_u = "";

            //4-4
            if (u.size() == 2)
            {
                new_u = "";
            }
            else 
            {
                //4-4
                int length = (int)u.size() - 2;
                new_u = u.substr(1, length);
            }
            
            //4-4
            for (int i = 0; i < new_u.size(); ++i)
            {
                if (new_u[i] == '(') new_u[i] = ')';
                else new_u[i] = '(';
            }

            ret += new_u;
            return ret;
        }
    }    
}

string solution(string p) {
    string answer = "";

    answer = solve(p);

    return answer;
}