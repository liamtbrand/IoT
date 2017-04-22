package hub;

import java.io.IOException;

public class Hub {

	public static void main(String[] args) {
		
		NodeController nodeController = new NodeController();
		try {
			nodeController.listen();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}

}
