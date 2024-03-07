#include <iostream>

using namespace std;

int n, dx, dy;

int main() {
    char cmd;
    int len;

    dx = 0;
    dy = 0;
    scanf("%d", &n);
    for(int i = 0; i < n; ++i){
        scanf(" %c %d", &cmd, &len);
        //printf("%c %d\n", cmd, len);
        switch(cmd){
        case 'W':
            dx -= len;
            break;
        case 'S':
            dy -= len;
            break;
        case 'N':
            dy += len;
            break;
        case 'E':
            dx += len;
            break;
        }
        //printf("%d %d\n", dx, dy);
    }

    printf("%d %d", dx, dy);

    return 0;
}