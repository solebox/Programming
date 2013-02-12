import java.awt.HeadlessException;


public class Main {
	public static void main(String[] args){
		try{
			new MovieSystemView();
		}catch(HeadlessException e){ //had to do it in the main :S my view inherits from JFrame since i wanted it to be a singleton
			System.err.println("gui failed to load: "+e);
		}
			
	}
	
}
