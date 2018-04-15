package csci201_project;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Scanner;
import java.util.Vector;

public class Server extends Thread{
	private Vector<ServerThread> threads;
	private Vector<GameRoom> roomSet;
	public static int serverPort;
	public static int clientID = 1;
	
	public static boolean checkPort(int port) {
		return (port>1024);
	}
	
	public void addRoom(String roomName, int capacity, int clientID, int userID) {
		GameRoom newRoom = new GameRoom(roomName, 1, capacity);
		newRoom.clientA = clientID;
		newRoom.userA = userID;
		roomSet.add(newRoom);
	}
	
	public GameRoom findRoom(String roomName) {
		for (int i = 0; i < roomSet.size(); i++) {
			if (roomName.toUpperCase().equals(roomSet.get(i).roomName.toUpperCase())) {
				return roomSet.get(i);
			}
		}
		return null;
	}
	
	public ServerThread findServer(int clientID) {
		for (int i = 0; i < threads.size(); i++) {
			if (threads.get(i).clientID==clientID) {
				return threads.get(i);
			}
		}
		return null;
	}
	
	public void deleteThread(ServerThread st) {
		threads.remove(st);
	}
	
	public void deleteRoom(String roomName) {
		for (int i = 0; i < roomSet.size(); i++) {
			if (roomName.toUpperCase().equals(roomSet.get(i).roomName.toUpperCase())) {
				roomSet.remove(i);
				System.out.println("deleting this game:" + roomName);
				return;
			}
		}
	}
	
	public void joinRoom(String roomName, int clientID, int userID) {
		for (GameRoom room: roomSet) {
			if (room.roomName.toUpperCase().equals(roomName.toUpperCase())) {
				room.playerNum++;
				room.clientB = clientID;
				room.userB = userID;
				return;
			}
		}
	}
	
	public void sendMessage(String message, int clientID) {
		if (message != null) {
			for(ServerThread threads : threads) {
				if (clientID == threads.clientID) {
					threads.sendMessageToClient(message);
				}
			}
		}
	}
	
	public void sendObject(Object object, int clientID){
		try {
			if (object != null) {
				for(ServerThread threads : threads) {
					if (clientID == threads.clientID) {
						threads.sendObjectToClient(object);
					}
				}
			}
		} catch(IOException ioe) {
			System.out.println(ioe.getMessage());
		}
	}
	
	public Server(int port) {
		Scanner scanner = new Scanner(System.in);
		
		boolean portOK=false;
		int tmp_port;
		do {
			System.out.println("Please enter a valid port:");
			tmp_port = 6789;
			portOK = checkPort(tmp_port);
			if (!portOK) System.out.println("Invalid port!");
		} while (!portOK);
		serverPort = tmp_port;
		
		this.start();
		
		try {
			ServerSocket ss = new ServerSocket(port);
			threads = new Vector<ServerThread>();
			roomSet = new Vector<GameRoom>();
			System.out.println("Success!");
			while (true) {
				Socket s = ss.accept();
				System.out.println("Connection from: " + s.getInetAddress());
				ServerThread st = new ServerThread(s, this, clientID++);
				threads.add(st);
			}
		} catch (IOException ioe) {
			System.out.println(ioe.getMessage());
		}
		
	}
	
	public void broadcast(String message, ServerThread st) {
		if (message != null) {
			System.out.println(message);
			for(ServerThread threads : threads) {
				if (st != threads) {
					threads.sendMessageToClient(message);
				}
			}
		}
	}
	
	public void run() {
		Scanner scanner = new Scanner(System.in);
		
		while (true) {
			String line = scanner.nextLine();
			if (line.equals("lr")) {
				for (int i = 0; i < roomSet.size(); i++) {
					System.out.println(roomSet.get(i).roomName + " " + roomSet.get(i).playerNum + " " + roomSet.get(i).capacity + "  " + roomSet.get(i).clientA + " " + roomSet.get(i).clientB);
				}
			}
		}
	}
	
	public static void main(String[] args) {
		Server server = new Server(6789);
	}
}
