package device;

import connections.SocketConnection;

public class DeviceController {
	
	private SocketConnection _socketConnection;
	
	public DeviceController(SocketConnection socketConnection){
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
