#define pii pair<int,int>
#define MAX_NUMBER 100001
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

int used[MAX_NUMBER];   //특정 숫자 몇 개나왔는지 counting

vector<string> split_by_comma(string& s)
{
    vector<string> ret;
    string token;
    stringstream ss(s);

    while (getline(ss, token, ',')) 
    {
        ret.push_back(token);
    }

    return ret;
}

vector<string> eliminate_bracket(vector<string>& sc)
{
    vector<string> ret;

    for (string str : sc)
    {
        string s = "";

        for (int i = 0; i < str.length(); ++i)
        {
            if ('0' <= str[i] && str[i] <= '9')
                s += str[i];
        }
        ret.push_back(s);
    }
    return ret;
}

void counting_number(vector<string>& sc)
{
    for (string str : sc)
    {
        int num = stoi(str);
        used[num] += 1;
    }
}

vector<pii> calculate_order()
{
    vector<pii> ret;

    for (int i = 0; i < MAX_NUMBER; ++i)
    {
        if (used[i])
        {
            ret.push_back({used[i],i});
        }
    }

    return ret;
}

vector<int> _make_tuple(vector<pii> order)
{
    vector<int> ret;

    for (pii info : order)
    {
        ret.push_back(info.second);
    }

    return ret;
}
vector<int> solution(string s) {
    vector<int> answer;
    vector<pii> order;
    vector<string> string_container, string_container2;

    //split_by_comma
    string_container = split_by_comma(s);

    //eliminate_bracket
    string_container2 = eliminate_bracket(string_container);

    //counting
    counting_number(string_container2);

    //calculate_order
    order = calculate_order();
    
    sort(order.begin(), order.end(), greater<pii>());

    //make_tuple
    answer = _make_tuple(order);

    return answer;
}