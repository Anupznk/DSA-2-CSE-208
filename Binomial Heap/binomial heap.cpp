#include<bits/stdc++.h>
using namespace std;

// MAX BINOMIAL HEAP

struct Node{
    int item, degree;
    Node *child, *sibling, *parent; // taking all the necessary pointer for a binomial tree
};

Node* initNode(int it){
    Node *newNode = new Node;
    newNode->item = it;

    newNode->child = nullptr;
    newNode->parent = nullptr;
    newNode->sibling = nullptr;
    newNode->degree = 0;
    return newNode;
}

class BinomialMaxHeap{
    list<Node*> rootList;   // the degree of a root node = the deg of that binomial tree in the binomial heap

public:

    BinomialMaxHeap(list<Node*> nodeList){
        rootList = nodeList;
    }

    BinomialMaxHeap(){

    }

    void insertItem(int it){
        Node *newNode = initNode(it);
        list<Node*> tempHeap;
        tempHeap.push_back(newNode);
        BinomialMaxHeap tempBinoHeap(tempHeap);

        unionTwoHeaps(tempBinoHeap);   // union of existing binomial heap and a new passed heap

        if(rootList.size() > 1)
            heapifyBino(); // updating the main binomial heap
        cout << "Inserted " << it << endl;
    }

    void unionTwoHeaps(BinomialMaxHeap newHeap){ // union of existing binomial heap and a new passed heap
        // this is just merge sort according to degree of the binomial trees

        list<Node*> unitedBinoHeap;
        list<Node*>::iterator i = rootList.begin();
        list<Node*>::iterator j = newHeap.rootList.begin();

        while (i != rootList.end() && j != newHeap.rootList.end()){ // merge sort
            if((*i)->degree <= (*j)->degree){
                unitedBinoHeap.push_back(*i);
                i++;
            }
            else{
                unitedBinoHeap.push_back(*j);
                j++;
            }
        }

        while(i != rootList.end()){
            unitedBinoHeap.push_back(*i);
            i++;
        }

        while(j != newHeap.rootList.end()){
            unitedBinoHeap.push_back(*j);
            j++;
        }
        rootList = unitedBinoHeap;
    }

    void heapifyBino(){
        // this will merge the equal ordered binomial trees in the current binomial heap
        // we will keep 3 iterators to handle different cases

        list<Node*>::iterator it1,it2,it3;
        it1 = it2 = it3 = rootList.begin();

        // shifting the iterators one unit to the right
        if (rootList.size() == 2){
            it2 = it1;
            it2++;
            it3 = rootList.end();
        } else{
            it2++;
            it3 = it2;
            it3++;
        }

        while (it1 != rootList.end()){
            if (it2 == rootList.end())
                it1++;


            else if ((*it1)->degree < (*it2)->degree){  // just move forward
                it1++;
                it2++;
                if(it3!=rootList.end())
                    it3++;
            }

            else if (it3!=rootList.end() && (*it1)->degree == (*it2)->degree && (*it1)->degree == (*it3)->degree){ // 3 consecutive trees with same degree
                it1++;
                it2++;
                it3++;
            }

            else if ((*it1)->degree == (*it2)->degree){ // 2 consecutive trees with same degree but not 3 consecutive trees
                *it1 = mergeBinomialTrees(*it1,*it2);   // will merge two nodes of the same degree
                it2 = rootList.erase(it2);  // erase returns a pointer to the next of the deleted object
                if(it3 != rootList.end())
                    it3++;
            }
        }
    }

    Node* mergeBinomialTrees(Node *node1, Node *node2){    // will merge two nodes of the same degree
        if (node1->item < node2->item){ // make sure that the value of node 1 bigger
            Node *tempNode;
            tempNode = node1;
            node1 = node2;
            node2 = tempNode;
        }

        // let's make tree 1 the parent of tree 2
        node2->parent = node1;
        node2->sibling = node1->child;
        node1->child = node2;
        node1->degree++;

        return node1;
    }

    Node* getMaxNode(){
        list<Node*>::iterator it = rootList.begin();
        Node *maxNode = *it;
        while (it != rootList.end()){
            if ((*it) -> item > maxNode -> item)
                maxNode = *it;
            it++;
        }
        return maxNode;
    }

    int getMaxItem(){
        Node *maxNode = getMaxNode();
        return maxNode->item;
    }

    int extractMax(){
        if(rootList.size() == 0){
            cout << "The heap is empty\n";
            return -1;
        }

        list<Node*> tempBinoHeap, childrenBinoHeap;
        Node *maxNode;

        maxNode = getMaxNode();
        list<Node*>::iterator it;
        it = rootList.begin();
        while (it != rootList.end()){
            if (*it != maxNode){
                // creating a new binomial heap without the max node
                tempBinoHeap.push_back(*it);
            }
            it++;
        }

        childrenBinoHeap = createBinoHeapFromChildren(maxNode);
        rootList = tempBinoHeap;
        unionTwoHeaps(childrenBinoHeap);
        heapifyBino();

        return maxNode->item;
    }

