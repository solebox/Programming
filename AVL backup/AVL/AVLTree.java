package AVL;

public class AVLTree {
	Node root;
	Node max;
//	helper methods
	public AVLTree(){
		root = null;
		max = null;
	}
	public Node treeSuccessor(Node x){
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
	public Node treePredecessor(Node x){
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
	public Node treeMin(Node q){
		while (q.left != null){
			q = q.left;
		}
		return q;
	}
	public Node treeMax(Node q){
		while (q.right != null){
			q = q.right;
		}
		return q;
	}
	public int hight(Node q){
		if (q == null){
			return -1;
		}else{
			return q.hight;
		}
	}
	public void computeHight(Node q){
		if (q != null){
			q.hight = 1 + Math.max(hight(q.left), hight(q.right));
		}
	}
	public int balanceFactor(Node q){
		return hight(q.left)-hight(q.right);
	}
	public Node higherSon(Node q){
		if (hight(q.left) > hight(q.right)){
			return q.left;
		}else if (hight(q.left) < hight(q.right)){
			return q.right;
		}else{
			return null;
		}
	}
	public boolean unbalanced(Node q){
		return Math.abs(balanceFactor(q)) > 1;
	}
//	rotations thank god they atleast work
	public void leftRotate(Node x){
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
	public void rightRotate(Node x){
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
	public void rebalance(Node q){
		Node r = higherSon(q);
		Node s = higherSon(r);
		if (s == null){
			if (r == q.left){
				rightRotate(q);
			}else{
				leftRotate(q);
			}
		}
		if (r == q.left){
			if (s == r.right){
				leftRotate(r);
				rightRotate(q);
			}else if ( s == r.left){
				rightRotate(q);
			}
		}
		else if (r == q.right){
			if (s == r.left){
				rightRotate(r);
				leftRotate(q);
			}else if ( s == r.right){
				leftRotate(q);
			}
		}
		
	}
	public void treeInsert(Node z){
		if (max != null && z.key > max.key){
			max = z;
		}else if (max == null){
			max = z;
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
	}
	public Node treeDelete(Node z){
		Node x,y,r;
		int tmp;
		boolean flag;
		boolean maxpresent=false;
		if (z == max)
			maxpresent = true;
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
		}
		r = y.parent;
		flag = true;
		while (r != null && flag){
			tmp = r.hight;
			computeHight(r);
			if (unbalanced(r)){
				rebalance(r);
				r = r.parent;
			}
			if (tmp == r.hight){
				flag = false;
				r = r.parent;
			}
		}
		if (maxpresent){
			max = findmax(root);
		}
		return y;
	}
	public void insertArr(int[] A){ // will be removed (works)
		for (int i = 0; i < A.length; i++) {
			treeInsert(new Node(A[i]));
		}
	}
	public void printTree(){ // will be removed (works) inorder
		printy(root);
	}
	public void printy(Node q){ //will be removed (works)
		if ( q != null){
			printy(q.left);
			System.out.print(q.key+" ");
			printy(q.right);
		}
	}
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
	public void searchAndDestroy(int num){ // look for node with key=num and delete (else do nothing)
		treeDelete(search(num));
	}
	public Node findmax(Node r){ //return max
		while (r.right != null){
			r = r.right;
		}
		return r;
	}
	
}
