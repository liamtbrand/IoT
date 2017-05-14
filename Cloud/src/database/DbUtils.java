package database;

import java.sql.Connection;
import java.sql.SQLException;
import java.sql.Statement;

public class DbUtils {

	public static void close(Connection conn){
		try {
			conn.close();
		} catch (SQLException e) {
			e.printStackTrace();
		}
	}

	public static void close(Statement statement) {
		try {
			statement.close();
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
}
