//
//  HeapSort.cpp
//  HeapSortProj4
//
//  Created by Xing song  Lin on 2/21/16.
//  Copyright Â© 2016 Xing song  Lin. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class HeapSort{
public:
    int *heapAry;
    int heapSize;
    int arraySize;
    
    HeapSort(int count){
        heapSize = 0;
        arraySize = count;
        heapAry = new int[count];
    }
    
    bool isHeapEmpty(){
        return (heapSize==0);
    }
    
    bool isHeapFull(){
        return  heapSize == arraySize;
    }
    
    int leftChild(int index){
        return 2*index +1;
    }
    int rightChild(int index){
        return 2* index +2;
    }
    int parent(int index){
        return (index -1)/2;
    }
    int getMinimun(){
        return heapAry[0];
    }
    
    bool hasLeft(int index){return leftChild(index)<heapSize;}
    bool hasRight(int index) {return rightChild(index)<heapSize;}
    
    void swap(int i, int j){
        int *temp = &heapAry[i];
        heapAry[i]= heapAry[j];
        heapAry[j]= *temp;
    }
    
    void insertOneDataItem(int data){
        heapSize++;
        heapAry[heapSize-1]=data;
        bubbleUp(heapSize-1);
    }
    
    void bubbleUp(int index){
        while(index>0){
            int p=parent(index);
            if(heapAry[index]>heapAry[p]){
                //cout<<"bubble Up switch: "<<heapAry[father]<< " to "<< heapAry[index]<<endl;
                swap(index, p);
                index = p;
            }
        }
    }
    int deleteRoot(){
        //cout<<"delete: "<<heapAry[0]<<endl;
        int answer = heapAry[0];
        swap(0,heapSize-1);
        heapSize=heapSize-1;
        bubbleDown(0);
        return answer;
    }
    
    void bubbleDown(int index){
        while(hasLeft(index)){
            int leftIndex = leftChild(index);
            int minIndex = leftIndex;
            if(hasRight(index)){
                int rightIndex = rightChild(index);
                if(heapAry[leftIndex]>heapAry[rightIndex]){
                    minIndex = rightIndex;
                }
            }
            if(heapAry[minIndex]>heapAry[index]){break;}
            swap(index, minIndex);
            index=minIndex;
        }
    }
    
    string printHeap(int data){
        string line;
        for(int i=0; i<=9; i++){
            line = line +"Heap index at "+ to_string(i) + ", data =" +to_string(heapAry[i]) + "\n";
        }
        return line;
    }
    ~HeapSort(){
        delete[] heapAry;}
};

int main(int argc, const char * argv[]) {
    ifstream input;
    ofstream output1;
    ofstream output2;
    
    //step 1: open the input file.
    input.open(argv[1]);
    output1.open(argv[2]);
    output2.open(argv[3]);
    
    
    int data;
    int count;
    //step 2: data from input file
    while(input>>data){
        ++count;
    }
    //step 1: close file
    input.close();
    input.open(argv[1]);
    HeapSort* tree = new HeapSort(count+1);
    while(input>>data){
        //cout<<"Inserting: "<<data<<endl;
        tree->insertOneDataItem(data);
        output1<<tree->printHeap(data);
        output1<<"\n";
    }
    //cout<<"------------------------"<<endl;
    
    while(!tree->isHeapEmpty()){
        tree->deleteRoot();
        output2<<tree->printHeap(data);
        output2<<"\n";
    }
    
    delete tree;
    
    input.close();
    output1.close();
    output2.close();
    return 0;
}