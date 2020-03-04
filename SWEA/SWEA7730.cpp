#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
using ll = long long;

//height: 현재 설정한 높이 값
//answer: 필요한 원목의 길이
bool isAnswer(vector<int> &wood, ll height, int answer)
{
    ll result = 0;
    
    for (int wood_height : wood)
    {
        if (wood_height > height)
        {
            result += (wood_height - height);
        }
    }

    if (result >= answer) {
        return true;
    }
    else 
    {
        return false;
    }
}

//최대 설정 높이 H를 return
//answer: 필요한 원목의 길이
//max_height: input 중 가장 긴 나무의 높이 (= upper)
ll solve(vector<int> &wood, int answer, int max_height)
{
    ll ans;
    ll lower = 0, upper = max_height;

    while (abs(lower-upper) > 10) 
    {
        ll mid = (lower + upper) / 2;
        
        if (isAnswer(wood, mid, answer))
        {
            lower = mid + 1;
        }
        else 
        {
            upper = mid;
        }
    }

    for (ll candidate = lower; candidate <= upper; ++candidate)
    {
        if (isAnswer(wood, candidate, answer)) 
        {
            ans = candidate;
        }
    }
    
    return ans;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	
	cin>>T;

	for(test_case = 1; test_case <= T; ++test_case)
	{
        int N,M, maxv = -1;
        vector<int> wood;
                
        cin >> N >> M;

        for (int x,loop = 0; loop < N; ++loop)
        {
            cin >> x;
            wood.push_back(x);
            maxv = max(maxv, x);
        }
	
        cout << "#" << test_case << " " << solve(wood, M, maxv) << "\n";
	}

	return 0;
}