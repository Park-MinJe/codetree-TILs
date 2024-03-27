#include <iostream>
#include <string>

using namespace std;

int binary[8] = {1, 2, 4, 8, 16, 32, 64, 128};

int main() {
    string bi;
    cin>>bi;

    int dec = 0,
        biLen = bi.length();
    for(int i = 0; i < biLen; ++i){
        dec += (bi[i]-'0') * binary[biLen - i - 1];
    }

    printf("%d", dec);

    return 0;
}