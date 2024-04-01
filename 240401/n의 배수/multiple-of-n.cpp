#include <iostream>

using namespace std;

int n;

int main() {
    cin>> n;
    for(int i = 1; i <= 200/n; ++i){
        if((n * i) % 10 == 0){
            break;
        }
        cout<<n * i<<" ";
    }
    return 0;
}