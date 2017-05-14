package rds;

public class RDSConnectionInfo {
	
	public final String hostname;
	public final int port;
	public final String dbName;
	public final String username;
	public final String password;
	
	public RDSConnectionInfo(String hostname, int port, String dbName, String username, String password){
		this.hostname = hostname;
		this.port = port;
		this.dbName = dbName;
		this.username = username;
		this.password = password;
	}

	public String toString(){
		return hostname+","+port+","+dbName+","+username+",****";
	}
}
