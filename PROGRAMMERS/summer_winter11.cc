#define ll long long
#include<vector>
#include<cmath>
#include<algorithm>
#include<iostream>
using namespace std;

int N;
ll getCost(vector<vector<int> >& land, ll h, int P, int Q)
{
    ll ret = 0;

    for (int i = 0; i < N; ++i)
    for (int j = 0; j < N; ++j)
    {
        ll diff = h - (ll)land[i][j];
        if (diff == 0) continue;
        else if (diff > 0) {
            ret += ((ll)diff * (ll)P);
        }
        else {
            ret += ((ll)abs(diff) * (ll)Q);
        }
    }
    return ret;
}
long long solution(vector<vector<int> > land, int P, int Q) {
    ll answer = __LONG_LONG_MAX__;
    ll minv, maxv;
    minv = 9999999999;
    maxv = -1;

    N = land.size();

    for (int i = 0; i < N; ++i)
    for (int j = 0; j < N; ++j)
    {
        minv = min(minv,(ll)land[i][j]);
        maxv = max(maxv,(ll)land[i][j]);
    }
    
    ll st, en, mid, before;

    st = minv, en = maxv+1;
    
    while (st < en) {
        //mid means x position
        mid = (st + en) / 2;

        ll y1 = getCost(land, mid, P, Q);
        ll y2 = getCost(land, mid +1, P, Q);

        //(y1 == y2)  == (기울기 == 0)
        //기울기가 0이라면 최소 비용지점이므로 break
        if (y1 == y2) 
            break;
        else if (y1 < y2) 
            en = mid;
        else 
            st = mid + 1;
    }

    //오차가 있을 수 있음.
    for (int i = mid -1; i <= mid +1; ++i)
        answer = min(answer, getCost(land, i, P, Q));

    return answer;
}