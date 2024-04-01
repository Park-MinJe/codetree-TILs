#include <iostream>

using namespace std;

int n;

int main() {
    cin>> n;
    for(int i = 1; i < 200.0/n; ++i){
        int nextN = n * i;
        cout<<n * i<<" ";
        if(nextN % 10 ==0) break;
    }
    return 0;
}