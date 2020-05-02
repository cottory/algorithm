#include <string>
#include <vector>
#include <locale>
#include <map>
#include <algorithm>
#include <iostream>
using namespace std;

int cSize;
map<string,int> cache;

int solution(int cacheSize, vector<string> cities) {
    int answer = 0;

    if (cacheSize == 0)
        answer = 5 * cities.size();
    else
    {
        int _time = 0;
        for (string city : cities)
        {
            _time += 1;
            transform(city.begin(), city.end(), city.begin(), ::tolower);
            
            if (cache.find(city) != cache.end())
            {
                answer += 1;
                cache[city] = _time;
            }
            else
            {
                if (cache.size() == cacheSize)
                {
                    int minv = 987654321;
                    string minv_s;

                    for (auto& info : cache)
                    {
                        if (info.second < minv)
                        {
                            minv = info.second;
                            minv_s = info.first;
                        }
                    }

                    cache.erase(minv_s);
                }

                cache[city] = _time;
                answer += 5;
            }
        }
    }
    
    return answer;
}