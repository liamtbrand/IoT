package hub;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;

public class NodeController {
	
	ServerSocket _serverSocket;
	
	public NodeController(){
		
	}

	public void listen() throws IOException{
		_serverSocket = new ServerSocket(9999);
		
		System.out.println("Listening...");
		
		Socket clientSocket = _serverSocket.accept();
		
	    PrintWriter out = new PrintWriter(clientSocket.getOutputStream(), true);
	    BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
	    
	    String message = "";
	    String response = "";
	    
	    while(!clientSocket.isClosed()){
	    	
	    	message = in.readLine();
	    	
	    	System.out.println(">> b'"+message+"'");
	    	
	    	if(message.equals("LIGHT:?")){
	    		response = "LIGHT:ON";
	    	}else if(message.equals("SWITCH:ON")){
	    		response = "LIGHT:ON";
	    	}else if(message.equals("SWITCH:OFF")){
	    		response = "LIGHT:OFF";
	    	}
	    	
	    	out.println(response);
	    	System.out.println("<< b'"+response+"'");
	    	
	    }
	}

}
