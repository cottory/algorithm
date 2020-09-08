#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int OFFSET = 1000;

int parse2processingTime(string time)
{
    //0.001s ~ 3s
    int len = 0;
    for (int idx = 0; idx < time.size(); ++idx)
    {
        if (time[idx] != 's')
            len += 1;
    }
    
    string processingTime = time.substr(0,len);
    return (int)(stod(processingTime) * OFFSET);
}

int time2second(vector<string> time)
{
    int ret = 0;

    ret += stoi(time[0]) * 3600 * OFFSET;
    ret += stoi(time[1]) * 60 * OFFSET;
    ret += int(stod(time[2]) * OFFSET);
    
    return ret;
}

vector<int> getStart2End(int endTime, int processingTime)
{
    vector<int> ret;
    int startTime = (endTime - processingTime + 1);
    startTime = max(0, startTime);

    ret.push_back(startTime);
    ret.push_back(endTime);
    return ret;
}

vector<string> stringParser(string str, char delimiter)
{
    string token;
    stringstream ss(str);
    vector<string> result;

    while (getline(ss, token, delimiter))
    {
        result.push_back(token);
    }
    return result;
}

int solution(vector<string> lines) {

    //st_time, end_time;
    vector<vector<int> > result;

    for (string timeLog : lines)
    {
        //ex: "2016-09-15 00:00:00.000 3s"

        //2016-09-15
        //00:00:00.000
        //0.001s ~ 3s
        vector<string> LogInfo = stringParser(timeLog, ' ');

        //00
        //00
        //00.000
        vector<string> timeInfo = stringParser(LogInfo[1], ':');

        int endTime = time2second(timeInfo);
        int processingTime = parse2processingTime(LogInfo[2]);

        //startTime, endTime
        vector<int> candidate = getStart2End(endTime, processingTime);
        result.push_back(candidate);
    }

    int answer = 0;
    int rSize = result.size();
    for (int idx = 0; idx < rSize; ++idx)
    {
        int cnt = 1;
        int candidateTime = result[idx][1] + (OFFSET-1);

        for (int nxt = idx + 1; nxt < rSize; ++nxt)
        {
            if (result[nxt][0] <= candidateTime)
                cnt += 1;
        }

        answer = max(cnt,answer);
    }

    return answer;
}