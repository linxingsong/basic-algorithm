//
//  main.cpp
//  proj10
//
//  Created by Xing song  Lin on 16/5/8.
//  Copyright © 2016年 Xing song  Lin. All rights reserved.
//

#include <iostream>
#include <fstream>
using namespace std;

class graphColoring{
public:
    int** adjacencyMatrix;
    int uncolorNode;
    int newColor;
    int numNode;
    
    graphColoring(int n){
        numNode = n;
        newColor =0;
        uncolorNode=0;
        adjacencyMatrix = new int*[numNode];
        for(int i=0; i<n; i++){
            adjacencyMatrix[i]= new int[numNode];
        }
        for(int i=0; i<numNode; i++){
            for(int j=0; j<numNode; j++){
                adjacencyMatrix[i][j]= 0; //initiall all cost to 0.
            }
        }
    }
    
    void insertMatrix(int a, int b){
        adjacencyMatrix[a][b] = 1;  //adjacency nodes a & b
    }
    
    bool allNodeColored(){
        for(int i=0; i<numNode; i++){
            if(adjacencyMatrix[i][i]== 0){
                return false;  //this node not colored.
            }
        }
        return true;
    }
    
    string printMatrix(){
        string l = "adjacency Matrix: \n";
        for(int i = 0; i<numNode; i++){
            for(int j=0; j<numNode; j++){
                l =l +  to_string(adjacencyMatrix[i][j])+ " ";
            }
            l= l+"\n";
        }
        return l;
    }
    
    ~graphColoring(){
        for(int i=0; i<numNode; i++){
            delete[]  adjacencyMatrix[i];
        }
        delete[] adjacencyMatrix;
    }
    
};

int main(int argc, const char * argv[]) {
    ifstream input;
    input.open(argv[1]);
    ofstream output;
    output.open(argv[2]);
    int numNodes;
    int node1;
    int node2;
    input>>numNodes;
    //cout<<"check point: numNode is "<<numNode<<endl;
    graphColoring graph = *new graphColoring(numNodes);  //step 0
    while(input>>node1>>node2){
        graph.insertMatrix(node1-1, node2-1);
        graph.insertMatrix(node2-1, node1-1);
    }
    output<<"initial matrix: \n";
    output<<graph.printMatrix();
    
    //cout<<"check point: After matrix, stop here."<<endl;
    while(!graph.allNodeColored()){
        int i=0;
        while(i<numNodes){
            if(graph.adjacencyMatrix[i][i]==0){//this node is uncolored.
                graph.newColor++;
                graph.uncolorNode = i; //set this node as uncolorNode.
                for(int j=0; j<numNodes; j++){
                    if(graph.adjacencyMatrix[graph.uncolorNode][j]==0 & graph.adjacencyMatrix[j][j]!= graph.newColor){//two node is not adjacency and second node is not colored.
                        graph.adjacencyMatrix[graph.uncolorNode][graph.uncolorNode] = graph.newColor;
                        graph.adjacencyMatrix[j][j] = graph.newColor;
                    }
                }
                output<<"*****************************\nColoring Node now: \n";
                output<<graph.printMatrix();
            }
            i++;
        }
    }
    
    output<<"----------------------------------\ntotal color assigned to graph: "<<to_string(graph.newColor)+".\n";
    output<<"-----------------------------------\nfinal Matrix: \n";
    output<<graph.printMatrix();  //step 6

     return 0;
}
