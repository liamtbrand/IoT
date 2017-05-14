package database;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;

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
		
		setupDatabase();
	}
	
	/**
	 * This will create any missing tables in the database.
	 */
	public void setupDatabase(){
		
		
		
	}
	
	public String getUserID(String email){
		Connection conn = null;
		Statement statement = null;
		ResultSet resultSet = null;
		
		String id = "";
		
		try {
			conn = DriverManager.getConnection(_jdbcUrl);
			
			statement = conn.createStatement();
			String sql = "SELECT * FROM User WHERE email='"+email+"';";
			
			resultSet = statement.executeQuery(sql);
			
			resultSet.first();
			id = resultSet.getString("idUser");
			
		} catch (SQLException e) {
			e.printStackTrace();
		} finally {
			DbUtils.close(statement);
			DbUtils.close(conn);
		}
		
		return id;
	}
	
	public List<String> getNodeIdsOwnedByUser(String idUser){
		
		Connection conn = null;
		Statement statement = null;
		ResultSet resultSet = null;
		
		List<String> ids = new ArrayList<String>();
		
		try {
			conn = DriverManager.getConnection(_jdbcUrl);
			
			statement = conn.createStatement();
			String sql = "SELECT * FROM Node WHERE owner_idUser='"+idUser+"';";
			resultSet = statement.executeQuery(sql);
		
			while(resultSet.next()){
				ids.add(resultSet.getString("idNode"));
			}
			
		} catch (SQLException e) {
			e.printStackTrace();
		} finally {
			DbUtils.close(statement);
			DbUtils.close(conn);
		}
		
		return ids;
		
	}
	
	public String getNodeName(String id){
		Connection conn = null;
		Statement statement = null;
		ResultSet resultSet = null;
		
		String name = "";
		
		try {
			conn = DriverManager.getConnection(_jdbcUrl);
			
			statement = conn.createStatement();
			String sql = "SELECT * FROM Node WHERE idNode='"+id+"';";
			
			resultSet = statement.executeQuery(sql);
			
			resultSet.first();
			name = resultSet.getString("name");
			
		} catch (SQLException e) {
			e.printStackTrace();
		} finally {
			DbUtils.close(statement);
			DbUtils.close(conn);
		}
		
		return name;
	}
	
}
