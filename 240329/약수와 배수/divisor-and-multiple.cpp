#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, k;
vector<int> arr;

void init(){
    scanf("%d", &n);
    arr.reserve(n);
    for(int i = 0; i < n; ++i){
        scanf(" %d", &arr[i]);
    }
    scanf(" %d", &k);

    sort(arr.begin(), arr.end());
}

int calcDiv(){
    int rt = 0;
    for(int i = 0; i < n; ++i){
        if(arr[i] > k){
            break;
        }
        if(k % arr[i] == 0){
            rt += arr[i];
        }
    }
    return rt;
}

int calcMult(){
    int rt = 0;
    for(int i = 0; i < n; ++i){
        if(arr[i] < k){
            continue;
        }
        if(arr[i] % k == 0){
            rt += arr[i];
        }
    }
    return rt;
}

int main() {
    init();
    printf("%d\n", calcDiv());
    printf("%d", calcMult());
    return 0;
}