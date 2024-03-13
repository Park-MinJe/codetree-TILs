#include <iostream>

using namespace std;

int n,
    maxSum = 0;
int** board;

int main() {
    scanf("%d", &n);
    board = new int*[n];
    for(int i = 0; i < n; ++i){
        board[i]=  new int[n];
    }
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            scanf(" %d", &board[i][j]);
        }
    }

    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n-2; ++j){
            int tmpSum = 0;
            for(int k = 0; k < 3; ++k){
                tmpSum += board[i][j+k];
            }
            if(maxSum < tmpSum){
                maxSum = tmpSum;
            }
        }
    }

    printf("%d", maxSum);
    
    return 0;
}