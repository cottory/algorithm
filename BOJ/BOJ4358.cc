#define TRIE_SIZE 128
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int total;
char tree[35];

typedef struct Trie {
    Trie *nextNode[TRIE_SIZE];
    int cnt;

    Trie() {
        fill(nextNode, nextNode + TRIE_SIZE, nullptr);
        cnt = 0;
    }

    ~Trie() {
        for (int i = 0; i < TRIE_SIZE; ++i)
            delete nextNode[i];
    }

    void insert(char *key)
    {
        if (*key == '\0') {
            cnt += 1;
            total += 1;
            return;
        }

        int nxt = *key;

        if (nextNode[nxt] == nullptr)
            nextNode[nxt] = new Trie;            

        nextNode[nxt]->insert(key + 1);
    }

    void printiTree(int idx)
    {
        if (cnt > 0) {
            tree[idx] = '\0';
            cout << tree << " " << 100 * cnt / (double)total << "\n";
        }

        for (int nxt = 0; nxt < TRIE_SIZE; ++nxt)
        {
            if (nextNode[nxt])
            {
                tree[idx] = nxt;
                nextNode[nxt]->printiTree(idx + 1);
            }
        }
    }
}Trie;

int main(void)
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cout << fixed;
    cout.precision(4);
    Trie *root = new Trie;

    while (cin.getline(tree, 35)) {
        root->insert(tree);
    }

    root->printiTree(0);
    return 0;
}

