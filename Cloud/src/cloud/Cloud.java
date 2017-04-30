package cloud;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import connections.ConnectionController;
import connections.SocketConnection;
import database.DBController;
import device.DeviceConnection;
import hub.HubConnection;
import node.NodeID;
import web.WebServer;

public class Cloud {
	
	public static void main(String[] args){
		
		ConnectionController deviceConns;
		ConnectionController hubConns;
		ConnectionController nodeConns;
		
		DBController dbConn;
		
		try {
			
			dbConn = new DBController("localhost",3306); // TODO get this working.
			
			deviceConns = new ConnectionController(8082);
			(new Thread(deviceConns)).start();
			
			hubConns = new ConnectionController(8083);
			(new Thread(hubConns)).start();
			
			// TODO node connection.
			
			List<DeviceConnection> devices;
			List<HubConnection> hubs;
			
			
			devices = new ArrayList<DeviceConnection>();
			hubs = new ArrayList<HubConnection>();
			
			NodeID nodeId = new NodeID();
			
			System.out.println("Testing service simply relays messages from devices to hubs and vice versa.");
			System.out.println("Ready...");
			
			while(true){
				
				if(deviceConns.hasConnection()){
					SocketConnection sockConn = hubConns.getConnection();
					devices.add(new DeviceConnection(sockConn));
					System.out.println("Device connected from: "+sockConn);
				}
				
				if(hubConns.hasConnection()){
					SocketConnection sockConn = hubConns.getConnection();
					hubs.add(new HubConnection(sockConn));
					System.out.println("Hub connected from: "+sockConn);
				}
				
				for(DeviceConnection device : devices){
					if(device.sockConn().hasMessage()){
						String message = device.sockConn().getMessage();
						for(HubConnection hub : hubs){
							hub.sockConn().sendMessage(message);
						}
					}
				}
				
				for(HubConnection hub : hubs){
					if(hub.sockConn().hasMessage()){
						String message = hub.sockConn().getMessage();
						for(DeviceConnection device : devices){
							device.sockConn().sendMessage(message);
						}
					}
				}
				
			}
			
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}
	
}
