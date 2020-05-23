#define MAX_LEN 505
#define ALPABET 26
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;

typedef struct Trie {
    Trie *nextNode[ALPABET];
    bool finished;

    Trie() {
        fill(nextNode, nextNode + ALPABET, nullptr);
        finished = false;
    }
    ~Trie() {
        for (int loop = 0; loop < ALPABET; ++loop)
            delete nextNode[loop];
    }

    void insert(char *key)
    {
        if (*key == '\0')
        {
            finished = true;
            return;
        }

        int nxtIdx = *key - 'a';
        
        if (!nextNode[nxtIdx])
        {
            nextNode[nxtIdx] = new Trie;
        }
        
        nextNode[nxtIdx]->insert(key + 1);
    }
    
}Trie;

int N, M;

bool find(Trie* trie, char *key)
{
    if (*key == '\0') 
        return trie->finished;

    int nowIdx = *key - 'a';

    if (trie->nextNode[nowIdx])
    {
        return find(trie->nextNode[nowIdx], key + 1);
    }
    else
        return false;    
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> M;
    Trie *root = new Trie;

    for (int i = 0; i < N; ++i)
    {
        char s[MAX_LEN];
        cin >> s;
        root->insert(s);
    }
    
    int ans = 0;
    
    for (int q = 0; q < M; ++q)
    {
        char target[MAX_LEN];
        cin >> target;
        if (find(root, target))
            ans++;
    }

    cout << ans << "\n";
    
    return 0;
}