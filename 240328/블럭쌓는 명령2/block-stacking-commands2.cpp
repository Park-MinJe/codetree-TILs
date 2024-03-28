#include <iostream>

#define MAX_N 101

using namespace std;

int n, k,
    arr[MAX_N];

int main() {
    int tmpA, tmpB;
    scanf("%d %d", &n, &k);
    for(int i = 0; i < k; ++i){
        scanf(" %d %d", &tmpA, &tmpB);
        for(int j = tmpA; j <= tmpB; ++j){
            ++arr[j];
        }
    }

    int _max = 0;
    for(int i = 1; i <= n; ++i){
        if(_max < arr[i]){
            _max = arr[i];
        }
    }
    printf("%d", _max);

    return 0;
}