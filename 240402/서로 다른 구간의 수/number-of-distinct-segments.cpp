#include <iostream>
#include <tuple>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

int n, ans = 0;
long long a, b;
vector<tuple<long long, int, int>> points;  // <좌표, +1/-1, idx>
unordered_set<long long> segs;

int main() {
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
    for(int i = 0; i < n*2; ++i){
        int x, v, idx;
        tie(x, v, idx) = points[i];
        if(v == 1){
            if(segs.empty()){
                ++ans;
            }
            segs.insert(idx);
        }
        else{
            segs.erase(idx);
        }
    }

    cout<<ans;

    return 0;
}