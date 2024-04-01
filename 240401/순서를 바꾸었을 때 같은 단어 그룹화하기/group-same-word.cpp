#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>
#include <algorithm>

#define MAX_N 1001

using namespace std;

int n, maxGroupSize = 0;
string arr[MAX_N];

unordered_map<string, int> wordCntMap;

bool compare(pair<string, int>& p1, pair<string, int>& p2){
    return p1.second > p2.second;
}

int main() {
    cin>>n;
    for(int i = 0; i < n; ++i){
        cin>>arr[i];
        sort(arr[i].begin(), arr[i].end());
        ++wordCntMap[arr[i]];

        if(maxGroupSize < wordCntMap[arr[i]]){
            maxGroupSize = wordCntMap[arr[i]];
        }
    }

    // vector<pair<string, int>> vecWordCntMap(wordCntMap.begin(), wordCntMap.end());
    // sort(vecWordCntMap.begin(), vecWordCntMap.end(), compare);
    // cout<<vecWordCntMap[0].second;

    cout<<maxGroupSize;

    return 0;
}