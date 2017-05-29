//
//  HeapSort.cpp
//  HeapSortProj4
//
//  Created by Xing song  Lin on 2/21/16.
//  Copyright Â© 2016 Xing song  Lin. All rights reserved.
//

//Based on 1D implementation of Partial Order Binary Trees/Priority Q
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class buildHeap{
public:
    int *heapAry;
    int heapSize;
    int arraySize;
    //define array
    buildHeap(int count){   //step 1.4
        heapSize = 0;
        arraySize = count+1;
        heapAry = new int[arraySize];
        heapAry[0]=0;
    }
    
    bool isHeapEmpty(){
        return (heapSize==0);
    }
    
    bool isHeapFull(){
        return  heapSize == arraySize-1;
    }
    
    int leftChild(int index){
        return 2*index;
    }
    int rightChild(int index){
        return 2* index +1;
    }
    int parent(int index){
        return index/2;
    }
    int getMinimun(){
        return heapAry[1];
    }
    //insert data
    void insertOneDataItem(int data){
        heapSize++;         //step 2.3
        heapAry[heapSize]=data;
        bubbleUp(heapSize);
    }
    
    void bubbleUp(int index){
        if(index==1) return;
        
        int parentIndex = parent(index);
        
        if(heapAry[index]<heapAry[parentIndex]){
            swap(heapAry[index], heapAry[parentIndex]);
            bubbleUp(parentIndex);
        }
    }
    //delete data.
    void deleteRoot(){
        if(isHeapEmpty()){
            cout<<"Heap is empty."<<endl;
        }
        else {
            //cout<<"delete: "<<heapAry[0]<<endl;
            //step 3.2
            heapAry[1] = heapAry[heapSize];
            heapSize--;
            if(heapSize>0)
                bubbleDown(1);
        }
    }
    
    void bubbleDown(int index){
        int leftIndex, rightIndex, minIndex;
        leftIndex = leftChild(index);
        rightIndex = rightChild(index);
        
        minIndex = index;
        
        if(leftIndex <= heapSize && heapAry[leftIndex]<heapAry[index])
        {
            minIndex = leftIndex;
        }
        if(rightIndex<= heapSize && heapAry[rightIndex]<heapAry[minIndex])
        {
            minIndex = rightIndex;
        }
        
        if(minIndex != index){
            swap(heapAry[index], heapAry[minIndex]);
            bubbleDown(minIndex);
        }
        
    }
    //print heap, save as string.
    //step 2.4 & step 3.3: print
    string printHeap(int data){
        string line;
        for(int i=1; i<=heapSize; i++){
            line = line +to_string(heapAry[i]) +" ";
        }
        line=line +"\n";
        return line;
    }
    ~buildHeap(){
        delete[] heapAry;}
};

int main(int argc, const char * argv[]) {
    ifstream input;
    ofstream output1;
    ofstream output2;
    
    //step 1.1: open the input file.
    input.open(argv[1]);
    output1.open(argv[2]);
    output2.open(argv[3]);
    
    
    int data;
    int count;
    //step 1.2: data from input file
    while(input>>data){
        ++count;
    }
    //step 1.3: close file
    input.close();
    input.open(argv[1]);
    buildHeap* tree = new buildHeap(count+1);
    while(input>>data){     //step 2.1,2.2 & 4
        //cout<<"Inserting: "<<data<<endl;
        tree->insertOneDataItem(data);  //step 2
        output1<<tree->printHeap(data);
        output1<<"\n";
    }
    //cout<<"------------------------"<<endl;
    
    while(!tree->isHeapEmpty()){    //step 3.1 & 4
        tree->deleteRoot();    //step 3
        output2<<tree->printHeap(data);
        output2<<"\n";
    }
    
    delete tree;  //step 5
    
    input.close();
    output1.close();
    output2.close();
    return 0;
}
