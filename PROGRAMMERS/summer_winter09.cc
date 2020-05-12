#include <vector>
#include <iostream>
#include <cmath>
using namespace std;

int answer = 0;
vector<int> ret;
vector<bool> used;

bool isPrime(int num)
{
    for (int i = 2; i <= sqrt(num); ++i)
    {
        if (num % i == 0)
            return false;
    }

    return true;
}

void combination(vector<int>& nums, int idx, int pick)
{
    if (idx == nums.size() && pick < 3)
        return;

    if (pick == 3)
    {
        int candidate = 0;
        for (int i = 0; i < ret.size(); ++i)
            candidate += ret[i];

        if (isPrime(candidate))
            answer += 1;

        return;
    }
    else
    {
        if (used[idx] == false)
        {
            used[idx] = true;
            ret.push_back(nums[idx]);
            combination(nums, idx + 1, pick + 1);
            ret.pop_back();
            used[idx] = false;
        }
        combination(nums, idx + 1, pick);
        return;
    }
}
int solution(vector<int> nums) {
    // [실행] 버튼을 누르면 출력 값을 볼 수 있습니다.
    used.resize(nums.size(), false);
    combination(nums, 0, 0);
    return answer;
}