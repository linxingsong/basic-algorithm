
//  main.cpp
//  StackProj2
//
//  Created by Xing song  Lin on 16/2/7.
//  Copyright Â© 2016å¹´ Xing song  Lin. All rights reserved.
//


#include<iostream>
#include <fstream>
#include <string>
using namespace std;

//Node class: ListNode
class ListNode     //step 0
{
public:                       
    //declare the integer variable
    int data;
    
    //declare a ListNode pointer variable
    ListNode* next;
    
    //Constructor
    ListNode()
    {
        data = 0;
        next = NULL;
    }
    
    //Parameterised constructor
    ListNode(int value)
    {
        data = value;
        next = NULL;
    }
    
    //destructor
    ~ListNode()
    {
    };
};

//Stack using Linked list class
class StackLinklist
{
public:
    //Declare a ListNode
    ListNode* top;
    
    //constructor
    StackLinklist(){
        this->top = NULL;
    }
    
    //push() method
    void push(int value)
    {
        ListNode *newNode = new ListNode;
        newNode->data = value;
        newNode->next = top;
        top = newNode;
        cout<< "Push: "<<newNode->data<<"\tAddress: "<<newNode<<endl;
    }
    
    //pop() method
    int pop()
    {
        ListNode *temp = top;
        top = top->next;
        temp->next = NULL;
        int data = temp->data;
        cout<<"POP: "<<temp->data<<"\tAddress: "<<temp<<endl;
        delete temp;
        return data;
    }
    
    //isEmpty()emthod
    bool isEmpty()
    {
        return (this->top == NULL);
    }
    
    //destructor
    ~StackLinklist()
    {
    };
};

//main function
int main(int argc, char * argv[1])
{
    //declare the requried variables
    int data;
    string filename;
    ifstream input;
    cout<<"Enter the file name: "<<endl;  //step 2
    cin>>filename;
    
    //read the file name from the command line and
    //assign the value into the filename
    //filename = argv[1];            //code use for argv[1]//step 1
    //input.open(filename);
    input.open(filename.c_str());   //step 1.
    
    while(input.fail())
    {           //step 4
        input.clear();
        cout<<"Wrong, enter again: "<<endl;
        cin>>filename;
        input.open(filename.c_str());
    }
    
    StackLinklist* stack = new StackLinklist();
    cout<<"reading file....."<<endl;
    while(input >> data)  {   //step 2 & 4
        stack->push(data);   //step 3
    }
    
    cout<< "Finish push. start pop now."<<endl;
    while(!stack->isEmpty())  { //step 7     
        stack->pop();      //step 6
    }
    input.close();   //step 5
    system("PAUSE");
    return 0;
}

