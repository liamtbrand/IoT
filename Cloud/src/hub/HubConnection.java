package hub;

import connections.SocketConnection;

public class HubConnection {
	
	private SocketConnection _conn;

	public HubConnection(SocketConnection connection) {
		_conn = connection;
	}
	
	public SocketConnection sockConn(){
		return _conn;
	}

}
