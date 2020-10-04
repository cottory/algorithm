#define DURA first
#define W second
#define Pair pair<int,int>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int N,ans;
vector<Pair> eggs;
vector<bool> isBroken;

void backtrack(int pick, vector<Pair>& nowEggs, int breakCount)
{
    if (pick == N)
    {
        ans = max(ans,breakCount);
        return;
    }

    if (isBroken[pick]) 
    {
        backtrack(pick+1,nowEggs,breakCount);
        return;
    }

    bool nowPick = false;

    //현재 내가 집은 계란은 안 깨진 상태
    for (int nxt = 0; nxt < N; ++nxt)
    {
        //자신은 제외
        if (pick == nxt)
            continue;

        //깨진 계란 제외
        if (isBroken[nxt])
            continue;

        //===============분기점===============
        //안 깨진 애들 중 하나를 골라서 shoot
        //1. CHANGE
        nowPick = true;
        nowEggs[pick].DURA -= nowEggs[nxt].W;
        nowEggs[nxt].DURA -= nowEggs[pick].W;

        int brokenCount = 0;
        bool pickChanged, nxtChanged;
        pickChanged = nxtChanged = false;
        
        if (nowEggs[pick].DURA <= 0) 
        {
            isBroken[pick] = true;
            pickChanged = true;
            brokenCount += 1;
        }
        if (nowEggs[nxt].DURA <= 0) 
        {
            isBroken[nxt] = true;
            nxtChanged = true;
            brokenCount += 1;
        }

        backtrack(pick + 1, nowEggs, breakCount + brokenCount);

        //2. ROLLBACK
        if (pickChanged)
        {
            isBroken[pick] = false;
        }
        if (nxtChanged)
        {
            isBroken[nxt] = false;
        }

        nowEggs[pick].DURA += nowEggs[nxt].W;
        nowEggs[nxt].DURA += nowEggs[pick].W;
        //===============분기점===============
    }

    //현재 깰 계란이 없으면 지금 계란 내려놓고 다음 계란 PICK
    if (nowPick == false) 
    {
        backtrack(pick+1,nowEggs,breakCount);
        return;
    }
}

int main(void) {

    cin >> N;
    isBroken.resize(N,false);

    for (int i = 0; i < N; ++i)
    {
        int d,w;
        cin >> d >> w;
        eggs.push_back(make_pair(d,w));
    }
    
    backtrack(0, eggs, 0);
    cout << ans << "\n";

    return 0;
}