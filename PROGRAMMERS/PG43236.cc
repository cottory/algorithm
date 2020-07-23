#include <string>
#include <vector>
#include <algorithm>
using namespace std;

bool isPossible(int distance, vector<int>& rocks, int n, int minDistance)
{
    int removeCnt = 0;
    int before = 0;
    
    for (int i = 0; i < rocks.size(); ++i)
    {
        int dist = rocks[i] - before;

        if (dist < minDistance) 
        {
            removeCnt += 1;
        }
        else 
        {
            before = rocks[i];
        }

    }

    if (distance - before < minDistance) 
        removeCnt += 1;

    return removeCnt <= n ? true : false;
}
int solution(int distance, vector<int> rocks, int n) {
    int answer = 0;
    int low, high, mid;
    sort(rocks.begin(), rocks.end());

    low = 0;
    high = distance;

    while (low < high)
    {
        mid = (low + high) / 2;

        if (isPossible(distance, rocks, n, mid)) 
        {
            low = mid + 1;
            answer = mid;
        }
        else 
        {
            high = mid;
        }
    }

    return answer;
}