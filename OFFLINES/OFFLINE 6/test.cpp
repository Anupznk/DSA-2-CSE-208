#include<bits/stdc++.h>
using namespace std;
const bool DEBUG = false;
const int MAX_SIZE = 1e9 + 9;
const int MAX_LOOP_SIZE = 1e7;

class Data{
    string key;
    int value;

public:
    Data(){
        key = " ";
        value = -1;
    }

    Data(string k, int v){
        key = k;
        value = v;
    }

    string getKey(){
        return key;
    }

    int getVal(){
        return value;
    }

    void setVal(int val){
        value = val;
    }

    void setKey(string k){
        key = k;
    }
};


int main(){
    Data * doubleHashTable;
    doubleHashTable = new Data[100];
    Data d("asfsaf", 2);
    doubleHashTable[0].setKey("set");
    cout <<  doubleHashTable[0].getKey();
}
