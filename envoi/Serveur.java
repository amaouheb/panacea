import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.InetAddress;
import java.net.DatagramSocket;
import java.net.Socket;
import java.net.UnknownHostException;
import java.io.PrintWriter;
import java.lang.Object;
import java.lang.String;
public class Serveur {
	
	public static void main(String[] zero) {
		
		
		try {
		
			//socketserver = new ServerSocket(2009,5,InetAddress.getByName("140.93.5.118"));
			//socketserver = new ServerSocket(2009);

			socketserver = new DatagramSocket(2009);

			DatagramePacket ps = new DatagramPacket(buf,length);

			sockettserver.receive(pr);

			DatagramePacket ps = new DatagramPacket(buf,length);

			socketserver.send(ps);

			/*System.out.println("Le serveur est à l'écoute du port "+socketserver.getLocalPort());
			socketduserveur = socketserver.accept(); 
		        System.out.println("Un zéro s'est connecté");
			out = new PrintWriter(socketduserveur.getOutputStream());
		        out.println("Vous êtes connecté zéro !");
		        out.flush();
		                
		        socketduserveur.close();
		        socketserver.close();*/
			

			DatagramSocket socket = new DatagramSocket(2009) ;
			DatagramPacket packet = new DatagramPacket(. . .) ;
			packet.setPort(serverPort) ;
			packet.setAddress(serverAddress) ;
			//Envoie de données
			byte[ ] sentBuffer  = ...;
			packet.setData(sentBuffer) ;
			socket.send(packet) ;
			//Récupératio nde données
			byte[ ] receiveBuffer = . . . ;
			packet.setData(receiveBuffer) ;
			socket.receive(packet) ;
			socket.close() ;

		        
		}catch (IOException e) {
			
			e.printStackTrace();
		}
	}
}
