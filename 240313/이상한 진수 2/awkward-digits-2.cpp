#include <iostream>
#include <string>

using namespace std;

string a;
int square[10] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512};

void init(){
    cin>>a;
}

void solve(){
    int len = a.size(),
        max = 0;
    bool isFound = false;
    for(int i = 0; i < len; ++i){
        if(!isFound && a[i] == '0'){
            a[i] = '1';
            isFound = true;
        }
        if(a[i] == '1'){
            max += square[len-1-i];
        }
    }
    printf("%d", max);
}

int main() {
    init();
    solve();
    return 0;
}