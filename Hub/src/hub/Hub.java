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

import node.Node;
import web.WebController;

public class Hub {

	public static void main(String[] args) {
		
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
		}
		
		ConnectionController nodeConns;
		ConnectionController webConns;
		
		try {
			
			// Port where nodes will connect
			nodeConns = new ConnectionController(9999);
			(new Thread(nodeConns)).start();
			
			// Port where web interfaces will connect
			webConns = new ConnectionController(8081); // Port where web controllers will connect
			(new Thread(webConns)).start();

			List<Node> _nodes;
			List<WebController> _webControllers;
			
			_nodes = new ArrayList<Node>();
			_webControllers = new ArrayList<WebController>();
			
			String message = "";
		
			while(true){
				
				if(nodeConns.hasConnection()){
					_nodes.add(new Node(nodeConns.getConnection()));
				}
				
				if(webConns.hasConnection()){
					_webControllers.add(new WebController(webConns.getConnection()));
				}
				
				for(Node node : _nodes){
					if(node.hasMessage()){
						message = node.getMessage();
						System.out.println("NODE >> "+message);
						for(WebController web : _webControllers){
							System.out.println("WEB << "+message);
							web.sendMessage(message);
						}
					}
				}
				
				for(WebController web : _webControllers){
					if(web.hasMessage()){
						message = web.getMessage();
						System.out.println("WEB >> "+message);
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
