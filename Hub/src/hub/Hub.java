package hub;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.Reader;
import java.io.StringReader;
import java.util.ArrayList;
import java.util.List;

import javax.json.Json;
import javax.json.stream.JsonParser;

import cloud.CloudConnection;
import connections.ConnectionController;
import device.DeviceController;
import node.Node;

public class Hub {

	public static void main(String[] args) {
		
		/*
		Reader reader = null;
		try {
			reader = new FileReader("config.json");
		} catch (FileNotFoundException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
		
		if(reader == null){
			String defaultConfig = "{\"test\":\"testing\"}";
			reader = new StringReader(defaultConfig);
		}
		
		JsonParser parser = Json.createParser(reader);
		
		while(parser.hasNext()){
			// TODO get next element.
		}*/
		
		ConnectionController nodeConns;
		ConnectionController deviceConns;
		CloudConnection cloudConn;
		
		try {
			
			// Port where nodes will connect
			nodeConns = new ConnectionController(9999);
			(new Thread(nodeConns)).start();
			
			// Interface with the cloud, if we can connect to it.
			cloudConn = new CloudConnection("localhost",8083);
			
			// Port where web interfaces will connect
			deviceConns = new ConnectionController(8081); // Port where web controllers will connect
			(new Thread(deviceConns)).start();

			List<Node> _nodes;
			List<DeviceController> _devices;
			
			_nodes = new ArrayList<Node>();
			_devices = new ArrayList<DeviceController>();
			
			String message = "";
			String response = "";
		
			while(true){
				
				if(nodeConns.hasConnection()){
					_nodes.add(new Node(nodeConns.getConnection()));
				}
				
				if(deviceConns.hasConnection()){
					_devices.add(new DeviceController(deviceConns.getConnection()));
				}
				
				for(Node node : _nodes){
					if(node.hasMessage()){
						message = node.getMessage();
						System.out.println("NODE >> "+message);
						
						if(message.equals("LIGHT:?")){ // If the node is asking for it's status
							// Send the state of the light to the node.
							response = "LIGHT:OFF";
							System.out.println("NODE << "+response);
							node.sendMessage(response+"\n");
						}
						
						for(DeviceController web : _devices){
							System.out.println("WEB << "+message);
							web.sendMessage(message);
						}
					}
				}
				
				for(DeviceController web : _devices){
					if(web.hasMessage()){
						message = web.getMessage();
						System.out.println("WEB >> "+message);
						//if(message.equals(""))
						
						for(Node node : _nodes){
							
							System.out.println("NODE << "+message);
							node.sendMessage(message+"\n");
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
