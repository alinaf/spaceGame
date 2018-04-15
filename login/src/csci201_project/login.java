package csci201_project;

import java.awt.Font;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JPasswordField;
import javax.swing.JTextField; 

public class login {
	/*
	private static Image image;  
	
    public static void main(String[] args) {    
        JFrame frame = new JFrame("Login");
        //frame.setSize(842, 631);
        frame.setBounds(100, 100, 840, 631);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        
        JPanel panel = new JPanel() {  
            protected void paintComponent(Graphics g) {  
                ImageIcon icon = new ImageIcon("E:\\USC\\201CSCI_Sofware\\finalProject\\background.png");  
                Image img = icon.getImage();  
                g.drawImage(img, 0, 0, icon.getIconWidth(),  
                        icon.getIconHeight(), icon.getImageObserver());  
                
            }  
  
        };  
        frame.add(panel);
        placeComponents(panel);

        frame.setVisible(true);
    }

    private static void placeComponents(JPanel panel) {
    	Font promptFont = new Font("Dialog", Font.PLAIN, 20);
        panel.setLayout(null);
        JLabel userLabel = new JLabel("User:");
        userLabel.setFont(promptFont);
        userLabel.setBounds(100,20,150,25);
        panel.add(userLabel);
        
        JTextField userText = new JTextField(20);
        userText.setBounds(300,20,200,25);
        panel.add(userText);
        
        JLabel passwordLabel = new JLabel("Password:");
        passwordLabel.setFont(promptFont);
        passwordLabel.setBounds(100,50,150,25);
        panel.add(passwordLabel);

        JPasswordField passwordText = new JPasswordField(20);
        passwordText.setBounds(300,50,200,25);
        panel.add(passwordText);

        JButton loginButton = new JButton("login");
        loginButton.setFont(promptFont);
        loginButton.setBounds(200, 100, 100, 25);
        loginButton.addMouseListener(new MouseAdapter() {
        	public void mouseClicked(MouseEvent event) {  
                loginValidate(event, userText.getText(), passwordText);  
            }  
        });
        panel.add(loginButton);
        
        JButton signupButton = new JButton("sign up");
        signupButton.setFont(promptFont);
        signupButton.setBounds(400, 100, 100, 25);
        signupButton.addMouseListener(new MouseAdapter() {
        	public void mouseClicked(MouseEvent event) {  
                loginValidate(event, userText.getText(), passwordText);  
            }  
        });
        panel.add(signupButton);
        
        JButton guestButton = new JButton("I'm a guest");
        guestButton.setFont(promptFont);
        guestButton.setBounds(280, 150, 150, 25);
        guestButton.addMouseListener(new MouseAdapter() {
        	public void mouseClicked(MouseEvent event) {  
                guestMode(event);  
            }  
        });
        panel.add(guestButton);
    }

    public static void guestMode(MouseEvent event) {
    	
    }
    
    public static void loginValidate(MouseEvent event, String username, JPasswordField password) {
    	String password_str = new String(password.getPassword());
    	String truepassword;
    	Connection conn = null;
		Statement st = null;
		boolean authenticate = false;
		PreparedStatement ps = null;
		ResultSet rs = null;
    	
		try {
			Class.forName("com.mysql.jdbc.Driver"); //acquire at run-time
			conn = DriverManager.getConnection("jdbc:mysql://localhost/CS201Proj?user=root&password=root&useSSL=false");
			st = conn.createStatement();
			ps = conn.prepareStatement(" SELECT * " + 
					 " FROM Users " + 
					 " WHERE userName = ? " + 
					 ";");
			ps.setString(1, username);
			rs = ps.executeQuery();
			if (rs.next()) {
				truepassword = rs.getString("userPassword");
				if (password_str.equals(truepassword)) {
					authenticate = true;
					System.out.println("Success");
				}
			}
	    	if (!authenticate) {
	    		password.setText("");
	    		System.out.println("Failed");
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
				if (st != null) {
					st.close();
				}
				if (conn != null) {
					conn.close();
				}
			} catch (SQLException sqle) {
				System.out.println("sqle closing streams: " + sqle.getMessage());
			}
		}
    }
    */
}