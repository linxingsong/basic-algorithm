//proj6: QuadTree
//Xing Song Lin

#include <iostream>
#include <fstream>
using namespace std;

class QuadTreeNode{     //step 0: prepare everything.
    friend class QuadTree;
    friend class image;
    
public:
    int numRows, numCols, minVal, maxVal, color, rowOffset, colOffset;
    QuadTreeNode* NW_kid;
    QuadTreeNode* SW_kid;
    QuadTreeNode* SE_kid;
    QuadTreeNode* NE_kid;
    
    
    QuadTreeNode(int r, int c, int rowOff, int colOff){
        numRows = r;
        numCols = c;
        rowOffset = rowOff;
        colOffset = colOff;
    }
    
    //printNode
    void printNode(QuadTreeNode *T, ofstream &of1){
        if(T == NULL){
            return ;
        }
        else if(T -> NW_kid == NULL || T->SW_kid == NULL || T->SE_kid == NULL || T->NE_kid == NULL){
            of1<< T->color << " "<< T->numRows << " "<<T->numCols<<" "<< T->minVal<< " "<<T->maxVal<< " "<<T->rowOffset<< " "<<T->colOffset<<" \n";
        }
        else{
            of1<< T->color << " " << T->numRows <<  " " << T->numCols << " " << T->minVal << " " << T->maxVal << " "<< T->rowOffset << " " << T->colOffset << " " << T->NW_kid->color << " " <<T->SW_kid->color << " " << T->SE_kid->color <<T->NE_kid->color << "\n";
        }
    }
    
    //deconstructor
    ~QuadTreeNode(){
        delete NW_kid;
        delete SW_kid;
        delete SE_kid;
        delete NE_kid;
    }
    
    //compute methods
    void computenumRowsCols(QuadTreeNode *T){
        if(T == NULL){
            return ;
        }
        if(T->color==0 || T->color ==1){
            T-> numRows = T-> numRows;
            T-> numCols = T-> numCols;
        }
        if(T->color ==2){
            T-> numRows = T-> numRows;
            T-> numCols = T-> numCols;
            T->NW_kid->numRows = T->numRows/2;
            T->NW_kid->numCols = T->numCols/2;
            T->SW_kid->numRows = T->numRows/2;
            T->SW_kid->numCols = T->numCols/2;
            T->SE_kid->numRows = T->numRows/2;
            T->SE_kid->numCols = T->numCols/2;
            T->NE_kid->numRows = T->numRows/2;
            T->NE_kid->numCols = T->numCols/2;
        }
    }

void computeOffset(QuadTreeNode *T){
    if(T == NULL){
        return ;
    }
    if(T != NULL){
        T-> rowOffset = T-> rowOffset;
        T-> colOffset = T-> colOffset;
        if(T->NW_kid != NULL){
            T->NW_kid->rowOffset = T->rowOffset;
            T->NW_kid->colOffset = T->colOffset;
        }
        if (T->SW_kid != NULL){
            T->SW_kid->rowOffset = T->rowOffset + (T->numRows/2);
            T->SW_kid->colOffset = T->colOffset;
        }
        if (T->SE_kid != NULL){
            T->SE_kid->rowOffset = T->rowOffset + (T->numRows/2);
            T->SE_kid->colOffset = T->colOffset + (T->numCols/2);
        }
        if (T->NE_kid != NULL) {
            T->NE_kid->rowOffset = T->rowOffset;
            T->NE_kid->colOffset = T->colOffset + (T->numCols/2);
        }
    }
}

void computeColor(QuadTreeNode *T){
    if((T-> minVal = T->maxVal) && T->maxVal ==0){
            T-> color =0;
        }
    else if((T->minVal = T->maxVal)&&T->minVal ==1){
            T->color =1;
        }
    else if((T-> minVal != T->maxVal)){
        T-> color =2;
    }
}

void computeMinMax(QuadTreeNode *T, int** ary){
    numRows = T-> numRows;
    numCols = T-> numCols;
    rowOffset = T-> rowOffset;
    colOffset = T-> colOffset;
    for(int i = rowOffset; i<numRows; i++){
        for(int j= colOffset; j<numCols; j++){
            if(ary[i][j]==ary[i][j+1] && ary[i][j] == ary[i+1][j]){  //each cell equl, min max will equal too.
                T->minVal=ary[rowOffset][colOffset];
                T->maxVal=ary[rowOffset][colOffset];
            }
            else {
                T->minVal =0;
                T->maxVal =1;
            }
        }
    }
}
};

