#include <iostream>
#include <tuple>
#include <vector>
#include <algorithm>
#include <unordered_set>
//#include <set>
#include <unordered_map>

using namespace std;

int n;
long long x1, x2,
    totalSize = 0,
    ans = 0;
vector<tuple<long long, int, int>> points;  // <x, v, idx>
unordered_set<int> segs;
//set<tuple<int, long long, int, long long, long long>> overlaps;  // <overlaps, size, idx, start, end>
unordered_map<int, long long> overlaps;     // <idx, 겹치는 구간 size>

void init(){
    cin>>n;
    for(int i = 0; i < n; ++i){
        cin>>x1>>x2;
        points.push_back(
            make_tuple(x1, 1, i)
        );
        points.push_back(
            make_tuple(x2, -1, i)
        );
    }
    sort(points.begin(), points.end());
}

bool compareSize(pair<int, long long>& p1, pair<int, long long>& p2){
    return p1.second < p2.second;
}

void solve(){
    // 겹치는 선분의 개수와 그 구간을 구한다.
    long long preX = 1, curX = 1,
        startX = 0;
    int overlap = 0;
    for(int i = 0; i < n*2; ++i){
        long long x;
        int v, idx;
        tie(x, v, idx) = points[i];

        preX = curX;
        curX = x;

        if(overlap == 1){   // 겹치는 선분이 1일 때만
            overlaps[*segs.begin()] += curX - preX;
            // overlaps.insert(
            //     make_tuple(overlap, curX - preX, idx, preX, curX)
            // );
            //debug
            //printf("%d %lld %lld\n", overlap, preX, curX);
            // printf("set size = %d\n", overlaps.size());
            // printf("%d %lld %lld\n", *segs.begin(), preX, curX);
        }
        
        overlap += v;

        // 기존 영역의 총 길이
        if(v == 1){
            if(segs.empty()){
                startX = x;
            }
            segs.insert(idx);
        }
        else if(v == -1){
            segs.erase(idx);
            if(segs.empty()){
                totalSize += x - startX;
            }
        }
    }

    //debug
    // set<tuple<int, long long, int, long long, long long>>::iterator it;
    //  // <overlaps,      size, idx,     start,       end>
    // for(it = overlaps.begin(); it != overlaps.end(); ++it){
    //     printf("%d %lld %d %lld %lld\n", get<0>(*it), get<1>(*it), get<2>(*it), get<3>(*it), get<4>(*it));
    // }
    // unordered_map<int, long long>::iterator it;
    // for(it = overlaps.begin(); it != overlaps.end(); ++it){
    //     printf("%d %lld\n", it->first, it->second);
    // }

    // 겹치는 선분 수의 최솟값이 1이 아닌 경우
    // 어떤 선분을 제거해도 영역의 총 길이는 바뀌지 않는다.
    //debug
    // printf("total size = %lld\n", totalSize);
    if(overlaps.empty()){
        ans = totalSize;
    }
    else{
        vector<pair<int, long long>> vec(overlaps.begin(), overlaps.end());
        sort(vec.begin(), vec.end(), compareSize);
        ans = totalSize - vec[0].second;
    }
}

int main() {
    init();
    solve();
    cout<<ans;
    return 0;
}