#include <iostream>
#include <vector>

#define MIN_INF -999999998

using namespace std;

int n, maxSum = MIN_INF;
vector<int> arr;

int main() {
    scanf("%d", &n);
    for(int i = 0; i < n; ++i){
        int tmp;
        scanf(" %d", &tmp);
        arr.push_back(tmp);
    }
    int tmpSum = 0;
    for(int i = 0; i < n; ++i){
        tmpSum += arr[i];
        if(maxSum < tmpSum){
            maxSum = tmpSum;
        }
        if(tmpSum < 0){
            tmpSum = 0;
        }
    }

    printf("%d", maxSum);
    return 0;
}