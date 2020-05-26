#define ll long long
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

ll G;
vector<ll> ans;
int main(void) {

    cin >> G;

    int loopSize = 50001;
    
    ll st,en;

    st = en = 1;

    while (en <= loopSize) {

        if (en*en - st*st == G)   
            ans.push_back(en);    

        if (en*en - st*st <= G) 
            en++;
        else if (en*en - st*st > G)
            st++;
    }

    if (ans.size()) {
        sort(ans.begin(), ans.end());
        for (ll num : ans)
            cout << num << "\n";
    }
    else cout << -1 << "\n";

    return 0;
}