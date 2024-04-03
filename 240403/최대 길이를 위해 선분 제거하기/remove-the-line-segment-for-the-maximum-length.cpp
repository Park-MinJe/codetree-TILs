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

    // 기존 영역의 총 길이-> 틀림. solv3에서 재정의
    // long long startX = 0;
    // for(int i = 0; i < n*2; ++i){
    //     long long x;
    //     int v, idx;
    //     tie(x, v, idx) = points[i];

    //     if(idx == i) continue;
        
    //     if(v == 1){
    //         if(segs.empty()){
    //             startX = x;
    //         }
    //         segs.insert(idx);
    //     }
    //     else{
    //         segs.erase(idx);
    //         if(segs.empty()){
    //             totalSize += x - startX;
    //         }
    //     }
    // }
}

bool compareSize(pair<int, long long>& p1, pair<int, long long>& p2){
    return p1.second < p2.second;
}

// 틀린 이유: 한 영역 또는 전체 영역을 모두 포함하는 구간이 존재하는 경우
void solve1(){
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
            printf("%d %lld %lld %lld\n", *segs.begin(), preX, curX, curX-preX);
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
    printf("total size = %lld\n", totalSize);
    if(overlaps.empty()){
        ans = totalSize;
    }
    else{
        vector<pair<int, long long>> vec(overlaps.begin(), overlaps.end());
        sort(vec.begin(), vec.end(), compareSize);
        ans = totalSize - vec[0].second;
    }
}

// 하나 씩 제외하면서 완전 탐색 -> 시간 초과
void solve2(){
    for(int i = 0; i < n; ++i){
        int tmpCnt = 0;
        long long startX = 0;
        for(int j = 0; j < n*2; ++j){
            long long x;
            int v, idx;
            tie(x, v, idx) = points[j];

            if(idx == i) continue;
            
            if(v == 1){
                if(segs.empty()){
                    startX = x;
                }
                segs.insert(idx);
            }
            else{
                segs.erase(idx);
                if(segs.empty()){
                    tmpCnt += x - startX;
                }
            }
        }
        if(ans < tmpCnt)
            ans = tmpCnt;
    }
}

// 선분 별로 겹치는 선분 수가 1인 구간 크기를 저장하고
// 전체 크기에서 해당 크기를 뺀 값 중 최대 값을 구한다.
void solve3(){
    // 겹치는 선분 수가 1인 구간의 선분 idx와 크기를 구한다.
    long long preX = 1, curX = 1;
    int overlap = 0;
    for(int i = 0; i < n*2; ++i){
        long long x;
        int v, idx;
        tie(x, v, idx) = points[i];

        preX = curX;
        curX = x;

        // 틀린 이유: 총 길이 구하는 데 오류
        if(!segs.empty()){
            totalSize += curX - preX;
        }

        if(overlap == 1){   // 겹치는 선분이 1일 때만
            overlaps[*segs.begin()] += curX - preX;
            // debug
            // printf("%d %lld %lld %lld\n", *segs.begin(), preX, curX, curX-preX);
        }
        
        overlap += v;
        if(v == 1){
            segs.insert(idx);
        }
        else if(v == -1){
            segs.erase(idx);
        }
    }

    // 해당 선분 구간에 선분 수가 1인 구간이 없는 경우 탐색
    // (total size를 그대로 쓰는 경우)
    for(int i = 0; i < n; ++i){
        if(overlaps.find(i) == overlaps.end()){
            ans = totalSize;
            return; // 종료
        }
    }
    
    // 겹치는 선분 수가 1인 구간이 가장 짧은 선분 제거
    vector<pair<int, long long>> vec(overlaps.begin(), overlaps.end());
    sort(vec.begin(), vec.end(), compareSize);
    ans = totalSize - vec[0].second;
}

int main() {
    init();
    // solve1();
    // solve2();
    solve3();
    // debug
    // printf("total size = %lld\n", totalSize);
    cout<<ans;
    return 0;
}