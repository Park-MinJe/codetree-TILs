#include <iostream>

using namespace std;

int n, m, r, c;
bool** isColored;
int* isComfort;

int diffX[4] = {0, 1, 0, -1};
int diffY[4] = {1, 0, -1, 0};
int isComfortable(){
    int cnt = 0;
    for(int i = 0; i<4; ++i){
        int tmpY = r+diffY[i],
            tmpX = c+diffX[i];
        if(tmpY<=0 || tmpY>n || tmpX<=0 || tmpX>n){
            continue;
        }
        if(isColored[tmpY][tmpX]){
            ++cnt;
        }
    }

    if(cnt == 3){
        return 1;
    }
    else{
        return 0;
    }
}

int main() {
    scanf("%d %d", &n, &m);
    isComfort = new int[m];
    isColored = new bool*[n+1];
    for(int i = 1; i <= n; ++i){
        isColored[i] = new bool[n+1];
        for(int j = 1; j <= n; ++j){
            isColored[i][j] = false;
        }
    }

    for(int i = 0; i<m; ++i){
        scanf("%d %d", &r, &c);
        isColored[r][c] = true;
        isComfort[i] = isComfortable();
    }

    for(int i = 0; i<m; ++i){
        printf("%d\n", isComfort[i]);
    }

    return 0;
}