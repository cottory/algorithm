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

    //���� ���� ���� ����� �� ���� ����
    for (int nxt = 0; nxt < N; ++nxt)
    {
        //�ڽ��� ����
        if (pick == nxt)
            continue;

        //���� ��� ����
        if (isBroken[nxt])
            continue;

        //===============�б���===============
        //�� ���� �ֵ� �� �ϳ��� ��� shoot
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
        //===============�б���===============
    }

    //���� �� ����� ������ ���� ��� �������� ���� ��� PICK
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