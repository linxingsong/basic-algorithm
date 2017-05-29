import java.io.*;
import java.util.Scanner;
//Xing Song Lin
//Proj4: Heap Sort
//Based on 1D implementation of Partial Order Binary Trees 
//2/22/2016
 class buildHeap{
	int[] heapAry;
	int heapSize; 
	int arraySize;
	//step 1.4
	buildHeap(int count){
		arraySize = count +1;
		heapAry = new int[arraySize];
		heapAry[0] = 0;
	}
	boolean isHeapEmpty(){
		return heapSize==0;
	}
	boolean isHeapFull(){
		return heapSize == arraySize-1;
	}
	int leftChild(int index){
		return 2+index;
	}
	int rightChild(int index){
		return 2*index+1;
	}
	int parent(int index){
		return index/2;
	}
	void insertOneDataItm(int data){
		 heapSize++;  //step 2.3
		 heapAry[heapSize]=data;
	     bubbleUp(heapSize);
	}
	void bubbleUp(int index){
        if(index==1) return;
        int parentIndex = parent(index);
        if(heapAry[index]<heapAry[parentIndex]){
            swap(index,parentIndex);
            bubbleUp(parentIndex);
        }
    }
	void swap(int i, int j) {
		int temp=heapAry[i];
		heapAry[i]=heapAry[j];
		heapAry[j]=temp;
	}
	//delete data.
    void deleteRoot(){
            //step 3.2
            heapAry[1] = heapAry[heapSize];
            heapSize--;   //heapAry[0]--
            bubbleDown(1);
    }

    void bubbleDown(int index){
        int left, right, size, min;
        left = leftChild(index);
        right = rightChild(index);
        size = heapSize;
        if(left > size){  //data is on the leaf.
            return;
        }
        else if(left == size){ //left is index at the end of tree/heapAry
            if(heapAry[left]<heapAry[index]){
                swap(left, index);
                bubbleDown(index);
            }
        }
        else if(right == size){
        	if (heapAry[left] <= heapAry[right]){
        		min = left;
        		}
        	else {
        		min = right;
        	}
        if(heapAry[min] <= heapAry[index]){
            swap(min, index);
            bubbleDown(min);
        	}
        }
    }
  //print heap, save as string.
    String printHeap(int data){
		String word = " ";
		for(int i=1; i<=heapSize; i++){
			word = word + " "+ heapAry[i];
		}
		word = word + " \n";
		return word;
	}
}
public class HeapSortProj4 {
	public static void main(String[] argv) throws IOException{
	    //step 1.1: open the input file.
		File inputFile = new File(argv[0]);
		Scanner input= new Scanner(inputFile);
	    File outputFile = new File(argv[1]);
	    FileWriter output1 = new FileWriter(outputFile);
	    File outputFile2 = new File(argv[2]);
	    FileWriter output2 = new FileWriter(outputFile2);
	    
	    int data = 0;
	    int count = 0;
	    //step 1.2: data from input file
		while(input.hasNextLine()){
			while(input.hasNextInt()){ // reads all ints from current line
				count++;
				input.nextInt();
			}
			input.nextLine(); /// moves to next line
		}
	    //step 1.3: close file
	    input.close();
	    Scanner input1= new Scanner(inputFile);
	    buildHeap tree = new buildHeap(count+1);
	    while(input1.hasNext()){     //step 2.1,2.2 & 4
	    	data = input1.nextInt();
	        tree.insertOneDataItm(data);  //step 2
	        String line = tree.printHeap(data);  //save data as string.
	        output1.write(line);  //write to output1 file.
	        
	    }	    
	    while(!tree.isHeapEmpty()){    //step 3.1 & 4
	        tree.deleteRoot();    //step 3
	        String line2 = tree.printHeap(data);
	        output2.write(line2);
	    }
	    input1.close();
	    output1.close();
	    output2.close();	
	}
}