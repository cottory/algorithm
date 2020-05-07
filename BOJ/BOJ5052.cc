#define TRIE_SIZE 10
#include <iostream>
#include <algorithm>
using namespace std;

typedef struct Trie {
    Trie *nextNode[TRIE_SIZE];
    bool finished;
    bool nextChild;

    Trie() {
        fill(nextNode, nextNode + TRIE_SIZE, nullptr);
        finished = nextChild = false;
    }
    ~Trie() {
        for (int loop = 0; loop < TRIE_SIZE; ++loop)
            delete nextNode[loop];
    }

    bool insert(string phoneNumber, int idx)
    {
        if (idx == phoneNumber.length())
        {
            finished = true;

            if (nextChild)
                return false;
            else 
                return true;
        }

        int num = phoneNumber[idx] - '0';

        if (!nextNode[num])
        {
            nextNode[num] = new Trie;
        }

        nextChild = true;

        bool ret = nextNode[num]->insert(phoneNumber, idx + 1);
        
        return !finished && ret;
    }
}Trie;

int main(void)
{
    ios::sync_with_stdio(0);

    cin.tie(nullptr);
    cout.tie(nullptr);

    int tc;
    cin >> tc;

    for (int n, t = 0; t < tc; ++t)
    {
        cin >> n;
        
        Trie *root = new Trie;
        bool ret = true;

        for (int loop = 0; loop < n; ++loop)
        {
            string phoneNumber;
            cin >> phoneNumber;

            bool chk = root->insert(phoneNumber, 0);

            if (!chk)
                ret = false;
        }

        if (ret)
            cout << "YES\n";
        else
            cout << "NO\n";

        delete root;
    }
    
    return 0;
}