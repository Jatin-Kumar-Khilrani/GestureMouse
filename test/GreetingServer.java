import java.net.*;
import java.io.*;

public class GreetingServer extends Thread{
	
	String mystr=null;
	Socket server;
	private ServerSocket serverSocket;
	
	public GreetingServer(int port) throws IOException{

		serverSocket = new ServerSocket(port);
		serverSocket.setSoTimeout(120000);
	}

	public void run(){
		
		while(true)
		{
			try{
				System.out.println("Waiting for client on port"+ serverSocket.getLocalPort()+"...");
				server = serverSocket.accept();
				
				System.out.println("Just connected to "+ server.getRemoteSocketAddress());
				DataInputStream in = new DataInputStream(server.getInputStream());

				System.out.println(in.readUTF());
				DataOutputStream out = new DataOutputStream(server.getOutputStream());

				out.writeUTF("Thankyou for connecting to "+ server.getLocalSocketAddress()+ "\n Goodbye!");
			//	server.close();
				while(!"STOP".equals(mystr))
				{
					if(server != null && server.isConnected())
					{
						if(in.available() > 0){
							mystr=in.readUTF().toString();
							System.out.println(""+mystr);
						}
					}
				}
				mystr = null;
			}
			catch(SocketTimeoutException e){
				try{
					server.close();
				}
				catch(Exception eone){
					System.out.println("Close failed\n");
				}
				System.out.println("Socket timed out!");
				break;
			}
			catch(IOException e){
				e.printStackTrace();
				break;
			}
		}
	}
	public static void main(String[] args)
	{
		int port = Integer.parseInt(args[0]);
		try{
			Thread t = new GreetingServer(port);
			t.start();
		}
		catch(IOException e)
		{
			e.printStackTrace();
		}
	}
}
