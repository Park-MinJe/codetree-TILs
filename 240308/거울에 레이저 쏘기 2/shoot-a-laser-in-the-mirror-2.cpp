#include <iostream>

using namespace std;

int n, k,
    curY, curX,
    dir;    // 0-N, 1-E, 2-S, 3-W
char** map;

int main() {
    // 격자 크기
    scanf("%d", &n);
    // 맵의 정보
    map = new char*[n+1];
    for(int i = 1; i<=n; ++i){
        map[i] = new char[n+1];
    }
    for(int i = 1; i<n+1;++i){
        for(int j = 1;j<n+1;++j){
            scanf(" %c",&map[i][j]);
        }
    }
    // 쏘는 위치 K
    scanf("%d", &k);
    if(k >= 1 && k <= 3){
        curY = 1;
        curX = k;
        dir = 2;
    }
    else if(k>=4 &&k<=6){
        curX = n;
        curY = k-3;
        dir = 3;
    }
    else if(k>=7 && k<=9){
        curY = n;
        curX = 10-k;
        dir = 0;
    }
    else if(k>=10 && k<=12){
        curX = 1;
        curY = 13-k;
        dir = 1;
    }

    int cnt = 0;
    while(curX >= 1 && curX <= n && curY >= 1 && curY <= n){
        switch(dir){
        case 0: 
            if(map[curY][curX] == '/'){
                ++curX;
                dir = (dir+1)%4;
            }
            else if(map[curY][curX] == '\\'){
                --curX;
                dir = (dir+3)%4;
            }
            break;
        case 1:
            if(map[curY][curX] == '/'){
                --curY;
                dir = (dir+3)%4;
            }
            else if(map[curY][curX] == '\\'){
                ++curY;
                dir = (dir+1)%4;
            }
            break;
        case 2:
            if(map[curY][curX] == '/'){
                --curX;
                dir = (dir+1)%4;
            }
            else if(map[curY][curX] == '\\'){
                ++curX;
                dir = (dir+3)%4;
            }
            break;
        case 3:
            if(map[curY][curX] == '/'){
                ++curY;
                dir = (dir+3)%4;
            }
            else if(map[curY][curX] == '\\'){
                --curY;
                dir = (dir+1)%4;
            }
            break;
        }
        ++cnt;
    }

    printf("%d", cnt);

    return 0;
}