#define SMALL_GARO 0    //()
#define BIG_GARO 1  //[]
#include <iostream>
#include <string>
#include <stack>
using namespace std;

int main(void) {

    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    while (true)
    {
        string line;
        getline(cin,line);
        if (line.compare(".") == 0)
        {
            break;
        }
        else
        {
            stack<int> garo;
            bool result = false;
            int i;

            for (i = 0; i < line.length(); ++i)
            {
                if (line[i] == '[')
                {
                    garo.push(BIG_GARO);
                }
                else if (line[i] == '(')
                {
                    garo.push(SMALL_GARO);
                }
                else if (line[i] == ']')
                {
                    if (garo.empty())
                        break;
                    else if (garo.top() != BIG_GARO)
                    {
                        break;
                    }
                    else
                    {
                        garo.pop();
                    }
                    
                }
                else if (line[i] == ')')
                {
                    if (garo.empty())
                        break;
                    else if (garo.top() != SMALL_GARO)
                    {
                        break;
                    }
                    else
                    {
                        garo.pop();
                    }
                }
            }

            if (i == line.length() && garo.empty())
            {
                result = true;
            }
            
            if (result) cout << "yes\n";
            else cout << "no\n";
        }
    }
    

    return 0;
}