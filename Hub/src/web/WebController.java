package web;

import hub.SocketConnection;

public class WebController {
	
	private SocketConnection _socketConnection;
	
	public WebController(SocketConnection socketConnection){
		_socketConnection = socketConnection;
	}

	public void sendMessage(String message) {
		_socketConnection.sendMessage(message);
	}
	
	public boolean hasMessage(){
		return _socketConnection.hasMessage();
	}
	
	public String getMessage(){
		return _socketConnection.getMessage();
	}

}
