import java.io.*;
import java.util.Scanner;

//Project 2: Stack implementation using link list
//Xing Song Lin
// 02/10/2016

public class StackProj2Java {

	public static void main(String[] args) throws FileNotFoundException{
		int data;		 
		String fileName = args[0];     //step 1
		Scanner inFile = new Scanner(new FileReader(fileName));
		StackLinkList stack = new StackLinkList();
		System.out.println("Reading the file......");
		
		while(inFile.hasNext()){   //step 4
			 data= inFile.nextInt();    //step 2
			stack.push(data);    //step 3
		}
		
		inFile.close();   //step 5
		
		System.out.println(" ");
		System.out.println("Finish pushing, Start to pop now.");
		System.out.println(" ");
		
		int finish = 1;  
		while(finish != 0){  //step 7
			stack.pop();		//step 6
			if(stack.isEmpty()==true){
				finish = 0;
			}
		}
		
		System.out.println("Finish pop. Stack is empty.");
		return;
	}
}