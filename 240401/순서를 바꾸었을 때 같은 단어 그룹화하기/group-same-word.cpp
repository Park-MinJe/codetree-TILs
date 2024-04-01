#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>
#include <algorithm>

#define MAX_N 1001

using namespace std;

int n, maxGroupSize = 0;
string arr[MAX_N];

// unordered_map<char, int> alphabetCntMap[MAX_N];
// bool isVisitedWord[MAX_N];

unordered_map<string, int> wordCntMap;

// bool isSameMap(unordered_map<char, int> m, unordered_map<char, int> trgtM){
//     int tmpAlphabetNum = m.size();

//     if(tmpAlphabetNum != trgtM.size())
//         return false;
    
//     unordered_map<char, int>::iterator itM;
//     for(itM = m.begin(); itM != m.end(); ++itM){
//         if(trgtM.find(itM->first) == trgtM.end()){    // 없으면
//             return false;
//         }
//         else{
//             if(itM->second != trgtM[itM->first]){
//                 return false;
//             }
//         }
//     }
//     return true;
// }

// void search(){
//     for(int i = 0; i < n; ++i){
//         if(!isVisitedWord[i]){
//             int tmpGroupSize = 1;

//             for(int j = i+1; j < n; ++j){
//                 if(!isVisitedWord[i] && isSameMap(alphabetCntMap[i], alphabetCntMap[j])){
//                     ++tmpGroupSize;
//                 }
//             }
//             if(maxGroupSize < tmpGroupSize)
//                 maxGroupSize = tmpGroupSize;
//         }
//     }
// }

bool compare(pair<string, int>& p1, pair<string, int>& p2){
    return p1.second > p2.second;
}

int main() {
    cin>>n;
    for(int i = 0; i < n; ++i){
        cin>>arr[i];
        sort(arr[i].begin(), arr[i].end());
        // isVisitedWord[i] = false;
        // for(int j = 0; j < arr[i].length(); ++j){
        //     ++alphabetCntMap[i][arr[i][j]];
        // }
        ++wordCntMap[arr[i]];
    }
    //search();
    //cout<<maxGroupSize;

    vector<pair<string, int>> vecWordCntMap(wordCntMap.begin(), wordCntMap.end());
    sort(vecWordCntMap.begin(), vecWordCntMap.end(), compare);
    cout<<vecWordCntMap[0].second;

    return 0;
}