    list<Node*> createBinoHeapFromChildren(Node *maxNode){
        // this will return the binomial heap containing the children of the max (deleted) node
        list<Node*> childrenBinoHeap;
        Node *temp = maxNode->child;
        Node *lo;

        while (temp != nullptr){
            lo = temp;
            temp = temp->sibling;
            lo->sibling = nullptr;
            childrenBinoHeap.push_front(lo);    // pushing in reverse order so that the sorted order of the degree is preserved in this binomial heap
        }
        return childrenBinoHeap;
    }

    int increaseKey(int item, int newKey){
        if (newKey < item || rootList.size() == 0){
            cout << "The new key is smaller than the current key\nIgnoring this update...";
            return -1;
        }

        Node *foundNode = searchKey(item);
        if(foundNode == nullptr){
            cout << item <<  " Not found.\n";
            return -1;
        }
//        cout << "Found node value: " << foundNode->item;

        // bubble up
        // exchange value with parent node if necessary until heap property is restored
        foundNode->item = newKey;
        Node *currNode = foundNode;
        Node *parent = currNode->parent;
//        cout << "parent: " << searchKey(12)->parent->item << endl;
        while(parent != nullptr && currNode->item > parent->item){
//            cout << "Currnode: " << currNode->item << " Parent: " << parent->item << endl;
            int tmp = currNode->item;
            currNode->item = parent->item;
            parent->item = tmp;
            currNode = parent;
            parent = currNode->parent;
        }

//        cout << "Increased "<< item << ". The updated value is " << newKey << ".\n";
        return newKey;
    }

    void deleteKey(int key){
        increaseKey(key, INT_MAX);
        extractMax();
        cout << "deleted " << key << endl;
    }

     Node* searchKey(int key){
        if(rootList.size() == 0){
            cout << "The heap is empty\n";
            return nullptr;
        }
        list<Node*> ::iterator it;
        it = rootList.begin();

        while(true){
            if((*it)->item == key)
                return (*it);
            Node *currNode = (*it)->child;
            while(currNode != nullptr){

                if(currNode->item == key)
                return currNode;
                Node *currSibling = currNode->sibling;

                while(currSibling != nullptr){
                    if(currSibling->item == key)
                        return currSibling;
                    currSibling = currSibling->sibling;
                }
                currNode = currNode->child;
            }
            it++;
            if(it == rootList.end())
                break;
        }
        return nullptr;
    }

    void printBinoHeap(){

        cout << "Printing Binomial Heap...\n--------------------------\n";
        if(rootList.size() == 0){
            cout << "The heap is empty\n";
            return;
        }

        list<Node*> ::iterator it;
        it = rootList.begin();

        int i = 0;
        while(true){
            cout << "Binomial Tree, B" << (*it)->degree << endl;
            int j = 0;
            cout << "Level " << j << " : " << (*it)->item  << endl;
            j++;
            Node *currNode = (*it)->child;
            while(currNode != nullptr){
                cout << "Level " << j << " : ";
                j++;
                cout << currNode->item << " ";
                Node *currSibling = currNode->sibling;

                while(currSibling != nullptr){
                    cout << currSibling->item << " ";
                    currSibling = currSibling->sibling;

                }
                currNode = currNode->child;
                cout << endl;
            }
            i++;
            it++;
            if(it == rootList.end())
                break;
        }
    }

    ~BinomialMaxHeap(){
        rootList.clear();
    }

};

const int INSERT = 1;
const int PRINT = 2;
const int INCREASE = 3;
const int FIND_MAX = 4;
const int EXTRACT_MAX = 5;
const int DELETE_ITEM = 6;
const int INVALID = -1;

int main() {
    BinomialMaxHeap binoHeap;
    fstream f("bino-heap.txt");
    if (!f.is_open()){
        cout<<"Unable to open file."<<endl;
        exit(1);
    }
    string cmd;
    int command = -1;
    while(!f.eof()){
        f >> cmd;
        if(cmd == "INS")    command = INSERT;
        if(cmd == "PRI")    command = PRINT;
        if(cmd == "FIN")    command = FIND_MAX;
        if(cmd == "EXT")    command = EXTRACT_MAX;
        if(cmd == "INC")    command = INCREASE;
        if(cmd == "DEL")    command = DELETE_ITEM;

        switch(command){
        case INSERT: {
            string word;
            f >>  word;
            int item = atoi(word.c_str());

            binoHeap.insertItem(item);
            break;
        }

        case INCREASE: {
            string word;
            f >>  word;
            int item = atoi(word.c_str());
            f >>  word;
            int newValue = atoi(word.c_str());

            binoHeap.increaseKey(item, newValue);
            break;
        }

        case FIND_MAX: {
            cout << "FindMax returned " << binoHeap.getMaxItem() << endl;
            break;
        }

        case PRINT: {
            binoHeap.printBinoHeap();
            break;
        }

        case EXTRACT_MAX: {
            int maxVal = binoHeap.extractMax();
            if (maxVal != -1)
                cout << "ExtractMax returned " << maxVal << endl;

            break;
        }

        case DELETE_ITEM: {
            string word;
            f >>  word;
            int item = atoi(word.c_str());
            binoHeap.deleteKey(item);
            break;
        }

        default:{
            cout << "Invalid Input" << endl;
        }

        }
    }

    f.close();
}









