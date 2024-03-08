#include <iostream>
#include <string>

using namespace std;

string cmds;
int moveX[4] = {0, 1, 0, -1};
int moveY[4] = {1, 0, -1, 0};

int main() {
    cin>>cmds;

    // 처음 (0,0) 북쪽
    int curX = 0, curY = 0,
        i = 0,
        cnt = 0,
        dir = 0;    // 0-N, 1-E, 2-S, 3-W
    for(i = 0; i < cmds.size(); ++i){
        switch(cmds[i]){
        case 'L':
            dir = (dir+3)%4;
            break;
        case 'R':
            dir = (dir+1)%4;
            break;
        case 'F':
            curX += moveX[dir];
            curY += moveY[dir];
            break;
        }
        if(curX == 0 && curY == 0){
            ++i;
            break;
        }
    }

    if(i == cmds.size()){
        i = -1;
    }
    printf("%d", i);
    
    return 0;
}