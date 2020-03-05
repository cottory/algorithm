#include<iostream>
#include<deque>
#include<algorithm>
using namespace std;

int HowManyBoxesRequired(int weight)
{
    if (weight >= 50) return 1;
    else if (25 <= weight && weight < 50) return 2;
    else if (17 <= weight && weight < 25) return 3;
    else if (13 <= weight && weight < 17) return 4;
    else if (10 <= weight && weight < 13) return 5;
    else if (weight == 9) return 6;
    else if (weight == 8) return 7;
    else if (weight == 7) return 8;
    else if (weight == 6) return 9;
    else if (weight == 5) return 10;
    else if (weight == 4) return 13;
    else if (weight == 3) return 17;
    else if (weight == 2) return 25;
    else return 50;
}

int solve(deque<int> &boxes)
{
    int result = 0;

    while (!boxes.empty())
    {
        int now_box = boxes.back(); boxes.pop_back();
        int cnt = HowManyBoxesRequired(now_box) - 1;
        int rest = boxes.size();

        if (cnt > rest)
        {
            break;
        }
        else
        {
            for (int loop = 0; loop < cnt; ++loop)
            {
                boxes.pop_front();
            }
        } 

        result += 1;       
    }

    return result; 
}

int main(int argc, char** argv)
{
	int test_case;
	int T;

	cin>>T;
	
	for(test_case = 1; test_case <= T; ++test_case)
	{
        int N, ans = 0;
        deque<int> dq;

        cin >> N;
        for (int x,loop = 0; loop < N; ++loop)
        {
            cin >> x;
            dq.push_back(x);
        }
            
        sort(dq.begin(), dq.end());
        ans = solve(dq);

        cout << "#" << test_case << " " << ans << "\n";
	}

	return 0;
}