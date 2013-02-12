import java.io.IOException;


public interface Controller {
	public void create(String term,String definition) throws BadInput;
	public void delete(String term);
	public void update(String term, String definition) throws BadInput;
	public String search(String term); //return definition of term if successful
	public void loadDict(); //loads the dict from its file
	public void saveDict() throws IOException; //saves dict from memory to file
	public String dictString(); //Returns the dictionary's string representation 
	public String[] getTerms(); // returns and array of all the terms in the dictionary  
}
