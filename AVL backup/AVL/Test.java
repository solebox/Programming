package AVL;

public class Test {
	public static void main(String arg[]){
		AVLTree tree = new AVLTree();
		int[] arr = {1,2,3,5,6,7,8};
		Node z = new Node(4);
		tree.treeInsert(z);
		tree.insertArr(arr);
		tree.searchAndDestroy(8);
		System.out.print(tree.treePredecessor(tree.max));
	}
}
