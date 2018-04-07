package csci201_project;

import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.geom.*;
import java.io.IOException;

import javax.swing.*;
import java.sql.*;

public class Welcome {
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				LoginFrame frame = new LoginFrame();
				frame.setExtendedState(Frame.NORMAL);
				frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
				frame.setVisible(true);
			}
		});
	}
}

class LoginFrame extends JFrame {
	private static final long serialVersionUID = 1L;
	private int sizeHeight = 600;
	private int sizeWidth = 800;

	public LoginFrame() {
		//Set Frame Style
		try {
			UIManager.setLookAndFeel("com.sun.java.swing.plaf.windows.WindowsLookAndFeel");
			//alternative: "com.sun.java.swing.plaf.windows.WindowsLookAndFeel"
			// "javax.swing.plaf.nimbus.NimbusLookAndFeel"
		} catch (Exception e) {
			System.out.println(e.getMessage());
		}
        //Set location and size
		Toolkit kit = Toolkit.getDefaultToolkit();
        Dimension screenSize = kit.getScreenSize();
        setBounds((int) (screenSize.getWidth() - sizeWidth) / 2, (int) (screenSize.getHeight() - sizeHeight) / 2 , sizeWidth, sizeHeight);
        //Set icon
        Image img = new ImageIcon("icon.png").getImage();
        setIconImage(img);
        //Set Title
        setTitle("Welcome to our SpaceGame!");

        //append components
        loginPanel loginp = new loginPanel();
        add(loginp);
        
        //pack(); //auto-size the whole frame
    }

}

class DrawComponent extends JComponent
{
	private static final long serialVersionUID = 1L;

    public void paintComponent(Graphics g){
        Graphics2D g2 = (Graphics2D)g;
        double leftX = 100;
        double topY = 100;
        double width = 200;
        double height = 150;
        Rectangle2D rect = new Rectangle2D.Double(leftX,topY,width,height);
        g2.draw(rect);
        Ellipse2D ellipse = new Ellipse2D.Double();
        ellipse.setFrame(rect);
        g2.draw(ellipse);
        g2.draw(new Line2D.Double(leftX,topY,leftX+width,topY+height));
        double centerX = rect.getCenterX();
        double centerY = rect.getCenterY();
        double radius = 150;
        Ellipse2D circle = new Ellipse2D.Double();
        circle.setFrameFromCenter(centerX, centerY, centerX+radius, centerY+radius);
        g2.draw(circle);
    }
}

class loginPanel extends JPanel {
	private static final long serialVersionUID = 1L;
	Image image;
	
	@Override
    public void paintComponent(Graphics g) {
      super.paintComponent(g);
      if (image != null) {
        g.drawImage(image, 0, 0, this);
      }
    }
	
	public loginPanel() {
		//Dynamic background
		
		image = Toolkit.getDefaultToolkit().createImage("background.gif");

		  
		//Place component
		setLayout(null);
		Font label_f = new Font("Dialog", Font.BOLD, 24);
		Font text_f = new Font("Dialog", Font.PLAIN, 20);
		
		Label userl = new Label(100,20,200,25, "Users: ", label_f, this);
		add(userl);
		
		Label passwordl = new Label(100,50,200,25, "Password: ", label_f, this);
		add(passwordl);
		
		JTextField userText = new JTextField();
		userText.setBounds(300,20,200,25);
		userText.setFont(text_f);
        add(userText);
        
        JPasswordField passwordText = new JPasswordField();
        passwordText.setBounds(300,50,200,25);
        passwordText.setFont(text_f);
        add(passwordText);
		
		
		Button loginButton = new Button(200, 100, 150, 25, "Login", label_f, this);
		loginButton.addMouseListener(new MouseAdapter() {
        	public void mouseClicked(MouseEvent event) {  
                loginValidate(event, userText, passwordText);  
            }  
        });
		add(loginButton);
		
		Button signupButton = new Button(400, 100, 150, 25, "Sign up", label_f, this);
		signupButton.addMouseListener(new MouseAdapter() {
        	public void mouseClicked(MouseEvent event) {  
                signupValidate(event, userText, passwordText);  
            }  
        });
		add(signupButton);
		
		Button guestButton = new Button(280, 150, 200, 25, "I'm a guest", label_f, this);
		guestButton.addMouseListener(new MouseAdapter() {
        	public void mouseClicked(MouseEvent event) {  
        		guestMode(event);  
            }  
        });
		add(guestButton);
	}
	
