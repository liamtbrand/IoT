package database;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

import rds.RDSConnectionInfo;

public class DBController {
	
	private final RDSConnectionInfo _dbConnInfo;
	private final String _jdbcUrl;

	public DBController(RDSConnectionInfo dbConnInfo) {
		_dbConnInfo = dbConnInfo;
		_jdbcUrl = "jdbc:mysql://" + _dbConnInfo.hostname +
				":" + _dbConnInfo.port +
			    "/" + _dbConnInfo.dbName + 
				"?user=" + _dbConnInfo.username + 
				"&password=" + _dbConnInfo.password;
		
		// Load the JDBC driver
		try {
			System.out.println("Loading MySQL JDBC driver...");
			System.out.println(this.getClass().getName());
			Class.forName("com.mysql.jdbc.Driver");
			System.out.println("MySQL JDBC driver loaded!");
		} catch (ClassNotFoundException e) {
			throw new RuntimeException("Cannot find the driver in the classpath!", e);
		}
	}
	
	public Connection getConnection(){
		
		try {
			Class.forName("com.mysql.jdbc.Driver");
		} catch (ClassNotFoundException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
		
		Connection conn = null;
		
		try {
			conn = DriverManager.getConnection(_jdbcUrl);
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		return conn;
	}
	
}
