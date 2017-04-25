package connections;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

public class SocketConnection {

	private PrintWriter _out;
	private BufferedReader _in;
	private Socket _clientSocket;
	
	public SocketConnection(Socket clientSocket) throws IOException {
		_clientSocket = clientSocket;
		_out = new PrintWriter(_clientSocket.getOutputStream(), true);
		_in = new BufferedReader(new InputStreamReader(_clientSocket.getInputStream()));
	}
	
	public boolean hasMessage(){
		try {
			if(_in.ready()){
				return true;
			}
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return false;
	}
	
	public String getMessage(){
		try {
			return _in.readLine();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return "";
	}
	
	public void sendMessage(String message){
		_out.println(message);
	}
	
	public boolean isClosed(){
		return _clientSocket.isClosed();
	}
}
