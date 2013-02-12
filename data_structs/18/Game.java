package AVL;

import java.util.ArrayList;
import java.util.ListIterator;
/** 
 * this is the complex data stracture's class, it uses the AVLTree class
 * there is the idTree which holds all the ids of the players , those
 * have pointers to the score nodes on the scoreTree and those have pointers
 * to sub AVL trees that hosts ids of the same score. 
 * all those trees use the same AVLTree class and Node class. the only difference
 * is what data is inserted to the key field.
 * @author solekiller
 *
 */
public class Game {
	public AVLTree idTree;
	public AVLTree scoreTree;
	public Game(){
		 idTree = new AVLTree();
		 scoreTree = new AVLTree();
	}
	/**
	 * inserts a new player to the data structure
	 * 
	 * @param id - the id of the player to be inserted 
	 */
	public void insertPlayer(int id){
		if (idTree.search(id) == null)
			insert(id, 0, 0);
		else
			System.out.println("Player "+id+" already exists");
	}
	/**
	 * gets the player's information from the data stracture
	 * @param id - the wanted player's id
	 * @return - an int array with the following information in it 
	 * in the following order [player's id,total score,number of games]
	 */
	public int[] getPlayer(int id){
		Node idNode = idTree.search(id);
		if (idNode == null)
			return null;
		int[] results = {idNode.key,idNode.nodePointer.key,idNode.games};
		return results;
	}
	/**
	 * gets rank of a player by looking for him first in the idtree
	 * in O(lgn) then following its pointer to the score node in O(1)
	 * then climbing up from the max value(in scoretree) to it and counting the 
	 * steps in O(y) (the way up is done using the prevInOrder pointers)
	 * plus nextInOrder pointers in subtrees 
	 * @param id - the id of the player in question
	 * @return - the players rank :)
	 */
	public int getRank(int id){
		int rank = 1;
		Node idNode = idTree.search(id);
		Node scoreNode = idNode.nodePointer;
		int score = scoreNode.key;
		if (scoreNode.avlPointer.size > 1)
			scoreNode = scoreNode.avlPointer.search(id);
		Node walker = scoreTree.max;
		while (walker != null && walker != scoreNode){
			AVLTree subtree = walker.avlPointer;
			if (subtree.size <= 1){
				rank++;
			}else{
				if(walker.key > score)
					rank = rank + subtree.size;
				else{
					walker = subtree.min;
					while (walker != scoreNode){
						rank++;
						walker = walker.nextInOrder;
					}
					return rank;
				}
			}
			walker = walker.prevInOrder;
		}
		return rank;
	}
	/**
	 * a method that gets the top players in an int[][] fomat
	 * it goes to the max node in the score tree then it walks 
	 * backwards in-order everytime it meets a tree that has more
	 * thank one node in it it goes inside and in it it jumps from min upwards
	 * every node it happens to meet it adds to the Array list
	 * then the array list is spilled (like a row) into and array of the same size
	 * 
	 * @param y - the amount of top players
	 * @return  - and int[][] in each cell there is a size 3 array of the 
	 * following format [id,score,games]
	 */
	public int[][] getTop(int y){
		ArrayList<int[]> list = new ArrayList<int[]>();
		Node walker = scoreTree.max;
		int i = 1;
		while ( walker != null && i <= y) {
				AVLTree subtree = walker.avlPointer;
			if (subtree != null && subtree.size <= 1){
				int[] arr = {walker.avlPointer.root.key,walker.key,walker.games};
				list.add(arr);
			}else{
				Node subWalker = subtree.min;
				while (subWalker != null && i <= y){
					int[] arr = {subWalker.key,subWalker.score,subWalker.games};
					list.add(arr);
					subWalker = subWalker.nextInOrder;
					i = i + 1;
				}
				
				i = i - 1; // the pointer node is counter twise(due to duplication for logical reasons) 
				
			}
			
			walker = walker.prevInOrder;
			i = i + 1;
		}
		ListIterator<int[]> itr = list.listIterator();
		int[][] array = new int[list.size()][3];
		int j = 0;
		while (itr.hasNext()){
			array[j] = itr.next();
			j = j +1 ;
		}
		return array;
	}
	/**
	 * well this method simply removes 2 players then inserts them with the new
	 * point and game values into the data structure 
	 * @param id1 - first player's id
	 * @param tactic1 - first player's tactic (r/p/s)
	 * @param id2 - second player's id
	 * @param tactic2 - second player's tactic (r/p/s)
	 */
	public void insertGame(int id1,String tactic1,int id2,String tactic2){
		int whowon = whoWon(tactic1,tactic2);
		int addpoints1 = 0;
		int addpoints2=0;
		Node holder1,holder2;
		if (whowon == 1){
			addpoints1 = 5;
			addpoints2 = 1;
		}else if (whowon == 2){
			addpoints1 = 1;
			addpoints2 = 5;
		}else{
			addpoints1 = 2;
			addpoints2 = 2;
		}
		holder1 = idTree.search(id1);
		holder2 = idTree.search(id2);
		int[] p1 = {id1,holder1.nodePointer.key+addpoints1,holder1.games+1};
		int[] p2 = {id2,holder2.nodePointer.key+addpoints2,holder2.games+1};
		remove(id1);
		remove(id2);
		insert(p1[0], p1[1], p1[2]);
		insert(p2[0], p2[1], p2[2]);
	}
	/**
	 * a method that checks who won 
	 * @param tactic1 - first player's tactic 
	 * @param tactic2 - second player's tactic
	 * @return - 1 if first player wins 2 if second wins and 0 if its a tie
	 */
	private int whoWon(String tactic1,String tactic2){
		if (tactic1.equals("r")){
			if(tactic2.equals("r"))
				return 0;
			else if(tactic2.equals("p"))
				return 2;
			else
				return 1;
		}else if(tactic1.equals("p")){
			if (tactic2.equals("r"))
				return 1;
			else if (tactic2.equals("p"))
				return 0;
			else
				return 2;
		}else{
			if (tactic2.equals("r"))
				return 2;
			else if (tactic2.equals("p"))
				return 1;
			else
				return 0;
		}
	}
	/**
	 * helper method to make my life alot easier 
	 * it checks id the player exists , if not 
	 * it inserts an idnode to idtree
	 * a score node to scoretree
	 * if the score exists it will draw a pointer to the existing node
	 * and insert the new score node to the score subtree
	 * if not it will simply insert the node into the tree and make it a fresh subtree
	 * O(lgn)
	 * @param id - the id of the inserted player
	 * @param score - the score of the inserted player
	 * @param game - the number of games of the inserted player
	 */
	private void insert(int id,int score,int game){
		Node idNode = new Node(id);
		Node scoreNode = new Node(score);
		if (scoreTree.search(score) == null)
			idNode.nodePointer = scoreNode;
		else
			idNode.nodePointer = scoreTree.search(score);
		idTree.treeInsert(idNode);
		
		scoreNode.id = id; scoreNode.games = game;
		idNode.score = score; idNode.games = game;
		
		if (scoreTree.search(score) == null){
			Node idn = idNode.copy();
			idn.score = score;
			scoreNode.avlPointer = new AVLTree();
			scoreTree.treeInsert(scoreNode);
			scoreNode.avlPointer.treeInsert(idn); 
		}else{
			Node idn = idNode.copy();
			idn.score = score;
			scoreTree.search(score).avlPointer.treeInsert(idn);
		}
	}
	/**
	 * helper method to remove players for game insertion
	 * @param id - the id to remove 
	 * it uses search O(lgn) and treedelete O(lgn) .
	 * total complexity O(lgn)
	 */
	private void remove(int id){
		Node idNode = idTree.search(id);
		if (idNode != null){
			Node scoreNode = idNode.nodePointer;
			if (scoreNode.avlPointer != null && scoreNode.avlPointer.size > 1){
				scoreNode.avlPointer.remove(id);
			}else{
				scoreTree.remove(scoreNode.key);
			}
			idTree.remove(idNode.key);
		}
	}
}
