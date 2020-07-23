#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

int countNumberOfWorkDone(vector<int>& cores, int time)
{
    int ret = cores.size();
    for (int i = 0; i < cores.size(); ++i)
        ret += (time / cores[i]);

    return ret;
}

int NumberOfThreadCanWork(vector<int>& cores, int time) 
{
    int ret = 0;
    for (int i = 0; i < cores.size(); ++i)
    {
        if (time % cores[i] == 0) 
            ret += 1;
    }

    return ret;
}
int solution(int n, vector<int> cores) {
    int answer = 0;

    int minv = 987654321, maxv = -1;
    int low, high, mid;

    for (int process_time : cores) {
        minv = min(minv, process_time);
        maxv = max(maxv, process_time);
    }

    low = (n * minv) / cores.size();
    high = (n * maxv) / cores.size();

    while (low < high) 
    {
        mid = (low + high) / 2;
        int workDone = countNumberOfWorkDone(cores, mid);   
        int numberOfThreadCanWork = NumberOfThreadCanWork(cores, mid);  

        if (workDone < n) 
        {
            low = mid + 1;
        }
        else if (n <= workDone - numberOfThreadCanWork)  
        {
            high = mid;
        } 
        else 
        {
            //현재 범위
            //(workDone - numberOfThreadCanWork) < n <= workDone
            int workCount = 0;
            int workShouldBeDone = n - (workDone - numberOfThreadCanWork);

            for (int i = 0; i < cores.size(); ++i)
            {
                if (mid % cores[i] == 0) {
                    workCount += 1;
                }

                if (workCount == workShouldBeDone) {
                    answer = i + 1;
                    return answer;
                }
            }            
        }
    }    

    return answer;
}