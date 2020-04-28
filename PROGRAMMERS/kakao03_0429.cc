#include <string>
#include <stack>
#include <queue>
#include <vector>
using namespace std;

vector<int> func(int n, int num)
{
    vector<int> ret;
    stack<int> s;

    while (num)
    {
        s.push(num % 2);
        num /= 2;
    }
    
    while (s.size() < n)
    {
        s.push(0);
    }

    while (!s.empty())
    {
        ret.push_back(s.top());
        s.pop();
    }

    return ret;
}

vector<string> intToStr(vector<vector<int> >& intArr)
{
    vector<string> ret;

    for (int i = 0; i < intArr.size(); ++i)
    {
        string s = "";
        for (int j = 0; j < intArr[i].size(); ++j)
        {
            if (intArr[i][j]) s += "#";
            else s += " ";
        }
        ret.push_back(s);
    }
    return ret;
}

vector<string> solution(int n, vector<int> arr1, vector<int> arr2) {
    vector<string> answer;
    vector<vector<int> > intArr(n, vector<int>(n,0));

    for (int i = 0; i < arr1.size(); ++i)
    {
        vector<int> v = func(n, arr1[i]);
        for (int j = 0; j < v.size(); ++j)
        {
            intArr[i][j] += v[j];
        }
    }

    for (int i = 0; i < arr2.size(); ++i)
    {
        vector<int> v = func(n, arr2[i]);
        for (int j = 0; j < v.size(); ++j)
        {
            intArr[i][j] += v[j];
        }
    }
    
    answer = intToStr(intArr);
    return answer;
}