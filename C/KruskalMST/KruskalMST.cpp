#include <iostream>
#include <fstream>

using namespace std;

class graphNode{
    public:
    int nodeID;
    graphNode * next;
    
    graphNode(int numb){
        nodeID = numb;
        next = NULL;
    }
    
    void insertNode(int numb){
        graphNode* newNode = new graphNode(numb);
        newNode->next = NULL;
    }
    
    void deleteNode(int numb){
        graphNode* taget = new graphNode(numb);
        free(taget);
    }
    
    ~graphNode(){
        delete next;
    }
};

class undirectedEdge{
    public:
    int Ni,Nj,edgeCost;
    undirectedEdge* next;
    undirectedEdge* listHead;
    
    undirectedEdge(int s1, int s2, int cost){
        Ni = s1;
        Nj = s2;
        edgeCost = cost;
        next = NULL;
    }
    
    string printEdge(undirectedEdge * T){
        string line = "PrintEdg list now: \n";
        while(T->next != NULL){
            line = line + to_string(T-> Ni) + "  " + to_string(T -> Nj)+ "  " + to_string(T -> edgeCost) + "\n";
            T = T -> next;
        }
        return line;
    }
    
    ~undirectedEdge(){
        delete next;
    }
    
    undirectedEdge* findSpot(undirectedEdge *listHead, int cost){
        undirectedEdge* spot = listHead;
        while( spot -> next != NULL && spot -> next -> edgeCost < cost){
            spot = spot -> next;
        }
        return spot;
    }
    
    void insert(undirectedEdge *listHead, undirectedEdge* newEdge){
        undirectedEdge* temp = findSpot(listHead, newEdge->edgeCost);
        newEdge -> next = temp -> next;
        temp -> next = newEdge;
    }
    
    void Delete(undirectedEdge* listHead, undirectedEdge* edge){
        undirectedEdge* temp = findSpot(listHead, edge -> edgeCost);
        temp -> next = temp -> next -> next; //always delete from front
    }
    
};

class KruskalMST{
    public:
    int numNodes, numSets, totalCost;
    int* inWhichSet;
    undirectedEdge* edgeListHead;
    undirectedEdge* MSTofG;
    
    KruskalMST(int n){
        edgeListHead = new undirectedEdge(-1, -1, -99999);//dummy node
        MSTofG= new undirectedEdge(-1, -1, -99999); //dummy node
        numNodes = n;
        numSets = numNodes;
        totalCost =0;
        inWhichSet =new int[numNodes+1];
        for(int i=1; i<numNodes; i++){
            inWhichSet[i]=i;
        }
    }
    
    string printMSTList(undirectedEdge* List){ //use MSTofG as dummy node for header
        string line = "********************************\n";
        line = line +"A MST of the input Graph: \n";
        line = line + "********************************\n";
        line = line + to_string(numNodes) + "\n";
        while(List -> next != NULL){
            line = line + to_string(List -> Ni) + "  "+to_string(List -> Nj) +"  "+ to_string(List -> edgeCost) + "\n";
            List = List -> next;
        }
        line = line +  to_string(List -> Ni) + "  "+ to_string(List -> Nj) +"  "+ to_string(List -> edgeCost) + "\n";
        line = line + "The total cost of the MST is: " + to_string(totalCost) + "\n";
        return line;
    }
    
    string printInWhichSet(){
        string n="InWhichSet array: \n";
        for(int i=0; i<numNodes; i++){
            n = n + to_string(i+1) +" "+ to_string(inWhichSet[i]) + "\n";
        }
        return n;
    }
    
    void mergeTwoSets( int ni, int nj){
        int min, max;
        
        if( inWhichSet[ni] <= inWhichSet[nj]){
            min = inWhichSet[ni];
            max = inWhichSet[nj];
        }else{
            min = inWhichSet[nj];
            max = inWhichSet[ni];
        }
        int index = min;
        while(index <= numNodes){
            if(inWhichSet[index]== max){
                inWhichSet[index] = min;
            }
            index++;
        }
    }
    
    ~KruskalMST(){
        delete[] inWhichSet;
        delete edgeListHead;
        delete MSTofG;
    }
    
};

int main(int argc, char ** argv){
    ifstream inFile(argv[1]);
    ofstream outFile1(argv[2]);
    ofstream outFile2(argv[3]);
    int n, s1,s2, cost;
    inFile>>n;
    int numbNodes = n;
    KruskalMST* s = new KruskalMST(numbNodes);
    while(inFile>>s1>>s2>>cost){
        undirectedEdge* newEdge = new undirectedEdge(s1,s2,cost);
        s->edgeListHead->insert(s->edgeListHead, newEdge);
    }
    //cout<<"1"<<endl;
    outFile2<<s->printInWhichSet();
    outFile2<<s->edgeListHead->printEdge(s->edgeListHead->next);
    //cout<<"2"<<endl;
    while(s->numSets>1){
        undirectedEdge* minEdge = s->edgeListHead->next;
        s->edgeListHead->Delete(s->edgeListHead, minEdge);
        if(s->inWhichSet[minEdge->Ni]!= s->inWhichSet[minEdge->Nj]){
            s->MSTofG->insert(s->MSTofG, minEdge);
            s->totalCost = s->totalCost + minEdge->edgeCost;
            s->mergeTwoSets(minEdge->Ni, minEdge->Nj);
            s->numSets--;
            outFile2<<s->MSTofG->printEdge(s->MSTofG->next);
            outFile2<<s->printInWhichSet();
        }
    }
    outFile1<<s->printMSTList(s->MSTofG->next);
    inFile.close();
    outFile1.close();
    outFile2.close();
    return 0;
    
}
