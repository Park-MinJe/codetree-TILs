#include <iostream>

#define MAX_ROOMS 1003
#define INF 99999999

using namespace std;

int n, minSum = INF;
int rooms[MAX_ROOMS];

void init(){
    scanf("%d", &n);
    for(int i = 0; i < n; ++i){
        scanf(" %d", &rooms[i]);
    }
}

void solve(){
    for(int i = 0; i < n; ++i){
        int tmpSum = 0;
        for(int j = 0; j < n; ++j){
            int curRoomIdx = (i+j)%n;
            tmpSum += rooms[curRoomIdx] * j;
        }
        if(minSum > tmpSum){
            minSum = tmpSum;
        }
    }
}

int main() {
    init();
    solve();
    printf("%d", minSum);
    return 0;
}