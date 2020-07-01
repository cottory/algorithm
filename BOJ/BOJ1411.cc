#define ALPHABET_SIZE 26
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int N, cnt;
vector<string> vs, pick;
vector<bool> used;

bool solve(vector<string> candidate) {
    string a = candidate[0];
    string b = candidate[1];
    
    if (a.length() != b.length()) return false;

    vector<char> alpha(ALPHABET_SIZE + 5, '0');
    vector<bool> isUsed(ALPHABET_SIZE, false);
    vector<bool> isMatched(ALPHABET_SIZE, false);
    
    for (int i = 0; i < a.length(); ++i) {
        int idx = a[i] - 'a';
        if (!isUsed[idx]) {
            
            isUsed[idx] = true;

            int idx2 = b[i] - 'a';
            if (!isMatched[idx2]) {
                //타겟알파벳으로 변경
                isMatched[idx2] = true;
                alpha[idx] = b[i];
            }
            else {
                if (alpha[idx] == b[i]) continue;
                else return false;
            }  
        }
        else {
            if (alpha[idx] == b[i]) continue;
            else return false;
        }
    }

    return true;
}

void combination(int n, int r) {

    if (r == 2) {
        if (solve(pick))
            cnt++;

        return;
    }   
    if (n == vs.size()) 
        return;

    int idx = n;
    if (!used[idx]) {
        used[idx] = true;
        pick.push_back(vs[idx]);
        combination(n+1,r+1);
        pick.pop_back();
        used[idx] = false;
    }

    combination(n+1,r);
}
int main(void) {

    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;
    used.resize(N,false);
    for (int i = 0; i < N; ++i) {
        string s;
        cin >> s;
        vs.push_back(s);
    }

    //pick 2
    combination(0,0);
    cout << cnt << "\n";
    return 0;
}