#define USED first
#define NXT second
#define pbl pair<bool, ll>
#define ll long long
#include <string>
#include <set>
#include <map>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

typedef struct token {
    ll roomNumber, nxt;
    token(ll _num) : roomNumber(_num) {
        nxt = _num + 1;
    }
    token(ll _num, ll _nxt) : roomNumber(_num), nxt(_nxt) {}
}token;

map<ll, pbl> room_info;
map<ll, ll> parent;

ll find(ll num)
{
    if (room_info.find(num) == room_info.end())
        return num;
    else
        return parent[num] = find(parent[num]);
}

ll solve(ll num)
{
    // ll before = num;
    ll nxt = find(num);

    //room_info[num] == FALSE
    return nxt;
}

vector<long long> solution(long long k, vector<long long> room_number) {
    vector<long long> answer;

    for (ll num : room_number)
    {
        if (room_info.find(num) == room_info.end())
        {
            //make Node && push
            room_info[num] = {true, num + 1};
            parent[num] = num + 1;
            answer.push_back(num);
        }
        else
        {
            //process
            ll nxt = solve(num);
            room_info[nxt] = {true, nxt + 1};
            parent[nxt] = nxt + 1;
            answer.push_back(nxt);
        }
    }

    return answer;
}