package AVL;
/**
 * hopefully a relieble AVL class that holds max,min,size and in-order pointers 
 * to the next and prev nodes.
 * 
 * @author solekiller
 *
 */
public class AVLTree {
	int size;
	Node root;
	Node max;
	Node min;
/**
 * tree constructor , very strait forward
 */
	public AVLTree(){
		root = null;
		max = null;
		min = null;
		size = 0;
	}
	/**
	 * finds a nodes successor node
	 * @param x - the node in question
	 * @return - x's successor node
	 */
	private Node treeSuccessor(Node x){
		if ( x.right != null ){
			return treeMin(x.right);
		}
		Node y = x.parent;
		while ( y != null && x == y.right){
			x = y;
			y = y.parent;
		}
		return y;
	}
	/**
	 * finds a node's predecessor
	 * @param x - the node in question 
	 * @return - x's predecessor
	 */
	private Node treePredecessor(Node x){
		if ( x.left != null ){
			return treeMax(x.left);
		}
		Node y = x.parent;
		while ( y != null && x == y.left){
			x = y;
			y = y.parent;
		}
		return y;
	}
	/**
	 * a method that foes left.
	 * @param q - node to start from
	 * @return - smallest key node. 
	 */
	private Node treeMin(Node q){
		while (q != null && q.left != null){
			q = q.left;
		}
		return q;
	}
	/**
	 * looks for the biggest node in a tree
	 * @param q - the start node
	 * @return - the resulting node
	 */
	private Node treeMax(Node q){
		while (q != null && q.right != null){
			q = q.right;
		}
		return q;
	}
	/**
	 * returns a nodes hight , if its null it will return -1
	 * @param q - we want this nodes hight
	 * @return - q's hight
	 */
	private int hight(Node q){
		if (q == null){
			return -1;
		}else{
			return q.hight;
		}
	}
	/**
	 * helper mthod to compute hights using a nodes sons
	 * @param q - the node
	 */
	private void computeHight(Node q){
		if (q != null){
			q.hight = 1 + Math.max(hight(q.left), hight(q.right));
		}
	}
	/**
	 * calculated a node's balance factor.
	 * @param q - node in question
	 * @return - q's balance factor
	 */
	private int balanceFactor(Node q){
		return hight(q.left)-hight(q.right);
	}
	/**
	 * calculates which of a node's sons is higher
	 * @param q - the father node
	 * @return - the highest son of the two q has
	 */
	private Node higherSon(Node q){
		if (hight(q.left) > hight(q.right)){
			return q.left;
		}else if (hight(q.left) < hight(q.right)){
			return q.right;
		}else{
			return null;
		}
	}
	/**
	 * checks if a tree/subtree is unbalanced
	 * @param q - the root of that tree
	 * @return
	 */
	private boolean unbalanced(Node q){
		return Math.abs(balanceFactor(q)) > 1;
	}
	/**
	 * left rotation method based on the AVL algorithm 
	 * @param x - the node around which the rotation accures 
	 */
	private void leftRotate(Node x){
		Node y = x.right;
		x.right = y.left;
		if (y.left != null){
			y.left.parent = x;
		}
		y.parent = x.parent;
		if ( x.parent == null){
			root = y;
		}else if (x == x.parent.left){
			x.parent.left = y;
		}else{
			x.parent.right = y;
		}
		y.left = x;
		x.parent = y;
		computeHight(x);
		computeHight(y);
	}
	/**
	 * a right rotation method based on the AVL algorithm 
	 * @param x - the node around which the rotation accures 
	 */
	private void rightRotate(Node x){
		Node y = x.left;
		x.left = y.right;
		if (y.right != null){
			y.right.parent = x;
		}
		y.parent = x.parent;
		if ( x.parent == null){
			root = y;
		}else if (x == x.parent.right){
			x.parent.right = y;
		}else{
			x.parent.left = y;
		}
		y.right = x;
		x.parent = y;
		computeHight(x);
		computeHight(y);
	}
	/**
	 * a method that rebalances an unbalanced tree
	 * @param q - the unbalanced tree's root
	 */
	private void rebalance(Node q){
		Node r = higherSon(q);
		Node s = higherSon(r);
		if (s == null){
			if (r == q.left){
				s = r.left;
			}else{
				s = r.right;
			}
		}
		if (r == q.left){
			if (s == r.right){
				leftRotate(r);
				rightRotate(q);
			}else if(s == r.left){
				rightRotate(r);
				leftRotate(q);
			}
		}
		
	}
	/**
	 * a method used to insert a new node into the AVL tree
	 * @param z - the node we want to insert
	 */
	public void treeInsert(Node z){
		size = size+1;
		if (max != null && z.key > max.key){
			max = z;
		}else if (max == null){
			max = z;
		}
		if (min != null && z.key < min.key){
			min = z;
		}else if (min == null){
			min = z;
		}
		Node y = null;
		Node x = root;
		Node critical = null;
		while (x != null){
			if ( balanceFactor(x) != 0 ){
				critical = x;
			}
			y = x;
			if (z.key < x.key){
				x = x.left;
			}else{
				x = x.right;
			}
		}
		z.parent = y;
		if (y == null){
			root = z;
		}else if (z.key < y.key){
			y.left = z;
		}else{
			y.right = z;
		}
		while (y != critical){
			computeHight(y);
			y = y.parent;
		}
		if (y != null && unbalanced(y)){
			rebalance(y);
		}
		addInOrderPointers(z);
	}
	/**
	 * a method to delete a node from the AVL tree
	 * @param z - a pointer to the node we want to delete
	 */
	public Node treeDelete(Node z){
		if (z == null)
			return null;
		size = size - 1;
		delInOrderPointers(z);
		Node x,y,r;
		int tmp;
		boolean flag;
		boolean maxpresent=false;
		boolean minpresent=false;
		if (z == max)
			maxpresent = true;
		if (z == min)
			minpresent = true;
		if (z.left == null || z.right == null){
			y = z;
		}else{
			y = treeSuccessor(z);
		}
		if (y.left != null){
			x = y.left;
		}else{
			x = y.right;
		}
		if (x != null){
			x.parent = y.parent;
		}
		if (y.parent == null){
			root = x;
		}else if (y == y.parent.left){
			y.parent.left = x;
		}else{
			y.parent.right = x;
		}
		if ( y != z ){
			z.key = y.key;
			z.score = y.score;
			z.id = y.id;
			z.games = y.games;
			z.avlPointer = y.avlPointer;
			z.nodePointer = y.nodePointer;
		}
		r = y.parent;
		flag = true;
		while (r != null && flag){
			tmp = hight(r);
			computeHight(r);
			if (unbalanced(r)){
				rebalance(r);
				r = r.parent;
			}
			if (tmp == hight(r)){
				flag = false;
				r = r.parent;
			}
		}
		if (maxpresent){
			max = treeMax(root);
		}
		if (minpresent){
			min = treeMin(root);
		}
		delInOrderPointers(z);
		return y;
	}
/**
 * searches for a node that has the num int key
 * @param num - the value we search for in all the nodes
 * @return - the first (and in our case the only) node that has that key
 */
	public Node search(int num){
		Node x = root;
		while (x != null && num != x.key  ){
			if (num < x.key)
				x = x.left;
			else
				x = x.right;
		}
		return x;
	}
	/**
	 * searches for a node that has num as its key and then uses treeDelete on it
	 * O(lgn)
	 * @param num - the value we search for
	 */
	public void remove(int num){ // look for node with key=num and delete (else do nothing)
		treeDelete(search(num));
	}
	/** 
	 * a method that updates successor and predecessor pointers in nodes that are
	 * just inserted
	 * @param z - the node that is updated
	 */
	private void addInOrderPointers(Node z){
		if (z != null){
			Node prev = treePredecessor(z);
			Node next = treeSuccessor(z);
			if (prev != null)
				prev.nextInOrder = z;
			if (next != null)
				next.prevInOrder = z;
			z.nextInOrder = next;
			z.prevInOrder = prev;	
		}
	
	}
	/**
	 * a method that removes a deleted node's pointers and 
	 * corrects the gap its absence  has caused 
	 * @param z - the node in question
	 */
	private void delInOrderPointers(Node z){
		if (z != null){
			Node prev = z.prevInOrder;
			Node next = z.nextInOrder;
			if (prev != null)
				prev.nextInOrder = next;
			if (next != null)
				next.prevInOrder = prev;
		}
	}

	
}
