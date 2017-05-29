package proj7;

//package proj7;

//Project 7: HuffmanCoding
//XingSong Lin
//4/7/2016

import java.io.*;
import java.util.Scanner;


//step 1
class listBinTreeNode{
  String chStr;
  int prob;
  listBinTreeNode next;
  listBinTreeNode left;
  listBinTreeNode right;
  
  listBinTreeNode(String character, int numb){
      chStr = character;
      prob = numb;
      next = null;
      left = null;
      right = null;
  }
  
  listBinTreeNode(){
      chStr = " ";
      prob = 0;
      next = null;
      left = null;
      right = null;
  }
  
  String printNode(listBinTreeNode T){
      String line = "Node: \n";
      if( T.next == null){
          if(T.left == null || T.right == null) {
              line += "Node character: "+T .chStr + ", Node probability: "+ T .prob + ", next Node: NULL" + ", Node.left character: NULL, Node.right character: NULL\n";
          } else
              line += "Node character: "+T .chStr + ", Node probability: "+ T .prob + ", next Node: NULL" + ", Node.left character: "+T .left .chStr +", Node.right character:" +T .right .chStr + "\n";
          
      }
      else if( T.left == null || T.right ==null){
          line += "Node character: "+T .chStr + ", Node probability: "+ T .prob + ", next Node character "+ T .next .chStr + ", "+"Node.left: NULL" +", " + "Node.right: NULL" + "\n";
      }
      else{
          line += "Node character: "+T .chStr + ", Node probability: "+ T .prob + ", next Node character "+ T .next .chStr + ", Node.left character: "+T .left .chStr +", Node.right character: " +T .right .chStr + "\n";
      }
      return line;
  }

}

class HuffmanLinkedList {  //step2: construct Huffman ordered linkedlist.
 
  listBinTreeNode listHead;
  listBinTreeNode oldListHead;
  
  HuffmanLinkedList(){
      listBinTreeNode newNode = new listBinTreeNode("dummy", 0);
      listHead = newNode;
  }
  
  void listInsert(listBinTreeNode T){
      listBinTreeNode spot = findSpot(T.prob);
      T.next = spot.next;
      spot.next = T;
  }
  
  listBinTreeNode findSpot(int numb){
      listBinTreeNode spot = listHead;
      while((spot.next != null) && (spot.next.prob < numb)){
          spot = spot.next;
      }
      return spot;
  }
  
  boolean isEmpty(){
      if(listHead.next == null){
          return true;
      }
      return false;
  }
  
  String printList(){
      String title="List: \n";
      String list= " ";
      if(isEmpty()){
          list = "listHead -->( dummy , 0 , null )-null \n";
      }
      else{
          list = "listHead -->( dummy , " + listHead.prob + ", " + listHead.next.chStr +")-->";
          listBinTreeNode current = listHead;
          while(current.next.next != null){
              list = list + "(" + current.next.chStr +", " + current.next.prob + ", " + current.next.next.chStr + ")-->";
              current = current.next;
          }
          list = list + "(" + current.next.chStr + ", " + current.next.prob + ", " + "null)--> null\n";
      }
      return title+list;
  }

}


class HuffmanBinaryTree{   //step3: construct Huffman Binary Tree
  String chStr;
  int prob;
  String code;
  listBinTreeNode root;
  
  HuffmanBinaryTree(listBinTreeNode T){
      root = T;
  }
  
  void preOrderTraveral(listBinTreeNode T, FileWriter output2) throws IOException{
      if(T == null){
          return ;
      }
      else{
          output2.write(T.printNode(T));
          preOrderTraveral(T.left, output2);
          preOrderTraveral(T.right, output2);
      }
  }
  
  void constructCharCode(listBinTreeNode T, String code, FileWriter output1) throws IOException{
      if(T == null){
          output1.write("Empty");
      }
      else if (T.left == null || T.right == null) {
          //cout << T.printNode(T) << endl;
          output1.write(T.chStr + " " + code + " \n");
      }
      else {
          //cout << T.printNode(T) << endl;
          constructCharCode(T.right, code+"1", output1);
          constructCharCode(T.left, code+"0", output1);  
      }
  }
}

public  class proj7{
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
	File outputFile3 = new File(args[3]);
    if(!outputFile3.exists()){
        outputFile3.createNewFile();
    }
	FileWriter output3 = new FileWriter(outputFile3);

	HuffmanLinkedList list = new HuffmanLinkedList();
    output3.write("Creating list: \n");
	while(input.hasNext()){  //step 2.1, 2.2 & 2.6
		String word = input.next();
		int data = input.nextInt();
        listBinTreeNode newNode = new listBinTreeNode(word, data); //step 2.3
        list.listInsert(newNode);  //step 2.4
        output3.write(list.printList()); //step 2.5
    }
	input.close();  //step 2.7
	output3.write("\nEnd! \nCombining list now: \n\n");

	listBinTreeNode oldListHead = new listBinTreeNode(); //maybe dont need. //step 3.0
	//list.oldListHead.next = list.listHead.next;
	//list.oldListHead = list.listHead;
	while(list.listHead.next.next != null){ //step 3.3
        listBinTreeNode newNode = new listBinTreeNode();  //step 3.1
        newNode.chStr = list.listHead.next.chStr + list.listHead.next.next.chStr;
        newNode.prob = list.listHead.next.prob + list.listHead.next.next.prob;
        newNode.left = list.listHead.next;
        newNode.right = list.listHead.next.next;
        list.listHead.next = list.listHead.next.next.next;
        list.listInsert(newNode);

        output3.write(list.listHead.printNode(newNode)+"\n");  //step 3.2
        output3.write(list.printList()+"\n");
	}

	output3.close();

	HuffmanBinaryTree tree = new HuffmanBinaryTree(list.listHead); //step 3.4
	output1.write("HuffmanCoding Table: \n -------------------------------\n");
	tree.constructCharCode(list.listHead.next," ",output1);  //step 4
	output1.close();

	output2.write( "Tree Node: \n\n");
	tree.preOrderTraveral(list.listHead.next, output2);  //step 5
	output2.close();
	return;
	}
}