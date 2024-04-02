#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

int n, maxOverlap = 0;
long long x1, x2;
vector<tuple<long long, int, int>> points;  // <x, v, idx>

int main() {
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

    int tmpOverlap = 0;
    sort(points.begin(), points.end());
    for(int i = 0; i < n*2; ++i){
        int x, v, idx;
        tie(x, v, idx) = points[i];

        tmpOverlap += v;
        if(maxOverlap < tmpOverlap)
            maxOverlap = tmpOverlap;
    }

    cout<<maxOverlap;

    return 0;
}