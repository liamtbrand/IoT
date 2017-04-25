package cloud;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import connections.ConnectionController;
import web.WebServer;

public class Cloud {
	
	public static void main(String[] args){
		
		ConnectionController webConns;
		
		try {
			webConns = new ConnectionController(8082);
			(new Thread(webConns)).start();
			
			List<WebServer> webServers;
			
			webServers = new ArrayList<WebServer>();
			
			while(true){
				
				if(webConns.hasConnection()){
					webServers.add(new WebServer());
				}
				
			}
			
			
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}
	
}
