#include <iostream>
#include <string>

using namespace std;

int n;
string cmd;

int main() {
    cin>>cmd;

    int dir = 0,    // 0: 북, 1: 동, 2: 남, 3: 서
        dx = 0, 
        dy = 0;
    for(int i = 0; i < cmd.length(); ++i){
        switch(cmd[i]){
        case 'L':
            dir = (dir + 3) % 4;
            break;
        case 'R':
            dir = (dir + 1) % 4;
            break;
        case 'F':
            switch(dir){
            case 0:
                dy++;
                break;
            case 1:
                dx++;
                break;
            case 2:
                dy--;
                break;
            case 3:
                dx--;
                break;
            }
            break;
        }
    }

    printf("%d %d", dx, dy);
    
    return 0;
}