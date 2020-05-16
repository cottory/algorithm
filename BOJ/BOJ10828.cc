#define STACK_SIZE 10005
#include <iostream>
using namespace std;

typedef struct STACK {
    int S[STACK_SIZE];
    int t, sz;

    STACK() : t(-1), sz(0) {}
    bool empty() {
        return t == -1 ? true : false;
    }
    int size() const {
        return sz;
    }
    void push(int val) {
        S[++t] = val;
        sz++;
    }
    int top() {
        if (empty()) return -1;
        else  return S[t];
    }
    int pop() {
        if (empty()) return -1;
        else {
            int ret = top();
            t--;
            sz--;
            return ret;
        }
    }
    
}STACK;

int N;
int main(void) {

    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    STACK s;
    cin >> N;
    while (N--) {
        string cmd;
        int val;
        cin >> cmd;
        
        if (cmd.compare("push") == 0) {
            cin >> val;
            s.push(val);
        }
        else if (cmd.compare("top") == 0) {
            cout << s.top() << "\n";
        }
        else if (cmd.compare("size") == 0) {
            cout << s.size() << "\n";
        }
        else if (cmd.compare("empty") == 0) {
            cout << s.empty() << "\n";
        }
        else 
            cout << s.pop() << "\n";
    }

    return 0;
}