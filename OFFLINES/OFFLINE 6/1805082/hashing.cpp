#include<bits/stdc++.h>
using namespace std;
const bool DEBUG = false;

const int MAX_LOOP_SIZE = 1e7;

const int C1 = 1003;
const int C2 = 57;

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

class HashTable{

private:
    long long tableSize;
    vector <vector <Data> > chainHashTable;
    Data *doubleHashTable;
    Data *customProbTable;
    int sepChainingCollision;
    int doubleHashCollision;
    int customProbCollision;
    long long currElements; // for double hashing
    long long currElements2; // for custom probing

public:

    Hash(){
        tableSize = 0;
        chainHashTable.resize(0, vector<Data>());
        sepChainingCollision = 0;
        doubleHashCollision = 0;
        currElements = 0;

        customProbCollision = 0;
        currElements2 = 0;
    }

    Hash(long long s){
        tableSize = s;
        chainHashTable.resize(tableSize, vector<Data>());
        sepChainingCollision = 0;
        doubleHashCollision = 0;
        currElements = 0;

        customProbCollision = 0;
        currElements2 = 0;
    }

    void setSize(int s){
        tableSize = s;
        chainHashTable.resize(tableSize, vector<Data>());
        Data nullItem(" ", -1);
        doubleHashTable = new Data[tableSize];
        customProbTable = new Data[tableSize];
        currElements = 0;
        currElements2 = 0;
    }

    void insertItemChain(Data data){
        string key = data.getKey();
        // inserting into separate chaining hash table
        int idx = hashFunc2(key)%tableSize;
        if(chainHashTable[idx].size() > 0){
            if(DEBUG)
                cout << "collision" << endl;
            sepChainingCollision ++;
        }
        chainHashTable[idx].push_back(data);
    }

    void insertItemDoubleHash(Data data){
        string key = data.getKey();
        // inserting into double hashing table

        if (currElements == tableSize){
            cout << "The array is full" << endl;
            return;
        }

        int index = hashFunc2(key)%tableSize;
        // we found an index which is already occupied
        if (doubleHashTable[index].getVal() != -1){
            int index2 = auxHashFunc(key)%tableSize;

            int i = 1;  // num of probes =  num of collisions
            while (true){
                int newIndex = (index + i * index2) % tableSize;  // it can cause inf loop if the table size is small

                // if no collision occurs, we can store the Data
                if (doubleHashTable[newIndex].getVal() == -1){
                    doubleHashTable[newIndex] = data;
                    if (DEBUG)
                        cout << data.getKey() <<  " collision and inserted" << endl;
                    break;
                }
                i++;
                if(i >= MAX_LOOP_SIZE){
                    cout << "loop detected. exiting program...";
                    exit(1);
                }
            }
            doubleHashCollision += i;

        } else{   // no collision
            if (DEBUG)
                cout << data.getKey() <<  " no collision inserted" << endl;
            doubleHashTable[index] = data;
        }
        currElements++;
    }

    void insertItemCustomProbing(Data data){
        string key = data.getKey();
        // inserting into double hashing table

        if (currElements2 == tableSize){
            cout << "The array is full" << endl;
            return;
        }

        int index = hashFunc2(key)%tableSize;
        // we found an index which is already occupied
        if (customProbTable[index].getVal() != -1){
            int index2 = auxHashFunc(key)%tableSize;

            int i = 1;  // num of probes =  num of collisions
            while (true){
                int newIndex = (index + C1 * i * index2 + C2 * i*i) % tableSize;  // it can cause inf loop if the table size is small

                // if no collision occurs, we can store the Data
                if (customProbTable[newIndex].getVal() == -1){
                    customProbTable[newIndex] = data;
                    if (DEBUG)
                        cout << data.getKey() <<  " collision and inserted" << endl;
                    break;
                }
                i++;
                if(i >= MAX_LOOP_SIZE){
                    cout << "loop detected. exiting program...";
                    exit(1);
                }
            }
            customProbCollision += i;

        } else{   // no collision
            if (DEBUG)
                cout << data.getKey() <<  " no collision inserted" << endl;
            customProbTable[index] = data;
        }
        currElements2++;
    }

    int getSepChainCollision(){
        return sepChainingCollision;
    }

    int getDoubleHashCollision(){
        return doubleHashCollision;
    }

    int getCustomProbCollision(){
        return customProbCollision;
    }

    void deleteKeyFromChain(string key){
        int idx = hashFunc2(key)%tableSize;
        vector <Data>::iterator i;

        for (i = chainHashTable[idx].begin(); i != chainHashTable[idx].end(); i++) {
            Data item = *i;
            if (item.getKey() == key)
                break;
        }

        if (i != chainHashTable[idx].end()){  // checking if the key is found
            chainHashTable[idx].erase(i);
            cout << key << " deleted successfully from separate chain hash table." << endl;
        } else{
            cout << key << " not found in separate chain hash table, cannot delete" << endl;
        }
    }

