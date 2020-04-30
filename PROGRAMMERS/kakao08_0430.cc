#define UID first
#define ACTION second
#define pss pair<string,string>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <queue>
using namespace std;

map<string,string> user_infor;
queue<pss> q;

vector<string> printQueue()
{
    vector<string> ret;

    while (!q.empty())
    {
        string message = "";
        string uid = q.front().UID;
        string action = q.front().ACTION;
        q.pop();

        if (action.compare("Enter") == 0) 
        {
            message += user_infor[uid];
            message += "님이 들어왔습니다.";
            ret.push_back(message);
        } 
        else if (action.compare("Leave") == 0)
        {
            message += user_infor[uid];
            message += "님이 나갔습니다.";
            ret.push_back(message);
        }        
        else 
        {
            continue;
        }
    }

    return ret;
}
pss parse_recod(string cmd)
{
    string token;
    stringstream ss(cmd);
    vector<string> str;
    //str[0]: action, str[1]: uid, str[2]: nickName
    
    while (getline(ss, token, ' '))
    {
        str.push_back(token);
    }

    if (str[0].compare("Leave") == 0) 
    {
    }   
    else 
    {
        //Global variable
        user_infor[str[1]] = str[2];
    }

    return {str[1], str[0]};
}

vector<string> solution(vector<string> record) {
    vector<string> answer;
    
    for (string cmd : record)
    {
        q.push(parse_recod(cmd));
    }
    
    answer = printQueue();

    return answer;
}