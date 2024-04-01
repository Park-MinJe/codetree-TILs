#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#define MAX_N 100001

using namespace std;

int n, k;
long long arr[MAX_N];
unordered_map<long long, int> freq;

bool compare(pair<long long, int>& p1, pair<long long, int>& p2){
    return p1.second > p2.second;
}

int main() {
    cin>>n>>k;
    for(int i = 0; i < n; ++i){
        cin>>arr[i];
        ++freq[arr[i]];
    }

    vector<pair<long long, int>> vec(freq.begin(), freq.end());
    sort(vec.begin(), vec.end(), compare);
    for(int i = 0; i < k; ++i){
        cout<<vec[i].first<<" ";
    }
    return 0;
}