    void deleteFromDoubleHash(string key){
        int index = hashFunc2(key);
        int index2 = auxHashFunc(key);
        int probes = 0;
        int currPos = (index + probes * index2) % tableSize;
        while (doubleHashTable[currPos].getKey() != key) {
            if (doubleHashTable[currPos].getVal() == -1) {
                cout << key << " not found in double hash table, cannot delete" << endl;
                return;
            }
            probes++;
        }
        // now currPos has the index which we need to delete
        doubleHashTable[currPos].setKey(" ");
        doubleHashTable[currPos].setVal(-1);
        cout << currPos << " ." << key << " deleted from double hash table" << endl;
    }

    void deleteFromCustomProbe(string key){
        int index = hashFunc2(key)%tableSize;
        int index2 = auxHashFunc(key)%tableSize;
        int probes = 0;
        int currPos = (index + C1 * probes * index2 + C2 * probes*probes) % tableSize;
        while (customProbTable[currPos].getKey() != key) {
            if (customProbTable[currPos].getVal() == -1) {
                cout << key << " not found in custom probe table, cannot delete" << endl;
                return;
            }
            probes++;
        }
        // now currPos has the index which we need to delete
        customProbTable[currPos].setKey(" ");
        customProbTable[currPos].setVal(-1);
        cout << currPos << " ." << key << " deleted from custom probe table" << endl;
    }

    int searchChain(string key, bool show){
        int probes = 1;
        int idx = hashFunc2(key)%tableSize;
        for(int i = 0; i<chainHashTable[idx].size(); i++){
            if(chainHashTable[idx][i].getKey() == key){
                if(show){
                    cout << key << " found in separate chain hash table" << endl;
                }
                return probes;
            }
            probes++;
        }
        cout << key <<  " not found in separate chaining" << endl;
        return probes;
    }

    bool isDuplicateInput(string key){
        int idx = hashFunc2(key)%tableSize;
        for(int i = 0; i<chainHashTable[idx].size(); i++){
            if(chainHashTable[idx][i].getKey() == key){
                return true;
            }
        }
        return false;
    }

    int searchDoubleHash(string key, bool show){
        int index = hashFunc2(key)%tableSize;
        int index2 = auxHashFunc(key)%tableSize;
        int probes = 0;
        while (doubleHashTable[(index + probes * index2) % tableSize].getKey() != key) {
            if (doubleHashTable[(index + probes * index2) % tableSize].getVal() == -1) {
                cout << key << " not found in double hash table" << endl;
                return probes + 1;
            }
            probes++;
        }
        if (show)
            cout << key << " found in double hash table" << endl;
        return probes+1;
    }

    int searchCustomProbe(string key , bool show){
        int index = hashFunc2(key)%tableSize;
        int index2 = auxHashFunc(key)%tableSize;
        int probes = 0;
        int currPos = (index + C1 * probes * index2 + C2 * probes*probes) % tableSize;
        while (customProbTable[currPos].getKey() != key) {
            if (customProbTable[currPos].getVal() == -1) {
                cout << key << " not found in custom probe table" << endl;
                return probes + 1;
            }
            probes++;
            currPos = (index + C1 * probes * index2 + C2 * probes*probes) % tableSize;// ei line ta if er age jete pare
        }
        if (show)
            cout << key << " found in custom probe table" << endl;
        return probes+1;
    }

    int hashFunc(string key) {
        int p = 31;
        long long pow = 1;
        long long hashValue = 0;

        for (int i = 0; i < key.length(); i++) {
            hashValue = (hashValue + (key[i] - 'a' + 1) * pow) % tableSize;
            pow = (pow * p) % tableSize;
        }
        return (hashValue % tableSize + tableSize) % tableSize;
    }

    int hashFunc2(string key) {
        int p = 44;
        long long pow = 1;
        long long hashValue = 0;

        for (int i = 0; i < key.length(); i++) {
            hashValue = (hashValue + (key[i] - 'a' + 1) * pow) % tableSize;
            pow = (pow * p) % tableSize;
        }
        return (hashValue % tableSize + tableSize) % tableSize;
    }

    int auxHashFunc(string key){
        int hashVal = 0;
        for (int i = 0; i<key.size(); i++){
            hashVal += (key[i] * 3) % tableSize;
        }
        return (13 - (hashVal % 13))%tableSize;
    }

    void showHashTable(){
        cout << "Showing Separate chaining hash table\n";
        for(int i = 0; i<chainHashTable.size(); i++){
            for(int j = 0; j<chainHashTable[i].size(); j++){
                cout << chainHashTable[i][j].getKey()  << " ";
            }
            cout << endl;
        }
        cout << endl;
        cout << "Showing Double hashing hash table\n";
        for(int i = 0; i<tableSize; i++){
            cout << i << ". "<< doubleHashTable[i].getKey() << endl;
        }

        cout << endl;
        cout << "Showing Custom Probing hash table\n";
        for(int i = 0; i<tableSize; i++){
            cout << i << ". "<< customProbTable[i].getKey() << endl;
        }
    }

    void clearHashTable(){
        chainHashTable.resize(0, vector<Data>());
        sepChainingCollision = 0;

        doubleHashCollision = 0;
        customProbCollision = 0;
    }
};