class QuadTree{
public:
    QuadTreeNode* root;
    
    QuadTree(int r, int c, int** ary, ofstream &of1){  //step 4 run here, create the quadtree root.
        QuadTreeNode *newNode = new QuadTreeNode(r,c,0,0);
        root = newNode; //declare this newNode is root for the QuadTree.
        buildQuadTree(root, ary);
        printQuadTree(root, of1);    //Step 6: printQuadTree.
    }
    
    void buildQuadTree(QuadTreeNode *T, int** ary){  //step 5: buildQuadTree
        T->computeMinMax(T, ary); ////assign min max for this root node.
        T->computeColor(T);  // declare color base on the minVal and maxVal.
        T->computenumRowsCols(T);//declare the numRos and numCols. also compute kid's rows & cols base on the node condition.
        T->computeOffset(T);// decalre the offset for the root, and his 4 kid's offset.
        if(T == NULL){
            return ;
        }
        if( T->color == 0 || T->color ==1){   //not gray node, dont need to creat new node.
            return ;
        }
        if(T-> color ==2){
            QuadTreeNode *newNW_kid = new QuadTreeNode(T->NW_kid->numRows, T->NW_kid->numCols, T->NW_kid->rowOffset, T->NW_kid->colOffset);
            T->NW_kid = newNW_kid;
            buildQuadTree(T->NW_kid, ary);
            
            QuadTreeNode *newSW_kid = new QuadTreeNode(T->SW_kid->numRows, T->SW_kid->numCols, T->SW_kid->rowOffset, T->SW_kid->colOffset);
            T->SW_kid = newSW_kid;
            buildQuadTree(T->SW_kid, ary);
            
            QuadTreeNode *newSE_kid = new QuadTreeNode(T->SE_kid->numRows, T->SE_kid->numCols, T->SE_kid->rowOffset, T->SE_kid->colOffset);
            T-> SE_kid = newSE_kid;
            buildQuadTree(T->SE_kid, ary);
            
            QuadTreeNode *newNE_kid = new QuadTreeNode(T->NE_kid->numRows, T->NE_kid->numCols, T->NE_kid->rowOffset, T->NE_kid->colOffset);
            T-> NE_kid = newNE_kid;
            buildQuadTree(T->NE_kid, ary);
        }
    }
    //printQuadTree
    void printQuadTree(QuadTreeNode *T,ofstream &of1){
        if(T == NULL){
            return ;
        }
        else{
            T->printNode(T, of1);
            printQuadTree(T->NW_kid, of1);
            printQuadTree(T->SW_kid, of1);
            printQuadTree(T->SE_kid, of1);
            printQuadTree(T->NE_kid, of1);
        }
    }
    
    ~QuadTree(){
        delete root;
    }
};

class image{
public:
    int numRows, numCols, minVal, maxVal, color;
    int** imgAry;
    
    //Step 2: make image. dynamical space
    void makeImgAry(ifstream &inputFile, const char* input){
        int **imgAry = new int*[numRows];
        for(int i=0; i<numRows; i++){
            imgAry[i]= new int[numCols];
        }
        loadImage(inputFile, imgAry);
    }
    
    //Step 3:load Image:
    void loadImage(ifstream &inputFile, int** imgAry){
        for(int i = 0; i<numRows; i++){
            for(int j = 0; j<numCols; j++){
                inputFile >> imgAry[i][j];   //fill in 2d array
                //cout<< imgAry[i][j]<<" ";
            }
        }
    }
    
    //img, inputfile and fill in data.
    image(const char* input, const char* output1, const char* output2){
        ifstream inputFile;
        ofstream of1;
        ofstream of2;
        inputFile.open(input);   //step 1:  open file, read image header.
        of1.open(output1);
        of2.open(output2);
        inputFile>>numRows>>numCols>>minVal>>maxVal;
        cout<< "Check header: "<<numRows<<" "<<numCols<<" "<<minVal<<" "<<maxVal<<endl;  //check
        makeImgAry(inputFile, input);      //step2: makeImgAry
        QuadTree tree(numRows, numCols, imgAry, of1);   //step 4
        inputFile.close();
        of1.close();
        of2.close();
    }
};

int main(int argc, char** argv){
    
    image imgAry(argv[1], argv[2], argv[3]);
    
    return 0;
}
