
//Xing Song Lin
//Proj5: Bucket Sort
//3/8/2016

import java.io.*;
import java.util.Scanner;

class bucketSortAry{
    int[] bucketAry;
    int bucketSize;
    
    bucketSortAry(int size){
        bucketAry = new int[size];
        bucketSize = size;
        for(int i=0; i<bucketSize; i++){
            bucketAry[i]=0;  //step 3.1: initiallize the array to zero
        }
    }
    
    void insertElements(int data){
        bucketAry[data]++;              //step 7
    }
    
    String printBucketAry(){   //step 10
        String index = " ";
        String  detail = " ";
        for(int i=0; i<=18; i++){
            index = index+ i + " ";
        }
        for(int i=0; i<=18; i++){
           detail = detail + bucketAry[i] + " ";
        }
        String finalLine = "Table for BucketSort Array: \n" + index + " \n" + detail + "\n";
        return finalLine;
    }
    
    String printSortedData(int min){  //step 11
        String table= "the Sorted Data: \n";
        for(int i=0; i<bucketSize; i++){
            while(bucketAry[i] >0){
                table = table + (i+min) + " ";
                bucketAry[i]--;
            }
        }
        table=table + "\n";
        return table;
    }
}

public class bucketSortProj5 {
	 public static void main(String[] argv) throws IOException{
		//step1: inFile
		File inputFile = new File(argv[0]);
		Scanner input = new Scanner(inputFile);
	    File outputFile = new File(argv[1]);
	    FileWriter output1 = new FileWriter(outputFile);
	    File outputFile2 = new File(argv[2]);
	    FileWriter output2 = new FileWriter(outputFile2);
		    
		    int temp, data, count = 0, offSet, minData = 9999999, maxData=0, size;
		    
		    while(input.hasNextInt()){    //step1.1: find Min & Max,
		        count++;
		        temp = input.nextInt();
		        if(temp>maxData){
		            maxData=temp;
		        }
		        if(temp<minData){
		            minData=temp;
		        }
		    }
		    offSet = minData;   //step 2: offSet, and declare the size.
		    size = maxData-minData+1;   //defind size for bucketAry.
		    bucketSortAry bucketAry = new bucketSortAry(size);
		    
		    input.close();      //step1.2: close file and reopen.
		    Scanner input1= new Scanner(inputFile);    //step 4: re-open
		    
		    while(input1.hasNext()){     //Step 5: data <--read from file & step 9
		    	data = input1.nextInt();
		    	bucketAry.insertElements(data-offSet);  //step 6: put data to bucketAry,
		                                                //data = data-offSet.
		    }
		    output2.write(bucketAry.printBucketAry());   //step 8 & 10
		    output1.write(bucketAry.printSortedData(offSet)); //step 11
		    input1.close();      //step 12
		    output1.close();
		    output2.close();
	}
}
