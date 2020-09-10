#include <iostream>
#include <sstream>
using namespace std;

int main(void) {

    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string str,token;
    getline(cin,str);

    int idx = 0;
    while (str[idx] == ' ')
    {
        idx += 1;
    }

    str = str.substr(idx);

    stringstream ss(str);

    int cnt = 0;
    while (getline(ss, token, ' '))
    {
        cnt += 1;
    }

    cout << cnt << endl;
    return 0;
}