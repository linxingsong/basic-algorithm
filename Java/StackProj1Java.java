import java.io.*;
import java.util.Scanner;
//project: stack implementation using array on java
//Xing Song Lin
//Data: 2/6/2016


public class StackProj1Java{ 
	 
	public static void main(String[] args) {   
		int count = 0;
		int numb;
		String name = null;
		try{
			System.out.println("Enter filename: ");  //step1
			Scanner in= new Scanner(System.in);
			name = in.next();
			Scanner inFile = new Scanner(new FileReader(name));	
			if(0< args.length){
				new File(args[0]);
			}
			while(inFile.hasNext()){		//step 2
				numb=inFile.nextInt();
				count++;  				//step 3
				System.out.println("number in file is: "+numb);
				
			}
			System.out.println("Total number in file is " + count);
			in.close(); 		//step 5
			inFile.close();
		}catch (Exception e){
			System.out.println("File read Error: "+ e.getMessage());
		}
		
		StackArray stack = new StackArray(count); 
		Scanner readFile = null;
		try {						//step 6
			readFile = new Scanner(new FileReader(name));
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		System.out.println("Start pushing to stack: ");
		
		int value=0;
		int data;
		while(readFile.hasNext()){    //step 8
			data= readFile.nextInt();
			System.out.println("Push: "+ data);
			stack.push(data);  			//step 7
		}
		
		while(!stack.isEmpty()){		//step 11
			int first = stack.ttop();
			System.out.println("popping: "+ first);		//step 10
			stack.pop();			//step 9
		}
		readFile.close();			//step12
		
	}
}
