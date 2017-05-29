
public class StackArray {   //step 0
	private int top;
	int size;
	int[] stack;
	
	public StackArray(int arraysize){
		size=arraysize;
		stack = new int[size];
		top=-1;
	}
	
	public void push(int value){
		if(top==size-1){
			System.out.println("Stack is full!");
		}
		else {
			top++;
			stack[top]=value;
		}
	}
	
	public void pop(){
		if(!isEmpty())
			top--;
		else {
			System.out.println("Stack Empty now.");
		}
	}
	
	public boolean isEmpty(){
		return top==-1;
	}
	
	public int ttop(){
		if(top==-1) {
			System.out.println("Stack empty.");
		}
		return stack[top];
	}
	
}
