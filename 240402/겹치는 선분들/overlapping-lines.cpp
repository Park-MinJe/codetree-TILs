#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <unordered_set>

using namespace std;

int n, k;
long long preX, curX,
    inputX, ans = 0;
char dir;
vector<tuple<long long, int, int>> points;  // <x, v, idx>
unordered_set<int> segs;

void init(){
    preX = 0; curX = 0;
    cin>>n>>k;

    for(int i = 0; i < n; ++i){
        preX = curX;
        cin>>inputX>>dir;

        // 방향에 따라 좌표 갱신
        if(dir == 'R'){
            curX += inputX;
            points.push_back(
                make_tuple(preX, 1, i)
            );
            points.push_back(
                make_tuple(curX, -1, i)
            );
        } else if(dir == 'L'){
            curX -= inputX;
            points.push_back(
                make_tuple(curX, 1, i)
            );
            points.push_back(
                make_tuple(preX, -1, i)
            );
        }
    }

    // 좌표 순서대로 정렬
    sort(points.begin(), points.end());
}

void solve(){
    int preSegsSize = 0,
        curSegsSize = 0;
    long long 
        startX = 0,
        endX = 0;
    for(int i = 0; i < n*2; ++i){
        long x;
        int v, idx;
        tie(x, v, idx) = points[i];

        preSegsSize = curSegsSize;
        if(v == 1){
            segs.insert(idx);
            curSegsSize = segs.size();
            
            // 겹치는 선분 수 k 이상으로 증가
            if(preSegsSize < k && curSegsSize >= k){
                startX = x;
            }
        } else if(v == -1){
            segs.erase(idx);
            curSegsSize = segs.size();

            // 겹치는 선분 수 k 미만으로 감소
            if(preSegsSize >= k && curSegsSize < k){
                ans += x - startX;
            }
        }
    }
}

int main() {
    init();
    solve();
    cout<<ans;
    return 0;
}