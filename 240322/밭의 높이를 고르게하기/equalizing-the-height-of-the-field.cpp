#include <iostream>
#include <vector>

using namespace std;

int n, h, t, minCost, preCost;
vector<int> lstHeight;
vector<int> lstCost;

int calcCost(int curH){
    return abs(h-curH);
}

int main() {
    scanf("%d %d %d", &n, &h, &t);
    for(int i = 0; i < n; ++i){
        int tmp;
        scanf(" %d", &tmp);
        lstHeight.push_back(tmp);
        lstCost.push_back(calcCost(tmp));

        if(i < t){
            preCost += lstCost[i];
        }
    }
    minCost = preCost;

    for(int i = 1; i < n-t; ++i){
        
        preCost = preCost - lstCost[i-1] + lstCost[i+t-1];
        if(minCost > preCost){
            minCost = preCost;
        }
    }

    printf("%d", minCost);
    return 0;
}