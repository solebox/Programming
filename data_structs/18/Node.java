package AVL;
/** 
 * a node class for the AVLTree class
 * @author solekiller
 *
 */
public class Node {
	int key;
	int hight;
	int score,games,id;
	Node nodePointer;
	Node left,right,parent;
	Node nextInOrder,prevInOrder;
	AVLTree avlPointer;
	/**
	 * a node constructor method
	 * @param val - the value we want key to have
	 */
	public Node(int val){
		key = val;
		hight = 0;
		left = null;
		right = null;
		parent = null;
		nextInOrder = null;
		prevInOrder = null;
	}
	/**
	 * override toString to make the node a little more user friendly 
	 */
	public String toString(){
		return ""+key;
	}
	/**
	 * a copy constructor
	 * @return - copies key and satellite data
	 */
	public Node copy(){
		Node x =  new Node(key);
		x.score = score;
		x.games = games;
		x.id = id;
		return x;
	}
	
}
