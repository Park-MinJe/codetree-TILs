#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>
#include <unordered_set>
#include <set>

#define INF_LL 9000000000000000000

using namespace std;

int n, ans = 0;
long long x, y, x1, x2,
    curY = INF_LL;  // 현재 가장 앞에 있는 선분의 Y 좌표
vector<tuple<long long, long long, int, int>> points;
            // <x, y, v, idx>
unordered_set<int> segs;
set<long long> ys;  // 겹치는 선분들의 y 좌표 (오름차순)

void init(){
    cin>>n;
    for(int i = 0; i < n; ++i){
        cin>>y>>x1>>x2;
        points.push_back(
            make_tuple(x1, y, 1, i)
        );
        points.push_back(
            make_tuple(x2, y, -1, i)
        );
    }
    sort(points.begin(), points.end());
}

void solve(){
    for(int i = 0; i < n*2; ++i){
        int v, idx;
        tie(x, y, v, idx) = points[i];

        if(v == 1){
            // if(segs.empty()){
            //     ++ans;
            // }

            ys.insert(y);
            if(curY > (*ys.begin())){
                // 현재 최소 y값이 변경될 때
                curY = (*ys.begin());
                ++ans;
            }

            segs.insert(idx);
        }
        else{
            ys.erase(y);
            segs.erase(idx);

            if(segs.empty()){
                curY = INF_LL;
            }
            else{
                if(curY == y){
                    curY = (*ys.begin());
                    ++ans;
                }
            }
        }

        //debug
        // printf("(%lld, %lld, %d, %d)::", x, y, v, idx);
        // printf("%d %lld\n", ans, curY);
    }
}

int main() {
    init();
    solve();
    cout<<ans;
    return 0;
}