#include <string>
#include <vector>
#include <map>
#include <iostream>
using namespace std;

vector<string> dic_vector;
map<string, int> dic;
vector<int> solution(string msg) {
    vector<int> answer;

    for (int loop = 0; loop < 26; ++loop)
    {
        char c = 'A' + loop;
        string s = "";
        s += c;
        dic[s] = loop + 1;
    }

    //parseMsg
    int dic_index = dic.size();

    //가장 긴 문자열 찾기
    int msg_size = msg.length();
    int startIdx = 0;
    
    string before_str;
    int before_len;

    while (startIdx < msg_size)
    {
        int len = 1;
        before_len = len;
        while ((startIdx + len) <= msg_size)
        {
            string target = msg.substr(startIdx, len);

            if (dic.find(target) == dic.end())
                break;
            else
            {
                before_str = target;
                before_len = len;
                len += 1;
            }
        }

        //
        answer.push_back(dic[before_str]);

        //사전에 등록

        string new_str;
        if (startIdx + len > msg_size) 
        {
            break;
        }
        else
        {
            new_str = msg.substr(startIdx, len);
            dic[new_str] = dic_index + 1;
            dic_index += 1;
            dic_vector.push_back(new_str);

            //OFFSET JUMP
            startIdx += before_len;
        }
    }

    return answer;
}

int main(void)
{
    return 0;
}