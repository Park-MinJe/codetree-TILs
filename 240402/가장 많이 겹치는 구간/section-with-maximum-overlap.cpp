#include <iostream>
#include <tuple>
#include <vector>
#include <algorithm>

#define INF 999999999

using namespace std;

int n, x1, x2,
    minX = INF, maxX = 0,
    maxOverlapCnt;
vector<pair<int, int>> points;

int main() {
    cin>>n;
    for(int i = 0; i < n; ++i){
        cin>>x1>>x2;
        if(minX > x1) minX = x1;
        if(maxX < x2) maxX = x2;
        points.push_back(make_pair(x1, 1));
        points.push_back(make_pair(x2, -1));
    }
    sort(points.begin(), points.end());

    int tmpOverlapCnt;
    for(int i = 0; i <= 2*n; ++i){
        int curX, curV;
        tie(curX, curV) = points[i];

        tmpOverlapCnt = 0;
        for(int j = 0; j < 2*n; ++j){
            int x, v;
            tie(x, v) = points[j];
            if(x > curX)
                break;
            
            tmpOverlapCnt += v;
        }
        //debug
        //printf("%d::%d\n", i, tmpOverlapCnt);
        if(maxOverlapCnt < tmpOverlapCnt)
            maxOverlapCnt = tmpOverlapCnt;
    }
    cout<<maxOverlapCnt;
    return 0;
}