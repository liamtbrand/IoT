package node;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import hub.SocketConnection;

public class Node {
	
	SocketConnection _conn;
	
	List<String> _messageLog;
	
	public Node(SocketConnection socketConnection) throws IOException{
		_conn = socketConnection;
		_messageLog = new ArrayList<String>();
	}
	
	public boolean hasMessage(){
		return _conn.hasMessage();
	}
	
	public String getMessage(){
		return _conn.getMessage();
	}
	
	public void sendMessage(String message){
		_conn.sendMessage(message);
	}

}
