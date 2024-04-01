#include <iostream>
#include <vector>
#include <unordered_map>

#define MAX_N 1001

using namespace std;

int n, k,
    arr[MAX_N];
vector<vector<int>> cases;
unordered_map<int, int> cnt;

// bool isAllUsed(){
//     unordered_map<int, bool>::iterator it;
//     for(it = isUsed.begin(); it != isUsed.end(); ++it){
//         if(!it->second){
//             return false;
//         }
//     }
//     return true;
// }

void searchCases(int curLen, vector<int> curCase, int curSum, unordered_map<int, bool> isUsed){
    if(curLen == 3){
        if(curSum == k)
            cases.push_back(curCase);
        return;
    }
    
    unordered_map<int, bool>::iterator it;
    for(it = isUsed.begin(); it != isUsed.end(); ++it){
        if(!it->second){
            it->second = true;
            curCase.push_back(it->first);
            searchCases(curLen+1, curCase, curSum+it->first, isUsed);
            //it->second = false;
            curCase.pop_back();
        }
    }
}

long long countTotalCases(){
    long long totalCnt = 0;
    vector<vector<int>>::iterator it;
    for(it = cases.begin(); it != cases.end(); ++it){
        long long tmpCnt = 1;
        for(int i = 0; i < 3; ++i){
            tmpCnt *= (long long)cnt[(*it)[i]];
        }
        totalCnt += tmpCnt;
    }
    return totalCnt;
}

int main() {
    unordered_map<int, bool> isUsed;

    cin>>n>>k;
    for(int i = 0; i < n; ++i){
        cin>>arr[i];
        ++cnt[arr[i]];
        isUsed[arr[i]] = false;
    }
    vector<int> tmpCase;
    // sol 1 - failed
    //searchCases(0, tmpCase, 0, isUsed);
    //cout<<countTotalCases();

    // sol 2 - 답안 내용
    long long ans = 0;
    for(int i = 0; i < n; ++i){
        cnt[arr[i]]--;

        for(int j = 0; j < i; ++j){
            if(cnt.count(k - arr[i] - arr[j]) > 0){
                ans += cnt[k - arr[i] - arr[j]];
            }
        }
    }
    cout<<ans;

    return 0;
}