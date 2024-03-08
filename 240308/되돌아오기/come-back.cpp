#include <iostream>

using namespace std;

int n, dy = 0, dx = 0;

int main() {
    scanf("%d", &n);

    char* dir = new char[n];
    int* cost = new int[n];
    int sum = 0;
    for(int i = 0; i<n; ++i){
        scanf(" %c %d", &dir[i], &cost[i]);
    }
    int iter = 0;
    for(iter = 0; iter<n; ++iter){
        switch(dir[iter]){
        case 'W':
            if(dx > 0 && dx <= cost[iter] && dy == 0){
                sum += dx;
                dx = 0;
            }
            else{
                dx -= cost[iter];
                sum += cost[iter];
            }
            break;
        case 'S':
            if(dy > 0 && dy <= cost[iter] && dx == 0){
                sum += dy;
                dy = 0;
            }
            else{
                dy -= cost[iter];
                sum += cost[iter];
            }
            break;
        case 'N':
            if(dy < 0 && (dy + cost[iter]) >= 0 && dx == 0){
                sum += abs(dy);
                dy = 0;
            }
            else{
                dy += cost[iter];
                sum += cost[iter];
            }
            break;
        case 'E':
            if(dx < 0 && (dx + cost[iter]) >= 0 && dy == 0){
                sum += abs(dx);
                dx = 0;
            }
            else{
                dx += cost[iter];
                sum += cost[iter];
            }
            break;
        }
        // printf("%d %d\n", iter, sum);
        // printf("%c %d\n", dir[iter], cost[iter]);
        // printf("%d %d\n\n", dx, dy);
        if(dx == 0 && dy == 0) break;
    }

    if(iter >= n) {
        printf("%d", -1);
    }
    else {
        printf("%d", sum);
    }

    return 0;
}