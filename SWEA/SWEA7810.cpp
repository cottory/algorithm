#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
 
bool check(vector<int> &arr, int num)
{
    int cnt = 0;
 
    for (int number : arr)
    {
        if (number >= num)
        {
            cnt += 1;
        }
    }    
 
    if (cnt >= num) return true;
    else return false;
}
 
int solve(vector<int> &arr, int maxv)
{
    int lower = 0, upper = maxv, ans = -1;
     
    while (lower <= upper)
    {
        int mid = (lower + upper) / 2;
 
        if (check(arr, mid))
        {
            ans = mid;
            lower = mid + 1;
        }
        else
        {
            upper = mid - 1;
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
        int N, maxv = -1;
        vector<int> num;
 
        cin >> N;
 
        for (int x,loop = 0; loop < N; ++loop)
        {
            cin >> x;
            maxv = max(maxv, x);
            num.push_back(x);
        }
         
        cout << "#" << test_case << " " << solve(num, maxv) << "\n";               
    }
 
    return 0;
}