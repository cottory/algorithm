#define Y first
#define X second
#define pii pair<int,int>
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

int solve(pii home, pii office, vector<pii>& client, vector<int>& order)
{
    int ret = 0;
    int cSize = client.size();
    int oSize = order.size();

    //first
    ret += abs(office.Y - client[order[0]].Y) + abs(office.X - client[order[0]].X);

    //middle
    for (int idx = 0; idx < oSize-1; ++idx)
    {
        ret += abs(client[order[idx]].Y - client[order[idx+1]].Y) + abs(client[order[idx]].X - client[order[idx+1]].X);
    }

    //last
    ret += abs(client[order[oSize-1]].Y - home.Y) + abs(client[order[oSize-1]].X - home.X);

    return ret;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;

	cin>>T;

	for(test_case = 1; test_case <= T; ++test_case)
	{
        int N, ans = 987654321;
        pii home, office;
        vector<pii> client;

        cin >> N;

        cin >> office.Y >> office.X >> home.Y >> home.X;
        client.resize(N);

        for (int y,x,loop = 0; loop<N; ++loop)
        {
            cin >> y >> x;
            client[loop].Y = y;
            client[loop].X = x;
        }

        //make permutation
        vector<int> order;
        
        for (int idx = 0; idx < N; ++idx)
        {
            order.push_back(idx);
        }
        
        do {

            ans = min(ans, solve(home, office, client, order));

        } while (next_permutation(order.begin(), order.end()));

        cout << "#" << test_case << " " << ans << "\n";
	}
    
	return 0;
}