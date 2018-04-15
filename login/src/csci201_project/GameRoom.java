package csci201_project;

import java.io.Serializable;

class GameRoom implements Serializable {
	public static final long serialVersionUID = 1;
	public String roomName;
	public int playerNum;
	public int capacity;
	public int clientA;
	public int clientB;
	public int userA;
	public int userB;
	
	public GameRoom(String s_name, int i_num, int i_cap) {
		roomName = s_name;
		playerNum = i_num;
		capacity = i_cap;
	}
}
