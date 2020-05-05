#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int MAX_WEIGHT = 200000000;

bool isPossible(vector<int>& stones, int k, int m)
{
    int cnt = 0;
    int maxv = -1;
    for (int i = 0; i < stones.size(); ++i)
    {
        if (stones[i] <= (m-1)) 
            cnt += 1;
        else
        {
            maxv = max(maxv, cnt);
            cnt = 0;
        }
    }

    maxv = max(cnt, maxv);
    return (maxv < k) ? true : false;
}

int binarySearch(vector<int>& stones, int k)
{
    int st = 1;
    int en = MAX_WEIGHT;
    int mid;

    while (st < en)
    {
        mid = (st + en) / 2;

        if (isPossible(stones, k, mid))
        {
            st = mid + 1;
        }
        else
        {
            en = mid;
        }        
    }

    return st - 1;
}
int solution(vector<int> stones, int k) {
    int answer = 0;

    answer = binarySearch(stones, k);
    return answer;
}