import java.io.IOException;

/**
 * this is the controller here all the coordination between the model and the view accrues 
 * basically its all a bunch of delegations to the model wrapped in an interface for the view to use
 * and an initialization of the 2
 * @author solekiller
 *
 */
public class DictionaryController implements Controller {
	private DictionaryModel _model;
	
	public DictionaryController(){
		_model = new DictionaryModel();
		new DictionaryView(this);

	}
	@Override
	public void create(String term, String definition) throws BadInput {
		_model.add(term, definition);
		
	}

	@Override
	public void delete(String term) {
		_model.remove(term);
	}

	@Override
	public void update(String term, String definition) throws BadInput {
		_model.update(term, definition);
	}

	@Override
	public String search(String term) {
		return _model.search(term);
	}

	@Override
	public void loadDict() {
		_model.loadDicFromFile();
	}

	@Override
	public void saveDict() throws IOException {
		_model.saveDicToFile();
	}

	@Override
	public String dictString() {
		return _model.toString();
	}
	@Override
	public String[] getTerms() {
		return _model.getTerms();
	}
	
}
