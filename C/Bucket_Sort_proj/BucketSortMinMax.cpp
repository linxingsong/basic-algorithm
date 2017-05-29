
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class bucketSort{
    public:
    int *bucketAry;
    int bucketSize;
    
    bucketSort(int size){
        bucketAry = new int[size];
        bucketSize = size;
        for(int i=0; i<=bucketSize; i++){
            bucketAry[i]=0;  //step 3.1: initiallize the array to zero
        }
    }
    
    void insertElements(int data){
        bucketAry[data]++;              //step 7
    }
    
    string printBucketAry(){   //step 10
        string index = " ";
        string  detail = " ";
        for(int i=0; i<=18; i++){
            index = index+ to_string(i)+ " ";
        }
        for(int i=0; i<=18; i++){
           detail = detail + to_string(bucketAry[i])+ " ";
        }
        string finalLine = "Table for BucketSort Array: \n" + index + " \n" + detail + "\n";
        return finalLine;
    }
    
    string printSortedData(int min){  //step 11
        string table= "the Sorted Data: \n";
        for(int i=0; i<bucketSize; i++){
            while(bucketAry[i] >0){
                table = table + to_string(i+min) + " ";
                bucketAry[i]--;
            }
        }
        table=table + "\n";
        return table;
    }
    
    ~bucketSort(){
        delete[] bucketAry;
    }
};

int main(int argc, const char * argv[]) {
    ifstream input;      //step1: inFile
    ofstream of1;
    ofstream of2;
    
    input.open(argv[1]);
    of1.open(argv[2]);
    of2.open(argv[3]);
    
    int data, count, offSet, minData = 9999999, maxData=0, size;
    
    while(input>>data){    //step1.1: find Min & Max,
        count++;
        if(data>maxData){
            maxData=data;
        }
        if(data<minData){
            minData=data;
        }
    }
    offSet = minData;   //step 2: offSet, and declare the size.
    //cout<<"Total number in file: "<<count<<endl;
    //cout<< "The maximum number is "<<maxData<<endl;
    //cout<< "The minimum number is "<<offSet<<endl;
    size = maxData-minData+1;   //defind size for bucketAry.
    //cout<<"The size of the bucketAry is "<<size<<endl;
     //step3: dynamically allocate the bucketAry
    bucketSort* bucketAry = new bucketSort(size);
    
    input.close();      //step1.2: close file and reopen.
    input.open(argv[1]);    //step 4: re-open
    
    while(input>>data){     //Step 5: data <--read from file & step 9
        bucketAry->insertElements(data-offSet);  //step 6: put data to bucketAry,
                                                //data = data-offSet.
    }
    of2<<bucketAry->printBucketAry();   //step 8 & 10
    of1<<bucketAry->printSortedData(offSet); //step 11
    delete bucketAry;
    input.close();      //step 12
    of1.close();
    of2.close();
    return 0;
}

