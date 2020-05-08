#define ALPABET 26
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

typedef struct Trie{
    Trie *nextNode[ALPABET];
    bool finished;
    int child;
    
    Trie() {
        fill(nextNode, nextNode + ALPABET, nullptr);
        finished = false;
        child = 0;
    }
    ~Trie() {
        for (int loop = 0; loop < ALPABET; ++loop)
            delete nextNode[loop];
    }

    void insert(const char *key)
    {
        if (*key == '\0')
        {
            child += 1;
            finished = true;
            return;
        }

        int nxtIdx = *key - 'a';

        if (!nextNode[nxtIdx])
            nextNode[nxtIdx] = new Trie;

        child += 1;
        nextNode[nxtIdx]->insert(key + 1);
    }
    
}Trie;

int find(Trie *tree, const char *target, int idx)
{
    if (*target == '\0')
        return idx;    
    if (tree->child == 1) 
        return idx;

    int nxtIdx = *target - 'a';
    
    if (tree->nextNode[nxtIdx]) 
        return find(tree->nextNode[nxtIdx], target + 1, idx + 1);
}

int solution(vector<string> words) {
    int answer = 0;

    Trie *root = new Trie;

    for (string word : words)
        root->insert(word.c_str());

    for (string word : words)
        answer += find(root, word.c_str(), 0);

    return answer;
}
