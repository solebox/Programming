import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.HashMap;
import java.util.Scanner;
import java.util.TreeSet;


/**
 * this is our model for the dictionary
 * here all the dictionary logic is held
 * @author solekiller
 *
 */
public class DictionaryModel {
	private HashMap<String,String> _hash;
	private TreeSet<String> _set;
	private final String _path = "src/Data/dict.txt";
	/**
	 * this is our dictionary constructor , we create a hashmap to hold the word => definition pairs and a treeset to hold the words in order
	 */
	public DictionaryModel(){
		_hash = new HashMap<String, String>();
		_set = new TreeSet<String>();
		openDic(_path);
		
	}
	/**
	 * a method to add a new word and definition to the dictionary
	 * @param term - the term we want to add
	 * @param definition - the definition we ant to add
	 * return - true if word added false if not (word already exists)
	 * @throws BadInput - if input that uses anything but letters or spaces is inserted this exception is thrown (or if an empty string)
	 */
	public boolean add(String term, String definition) throws BadInput{
		String pat = "[a-zA-Z\\s]+";
		if (!term.matches(pat) || !definition.matches(pat))
			throw new BadInput();
		if (!_set.contains(term)){
			_set.add(term);
			_hash.put(term, definition);
			return true;
		}
		return false;
	}
	/**
	 * this method removes a word and its definition from the dictionary
	 * @param term - the term we want to remove (the corresponding definition will be removed as well consequentially)
	 */
	public void remove(String term){
		if (_set.contains(term)){
			_set.remove(term);
			_hash.remove(term);
		}
	}
	/**
	 * this method allows us to change a word in our dictionary , if the word exists the definition is changed if it doesn't
	 * nothing happens
	 * @param term - the word for which the definition we want to change
	 * @param definition - the new definition we want to put instead of the old one
	 * @throws BadInput - if bad input is inserted
	 */
	public void update(String term, String definition) throws BadInput{
		String pat = "[a-zA-Z\\s]+";
		if (!term.matches(pat) || !definition.matches(pat))
			throw new BadInput();
		if (_set.contains(term)){
			_hash.put(term, definition);
		}
	}
	/**
	 * this method is the method for searching the dictionary, if the word exists in the dictionary the definition
	 * is returned , if not null is returned
	 * @param word - the word we are searching the definition for in the dictionary 
	 * @return null if word doesn't exits , definition if it does
	 */
	public String search(String word){
		if (_set.contains(word)){
			return _hash.get(word);
		}
		return null;
	}
	private void openDic(String path){
		Scanner input;
		String line;
		String[] pair;
		int lineCounter = 1;
		try {
			input = new Scanner(new File(path));
			while (input.hasNextLine()){
				line = input.nextLine();
				pair = line.split(",");
				if (pair.length != 2){
					System.err.println("(in file:"+ path + "): badly formatted line : "+lineCounter);
				}else{
					_set.add(pair[0]);
					_hash.put(pair[0], pair[1]);
				}
			}
		}catch(IOException e){
			System.err.println("couldn't open: "+path);
		}
		catch(Exception e){
			System.err.print("some unexpected error accured while trying to open: "+ path);
		}
	}
	/**
	 * this method returns an ordered string representation of our dictionary (at current state in ram)
	 */
	public String toString(){
		String rep = "";
		String[] keys = _set.toArray(new String[_set.size()]);
		for (int i = 0; i < keys.length; i++) {
			rep += keys[i]+" => ";
			rep += _hash.get(keys[i])+"\n";
		}
		return rep;
	}
	/**
	 * this method saves the dictionary from the ram to the file at path
	 * @param path
	 * @throws IOException 
	 */
	private void saveDicToFile(String path) throws IOException{
		try{
			PrintWriter out = new PrintWriter(new FileWriter(path));
			String[] keys = _set.toArray(new String[_set.size()]);
			for (int i = 0; i < keys.length; i++) {
				out.println(keys[i]+","+_hash.get(keys[i]));
			}
			out.close();
		}catch(IOException e){
			throw new IOException();
		}catch(Exception e){
			System.err.println("encountered issues while trying to open: "+path+" for writing.");
		}
	}
	/**
	 * this method saves the dictionary to the default dict file 
	 * @throws IOException 
	 */
	public void saveDicToFile() throws IOException{
		saveDicToFile(_path);
	}
	public void loadDicFromFile(){
		openDic(_path);
	}
	/**
	 * returns a list of all the terms in the dictionary 
	 * @return - an array of all the terms
	 */
	public String[] getTerms(){
		return _set.toArray(new String[_set.size()]);
	}
}
