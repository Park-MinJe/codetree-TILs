#include <iostream>

using namespace std;

int n, t, r, c, dirIdx;
char d;
char dir[4] = {'U', 'R', 'D', 'L'};

void setDirIdx(){
    switch(d){
    case 'U':
        dirIdx = 0;
        break;
    case 'R':
        dirIdx = 1;
        break;
    case 'D':
        dirIdx = 2;
        break;
    case 'L':
        dirIdx = 3;
        break;
    }
}

bool isBoarder(){
    switch(d){
    case 'U':
        if(r == n){
            return true;
        }
        return false;
        break;
    case 'R':
        if(c == n){
            return true;
        }
        return false;
        break;
    case 'D':
        if(r == 1){
            return true;
        }
        return false;
        break;
    case 'L':
        if(c == 1){
            return true;
        }
        return false;
        break;
    }
}

void calcDyDx(){
    switch(d){
    case 'U':
        ++r;
        break;
    case 'R':
        ++c;
        break;
    case 'D':
        --r;
        break;
    case 'L':
        --c;
        break;
    }
}

int main() {
    scanf("%d %d", &n, &t);
    scanf("%d %d %c", &r, &c, &d);

    // 방향 초기화
    setDirIdx();
    for(int i = 0; i < t; ++i){
        //printf("%d %c %d %d\n", i, d, r, c);

        if(isBoarder()){
            dirIdx = (dirIdx+2) % 4;
            d = dir[dirIdx];
            ++i;
            //printf("%d %c %d %d\n", i, d, r, c);
        }
        if(i >= t) break;
        calcDyDx();
    }

    printf("%d %d", r, c);

    return 0;
}