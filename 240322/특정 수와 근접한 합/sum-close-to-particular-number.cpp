#include <iostream>
#include <algorithm>

#define MAX_N 1001
#define INF 999999999

using namespace std;

int n, s, totalSum = 0, minDiff = INF,
    arr[MAX_N];

int main() {
    scanf("%d %d", &n, &s);
    for(int i = 0; i < n; ++i){
        scanf(" %d", &arr[i]);
        totalSum += arr[i];
    }
    sort(arr, arr+n);
    for(int i = 0; i < n; ++i){
        for(int j = i+1; j < n; ++j){
            int tmp = totalSum-(arr[i]+arr[j]),
                tmpDiff = abs(s - tmp);
            if(minDiff > tmpDiff)
                minDiff = tmpDiff;
        }
    }

    printf("%d", minDiff);
    return 0;
}