#define QUEUE_SIZE 100001
#include <iostream>
#include <string>
using namespace std;

typedef struct QUEUE {
    int Q[QUEUE_SIZE];
    int f, r, sz;
    QUEUE() {
        f = r = sz = 0;
    }
    bool empty() {
        return (f == r ? true : false);
    }
    int front() {
        if (empty()) return -1;
        else return Q[f];
    }
    int back() {
        if (empty()) return -1;
        else return Q[(r-1 + QUEUE_SIZE) % QUEUE_SIZE];
    }
    int pop() {
        if (empty()) return -1;
        else {
            int ret = Q[f];
            f = (f + 1) % QUEUE_SIZE;
            sz--;
            return ret;
        }
    }
    void push(int val) {
        Q[r] = val;
        sz++;
        r = (r + 1) % QUEUE_SIZE;
    }
    int size() const {
        return sz;
    }
}QUEUE;
int N;
int main(void) {

    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;
    QUEUE q;

    while (N--) {
        string cmd;
        int num;

        cin >> cmd;
        if (cmd.compare("push") == 0) {
            cin >> num;
            q.push(num);
        }
        else if (cmd.compare("pop") == 0) {
            cout << q.pop() << "\n";
        }
        else if (cmd.compare("size") == 0) {
            cout << q.size() << "\n";
        }
        else if (cmd.compare("empty") == 0) {
            cout << q.empty() << "\n";
        }
        else if (cmd.compare("front") == 0) {
            cout << q.front() << "\n";
        }
        else 
            cout << q.back() << "\n";
    }
    return 0;
}