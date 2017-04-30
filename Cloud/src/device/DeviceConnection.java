package device;

import connections.SocketConnection;

public class DeviceConnection {

	private SocketConnection _conn;
	
	public DeviceConnection(SocketConnection connection) {
		_conn = connection;
	}
	
	public SocketConnection sockConn(){
		return _conn;
	}

}
