package node;

public class NodeID {
	
	private char[] _allowedCharacters;
	private int _numberOfAllowedCharacters;
	private static final String _alphabet = "abcdefghijklmnopqrstuvwxyz";
	private static final String _numbers = "0123456789";
	private static final String _specialCharacters = "-_";

	public NodeID(){
		Math.random();
		
		String allowedCs = _alphabet + _alphabet.toUpperCase() + _numbers + _specialCharacters;
		_allowedCharacters = allowedCs.toCharArray();
		_numberOfAllowedCharacters = _allowedCharacters.length;
	}
	
	public boolean existsID(String id){
		return false; // TODO make this check whether the id exists or not.
	}
	
	private String generateID(){
		char[] chars = new char[8];
		for(int i = 0; i < 8; ++i){
			chars[i] = _allowedCharacters[((int) (Math.random()*_numberOfAllowedCharacters))];
		}
		return new String(chars);
	}
	
	// Generates a new id and makes sure it's unique.
	public String generateNewID(){
		String id = generateID();
		while(existsID(id)){
			id = generateID();
		}
		return id;
	}
}
