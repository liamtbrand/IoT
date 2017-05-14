package rds;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

public class RDSConfigFile {
	
	public static class Tag {
		public static String hostname = "hostname";
		public static String port = "port";
		public static String dbName = "dbName";
		public static String username = "username";
		public static String password = "password";
	}
	
	private String _filename;
	
	public RDSConfigFile(String filename){
		_filename = filename;
	}
	
	public RDSConnectionInfo loadRDSConnectionInfo() throws IOException, RDSConfigFileException{
		
		RDSConnectionInfo connInfo = null;
		File f = new File(_filename);
		
		if(!f.exists()){
			
			// If the config file doesn't exist, create it.
			f.getParentFile().mkdirs();
			f.createNewFile();
			
			FileWriter fw = new FileWriter(f);
			BufferedWriter bw = new BufferedWriter(fw);
			
			bw.write("# This is the default RDS Config File.\n");
			bw.write("# Please modify the connection values below.\n");
			bw.write("hostname=localhost\n");
			bw.write("port=3306\n");
			bw.write("dbName=db_name\n");
			bw.write("username=user\n");
			bw.write("password=pass\n");
			
			bw.close();
			fw.close();
		}
		
		if(f.exists()){
			
			// Read in the contents of the file.
			
			FileReader fr = new FileReader(f);
			BufferedReader br = new BufferedReader(fr);
			
			Map<String,String> values = new HashMap<String,String>();
		
			String line;
			String[] var;
			
			while((line = br.readLine()) != null){
				
				if(line.charAt(0) != '#'){ // Not a comment
					var = line.split("=",2);
					if(var.length > 1){
						values.put(var[0], var[1]);
					}
				}
				
			}
			
			br.close();
			fr.close();
			
			// Check all the values are there and add them.
			
			String[] keys = {"hostname","port","dbName","username","password"};
			for(String key : keys){
				if(!values.containsKey(key)){
					throw new RDSConfigFileException("All parameters must be specified in the config file.");
				}
			}
			
			try{
				connInfo = new RDSConnectionInfo(
						values.get(Tag.hostname),
						Integer.valueOf(values.get(Tag.port)),
						values.get(Tag.dbName),
						values.get(Tag.username),
						values.get(Tag.password)
				);
			} catch (NumberFormatException nfe){
				nfe.getStackTrace();
				throw new RDSConfigFileException("Port must be an integer");
			}
			
			
		}else{
			throw new RDSConfigFileException("Unable to find/create an RDS Config File!");
		}
		
		return connInfo;
	}

}
