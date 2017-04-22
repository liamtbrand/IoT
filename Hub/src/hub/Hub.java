package hub;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import node.Node;
import web.WebController;

public class Hub {

	public static void main(String[] args) {
		
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
