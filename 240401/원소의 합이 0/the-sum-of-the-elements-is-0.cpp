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
    
    for(int i = 0; i < 2; ++i){
        unordered_map<int, int>::iterator itA;
        unordered_map<int, int>::iterator itB;
        for(itA = cnt[i*2].begin(); itA != cnt[i*2].end(); ++itA){
            for(itB = cnt[i*2+1].begin(); itB != cnt[i*2+1].end(); ++itB){
                int tmpSumAB = itA->first + itB->first,
                    tmpCntAB = itA->second * itB->second;

                twoSumCnt[i][tmpSumAB] += tmpCntAB;
            }
        }
    }

    unordered_map<int, int>::iterator itAB;
    unordered_map<int, int>::iterator itCD;
    for(itAB = twoSumCnt[0].begin(); itAB != twoSumCnt[0].end(); ++itAB){
        int diff = -(itAB->first);
        if(twoSumCnt[1].find(diff) != twoSumCnt[1].end()){
            cntZeroSum += twoSumCnt[1][diff] * (itAB->second);
        }
        // for(itCD = twoSumCnt[1].begin(); itCD != twoSumCnt[1].end(); ++itCD){
        //     if(itAB->first + itCD->first == 0){
        //         cntZeroSum += itAB->second * itCD->second;
        //     }
        // }
    }
    cout<<cntZeroSum;

    return 0;
}