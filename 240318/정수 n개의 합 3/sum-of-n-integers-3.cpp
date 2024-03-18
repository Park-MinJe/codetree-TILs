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
    for(int r = 0; r < n; ++r){
        for(int c = 0; c < n; ++c){
            scanf(" %d", &map[r][c]);
        }
    }
    
    for(int r = 0; r < n; ++r){
        for(int c = 0; c < n-k+1; ++c){
            if(c == 0){
                for(int l = 0; l < k; ++l){
                    partialSumByRow[r][c] += map[r][l];
                }
            }
            else{
                partialSumByRow[r][c] = partialSumByRow[r][c-1] - map[r][c-1] + map[r][c+k-1];
            }
            //debug
            //printf("%d ", partialSumByRow[r][c]);
        }
        //debug
        //printf("\n");
    }

    maxSum = 0;
    for(int c = 0; c < n-k+1; ++c){
        for(int r = 0; r < n-k+1; ++r){
            if(r == 0){
                for(int l = 0; l < k; ++l){
                    partialSum[r][c] += partialSumByRow[l][c];
                }
            }
            else{
                partialSum[r][c] = partialSum[r-1][c] - partialSumByRow[r-1][c] + partialSumByRow[r+k-1][c];
            }
            //debug
            //printf("%d ", partialSum[r][c]);
            if(maxSum < partialSum[r][c]){
                maxSum = partialSum[r][c];
            }
        }
        //debug
        //printf("\n");
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