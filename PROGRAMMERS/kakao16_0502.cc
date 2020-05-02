#include <string>
#include <vector>
#include <locale>
#include <algorithm>
#include <ctype.h>
#include <iostream>
using namespace std;

typedef struct _FILE {
    string origin_info;
    string head;
    string tail;
    int number;
    int id;
    _FILE(string _origin, string _head, int _number, string _tail, int _id) : 
        origin_info(_origin), head(_head), tail(_tail), number(_number), id(_id) {}
}_FILE;

bool comp(_FILE f1, _FILE f2)
{
    if (f1.head.compare(f2.head) == 0) 
    {
        if (f1.number == f2.number)
        {
            return f1.id < f2.id;
        }
        else
            return f1.number < f2.number;
    }
    else
        return f1.head < f2.head;
}

vector<_FILE> parseData(vector<string>& vs)
{
    vector<_FILE> ret;

    int str_id = 0;
    for (string info : vs)
    {
        int number;
        string header = "";
        string str_number;
        string tail;
        string origin_info;

        origin_info = info;
        str_id += 1;
        transform(info.begin(), info.end(), info.begin(), ::tolower);

        //parse_header
        int idx;
        for (idx = 0; idx < info.length(); ++idx)
        {
            if ('0' <= info[idx] && info[idx] <= '9')
                break;
            else
                header += info[idx];
        }

        //parse_number
        int st_point = idx;
        for (idx; idx <info.length(); ++idx)
        {
            if ('0' <= info[idx] && info[idx] <= '9')
                continue;
            else 
                break;
        }

        str_number = info.substr(st_point, idx-st_point);
        number = stoi(str_number);
        
        //parse_tail    
        tail = info.substr(idx);

        _FILE f(origin_info, header, number, tail, str_id);
        ret.push_back(f);        
    }

    return ret;
}

vector<string> reverse_parseData(vector<_FILE> vf)
{
    vector<string> ret;

    for (_FILE f : vf)
    {
        string str = f.origin_info;
        ret.push_back(str);
    }

    return ret;
}

vector<string> solution(vector<string> files) {
    vector<string> answer;
    vector<_FILE> fileList;

    //파싱
    fileList = parseData(files);

    //정렬
    sort(fileList.begin(), fileList.end(), comp);

    //리턴 데이터
    answer = reverse_parseData(fileList);

    return answer;
}