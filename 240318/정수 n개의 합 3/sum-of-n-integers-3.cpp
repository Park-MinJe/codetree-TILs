#include <iostream>

#define MAX_N 500

using namespace std;

int n, k,
    tmpSum = 0,
    maxSum = 0,
    map[MAX_N][MAX_N],
    partialSumByRow[MAX_N][MAX_N],
    partialSum[MAX_N][MAX_N];

void init(){
    scanf("%d %d", &n, &k);
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            scanf(" %d", &map[i][j]);
            if(j == 0){
                for(int l = 0; l < k; ++l){
                    partialSumByRow[i][j] += map[i][l];
                }
            }
            else if(j < n-k){
                partialSumByRow[i][j] = partialSumByRow[i][j-1] - map[i][j-1] + map[i][j+k-1];
            }
        }
    }

    maxSum = 0;
    for(int i = 0; i < n-k; ++i){
        for(int j = 0; j < n-k; ++j){
            for(int l = 0; l < k; ++l){
                partialSum[i][j] += partialSumByRow[i+l][j];
            }
            if(maxSum < partialSum[i][j]){
                maxSum = partialSum[i][j];
            }
        }
    }
}

// void solve(){
//     for(int i = 0; i < n-k; ++i){
//         for(int j = 0; j < n-k; ++j){
//             tmpSum = 0;
            

//             if(j != 0){

//             }
//         }
//     }
// }

int main() {
    init();
    printf("%d", maxSum);
    //solve();
    return 0;
}