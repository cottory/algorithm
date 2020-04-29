#define OFFSET 65536
#define pii pair<int,int>
#include <string>
#include <algorithm>
#include <map>
#include <vector>
#include <locale>
using namespace std;

map<string,pii> strMap;
vector<string> pStr1, pStr2, interSect, uni;

string toLower_str(string str) 
{
    locale loc;
    string lower_str = "";
    for (int i = 0; i < str.size(); ++i)
    {
        if ('A' <= str[i] && str[i] <= 'Z')
            lower_str += tolower(str[i], loc);
        else 
            lower_str += str[i];
    }
    return lower_str;
}

bool isString(string str)
{
    if ('a' <= str[0] && str[0] <= 'z') {
        if ('a' <= str[1] && str[1] <= 'z') {
            return true;
        }
        else return false;
    }
    else return false;
}
vector<string> makePartString(string str)
{
    string lower_str = toLower_str(str);
    vector<string> ret;

    int len = lower_str.size();
    for (int i = 0; i < len - 1; ++i)
    {
        string subStr = lower_str.substr(i, 2);
        if (isString(subStr)) 
        {
            ret.push_back(subStr);
        }
    }

    return ret;
}

int solution(string str1, string str2) {

    int answer = 0;

    if (toLower_str(str1).compare(toLower_str(str2)) == 0)
    {
        return answer = OFFSET * 1;
    }

    pStr1 = makePartString(str1);
    pStr2 = makePartString(str2);

    //pStr1을 map에 input
    for (string str : pStr1)
    {
        if (strMap[str].first) {
            pii tmp = strMap[str];
            tmp.first += 1;
            tmp.second += 1;
            strMap[str] = tmp;
        }
        else {
            strMap[str] = {1,1};
        }
    }

    //pStr2와 map을 비교
    for (string str : pStr2)
    {
        if ((strMap.find(str) != strMap.end()) && strMap[str].second > 0)
        {
            strMap[str].second -= 1;
        }
        else {
            uni.push_back(str);
        }
    }
    
    //교집합 만들기, 합집합 만들기
    for (auto token : strMap)
    {
        int inter_cnt = token.second.first - token.second.second;
        int union_cnt = token.second.second;

        for (int loop = 0; loop < inter_cnt; ++loop) 
        {
            interSect.push_back(token.first);
        }

        for (int loop = 0; loop < union_cnt; ++loop) 
        {
            uni.push_back(token.first);
        }

    }

    for (string str : interSect)
    {
        uni.push_back(str);
    }

    answer = OFFSET * interSect.size();
    answer /= uni.size();
    
    return answer;
}