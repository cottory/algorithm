#include <iostream>
#include <algorithm>
#include <map>
#include <string>
#include <vector>
using namespace std;

map<string,vector<string>> state;
int main(void) {

    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t;
    cin >> t;
    
    while (t--)
    {
        state.clear();
        int N;
        cin >> N;

        for (int i = 0; i < N; ++i)
        {
            string cloth, clothType;
            cin >> cloth >> clothType;

            state[clothType].push_back(cloth);
        }

        int result = 1;

        for (auto s : state)
        {
            result *= (s.second.size() + 1);
        }

        result--;

        cout << result << "\n";
    }

    return 0;
}