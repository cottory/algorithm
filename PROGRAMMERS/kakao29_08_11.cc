#define ALPHA_SIZE 26
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

typedef struct Trie {
    Trie* next[ALPHA_SIZE];
    bool finished;
    int hasNext;

    Trie() {
        fill(next, next + ALPHA_SIZE, nullptr);
        finished = false;
        hasNext = 0;
    }

    ~Trie(){
        for (int i = 0; i<ALPHA_SIZE; i++){
            if (next[i])
                delete next[i];
        }
    }

    void insert(const char *key)
    {
        if (*key == '\0')
        {
            finished = true;
            return;
        }

        int idx = (*key) - 'a';
        if (next[idx] == nullptr)
        {
            next[idx] = new Trie();
        }
        
        next[idx]->insert(key+1);
        hasNext += 1;
    }

    int find(const char *key)
    {
        if (*key == '\0')
        {
            if (finished) return 1;
            else return 0;
        }

        int idx = (*key) - 'a';

        if (*key == '?')
        {
            int result = 0;
            for (int i = 0; i < ALPHA_SIZE; ++i)
            {
                if (next[i] != nullptr)
                {
                    result += next[i]->hasNext;
                }
            }
            return result;
        }
        
        if (next[idx] == nullptr)
        {
            return 0;
        }
            
        if ((*(key+1)) == '?')
        {
            return next[idx]->hasNext;
        }
        else 
        {
            return next[idx]->find(key + 1); 
        }
    }

}Trie;

Trie* root[10001];
Trie* reverse_root[10001];

vector<int> solution(vector<string> words, vector<string> queries) {
    vector<int> answer;

    for (string word : words)
    {
        int wSize = word.size();
        if (root[wSize] == nullptr) 
        {
            root[wSize] = new Trie();
        }

        root[wSize]->insert(word.c_str());

        string reverse_word = word;
        reverse(reverse_word.begin(), reverse_word.end());
        if (reverse_root[wSize] == nullptr) 
        {
            reverse_root[wSize] = new Trie();
        }

        reverse_root[wSize]->insert(reverse_word.c_str());
    }

    for (string word : queries)
    {
        int wSize = word.size();
        if (word[0] == '?') 
        {
            if (reverse_root[wSize] == nullptr)
            {
                answer.push_back(0);
            }
            else 
            {
                reverse(word.begin(), word.end());
                answer.push_back(reverse_root[wSize]->find(word.c_str()));
            }
        }
        else 
        {
            if (root[wSize] == nullptr)
            {
                answer.push_back(0);
            }
            else 
            {
                answer.push_back(root[wSize]->find(word.c_str()));
            }
        }
    }

    return answer;
}