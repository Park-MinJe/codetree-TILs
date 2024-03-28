#include <iostream>

#define MAX_N 1001

using namespace std;

int n, k, front, _end, cnt = 0,
    arr[MAX_N];

int main() {
    scanf("%d %d", &n, &k);

    for(int i = 0; i < n; ++i){
        scanf(" %d", &arr[i]);
    }
    
    front = 0, _end = 0;
    int tmpSum = 0;
    for(; _end < n; ++_end){
        tmpSum += arr[_end];

        if(tmpSum > k){
            for(; front <= _end; ++front){
                tmpSum -= arr[front];
                if(tmpSum == k){
                    ++cnt;
                }
                else if(tmpSum < k){
                    break;
                }
            }
        }
        else if(tmpSum == k){
            ++cnt;
        }
    }
    printf("%d", cnt);
    return 0;
}