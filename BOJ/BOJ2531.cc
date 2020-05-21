#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

int N,D,K,C, answer;
vector<int> food;
map<int,int> eated;
int main(void)
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> D >> K >> C;

    for (int num, i = 0; i < N; ++i)
    {
        cin >> num;
        food.push_back(num);
    }

    int st = 0, en = 0;
    int pick = 0;

    while (st < N)
    {
        if (pick < K) {

            if (eated.find(food[en]) != eated.end()) 
                eated[food[en]] += 1;
            else
                eated[food[en]] = 1;

            en = (en + 1) % N;
            pick += 1;
        }
        else if (pick >= K) {
            
            if (eated[food[st]] > 1) 
                eated[food[st]] -= 1;
            else 
                eated.erase(food[st]);

            st++;
            pick -= 1;
        }

        if (pick == K) {
            
            int candidate = 0;
            if (eated.find(C) != eated.end())
                candidate = eated.size();
            else
                candidate = eated.size() + 1;
            
            answer = max(answer, candidate);
        }
    }

    cout << answer << "\n";

    return 0;
}