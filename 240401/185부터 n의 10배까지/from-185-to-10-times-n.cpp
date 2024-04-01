#include <iostream>

#define START 185

using namespace std;

int n, nX10;

int totalSum(){
    return (nX10+1)*nX10/2 - START*(START-1)/2;
}

double totalMean(int sum){
    return (double)sum / (double)(nX10-START+1);
}

int main() {
    cin>>n;
    nX10 = n*10;
    int sum = totalSum();
    double mean = totalMean(sum);
    printf("%d %.1lf", sum, mean);
    return 0;
}