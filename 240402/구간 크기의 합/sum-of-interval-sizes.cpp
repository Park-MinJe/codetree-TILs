#include <iostream>
#include <tuple>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

int n;
long long a, b, ans = 0;
vector<tuple<long long, int, int>> points;  // <x, v, idx>
unordered_set<int> segs;

void init(){
    cin>>n;
    for(int i = 0; i < n; ++i){
        cin>>a>>b;

        points.push_back(
            make_tuple(a, 1, i)
        );
        points.push_back(
            make_tuple(b, -1, i)
        );
    }

    sort(points.begin(), points.end());
}

void solve(){
    long long startX;
    for(int i = 0; i < n*2; ++i){
        long long x;
        int v, idx;
        tie(x, v, idx) = points[i];

        if(v == 1){
            if(segs.empty()){
                startX = x;
            }
            segs.insert(idx);
        }
        else{
            segs.erase(idx);
            if(segs.empty()){
                ans += x-startX;
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