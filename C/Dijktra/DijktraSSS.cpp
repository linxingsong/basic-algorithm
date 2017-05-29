//
//  main.cpp
//  proj8
//
//  Created by Xing song  Lin on 16/4/27.
//  Copyright © 2016年 Xing song  Lin. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class DijktraSSS{
    private:
        int numNodes, sourceNode, minNode, newCost, currentNode;
        int** costMatrix;
        int* fatherAry;
        int* markedAry;
        int* bestCostAry;
    public:
        DijktraSSS(int x){
            numNodes = x;
            fatherAry = new int[numNodes];
            markedAry = new int[numNodes];
            bestCostAry = new int[numNodes];
            costMatrix = new int*[numNodes];
            for(int i=0; i<numNodes; i++){
                costMatrix[i]= new int[numNodes];
            }
            for(int i=0; i<numNodes; i++){
                for(int j=0; j<numNodes; j++){
                    costMatrix[i][j]= 99999; //initiall all cost to 99999.
                }
            }
        }
    
        void setSourceNode(int s){
            sourceNode = s;
            fatherAry = new int[numNodes];
            markedAry = new int[numNodes];
            bestCostAry =new int[numNodes];
            for(int i=0; i<numNodes; i++){  //initiall 3 Arys.
                fatherAry[i] = i;
                markedAry[i] = 0;
                bestCostAry[i] = 99999;
            }
            bestCostAry[sourceNode] = 0;
        }
    
        string printSourceNode(){
            string line = "\n";
            line = line + "Source node is: "+ to_string(sourceNode+1)+ "\n";
            return line;
        }
    
        string printFatherAry(){
            string fatherAryLine = "fatherAry: ";
            for(int i=0; i<numNodes; i++){
                fatherAryLine = fatherAryLine + to_string(fatherAry[i] +1) + " ";
            }
            fatherAryLine = fatherAryLine + "\n";
            return fatherAryLine;
        }
    
        string printBestCostAry(){
            string bestCostAryLine= "Best Cost Ary: ";
            for(int i =0; i<numNodes; i++){
                bestCostAryLine = bestCostAryLine + to_string(bestCostAry[i]) + " ";
            }
            bestCostAryLine = bestCostAryLine+"\n";
            return bestCostAryLine;
        }
    
        string printMarkedAry(){
            string MarkedAryLine = "MarkedAry: ";
            for(int i=0; i<numNodes; i++){
                MarkedAryLine = MarkedAryLine+ to_string(markedAry[i]) + " ";
            }
            MarkedAryLine = MarkedAryLine+"\n";
            return MarkedAryLine;
        }
    
        string debugPrint(){ //step 2: load all Arrays
            string finalyLine = "------------------------------------";
            finalyLine = finalyLine+ printSourceNode() + "\n" + printFatherAry() + "\n" + printBestCostAry() + "\n" + printMarkedAry();
            finalyLine = finalyLine + "------------------------------------\n";
            return finalyLine;
        }
    
        void newMarkedAry(int a){
            markedAry[a] =1;
        }
    
        void newFatherAry(int a, int b){
            fatherAry[a] = b;
        }
    
        void newBestCostAry(int a, int b){
            bestCostAry[a] = b;
        }
    
        void insertcostMatrix(int a, int b, int c){
            costMatrix[a][b] = c;
        }
    
        string buildUp(){
            string s = "";
            minNode = sourceNode;  //step 3
            while(!markedNode()){ //step6: repeat step 3 to 5 until all node are marked.
                int min = 999999;
                for(int i=0; i<numNodes; i++){
                    if((markedAry[i] == 0) && (min>bestCostAry[i])){
                        min = bestCostAry[i];
                        minNode = i;
                        }
                    }
                newMarkedAry(minNode); //markMinNode(minNode)
                s = s + "\n";
                s = s+ "minNode: "+ to_string(minNode+1)+ "\n";
                s = s+ debugPrint();  //call debugPrint
                s = s+ expanding();
            }
            return s;
        }
    
        bool markedNode(){
            for(int i=0; i<numNodes; i++){
                if(markedAry[i]==0){
                    return false;
                }
            }
            return true;
        }
    
        string expanding(){  //step 4
            string s = "";
            int n=0;
            while(n< numNodes){ //step5: repeat step 4 until all unmarked node in markedAry
                if(markedAry[n] == 0){
                    currentNode = n;  //currentNode <-- find next unmarked node in markedAry
                    				//step 7: current node is 1
                    newCost = bestCostAry[minNode] + computeCost(minNode, currentNode); //newCost
                    if(newCost< bestCostAry[currentNode]){
                        newFatherAry(currentNode, minNode);
                        newBestCostAry(currentNode, newCost);
                    }
                }
                n++; 
            }
            return s;
        }
    
        int computeCost(int a, int b){
            return costMatrix[a][b];
        }
    
        string findAllShortestPath() {
            string finalLine = "";
            finalLine = finalLine +"=============================\n"+ "The graph has " + to_string(numNodes) + " nodes.\n"+"=============================\n=============================\n"+"\nT.he source node = " + to_string(sourceNode + 1) + "." + "\n";
            int k = 0;
            while (k < numNodes) { //step 10
            	string n="";
            	string s="";
            	if(fatherAry[k]!=k){  //step 8
               		 n = n + "The path from " + to_string(sourceNode + 1) + " to " + to_string(k + 1) + " :";
                	int f = fatherAry[k];
                	n = n + to_string(sourceNode + 1) + "->";
               		while (f != sourceNode) {
                    	s = to_string(f + 1) + "->" + s;
                    	f = fatherAry[f];
                    	}
                	n = n + s + to_string(k + 1) + " : cost = " + to_string(bestCostAry[k]) + "\n";
                }
            	else{
                	if(fatherAry[k]==sourceNode){
                    	n = n + "The path from " + to_string(sourceNode + 1) + " to " + to_string(k + 1) + " : cost = " + to_string(bestCostAry[k]) + "\n";
                		}
					else{
                    	n = n + "The path from " + to_string(sourceNode + 1) + " to " + to_string(k + 1) + " : Impossible" + "\n";
                	}
            	}
                finalLine = finalLine + n;
                k++; //step 9: k is current node
            }
        return finalLine;
    }

        ~DijktraSSS(){
            delete[] fatherAry;
            delete[] markedAry;
            delete[] bestCostAry;
            for(int i=0; i<numNodes; i++){
                delete[] costMatrix[i];
                }
            delete[] costMatrix;
        }
};

int main(int argc, const char * argv[]) {
    ifstream inFile;   //step 0
    ofstream outFile1;
    ofstream outFile2;
    inFile.open(argv[1]);
    outFile1.open(argv[2]);
    outFile2.open(argv[3]);
    int n,a,b,c;
    inFile>>n;   // numNode<-- geet from input
  	//cout << n;
    //cout<<"read here";
    DijktraSSS sss = *new DijktraSSS(n);  //create DijkstraSSS class 
    while(inFile>>a>>b>>c){   //step 1: loadMatrix
        sss.insertcostMatrix(a-1, b-1, c);
    	//cout<<"broken here"<<endl;
    }
    for(int i=0; i<n; i++){  //step 11: repeat step 2 to 10 
        sss.setSourceNode(i);  // sourNode ==1  at beginning.
        outFile2<< "*************************************************\n";
        outFile2<< "Beginning: \n" << sss.debugPrint();
        outFile2<<sss.buildUp();
        outFile1<<sss.findAllShortestPath();  //step 8
        outFile2<< "Final: \n" + sss.debugPrint();
        outFile2<< "*************************************************\n";
    }
    outFile1.close();
    outFile2.close();
    inFile.close();
    
    return 0;
}
