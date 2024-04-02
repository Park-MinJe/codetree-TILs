#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Op{
public:
    int size,
        leftX,
        rightX;
    char dir;
    Op(){}
    string toString(){
        return to_string(leftX) + " ~ " + to_string(rightX) + "::" + dir;
    }
};

class Segment{
public:
    int leftX, rightX;
    Segment(){}
};

int n,
    preX, curX,
    minX, maxX,
    asr = 0;
vector<Op> ops;
vector<Segment> overlappedSegments;

int main() {
    cin>>n;
    preX = 0; curX = 0;
    for(int i = 0; i < n; ++i){
        preX = curX;    // 이동 전 위치 저장

        Op tmp;
        cin>>tmp.size>>tmp.dir;

        if(tmp.dir == 'L'){
            curX -= tmp.size;
            tmp.leftX = curX;
            tmp.rightX = preX;
        }else if(tmp.dir == 'R'){
            curX += tmp.size;
            tmp.leftX = preX;
            tmp.rightX = curX;
        }

        ops.push_back(tmp);
    }
    
    //debug
    // vector<Op>::iterator debugIt;
    // for(debugIt = ops.begin(); debugIt != ops.end(); ++debugIt){
    //     cout<<debugIt->toString()<<"\n";
    // }

    

    return 0;
}