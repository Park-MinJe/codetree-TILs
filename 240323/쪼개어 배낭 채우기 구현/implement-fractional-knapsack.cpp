#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>

using namespace std;

class Jerm{
public:
    int idx;
    double w, cost, costPerW;
    Jerm(){}
    Jerm(int iIdx, double iW, double iCost): idx(iIdx), w(iW), cost(iCost){
        costPerW = cost / w;
    }
    string toString(){
        return to_string(idx) + " " + to_string(w) + " " + to_string(cost) + " " + to_string(costPerW);
    }
};

bool CompJerm(Jerm& j1, Jerm& j2){
    return j1.costPerW > j2.costPerW;
}

int n;
long m;
double maxCost;
vector<Jerm> lstJerms;

int main() {
    scanf("%d %ld", &n, &m);

    int tmpW, tmpCost;
    for(int i = 0; i < n; ++i){
        scanf(" %d %d", &tmpW, &tmpCost);
        lstJerms.push_back(Jerm(i, tmpW, tmpCost));
    }
    sort(lstJerms.begin(), lstJerms.end(), CompJerm);
    //debug
    // for(int i = 0; i < n; ++i){
    //     cout<<lstJerms[i].toString() + "\n";
    // }
    vector<Jerm>::iterator it;
    for(it = lstJerms.begin(); it != lstJerms.end(); ++it){
        if((*it).w > m){
            // printf("%lf\n", (*it).cost * (m/(*it).w));
            maxCost += (*it).cost * (m/(*it).w);
            break;
        }
        else{
            maxCost += (*it).cost;
            m -= (*it).w;
            if(m == 0) break;
        }
        // cout << maxCost << "\n";
    }
    printf("%0.3lf", round(maxCost*1000)/1000);
    return 0;
}