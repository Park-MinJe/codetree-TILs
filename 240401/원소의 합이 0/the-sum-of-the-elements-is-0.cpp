#include <iostream>
#include <vector>
#include <unordered_map>

#define MAX_N 5001

using namespace std;

int n, cntZeroSum = 0,
    tmpArr[4][MAX_N];
unordered_map<int, int> cnt[4];
unordered_map<int, int> twoSumCnt[2];   // A+B, C+D 경우의 수
unordered_map<int, int> totalSumCnt;    // (A+B)+(C+D) 경우의 수

int main() {
    cin>>n;
    for(int i = 0; i < 4; ++i){
        for(int j = 0; j < n; ++j){
            cin>>tmpArr[i][j];
            ++cnt[i][tmpArr[i][j]];
        }
    }
    
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            int tmpSumAB = tmpArr[0][i] + tmpArr[1][j],
                tmpSumCD = tmpArr[2][i] + tmpArr[3][j],
                tmpCntAB = cnt[0][tmpArr[0][i]] * cnt[1][tmpArr[1][j]],
                tmpCntCD = cnt[2][tmpArr[2][i]] * cnt[3][tmpArr[3][j]];
            for(int k = 0; k < 4; ++k){
                --cnt[k][tmpArr[k][i]];
            }
            twoSumCnt[0][tmpSumAB] += tmpCntAB;
            twoSumCnt[1][tmpSumCD] += tmpCntCD;
        }
    }

    unordered_map<int, int>::iterator itAB;
    unordered_map<int, int>::iterator itCD;
    for(itAB = twoSumCnt[0].begin(); itAB != twoSumCnt[0].end(); ++itAB){
        for(itCD = twoSumCnt[1].begin(); itCD != twoSumCnt[1].end(); ++itCD){
            if(itAB->first + itCD->first == 0){
                ++cntZeroSum;
            }
            --(itAB->second);
            --(itCD->second);
        }
    }
    cout<<cntZeroSum;

    return 0;
}