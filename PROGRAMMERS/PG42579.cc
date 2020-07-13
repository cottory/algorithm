#define pis pair<int,string>
#define tiii tuple<int,int,int>
#include <string>
#include <vector>
#include <map>
#include <tuple>
#include <iostream>
#include <algorithm>
using namespace std;

map<string,int> genresCnt, genresIdx;
vector<pis> vec;
vector<tiii> result;
vector<int> streamingCnt;
vector<int> solution(vector<string> genres, vector<int> plays) {
    
    vector<int> answer;
    const int pSize = plays.size();
    
    //1. Count Genre playList;
    for (int idx = 0; idx < pSize; ++idx) {
        string genre = genres[idx];
        int playCnt = plays[idx];
        
        if (genresCnt.find(genre) == genresCnt.end()) {
            genresCnt[genre] = playCnt;
        }
        else {
            genresCnt[genre] += playCnt;
        }
    }

    //음수로 내림차순 정렬을 위해 음수로 넣었음
    for (auto v : genresCnt) {
        pis now = make_pair(-v.second, v.first);
        vec.push_back(now);
    }
    
    sort(vec.begin(), vec.end());
    
    //재생횟수가 큰 장르가 idx값이 작음
    for (int idx = 0; idx < vec.size(); ++idx) {
        string genre = vec[idx].second;
        genresIdx[genre] = idx;
    }

    for (int loop = 0; loop < pSize; ++loop) {
        string genre = genres[loop];
        int priority = genresIdx[genre];
        result.push_back(make_tuple(priority, -plays[loop],loop));
    }

    sort(result.begin(), result.end());
    streamingCnt.resize(vec.size(), 0);

    for (tiii t : result) {
        int genreIdx = get<0>(t);
        int pk = get<2>(t);

        if (streamingCnt[genreIdx] < 2) {
            streamingCnt[genreIdx] += 1;
            answer.push_back(pk);
        }
    }

    return answer;
}