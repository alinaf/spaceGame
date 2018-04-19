package csci201_project;


import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.PrintWriter;
import java.net.Socket;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import javax.swing.JOptionPane;

public class ServerThread extends Thread {

	private PrintWriter pw;
	private BufferedReader br;
	private ObjectInputStream ois= null;
	private ObjectOutputStream oos = null;
	public int clientID;
	public int oppoClientID;
	public int userID;
	
	private Server server;
	public String roomName;
	public ServerThread(Socket s, Server server, int clientID) {
		try {
			this.clientID = clientID;
			this.server = server;
			pw = new PrintWriter(s.getOutputStream());
			br = new BufferedReader(new InputStreamReader(s.getInputStream()));
			ois= new ObjectInputStream(s.getInputStream());
			oos= new ObjectOutputStream(s.getOutputStream());
			this.start();
		} catch (IOException ioe) {
			System.out.println("ioe in ServerThread constructor: " + ioe.getMessage());
		}
	}

	public void sendMessageToClient(String message) {
		System.out.println("send to client" + clientID +": " + message);
		pw.println(message);
		pw.flush();
	}
	
	public void sendObjectToClient(Object obj) throws IOException {
		System.out.println("send to client" + clientID + " one object");
		oos.writeObject(obj);
		oos.flush();
	}
	
	private void addDatabase(GameRoom gameroom) {
    	Connection conn = null;
		PreparedStatement ps = null;
		PreparedStatement ps2 = null;
		PreparedStatement ps3 = null;
		ResultSet rs = null;
		try {
			Class.forName("com.mysql.jdbc.Driver"); //acquire at run-time
			conn = DriverManager.getConnection("jdbc:mysql://localhost/CS201Proj?user=root&password=root&useSSL=false");
			{
				ps = conn.prepareStatement(" SELECT * " + 
						 " FROM Game " + 
						 " WHERE gameName = '" + gameroom + "'" +
						 ";");
				rs = ps.executeQuery();
				if (rs.next()) {
					JOptionPane.showMessageDialog(null, "Got existed room!", "CreateARoom Error", JOptionPane.ERROR_MESSAGE);
				}
				else {
					ps2 = conn.prepareStatement(" INSERT INTO Game(userID, points, livesnum, gameName) VALUES" + 
							 " (" + gameroom.userA + ", 0, 3, '" + gameroom.roomName + "') ;");
					ps2.executeUpdate();
					
					ps3 = conn.prepareStatement(" INSERT INTO Game(userID, points, livesnum, gameName) VALUES" + 
							 " (" + gameroom.userB + ", 0, 3, '" + gameroom.roomName + "') ;");
					ps3.executeUpdate();
				}
			}
		} catch (SQLException sqle) {
			System.out.println("Sqle: " + sqle.getMessage());
		} catch (ClassNotFoundException cnfe) {
			System.out.println("cnfe: " + cnfe.getMessage());
		} finally {
			try {
				if (rs != null) {
					rs.close();
				}
				if (ps != null) {
					ps.close();
				}
				if (ps2 != null) ps2.close();
				if (ps3 != null) ps3.close();
				if (conn != null) {
					conn.close();
				}
			} catch (SQLException sqle) {
				System.out.println("sqle closing streams: " + sqle.getMessage());
			}
		}
	}
	
	public void run() {
		try {
			while(true) {
				String line = br.readLine();
				System.out.println("Server recieve: " + line);
				if (line.indexOf("checkNameExist")>-1) {
					String [] param = line.split(" ");
					GameRoom room = server.findRoom(param[1].toUpperCase());
					if (room!=null) {
						sendMessageToClient("true");
						sendObjectToClient(room);
					}
					else sendMessageToClient("false");
				}
				else if (line.indexOf("createRoom")>-1) {
					String [] param = line.split(" ");
					roomName = param[1].toUpperCase();
					userID = Integer.parseInt(param[2]);
					server.addRoom(param[1].toUpperCase(), 2, clientID, userID);
					GameRoom room = server.findRoom(param[1].toUpperCase());
					sendObjectToClient(room);
				}
				else if (line.indexOf("joinRoom")>-1) {
					String [] param = line.split(" ");
					roomName = param[1].toUpperCase();
					GameRoom room = server.findRoom(param[1].toUpperCase());
					userID = Integer.parseInt(param[2]);
					server.joinRoom(param[1].toUpperCase(), clientID, userID);
					oppoClientID = room.clientA;
					server.sendMessage("ready", room.clientA);
					sendMessageToClient("ready");
					server.sendMessage(room.roomName, room.clientA);
					sendMessageToClient(room.roomName);
					
					addDatabase(room);
					ServerThread oppoServer = server.findServer(room.clientA);
					oppoServer.oppoClientID = clientID;
				}
				else if (line.indexOf("shutdown") > -1) {
					System.out.println("#" + clientID + " quits.");
					server.deleteRoom(roomName);
					server.deleteThread(this);
					break;
				}
			}
		} catch (IOException ioe) {
			System.out.println("ioe in ServerThread.run(): " + ioe.getMessage());
		}
	}
}
