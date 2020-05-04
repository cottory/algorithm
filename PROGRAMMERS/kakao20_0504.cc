#define PLAYTIME first
#define IDX second
#define pii pair<int,int>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

//0: st
//1: en
//2: title
//3: melody
vector<vector<string> > infoList;
vector<pii> compList, ansList;

bool comp(pii p1, pii p2)
{
    if (p1.PLAYTIME == p2.PLAYTIME)
        return (p1.IDX < p2.IDX);
    else
        return (p1.PLAYTIME > p2.PLAYTIME);
}

string stretch_melody(string origin, int time)
{
    string ret = "";

    int len = origin.length();
    int q = time / len;
    int r = time % len;

    while(q--)
    {
        ret += origin;
    }   

    ret += (origin.substr(0, r));
    
    return ret;
}
int parse_time(string st, string en)
{
    int ret = 0;

    int st_hour, st_minute, en_hour, en_minute;

    st_hour = stoi(st.substr(0, 2));
    st_minute = stoi(st.substr(3, 2));

    en_hour = stoi(en.substr(0, 2));
    en_minute = stoi(en.substr(3, 2));
    
    ret = (60 * (en_hour - st_hour)) + (en_minute - st_minute);

    return ret;
}
string parse_melody(string str)
{
    //A#
    size_t idx;
    while ((idx = str.find("A#")) != string::npos)
    {
        str.replace(str.begin() + idx, str.begin() + (idx + 2), "H");
    }

    //C#
    while ((idx = str.find("C#")) != string::npos)
    {
        str.replace(str.begin() + idx, str.begin() + (idx + 2), "I");
    }

    //D#
    while ((idx = str.find("D#")) != string::npos)
    {
        str.replace(str.begin() + idx, str.begin() + (idx + 2), "J");
    }

    //F#
    while ((idx = str.find("F#")) != string::npos)
    {
        str.replace(str.begin() + idx, str.begin() + (idx + 2), "K");
    }

    //G#
    while ((idx = str.find("G#")) != string::npos)
    {
        str.replace(str.begin() + idx, str.begin() + (idx + 2), "L");
    }

    return str;
}

string solution(string m, vector<string> musicinfos) {
    string answer = "";

    for (string info : musicinfos)
    {   
        stringstream ss(info);
        string token;
        vector<string> vs;

        while (getline(ss, token, ','))
        {
            vs.push_back(token);
        }
        
        infoList.push_back(vs);
    }
    
    int idx = 0;
    for (vector<string> &info : infoList)
    {
        info[3] = parse_melody(info[3]);
        int _time = parse_time(info[0], info[1]);
        info[3] = stretch_melody(info[3], _time);
        compList.push_back({_time, idx});   
        idx += 1;
    }
   
    //find
    m = parse_melody(m);
    
    idx = 0;
    for (vector<string> &info : infoList)
    {
        if (info[3].find(m) != string::npos)
        {
            ansList.push_back(compList[idx]);
        }
        idx += 1;
    }
    
    if (ansList.empty())
    {
        answer = "(None)";
    }
    else
    {
        sort(ansList.begin(), ansList.end(), comp);
        answer = infoList[ansList[0].IDX][2];
    }
    
    return answer;
}