	public static void guestMode(MouseEvent event) {
    	launchGame("");
    }
	
	public static boolean checkUsernameValid(String username) {
		if (username.length()<=1 || username.length()>=9) return false;
		return username.matches("[a-zA-Z0-9]+");
	}
	
	public static boolean checkPasswordValid(String password) {
		if (password.length()<=5 || password.length()>=21) return false;
		return password.matches("[a-zA-Z0-9]+");
	}
	
	public static void signupValidate(MouseEvent event, JTextField userText, JPasswordField password) {
		String password_str = new String(password.getPassword());
    	String username = userText.getText();
    	Connection conn = null;
		PreparedStatement ps = null;
		PreparedStatement ps2 = null;
		ResultSet rs = null;
    	
		try {
			Class.forName("com.mysql.jdbc.Driver"); //acquire at run-time
			conn = DriverManager.getConnection("jdbc:mysql://localhost/CS201Proj?user=root&password=root&useSSL=false");
			if (!checkUsernameValid(username)) {
				JOptionPane.showMessageDialog(null, "Username should be 2-8 letters!", "Signup Error", JOptionPane.ERROR_MESSAGE);
			}
			else if (!checkPasswordValid(password_str)) {
				JOptionPane.showMessageDialog(null, "Password should be 6-20 letters!", "Signup Error", JOptionPane.ERROR_MESSAGE);
				password.setText("");
			}
			else {
				ps = conn.prepareStatement(" SELECT * " + 
						 " FROM Users " + 
						 " WHERE userName = '" + username + "'" +
						 ";");
				rs = ps.executeQuery();
				if (rs.next()) {
					JOptionPane.showMessageDialog(null, "Username Taken!", "Signup Error", JOptionPane.ERROR_MESSAGE);
					password.setText("");
				}
				else {
					ps2 = conn.prepareStatement(" INSERT INTO Users(userName, userPassword) VALUES" + 
							 " ('" + username + "', '" + password_str + "'" + ") ;");
					ps2.executeUpdate();
					JOptionPane.showMessageDialog(null, "Sign up successfully!", "OK", JOptionPane.INFORMATION_MESSAGE);
					launchGame("");
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
				if (conn != null) {
					conn.close();
				}
			} catch (SQLException sqle) {
				System.out.println("sqle closing streams: " + sqle.getMessage());
			}
		}
	}
	
	public static void loginValidate(MouseEvent event, JTextField userText, JPasswordField password) {
    	String password_str = new String(password.getPassword());
    	String truepassword;
    	String username = userText.getText();
    	Connection conn = null;
		boolean authenticate = false;
		PreparedStatement ps = null;
		ResultSet rs = null;
		try {
			Class.forName("com.mysql.jdbc.Driver"); //acquire at run-time
			conn = DriverManager.getConnection("jdbc:mysql://localhost/CS201Proj?user=root&password=root&useSSL=false");
			if (!checkUsernameValid(username)) {
				authenticate = false;
			}
			else {
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
			}
			if (!authenticate) {
	    		password.setText("");
	    		JOptionPane.showMessageDialog(null, "Login Failed!", "Login Error", JOptionPane.ERROR_MESSAGE);
	    	}
			else 
				launchGame("");
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
				if (conn != null) {
					conn.close();
				}
			} catch (SQLException sqle) {
				System.out.println("sqle closing streams: " + sqle.getMessage());
			}
		}
    }
	
	public static void launchGame(String param) {
		try {
			Process p = Runtime.getRuntime().exec("deploy_win\\Game.exe " + param);
		} catch (IOException e) {
			System.out.println(e.getMessage());
		} 
	}
}

class Label extends JLabel {
	private static final long serialVersionUID = 1L;
	public Label(int X, int Y, int Width, int Height, String name, Font f, JPanel parent) {
		super(name);
		setBounds(X, Y, Width, Height);
		setFont(f);
		setForeground(Color.white);
	}
}

class Button extends JButton {
	private static final long serialVersionUID = 1L;
	
	public Button(int X, int Y, int Width, int Height, String name, Font f, JPanel parent) {
		super(name);
		setBounds(X, Y, Width, Height);
		setFont(f);
	}
}


