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
import rds.RDSConfigFile;
import rds.RDSConnectionInfo;

public class Cloud {
	
	public static void main(String[] args){
		
		ConnectionController deviceConns;
		ConnectionController hubConns;
		ConnectionController nodeConns;
		
		DBController dbConn;
		
		try {
			
			// Create the RDS config file object and load in the configuration if it exists.
			RDSConfigFile configFile = new RDSConfigFile("config/rds.config");
			RDSConnectionInfo dbConnInfo = null;
			try {
				dbConnInfo = configFile.loadRDSConnectionInfo();
			} catch (Exception e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
			dbConn = new DBController(dbConnInfo); // TODO get this working.
			
			System.out.println(dbConn.getNodeName("0"));
			for(String id : dbConn.getNodeIdsOwnedByUser(dbConn.getUserID("liamtbrand@gmail.com"))){
				System.out.println(id);
			}
			
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
					SocketConnection sockConn = deviceConns.getConnection();
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
				
				try {
					Thread.sleep(50); // TODO make this better. It was chewing cpu on the ec2 vm.
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				
			}
			
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}
	
}
