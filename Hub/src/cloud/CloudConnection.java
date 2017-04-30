package cloud;

import java.io.IOException;
import java.net.Socket;
import java.net.UnknownHostException;

import connections.SocketConnection;

public class CloudConnection {
	
	private SocketConnection _conn;
	
	private String _address;
	private int _port;
	
	public CloudConnection(String address, int port){
		_address = address;
		_port = port;
		
		try {
			_conn = new SocketConnection(new Socket(_address,port));
		} catch (UnknownHostException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
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
