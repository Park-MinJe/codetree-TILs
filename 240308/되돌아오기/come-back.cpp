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
        // printf("%c %d\n", dir[i], cost[i]);
    }
    for(int i = 0; i<n; ++i){
        switch(dir[i]){
        case 'W':
            if(dx > 0 && dx <= cost[i] && dy == 0){
                sum += dx;
                dx = 0;
            }
            else{
                dx -= cost[i];
                sum += cost[i];
            }
            break;
        case 'S':
            if(dy > 0 && dy <= cost[i] && dx == 0){
                sum += dy;
                dy = 0;
            }
            else{
                dy -= cost[i];
                sum += cost[i];
            }
            break;
        case 'N':
            if(dy < 0 && (dy + cost[i]) >= 0 && dx == 0){
                sum += abs(dy);
                dy = 0;
            }
            else{
                dy += cost[i];
                sum += cost[i];
            }
            break;
        case 'E':
            if(dx < 0 && (dx + cost[i]) >= 0 && dy == 0){
                sum += abs(dx);
                dx = 0;
            }
            else{
                dx += cost[i];
                sum += cost[i];
            }
            break;
        }
        // printf("%d %d\n", i, sum);
        // printf("%d %d\n\n", dx, dy);
        if(dx == 0 && dy == 0) break;
    }

    printf("%d", sum);

    return 0;
}