#include <iostream>
#include <map>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

int N,M,K;
map<int,int> upperJBNU, lowerJBNU;

vector<int> findKey(int key)
{
    map<int,int>::iterator uIter = upperJBNU.lower_bound(key);
    map<int,int>::iterator lIter = lowerJBNU.lower_bound(-key);

    int upperDiff = abs(key - uIter->first);
    int lowerDiff = abs(key - -(lIter->first));

    if (upperDiff > K && lowerDiff > K)
        return { };
    else if (upperDiff > K || lowerDiff > K)
    {
        if (upperDiff <= K)
        {
            return { uIter-> first }; 
        }
        else 
        {
            return { -(lIter->first) };
        }
    }
    //둘 다 K이하인 경우
    else if (upperDiff <= K && lowerDiff <= K)
    {
        if (upperDiff < lowerDiff)
            return { uIter->first };
        else if (lowerDiff < upperDiff)
            return { -(lIter->first) };
        else if ( uIter->first != -(lIter->first))
            return { uIter->first, -(lIter->first) };
    }
    
    return { };
}

void insertKey(int key, int val) 
{
    upperJBNU.insert({key,val});
    lowerJBNU.insert({-key,val});
    return;
}

void updateKey(int key, int val) 
{
    if (upperJBNU.count(key))
    {
        upperJBNU.insert({key,val});
        lowerJBNU.insert({-key,val});
    }
    else
    {
        vector<int> candidateKey = findKey(key);

        if (candidateKey.size() != 1) return;
        else
        {
            upperJBNU[candidateKey[0]] = val;
            lowerJBNU[-candidateKey[0]] = val;
        }
    }
    
}

void printKey(int key)
{
    if (upperJBNU.count(key))
    {
        cout << upperJBNU[key] << "\n";
    }
    else
    {
        vector<int> candidateKey = findKey(key);

        if (candidateKey.size() == 0) cout << -1 << "\n";
        else if (candidateKey.size() == 2) cout << "?\n";
        else if (candidateKey.size() == 1) cout << upperJBNU[candidateKey[0]] << "\n";
    }

    return;
}
int main(void) {

    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> M >> K;

    for (int i = 0; i < N; ++i)
    {
        int key, value;
        cin >> key >> value;
        insertKey(key, value);
    }

    while (M--)
    {
        int cmd,key,value;
        cin >> cmd;

        if (cmd == 1)
        {
            cin >> key >> value;
            insertKey(key,value);
        }
        else if (cmd == 2)
        {
            cin >> key >> value;
            updateKey(key,value);
        }
        else
        {
            cin >> key;
            printKey(key);
        }
    }

    return 0;
}