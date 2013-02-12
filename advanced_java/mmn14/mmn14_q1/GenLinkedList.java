/**
 * this is a generic linked list, it holds generic nodes that hold a type K value
 * @author solekiller
 *
 * @param <K>
 */
public class GenLinkedList<K> {
	GenNode<K> _head;
	GenNode<K> _tail;
	/**
	 * this is our linked list constructor, its an empty constructor that creates and empty list, it must be sad that its so empty
	 */
	public GenLinkedList() {
		_head = null;
		_tail = _head;
	}
	/**
	 * this is our head getter
	 * @return the head node
	 */
	public GenNode<K> getHead() {
		return _head;
	}
	/**
	 * this is our tail getter
	 * @return - gets our tail node, the last node in the bunch 
	 */
	public GenNode<K> getTail() {
		return _tail;
	}
	/**
	 * this method adds a node to our list, with the given value
	 * @param value the value we want the new node to have
	 */
	public void add(K value){
		if (isEmpty()){
			_head = new GenNode<K>(value);
			_tail = _head;
		}else{
			_tail.setNext(new GenNode<K>(value));
			_tail = _tail.getNnext();
		}
	}
	/**
	 * this method removes a node from the head of the list 
	 * @return the removed node
	 * @throws EmptyListException - throws when no more to remove but user is insistant to shift out another
	 */
	public K remove() throws EmptyListException{
		K value;
		if (isEmpty()){
			throw new EmptyListException();
		}else{
			value = _head.getValue();
			_head = _head.getNnext(); // decapitate much?
		}
		return value;
	}
	private boolean isEmpty(){
		return _head == null;
	}
	public String toString(){
		String list = "";
		GenNode<K> node = _head;
		if (isEmpty()){
			list = "[]";
		}else{
			list += "[";
			while (node.getNnext() != null){
				list += node.getValue() +",";
				node = node.getNnext();
			}
			list += node.getValue() + "]";
		}
		return list;
	}
	/**
	 * makes sure our list is not empty
	 * @return true if not , false if empty
	 */
	public boolean notEmpty(){
		return !isEmpty();
	}
	/**
	 * this method takes a list finds its min and returns it without damaging the medium it was given
	 * @param list the list to check
	 * @return the minimum value
	 */
	public static <T extends Comparable<T>> T minimum(GenLinkedList<T> list){
		GenLinkedList<T> helper = new GenLinkedList<T>();
		T tmp, min = null;
		try{
			min = list.remove();
			helper.add(min);
		}
		catch(EmptyListException e){
			System.err.println("minimum was given an empty list");
		}
		while (list.notEmpty()){
			try{
				tmp = list.remove();
				helper.add(tmp);
				if (tmp.compareTo(min) < 0){
					min = tmp;
				}
				
			}
			catch(EmptyListException e){
				System.err.println("tried to remove from empty list");
			}
		}
		while (helper.notEmpty()){
			try{
				list.add(helper.remove());
			}catch(Exception e){
				System.err.println("tried to remove from empty list.");
			}
		}
	
		return min;
	}


	
}
