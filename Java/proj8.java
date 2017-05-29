package proj8;
import java.io.*;
import java.util.Scanner;

class DijktraSSS{
    private int numNodes, sourceNode, minNode, newCost, currentNode;
    private int costMatrix[][];
    private int fatherAry[];
    private int markedAry[];
    private int bestCostAry[];
    
    DijktraSSS(int x){
        numNodes = x;
        fatherAry = new int[numNodes];
        markedAry = new int[numNodes];
        bestCostAry = new int[numNodes];
        costMatrix = new int[numNodes][numNodes];
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

    String printSourceNode(){
        String line = "\n";
        line = line + "Source node is: "+ Integer.toString(sourceNode+1)+ "\n";
        return line;
    }

    String printFatherAry(){
        String fatherAryLine = "fatherAry: ";
        for(int i=0; i<numNodes; i++){
            fatherAryLine = fatherAryLine + Integer.toString(fatherAry[i] +1) + " ";
        }
        fatherAryLine = fatherAryLine + "\n";
        return fatherAryLine;
    }

    String printBestCostAry(){
        String bestCostAryLine= "Best Cost Ary: ";
        for(int i =0; i<numNodes; i++){
            bestCostAryLine = bestCostAryLine + Integer.toString(bestCostAry[i]) + " ";
        }
        bestCostAryLine = bestCostAryLine+"\n";
        return bestCostAryLine;
    }

    String printMarkedAry(){
        String MarkedAryLine = "MarkedAry: ";
        for(int i=0; i<numNodes; i++){
            MarkedAryLine = MarkedAryLine+ Integer.toString(markedAry[i]) + " ";
        }
        MarkedAryLine = MarkedAryLine+"\n";
        return MarkedAryLine;
    }

    String debugPrint(){ //step 2: load all Arrays
        String finalyLine = "------------------------------------";
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

    String buildUp(){
        String s = "";
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
            s = s+ "minNode: "+ Integer.toString(minNode+1)+ "\n";
            s = s+ debugPrint();  //call debugPrint
            s = s+ expanding();
        }
        return s;
    }

    boolean markedNode(){
        for(int i=0; i<numNodes; i++){
            if(markedAry[i]==0){
                return false;
            }
        }
        return true;
    }

    String expanding(){  //step 4
        String s = "";
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

    String findAllShortestPath() {
        String finalLine = "";
        finalLine = finalLine +"=============================\n"+ "The graph has " + Integer.toString(numNodes) + " nodes.\n"+"=============================\n=============================\n"+"\nT.he source node = " + Integer.toString(sourceNode + 1) + "." + "\n";
        int k = 0;
        while (k < numNodes) { //step 10
        	String n="";
        	String s="";
        	if(fatherAry[k]!=k){  //step 8
           		 n = n + "The path from " + Integer.toString(sourceNode + 1) + " to " + Integer.toString(k + 1) + " :";
            	int f = fatherAry[k];
            	n = n + Integer.toString(sourceNode + 1) + "->";
           		while (f != sourceNode) {
                	s = Integer.toString(f + 1) + "->" + s;
                	f = fatherAry[f];
                	}
            	n = n + s + Integer.toString(k + 1) + " : cost = " + Integer.toString(bestCostAry[k]) + "\n";
            }
        	else{
            	if(fatherAry[k]==sourceNode){
                	n = n + "The path from " + Integer.toString(sourceNode + 1) + " to " + Integer.toString(k + 1) + " : cost = " + Integer.toString(bestCostAry[k]) + "\n";
            		}
				else{
                	n = n + "The path from " + Integer.toString(sourceNode + 1) + " to " + Integer.toString(k + 1) + " : Impossible" + "\n";
            	}
        	}
            finalLine = finalLine + n;
            k++; //step 9: k is current node
        }
    return finalLine;
    }

 /**   ~DijktraSSS(){
        delete[] fatherAry;
        delete[] markedAry;
        delete[] bestCostAry;
        for(int i=0; i<numNodes; i++){
            delete[] costMatrix[i];
            }
        delete[] costMatrix;
    } */
}

public class proj8{
	public static void main(String[] args) throws IOException{
		//step 2.0
		File inputFile = new File(args[0]);
		Scanner input= new Scanner(inputFile);
		File outputFile = new File(args[1]);
	    if(!outputFile.exists()){
	        outputFile.createNewFile();
	    }
		FileWriter output1 = new FileWriter(outputFile);
		File outputFile2 = new File(args[2]);
	    if(!outputFile2.exists()){
	        outputFile2.createNewFile();
	    }
		FileWriter output2 = new FileWriter(outputFile2);
		int n,a,b,c;
		input.hasNext();
		n= input.nextInt();// numNode<-- geet from input
	    DijktraSSS sss = new DijktraSSS(n);  //create DijkstraSSS class 
	    while(input.hasNext()){   //step 1: loadMatrix
	       a=input.nextInt();
	       b=input.nextInt();
	       c=input.nextInt();
	    	sss.insertcostMatrix(a-1, b-1, c);
	    	//cout<<"broken here"<<endl;
	    }
	    for(int i=0; i<n; i++){  //step 11: repeat step 2 to 10 
	        sss.setSourceNode((n- 1+i)%n);  // sourNode ==1  at beginning.
	        output2.write( "*************************************************\n");
	        output2.write( "Beginning: \n" + sss.debugPrint());
	        output2.write(sss.buildUp());
	        output1.write(sss.findAllShortestPath());  //step 8
	        output2.write( "Final: \n" + sss.debugPrint());
	        output2.write("*************************************************\n");
	    }

       input.close();
       output1.close();
       output2.close();

	}

}

