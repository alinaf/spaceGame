package csci201_project;

import java.io.Serializable;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import javax.swing.JOptionPane;



public class GameServer {
	public static boolean checkUsernameValid(String username) {
		if (username.length()<=1 || username.length()>=9) return false;
		return username.matches("[a-zA-Z0-9]+");
	}
	
	
}
