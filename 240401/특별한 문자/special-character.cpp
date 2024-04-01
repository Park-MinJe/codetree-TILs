#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

class Data{
public:
    int firstIdx,
        cnt;
    Data(){}
};

string str;
unordered_map<char, Data> alphabetCntMap;

bool compare(pair<char, Data> p1, pair<char, Data> p2){
    return p1.second.cnt < p2.second.cnt
        || (p1.second.cnt == p2.second.cnt && p1.second.firstIdx < p2.second.firstIdx);
}

int main() {
    cin>>str;
    for(int i = 0; i < str.length(); ++i){
        if(alphabetCntMap.find(str[i]) == alphabetCntMap.end()){    // 처음
            alphabetCntMap[str[i]].firstIdx = i;
        }
        ++alphabetCntMap[str[i]].cnt;
    }

    vector<pair<char, Data>> vec(alphabetCntMap.begin(), alphabetCntMap.end());
    sort(vec.begin(), vec.end(), compare);
    if(vec[0].second.cnt == 1){
        cout<<vec[0].first;
    }
    else{
        cout<<"None";
    }
    
    return 0;
}