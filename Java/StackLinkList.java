
//step 0
public class StackLinkList { 
	int data;
	ListNode top;
	ListNode newNode;
	StackLinkList(){
		top = null;
	}
	
	void push(int value){
		ListNode newNode = new ListNode();
		newNode.data = value;
		newNode.next = top;
		top = newNode;
		System.out.println("Push: "+ newNode.data + " Address: "+ newNode);
	}
	
	int pop(){
		ListNode temp = top;
		top = top.next;
		temp.next= null;
		int data = temp.data;
		System.out.println("Pop: "+temp.data+" Address: "+temp);
		return data;
	}
	
	boolean isEmpty(){
		return top == null;
	}
}
