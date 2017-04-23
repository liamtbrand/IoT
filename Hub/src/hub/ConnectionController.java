package hub;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.List;

public class ConnectionController implements Runnable {
	
	private ServerSocket _serverSocket;
	
	private List<SocketConnection> _conns;

	public ConnectionController(int port) throws IOException {
		_serverSocket = new ServerSocket(port);
		_conns = new ArrayList<SocketConnection>();
	}

	@Override
	public void run() {
		System.out.println("Listening for connections on port: "+String.valueOf(_serverSocket.getLocalPort()));
		Socket clientSocket;
		while(true){
			try {
				clientSocket = _serverSocket.accept();
				System.out.println("Connection accepted from: "+clientSocket.getInetAddress());
				_conns.add(new SocketConnection(clientSocket));
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}
	
	public synchronized boolean hasConnection(){
		return !_conns.isEmpty();
	}
	
	public synchronized SocketConnection getConnection(){
		SocketConnection sc = _conns.get(0);
		_conns.remove(0);
		return sc;
	}
	
}
