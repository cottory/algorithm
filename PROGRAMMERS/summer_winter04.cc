#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int W;
int idx = 0;

int set(int st, int en)
{
    if (st >= en) return 0;
    // st < en

    int rest = en - st;
    int q = rest / (2*W + 1);
    int r = rest % (2*W + 1);

    if (r == 0)
        return q;
    else 
        return q + 1;
}
int solution(int n, vector<int> stations, int w)
{
    W = w;
    int answer = 0;

    for (int pos : stations)
    {
        pos -= 1;

        if (idx > pos) {
            idx = pos + w + 1;
            continue;
        }

        answer += set(idx, pos - w);
        idx = pos + w + 1;
    }

    if (idx < n)
        answer += set(idx, n);   

    return answer;
}