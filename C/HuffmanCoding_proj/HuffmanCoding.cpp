//  HuffmanCoding
//  main.cpp
//  proj7
//
//  Created by Xing song  Lin on 3/28/16.
//  Copyright ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â© 2016 Xing song  Lin. All rights reserved.
//

#include <iostream>
#include <fstream>
using namespace std;
//step 1
class listBinTreeNode{
    friend class HuffmanLinkedList;
    friend class HuffmanBinaryTree;
    
public:
    string chStr;
    int prob;
    listBinTreeNode *next;
    listBinTreeNode *left;
    listBinTreeNode *right;
    
    listBinTreeNode(string character, int numb){
        chStr = character;
        prob = numb;
        next = NULL;
        left = NULL;
        right = NULL;
    }
    
    listBinTreeNode(){
        chStr = "";
        prob = 0;
        next = NULL;
        left = NULL;
        right = NULL;
    }
    
    string printNode(listBinTreeNode *T){
        string line = "Node: \n";
        if( T -> next == NULL){
            if(T->left == NULL || T->right == NULL) {
                line += "Node character: "+T -> chStr + ", Node probability: "+ to_string(T -> prob) + ", next Node: NULL" + ", Node->left character: NULL, Node->right character: NULL\n";
            } else
                line += "Node character: "+T -> chStr + ", Node probability: "+ to_string(T -> prob) + ", next Node: NULL" + ", Node->left character: "+T -> left -> chStr +", Node->right character:" +T -> right -> chStr + "\n";
            
        }
        else if( T -> left == NULL || T -> right ==NULL){
            line += "Node character: "+T -> chStr + ", Node probability: "+ to_string(T -> prob) + ", next Node character "+ T -> next -> chStr + ", "+"Node->left: NULL" +", " + "Node->right: NULL" + "\n";
        }
        else{
            line += "Node character: "+T -> chStr + ", Node probability: "+ to_string(T -> prob) + ", next Node character "+ T -> next -> chStr + ", Node->left character: "+T -> left -> chStr +", Node->right character: " +T -> right -> chStr + "\n";
        }
        return line;
    }
    
    ~listBinTreeNode(){
        delete next;
        //delete left;
        //delete right;
    }
};

class HuffmanLinkedList {  //step2: construct Huffman ordered linkedlist->
    
public:
    listBinTreeNode *listHead;
    listBinTreeNode *oldListHead;
    
    HuffmanLinkedList(){
        listBinTreeNode *newNode = new listBinTreeNode("dummy", 0);
        listHead = newNode;
    }
    
    void listInsert(listBinTreeNode *T){
        listBinTreeNode* spot = findSpot(T->prob);
        T-> next = spot->next;
        spot->next = T;
    }
    
    listBinTreeNode* findSpot(int numb){
        listBinTreeNode* spot = listHead;
        while((spot->next != NULL) && (spot->next->prob < numb)){
            spot = spot->next;
        }
        return spot;
    }
    
    bool isEmpty(){
        if(listHead->next == NULL){
            return true;
        }
        return false;;
    }
    
    string printList(){
        string list= "\n list: \n";
        if(isEmpty()){
            list += "listHead -->( dummy , 0 , NULL )--> NULL\n";
        }
        else{
            list += "listHead -->( dummy , " + to_string(listHead -> prob) + ", " + listHead -> next -> chStr +")-->";
            listBinTreeNode* current = listHead;
            while(current -> next -> next != NULL){
                list += "(" + current -> next -> chStr +", " + to_string(current -> next -> prob) + ", " + current -> next -> next -> chStr + ")-->";
                current = current -> next;
            }
            list += list + "(" + current -> next -> chStr + ", " + to_string(current-> next -> prob) + ", " + "NULL)--> NULL\n";
        }
        return list;
    }
    
    ~HuffmanLinkedList(){
        delete listHead;
        delete oldListHead;
    }
};


class HuffmanBinaryTree{   //step3: construct Huffman Binary Tree
public:
    string chStr;
    int prob;
    string code;
    listBinTreeNode* root;
    
    HuffmanBinaryTree(listBinTreeNode *T){
        root = T;
    }
    
    void preOrderTraveral(listBinTreeNode *T, ofstream& outFile2){
        if(T == NULL){
            return ;
        }
        else{
            outFile2<<T->printNode(T);
            preOrderTraveral(T->left, outFile2);
            preOrderTraveral(T->right, outFile2);
        }
    }
    
    void constructCharCode(listBinTreeNode *T, string code, ofstream &outFile1){
        if(T == NULL){
            outFile1<<"Empty";
        }
        else if (T->left == NULL || T->right == NULL) {
            //cout << T->printNode(T) << endl;
            outFile1<< T->chStr + " " + code + " \n";
        }
        else {
            //cout << T->printNode(T) << endl;
            constructCharCode(T->right, code+"1", outFile1);
            constructCharCode(T->left, code+"0", outFile1);
            
        }
    }
    
    ~HuffmanBinaryTree(){
        delete root;
    }
};

int main(int argc, char ** argv) {
    ifstream inFile;
    ofstream outFile1;  //step 2.0
    ofstream outFile2;
    ofstream outFile3;
    inFile.open(argv[1]);
    outFile1.open(argv[2]);
    outFile2.open(argv[3]);
    outFile3.open(argv[4]);
    
    int data;
    string word;
    HuffmanLinkedList *list = new HuffmanLinkedList();
    while(inFile>>word>>data){  //step 2.1, 2.2 & 2.6
        listBinTreeNode* newNode = new listBinTreeNode(word, data); //step 2.3
        list->listInsert(newNode);  //step 2.4
        outFile3<< list->printList(); //step 2.5
    }
    inFile.close();  //step 2.7
    outFile3<< "\n End! \n\n";
    
    //listBinTreeNode* oldListHead = new listBinTreeNode(); //maybe dont need. //step 3.0
    //list->oldListHead ->next = list->listHead->next;
    list->oldListHead = list->listHead;
    while(list->listHead->next->next != NULL){ //step 3.3
        listBinTreeNode* newNode = new listBinTreeNode();  //step 3.1
        newNode->chStr = list->listHead->next->chStr + list->listHead->next->next->chStr;
        newNode->prob = list->listHead->next->prob + list->listHead->next->next->prob;
        newNode->left = list->listHead->next;
        newNode->right = list->listHead->next->next;
        list->listHead->next = list->listHead->next->next->next;
        list->listInsert(newNode);
        
        outFile3<<list->listHead->printNode(newNode) << endl;  //step 3.2
        outFile3<<list->printList() << endl;
    }
    
    outFile3.close();
    
    HuffmanBinaryTree tree = *new HuffmanBinaryTree(list->listHead); //step 3.4
    outFile1<< "HuffmanCoding Table: \n -------------------------------\n";
    tree.constructCharCode(list->listHead->next," ",outFile1);  //step 4
    outFile1.close();
    
    outFile2<< "Tree Node: \n\n";
    tree.preOrderTraveral(list->listHead->next, outFile2);  //step 5
    outFile2.close();
    
    return 0;
}