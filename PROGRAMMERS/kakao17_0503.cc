#define ll long long
#define pll pair<ll,ll>
#define TIME first
#define IDX second
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

bool compByIdx(pll f1, pll f2)
{
    return f1.second < f2.second;
}

int solution(vector<int> food_times, long long k) {
    int answer = -1;
    int size = food_times.size();
    vector<pll> foodList;

    for (int idx = 0; idx < food_times.size(); ++idx)
        foodList.push_back({food_times[idx], idx});

    sort(foodList.begin(), foodList.end());

    ll before = 0;
    ll now_idx = 0;

    while (now_idx < size)
    {
        ll now_time = foodList[now_idx].TIME;
        ll startIdx = now_idx;
        ll now_size = size - startIdx;

        while (now_idx + 1 < size && foodList[now_idx+1].TIME == now_time)
        {
            now_idx += 1;
        }

        if (k < ((now_time - before) * now_size))
        {
            sort(foodList.begin() + startIdx, foodList.end(), compByIdx);
            
            int offset = k % now_size;
            answer = foodList[startIdx + offset].IDX + 1;
            break;
        }
        
        k -= ((now_time - before) * now_size);
        before = now_time;
        now_idx += 1;
    }

    return answer;
}