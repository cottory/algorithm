#include <iostream>
using namespace std;

int solution(int n)
{
    int ans = 0;
    
    while (n)
    {
        int r = n%2;
        ans += r;
        n /= 2;
    }

    return ans;
}