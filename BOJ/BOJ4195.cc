#include <unordered_map>
#include <iostream>
#include <vector>
using namespace std;

int T,K;
unordered_map<string,string> parent;
unordered_map<string,int> child;

string find(string node)
{
    if ((parent.find(node) == parent.end()) || (parent[node].compare(node) == 0))
    {
        return parent[node] = node;
    }

    return parent[node] = find(parent[node]);
}

void setUnion(string f1, string f2)
{
    parent[f2] = f1;
    return;
}

int cntMember(string component1, string component2)
{
    if (child.find(component1) == child.end()) 
    {
        child[component1] = 1;
    }
    if (child.find(component2) == child.end())
    {
        child[component2] = 1;
    }

    if (component1.compare(component2) == 0)
        return child[component1];
    else 
    {
        child[component1] += child[component2];
        return child[component1];
    }
}
int main(void) {

    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> T;

    while (T--)
    {
        parent.clear();
        child.clear();

        cin >> K;

        for (int i = 0; i < K; ++i)
        {
            string f1, f2;
            cin >> f1 >> f2;
            
            //merge f1 and f2
            string compo1, compo2;

            compo1 = find(f1);
            compo2 = find(f2);

            setUnion(compo1, compo2);
            
            //count component 
            printf("%d\n",cntMember(compo1,compo2));
        }
    }

    return 0;
}


int cntMember(string f1, string f2)
{
    if (child.find(f1) == child.end()) 
    {
        child[f1] = 1;
    }
    if (child.find(f2) == child.end())
    {
        child[f2] = 1;
    }

    child[f1] += child[f2];
    return child[f1];
}