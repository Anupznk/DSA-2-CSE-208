#include<cstdlib>
#include<vector>
#include<iostream>

using namespace std;
#ifndef MYHEAP_HEAP_H

class Heap {
private:
    int *numbers;
    int length;
    int arraySize;
    int DEFAULT_SIZE = 1000;

public:
    Heap() {
        numbers = new int[DEFAULT_SIZE];
        arraySize = DEFAULT_SIZE;
        length = 0;
    }

    Heap(int size) {
        numbers = new int[size];
        arraySize = size;
        length = 0;
    }

    int getParentIndex(int index) {
        return (index-1)/2;
    }

    void swapNums(int firstIndex, int secondIndex) {
        int temp;
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
            if (numbers[parent] < numbers[index]) { //  REVERSE CONDITION FOR MIN HEAP
                //  THIS VIOLATES THE PROPERTY OF MAX HEAP
                swapNums(parent, index);
                bubbleUp(parent);
            }
        }
    }

    void insert(double number) {
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

    int getMax() {
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

    void maxHeapify(int index) {
        // O(log n)
        int maxValIndex = index;

        int leftChildIndex = getLeftChild(index);
        int rightChildIndex = getRightChild(index);



        if (leftChildIndex < length && numbers[leftChildIndex] > numbers[maxValIndex]) {
            // numbers[leftChildIndex] < numbers[maxValIndex] FOR MIN HEAP
            maxValIndex = leftChildIndex;
        }
        if (rightChildIndex < length && numbers[rightChildIndex] > numbers[maxValIndex]) {
            // numbers[rightChildIndex] > numbers[maxValIndex] FOR MIN HEAP
            maxValIndex = rightChildIndex;
        }

        if (maxValIndex != index) {
            swapNums(maxValIndex, index);
            maxHeapify(maxValIndex);
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
            int lastNum = numbers[length - 1];
            numbers[0] = lastNum;
            length--;

            maxHeapify(0);  // O(log n)
        }
    }

    void increaseKey(int pos, int key){
        // O(log n)
        // increasing the element in pos-th position to key in MAX heap
        if(key < numbers[pos]){
            cout << "The number is already greater than the key, cannot increase.";
        } else {
            numbers[pos] = key;
            while(pos > 1 && numbers[pos/2] < numbers[pos]){ // numbers[pos/2] < numbers[pos] violates the MAX heap property
                                                            // continuing this until we reach the root
                swapNums(pos, pos/2);
                pos = pos/2;    // going up to the parent and continue checking
            }
        }
    }

    void decreaseKey(int pos, int key){
        // decreasing the element in pos-th position to key in MAX heap
        if(key > numbers[pos]){
            cout << "The number is already less than the key, cannot decrease.";
        } else {
            numbers[pos] = key;
            maxHeapify(pos);    // O(log n)
        }
    }

    int findMinInMaxHeap(Heap h){
        // O(n)
        // min value should be on a leaf, so, search the leaves
        int minVal = numbers[length/2];
        for (int i = 1 + length/2; i<length; i++){
            minVal = min(minVal, numbers[i]);
        }
        return minVal;
    }

    int size() {
        return length;
    }

    int * getHeap() {
        return numbers;
    }

    void setHeap(int * numbers) {
        this->numbers = numbers;
    }

    ~Heap() {
        delete [] numbers;
    }
};

bool isMaxHeap(int arr[], int n){
    for(int i = 0; i<n/2; i++){
        if (arr[i] < arr[2*1 + 1]){ // here the max index for arr is n-1, so, no array out of bound
            return false;
        }
        if (2*i+2 < n arr[i] < arr[2*i + 2]){ // it is possible for a heap to have no right child
            return false;
        }
    }
    return true;
}

void heapsort(vector<int>&v) {
    // O(n log n)
    Heap newHeap(v.size());

    for(int i = 0; i < v.size(); i++)
        newHeap.insert(v[i]);

    v.clear();

    for (int i = 0;  newHeap.size(); i--) {
        v.push_back(newHeap.getMax());
        newHeap.deleteKey();
    }
 }

#endif
