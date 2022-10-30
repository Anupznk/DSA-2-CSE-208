#include<cstdlib>
#include<vector>
#include<iostream>

using namespace std;
#ifndef MYHEAP_HEAP_H

class Vertex{
    int v;
    int inDegree;
public:
    Vertex(){
        inDegree = 0;
    }
    Vertex(int x, int d){
       v = x;
       inDegree = d;
    }

    int getInDeg(){
        return inDegree;
    }

    int getVertex(){
        return v;
    }

    void setInDeg(int degree){
        inDegree = degree;
    }
};

class Heap {
private:
    Vertex *numbers;
    int length;
    int arraySize;
    int DEFAULT_SIZE = 1000;

public:
    Heap() {
        numbers = new Vertex[DEFAULT_SIZE];
        arraySize = DEFAULT_SIZE;
        length = 0;
    }

    Heap(int size) {
        numbers = new Vertex[size];
        arraySize = size;
        length = 0;
    }

    int getParentIndex(int index) {
        return (index-1)/2;
    }

    void swapNums(int firstIndex, int secondIndex) {
        Vertex temp;
        temp = numbers[firstIndex];
        numbers[firstIndex] = numbers[secondIndex];
        numbers[secondIndex] = temp;
    }

    void bubbleUp(int index) {
        // O(log n)
        int parent;
        if (index == 0)
            return;
        else {
            parent = getParentIndex(index);
            if (numbers[parent].getInDeg() > numbers[index].getInDeg()) { //  REVERSE CONDITION FOR MAX HEAP
                //  THIS VIOLATES THE PROPERTY OF MIN HEAP
                swapNums(parent, index);
                bubbleUp(parent);
            }
        }
    }

    void insert(Vertex number) {
        if (length == arraySize) {
            try{
                throw length;
            }
            catch(int ex) {
                cout<<"Exception: The Heap is Full"<<endl;
            }
        } else {
            numbers[length] = number;
            //  INSERTING AT THE END OF THE ARRAY
            length++;
            bubbleUp(length-1); // O(log n)
        }
    }

    Vertex getMin() {
        if (length > 0)
            return numbers[0];
        else {
            try{
                throw length;
            }
            catch(int ex) {
                cout<<"Exception: The Heap is empty. Garbage value alert"<<endl;
            }
        }
    }

    int getLeftChild(int index) {
        return (index + 1) * 2 - 1;
    }

    int getRightChild(int index) {
        return (index + 1) * 2;
    }

    void minHeapify(int index) {
        // O(log n)
        int maxValIndex = index;

        int leftChildIndex = getLeftChild(index);
        int rightChildIndex = getRightChild(index);



        if (leftChildIndex < length && numbers[leftChildIndex].getInDeg() < numbers[maxValIndex].getInDeg()) {
            // numbers[leftChildIndex] > numbers[maxValIndex] FOR MAX HEAP
            maxValIndex = leftChildIndex;
        }
        if (rightChildIndex < length && numbers[rightChildIndex].getInDeg() > numbers[maxValIndex].getInDeg()) {
            // numbers[rightChildIndex] < numbers[maxValIndex] FOR MAX HEAP
            maxValIndex = rightChildIndex;
        }

        if (maxValIndex != index) {
            swapNums(maxValIndex, index);
            minHeapify(maxValIndex);
        }
    }

    void deleteKey() {
        if (length == 0) {
            try{
                throw length;
            }
            catch(int ex) {
                cout<<"Exception: The Heap is empty. Cannot delete"<<endl;
            }
        } else{
            Vertex lastNum = numbers[length - 1];
            numbers[0] = lastNum;
            length--;

            minHeapify(0);  // O(log n)
        }
    }

//    void decreaseKey(int pos, int key){
//        // O(log n)
//        // decreasing the element in pos-th position to key in MIN heap
//        if(key > numbers[pos].getInDeg()){
//            cout << "The number is already less than the key, cannot decrease.";
//        } else {
//            numbers[pos] = key;
//            while(pos > 1 && numbers[pos/2] > numbers[pos]){ // numbers[pos/2] > numbers[pos] violates the MIN heap property
//                                                            // continuing this until we reach the root
//                swapNums(pos, pos/2);
//                pos = pos/2;    // going up to the parent and continue checking
//            }
//        }
//    }

    void decreaseKeyByOne(int pos){
        // O(log n)
        // decreasing the element in pos-th position to key in MIN heap

        int x = numbers[pos].getInDeg();
        numbers[pos].setInDeg(x-1);
        while(pos > 1 && numbers[pos/2].getInDeg() > numbers[pos].getInDeg()){ // numbers[pos/2] > numbers[pos] violates the MIN heap property
                                                        // continuing this until we reach the root
            swapNums(pos, pos/2);
            pos = pos/2;    // going up to the parent and continue checking
        }

    }

//    void increaseKey(int pos, int key){
//        // increasing the element in pos-th position to key in MIN heap
//        if(key < numbers[pos]){
//            cout << "The number is already greater than the key, cannot increase.";
//        } else {
//            numbers[pos] = key;
//            minHeapify(pos);    // O(log n)
//        }
//    }

    void increaseKeyByOne(int pos){
        // increasing the element in pos-th position to key in MIN heap

        int x = numbers[pos].getInDeg();
        numbers[pos].setInDeg(x+1);
        minHeapify(pos);    // O(log n)
    }

//    int findMinInMaxHeap(Heap h){
//        // O(n)
//        // min value should be on a leaf, so, search the leaves
//        int minVal = numbers[length/2];
//        for (int i = 1 + length/2; i<length; i++){
//            minVal = min(minVal, numbers[i]);
//        }
//        return minVal;
//    }

    int size() {
        return length;
    }

    Vertex * getHeap() {
        return numbers;
    }

    void setHeap(Vertex * numbers) {
        this->numbers = numbers;
    }

    ~Heap() {
        delete [] numbers;
    }
};

//bool isMaxHeap(int arr[], int n){
//    for(int i = 0; i<n/2; i++){
//        if (arr[i] < arr[2*1 + 1]){ // here the max index for arr is n-1, so, no array out of bound
//            return false;
//        }
//        if (2*i+2 < n arr[i] < arr[2*i + 2]){ // it is possible for a heap to have no right child
//            return false;
//        }
//    }
//    return true;
//}

//void heapsort(vector<int>&v) {
//    // O(n log n)
//    Heap newHeap(v.size());
//
//    for(int i = 0; i < v.size(); i++)
//        newHeap.insert(v[i]);
//
//    v.clear();
//
//    for (int i = 0;  newHeap.size(); i--) {
//        v.push_back(newHeap.getMin());
//        newHeap.deleteKey();
//    }
// }

#endif
