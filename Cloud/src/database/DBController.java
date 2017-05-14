package database;

import rds.RDSConnectionInfo;

public class DBController {
	
	private RDSConnectionInfo _dbConnInfo;

	public DBController(RDSConnectionInfo dbConnInfo) {
		_dbConnInfo = dbConnInfo;
	}
	
}