bool isPrime(int x){
    for (int i = 2; i <= sqrt(x); i++) {
        if (x % i == 0) {
            return false;
        }
    }
    return true;
}

long long immediatePrime(int n){
    long long prime = 1e5 + 9;
    for(int i = n+1; ; i++){
        if(isPrime(i)){
            return i;
        }
        if(i == prime)
            break;
    }
    return prime;
}

int main(){
    int n;
    int tableSize;
    HashTable inputStrTable;
    HashTable inputStrTable2;
    HashTable hashTable;
    HashTable customProbeTable;
    hashTable.clearHashTable();
    customProbeTable.clearHashTable();
    inputStrTable.clearHashTable();
    inputStrTable2.clearHashTable();
    srand(time(0));

    cout << "\nStarting a new hash table\n";
    cout << "\nEnter the number of inputs:\n";
    cin >> n;
    cout << "Enter the table size (prime number bigger than " << n << "):\n";
    cin >> tableSize;
//        n = immediatePrime(tableSize);
    cout << "table size: "  << tableSize << endl;
    hashTable.setSize(tableSize);
    inputStrTable.setSize(tableSize);
    inputStrTable2.setSize(tableSize);
    string input[10000];
    // inserting to the hash table
    for(int k = 0; k<n; k++){   // generating n random words
        int word_len = 7;
        char valid[] = "abcdefghijklmnopqrstuvwxyz";
        char randArr[word_len];
        int l = 26;

        for (int i = 0; i < word_len; ++i){
            randArr[i] = valid[rand() % l];
        }

        string wordStr(randArr);
        input[k] = wordStr;
        Data newItem(wordStr, k);
        if (inputStrTable.isDuplicateInput(wordStr)){
            cout << "duplicate found, ignoring..." << endl;
            k--;
            continue;
        } else{
            inputStrTable.insertItemChain(newItem);
        }

        // 1. Separate Chaining
        hashTable.insertItemChain(newItem);

        // 2. Double Hashing
        hashTable.insertItemDoubleHash(newItem);

        // 3. Custom Probing
        hashTable.insertItemCustomProbing(newItem);

        if(DEBUG){
            cout<<"The Random word is : "<<wordStr << endl;
        }
    }

    string inputStr;
    while(true){
        cout<<"\n\nEnter your choice"<<endl;
        cout<<"1. Search"<<endl;
        cout<<"2. Delete item"<<endl;
        cout<<"3. Show table data"<<endl;
        cout<<"4. Generate Report"<<endl;
        cout<<"Press q to quit\n\n"<<endl;

        char cmd;
        cin >> cmd;
        if(cmd == 'q' || cmd == 'Q')
            break;
        switch(cmd){
            case '1':{
                // 1. Separate Chaining
                cout << "Enter a string to search in the hash table: ";
                cin >> inputStr;
                hashTable.searchChain(inputStr, true);

                // 2. Double Hashing
                hashTable.searchDoubleHash(inputStr, true);

                // 3. Custom Probing
                hashTable.searchCustomProbe(inputStr, true);

                break;
            }
            case '2':{
                // 1. Separate Chaining
                cout << "Enter a string to delete from the hash table: ";
                cin >> inputStr;
                hashTable.deleteKeyFromChain(inputStr);

                // 2. Double Hashing
                hashTable.deleteFromDoubleHash(inputStr);

                // 3. Custom Probing
                hashTable.deleteFromCustomProbe(inputStr);

                break;
            }
            case '3':{
                hashTable.showHashTable();
                break;
            }

            case '4':{
                cout << "Generating report for hash 2" << endl;
                cout << "No of collision in separate chaining: " << hashTable.getSepChainCollision() << endl;
                cout << "No of collision in Double Hashing: " << hashTable.getDoubleHashCollision() << endl;
                cout << "No of collision in Custom Probing: " << hashTable.getCustomProbCollision() << endl;

                // searching 1000 items from the 3 hash tables
                int i = 0;
                double totalProbeChain = 0;
                double totalProbeDoubleHash = 0;
                double totalProbeCustomProbe = 0;
                int searchItemNum = 1000;
                while(i < searchItemNum){
                    string wordStr = input[rand()%10000];
                    totalProbeChain += hashTable.searchChain(wordStr, false);
                    totalProbeDoubleHash += hashTable.searchDoubleHash(wordStr, false);
                    totalProbeCustomProbe += hashTable.searchCustomProbe(wordStr, false);
                    i++;
                }

                cout << "Avg No of probes in separate chaining: " << totalProbeChain/searchItemNum << endl;
                cout << "Avg No of probes in Double hashing: " << totalProbeDoubleHash/searchItemNum << endl;
                cout << "Avg No of probes in Custom Probing: " << totalProbeCustomProbe/searchItemNum << endl;

                break;
            }

            default:{
                cout << "Invalid input." << endl;
            }
        }
    }

    hashTable.clearHashTable();
    customProbeTable.clearHashTable();
    inputStrTable.clearHashTable();
    inputStrTable2.clearHashTable();

}
