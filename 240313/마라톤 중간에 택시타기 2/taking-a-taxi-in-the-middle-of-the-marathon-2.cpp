#include <iostream>
#include <vector>

#define INF 99999999

using namespace std;

class Coord{
public:
    int x, y;
    Coord(){}
    Coord(int ix, int iy): x(ix), y(iy){}
};

int n,
    originDist = 0,
    minDist = INF;
vector<Coord> lstBreakPoints;
int* lstDsts;

int calcDist(Coord start, Coord end){
    return abs(start.x-end.x) + abs(start.y-end.y);
}

void init(){
    scanf("%d", &n);
    lstDsts = new int[n];
    for(int i = 0;i < n; ++i){
        int tmpX, tmpY;
        scanf(" %d %d", &tmpX, &tmpY);
        lstBreakPoints.push_back(Coord(tmpX, tmpY));

        if(i > 0){
            lstDsts[i] = calcDist(lstBreakPoints[i-1], lstBreakPoints[i]);
            originDist += lstDsts[i];
        }
    }
}

void solve(){
    for(int i = 1; i < n-1; ++i){
        int tmpDist = originDist - lstDsts[i] - lstDsts[i+1] + calcDist(lstBreakPoints[i-1], lstBreakPoints[i+1]);
        if(minDist > tmpDist){
            minDist = tmpDist;
        }
    }
}

int main() {
    init();
    solve();
    printf("%d", minDist);
    return 0;
}