package AVL;

public class Node {
	int key;
	int hight;
	Node left,right,parent;
	Node nextInOrder,prevInOrder;
	public Node(int val){
		key = val;
		hight = 0;
		left = null;
		right = null;
		parent = null;
	}
	public String toString(){
		return ""+key;
	}
	
}
