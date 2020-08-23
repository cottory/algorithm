#include <iostream>
using namespace std;

unsigned int state = 0;
int N;

unsigned int add(int num) {
    return (state | (1 << num));
}

unsigned int remove(int num) {
    int candidate = (1 << num);
    candidate = ~candidate;
    return (state & candidate);
}

bool check(int num) {
    return (state & (1 << num)) > 0 ? true : false;
}

unsigned int toggle(int num) {
    int candidate = (1 << num);
    candidate = ~candidate;
    return (state ^ (1 << num));
}

unsigned int all() {
    int candidate = (1 << 21);
    return ~candidate;
}

unsigned int empty() {
    return 0;
}

int main(void) {

    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;
    while (N--)
    {
        string cmd;
        unsigned int num;
        cin >> cmd;

        if (cmd.compare("add") == 0) 
        {
            cin >> num;
            state = add(num);
        }
        else if (cmd.compare("remove") == 0)
        {
            cin >> num;
            state = remove(num);
        }
        else if (cmd.compare("check") == 0)
        {
            cin >> num;
            cout << check(num) << "\n";
        }
        else if (cmd.compare("toggle") == 0)
        {
            cin >> num;
            state = toggle(num);
        }
        else if (cmd.compare("all") == 0)
        {
            state = all();
        }
        else if (cmd.compare("empty") == 0)
        {
            //empty
            state = empty();
        }
    }

    return 0;
}