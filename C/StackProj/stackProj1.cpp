//
//  main.cpp
//  stackProj1
//
//  Created by Xing song  Lin on 2/3/16.
//  Copyright © 2016 Xing song  Lin. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <stack>
using namespace std;

class stack1{      //step 0
private:
    int *Array;
    int top;
    int count;
public:
    stack1(int numb){
        top=-1;
        count = numb;
        Array = new int[numb];
    }
    void push(int a){
        if(top == count) return ;
        Array[++top] = a;
    }
    int ttop(){
        if(top == -1){ cout<<"stack empty"<<endl;}
        return Array[top];
    }
    
    void pop(){
        if(top==-1){
            cout<<"empty now."<<endl;}
        top--;
    }
    bool isEmpty(){ return (top==-1);}
    ~stack1(){
        delete[] Array;}
};


int main(int argc, char * argv[]) {
    string filename;
    int data;
    int count=0;        //count how many char in the file
    string word;
    
    ifstream input;   //step 1
    cout<<"Enter the file name: "<<endl;  //step 2
    cin>>filename;
    input.open(filename.c_str());
    
    while(input.fail()){           //step 4
        input.clear();
        cout<<"Wrong, enter again: "<<endl;
        cin>>filename;
        input.open(filename.c_str());
    }
    
    while (input>>data){         //looking for character in the inputfile             //step 3
        ++count;
        cout<<data<<endl;
    }
    cout<< "Number of words in that file is "<<count<<endl;
    
    input.close();    //step 5
    
    stack1* s = new stack1(count);
    
    //reopen file, step 5
    input.open(filename.c_str());
    cout<<"Reading data now: "<<endl;
    
    //save all data from file to stack using push method.
    //step 6
    while(count-- > 0){   //step 8
        input>>data;
        s->push(data);   //step 7
        cout<< "push: "<<data<<endl;
    }
    //step 9
    while(! s->isEmpty()){  //step 11
        int num;
        num = s->ttop();
        cout<<"pop number is: "<<num<<endl;
        s->pop();   //step 10
    }
    
    input.close();   //step 12
    delete s;
    system("PAUSE");
    return 0;
}
