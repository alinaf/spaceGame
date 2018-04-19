package csci201_project;

import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.geom.*;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.PrintWriter;
import java.net.Socket;

import javax.swing.*;
import java.sql.*;
import java.util.Scanner;

public class Welcome {
	
	public static boolean checkPort(int port) {
		return (port>=1024 && port<=65535);
	}
	
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
	private int sizeHeight = 960;
	private int sizeWidth = 1280;
	private Welcome parent;

	public LoginFrame() {
		this.parent = parent;
		//Set Frame Style
		try {
			UIManager.setLookAndFeel("javax.swing.plaf.nimbus.NimbusLookAndFeel");
			//alternative: "com.sun.java.swing.plaf.windows.WindowsLookAndFeel"
			// com.sun.java.swing.plaf.gtk.GTKLookAndFeel
			// com.sun.java.swing.plaf.motif.MotifLookAndFeel
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
	private int myUserID;
	private static String svrIP;
	private static int svrPort;
	public static ObjectInputStream ois;
	public static ObjectOutputStream oos;
	public static BufferedReader br;
	public static PrintWriter pw;
	private String status;
	private String roomname;
	
	@Override
    public void paintComponent(Graphics g) {
      super.paintComponent(g);
      if (image != null) {
        g.drawImage(image, 0, 0, this);
      }
    }
	
	public boolean checkNameExist(String name) {
		try {
			sendMessageToServer("checkNameExist " + name);
			String response = br.readLine();
			if (response.equals(("false"))) return false;
			if (response.equals(("true")))  return true;
	  	} catch (IOException ioe) {
	  		System.out.println("ioe in ChatClient.run(): " + ioe.getMessage());
	  	} 
		return false;
	}
	
	public void sendMessageToServer(String msg) {
		pw.println(msg);
		pw.flush();
	}
	
	public String receiveMessageFromServer() {
		try {
			return br.readLine();
		} catch (IOException ioe) {
			System.out.println("error");
		}
		return null;
	}
	
	public loginPanel() {
		//Dynamic background
		Socket s = null;
		int screenWidth = 1280;
		int buttonWidth = 500;
		int labelWidth = 400;
		int textWidth = 500;
		int textStartY = 100;
		int textSplitY = 70;
		int labelX = 200;
		int buttonHeight = 50;
		
		svrIP = "localhost"; //Hard-coded so far
		svrPort = 6789;
		
		try {
			s = new Socket(svrIP, svrPort);
			System.out.println("Connected to " + svrIP + ":" + svrPort);
			br = new BufferedReader(new InputStreamReader(s.getInputStream()));
			pw = new PrintWriter(s.getOutputStream());
			oos = new ObjectOutputStream(s.getOutputStream());
			ois = new ObjectInputStream(s.getInputStream());
		} catch (IOException ioe) {
			JOptionPane.showMessageDialog(null, "Can't connect to the server, please try again later", "Connection Error", JOptionPane.ERROR_MESSAGE);
			System.out.println("ioe in Client constructor: " + ioe.getMessage());
			System.out.println("Please type your connection info again.");
			System.exit(1);
		}
		
		image = Toolkit.getDefaultToolkit().createImage("clouds.gif");

		  
		//Place component
		setLayout(null);
		Font label_f = new Font("ARCADECLASSIC", Font.BOLD, 44);
		Font text_f = new Font("ARCADECLASSIC", Font.PLAIN, 40);
		
		Label userl = new Label(labelX,textStartY,labelWidth,25, "Users ", label_f, this);
		add(userl);
		
		Label passwordl = new Label(labelX,textStartY + textSplitY * 1,labelWidth,25, "Password ", label_f, this);
		add(passwordl);
		
		Label gamenamel = new Label(labelX, textStartY + textSplitY * 2, labelWidth, 25, "Gamename ", label_f, this);
		add(gamenamel);
		
		Label errormsgl = new Label(100, textStartY + textSplitY * 3, 1500, 25, "", label_f, this);
		errormsgl.setForeground(Color.RED);
		add(errormsgl);
		
		JTextField userText = new JTextField();
		userText.setBounds(600,textStartY,textWidth,40);
		userText.setFont(text_f);
        add(userText);
        
        JPasswordField passwordText = new JPasswordField();
        passwordText.setBounds(600,textStartY + textSplitY * 1,textWidth,40);
        passwordText.setFont(text_f);
        add(passwordText);
        
        JTextField gamenameText = new JTextField();
        gamenameText.setBounds(600,textStartY + textSplitY * 2,textWidth,40);
        gamenameText.setFont(text_f);
		add(gamenameText);
		
		
		Button loginButton = new Button((screenWidth - buttonWidth) / 2, 400, buttonWidth, buttonHeight, "Ready Player One", label_f, this);
		loginButton.addMouseListener(new MouseAdapter() {
        	public void mouseClicked(MouseEvent event) {  
                myUserID = loginValidate(event, userText, passwordText, errormsgl); 
                System.out.println(myUserID);
                if (myUserID>0) {
                	boolean isExisted = checkNameExist(gamenameText.getText());
                	System.out.println(isExisted);
                	if (isExisted) {
                		errormsgl.setText("Create Game Error  Game name has existed");
                	}
                	else {
                    	System.out.println("Now waiting for another thread...");
                		sendMessageToServer("createRoom " + gamenameText.getText() + " " + myUserID);
                    	status = receiveMessageFromServer();
                    	roomname = receiveMessageFromServer();
                    	System.out.println("Starting" + roomname + "...");
                    	errormsgl.setText("Starting" + roomname + "...  ENJOY!!");
                    	launchGame(roomname + " A");
                	}
                }
                else {
                	
                }
            }  
        });
		add(loginButton);
		
		Button joinButton = new Button((screenWidth - buttonWidth) / 2, 500, buttonWidth, buttonHeight, "Ready Player Two", label_f, this);
		joinButton.addMouseListener(new MouseAdapter() {
        	public void mouseClicked(MouseEvent event) {  
                myUserID = loginValidate(event, userText, passwordText, errormsgl);  
                if (myUserID > 0) {
                	boolean checkOK = checkNameExist(gamenameText.getText());
                	if (checkOK) {
                		errormsgl.setText("");
                		sendMessageToServer("joinRoom " + gamenameText.getText() + " " + myUserID);
                    	System.out.println("be about to start");
                    	status = receiveMessageFromServer();
                    	System.out.println("Starting" + roomname + "...");
                    	errormsgl.setText("Starting" + roomname + "...  ENJOY!!");
                    	launchGame(roomname + " B");
                	}
                	else {
                		errormsgl.setText("Join Game Error   Game not existed");
                	}
                }
            }  
        });
		add(joinButton);
		
		Button signupButton = new Button((screenWidth - buttonWidth) / 2, 600, buttonWidth, buttonHeight, "Sign up", label_f, this);
		signupButton.addMouseListener(new MouseAdapter() {
        	public void mouseClicked(MouseEvent event) {  
                signupValidate(event, userText, passwordText, errormsgl);  
            }  
        });
		add(signupButton);
		
		Button guestButton = new Button((screenWidth - buttonWidth) / 2, 700, buttonWidth, buttonHeight, "Guest Mode", label_f, this);
		guestButton.addMouseListener(new MouseAdapter() {
        	public void mouseClicked(MouseEvent event) {  
        		guestMode(event);  
            }  
        });
		add(guestButton);
		
		
	}
	
	public static void guestMode(MouseEvent event) {
    	launchGame("Guest");
    }
	
	public static boolean checkUsernameValid(String username) {
		if (username.length()<=1 || username.length()>=9) return false;
		return username.matches("[a-zA-Z0-9]+");
	}
	
	public static boolean checkPasswordValid(String password) {
		if (password.length()<=5 || password.length()>=21) return false;
		return password.matches("[a-zA-Z0-9]+");
	}
	
	public static String signupValidate(MouseEvent event, JTextField userText, JPasswordField password, JLabel errmsg) {
		String password_str = new String(password.getPassword());
    	String username = userText.getText();
    	Connection conn = null;
		PreparedStatement ps = null;
		PreparedStatement ps2 = null;
		ResultSet rs = null;
    	
		errmsg.setText("");
		
		try {
			Class.forName("com.mysql.jdbc.Driver"); //acquire at run-time
			conn = DriverManager.getConnection("jdbc:mysql://" + svrIP + "/CS201Proj?user=root&password=root&useSSL=false");
			if (!checkUsernameValid(username)) {
				errmsg.setText("Signup Error   Username should be 2 to 8 letters");
				return "usernameerr";
			}
			else if (!checkPasswordValid(password_str)) {
				errmsg.setText("Signup Error   Password should be 6 to 20 letters");
				password.setText("");
				return "passworderr";
			}
			else {
				ps = conn.prepareStatement(" SELECT * " + 
						 " FROM Users " + 
						 " WHERE userName = '" + username + "'" +
						 ";");
				rs = ps.executeQuery();
				if (rs.next()) {
					errmsg.setText("Username Taken!");
					password.setText("");
				}
				else {
					ps2 = conn.prepareStatement(" INSERT INTO Users(userName, userPassword) VALUES" + 
							 " ('" + username + "', '" + password_str + "'" + ") ;");
					ps2.executeUpdate();
					JOptionPane.showMessageDialog(null, "Sign up successfully!", "OK", JOptionPane.INFORMATION_MESSAGE);
					return "success";
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
		return "";
	}
	
	@SuppressWarnings("finally")
	public static int loginValidate(MouseEvent event, JTextField userText, JPasswordField password, JLabel errmsg) {
    	String password_str = new String(password.getPassword());
    	String truepassword;
    	String username = userText.getText();
    	Connection conn = null;
		boolean authenticate = false;
		PreparedStatement ps = null;
		ResultSet rs = null;
		
		errmsg.setText("");
		int myUserID = -1;
		try {
			Class.forName("com.mysql.jdbc.Driver"); //acquire at run-time
			conn = DriverManager.getConnection("jdbc:mysql://" + svrIP + "/CS201Proj?user=root&password=root&useSSL=false");
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
						myUserID = rs.getInt("userID");
						System.out.println("Success");
					}
				}
			}
			if (!authenticate) {
	    		password.setText("");
	    		errmsg.setText("Login Failed!");
	    		return -1;
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
				if (conn != null) {
					conn.close();
				}
			} catch (SQLException sqle) {
				System.out.println("sqle closing streams: " + sqle.getMessage());
			}
			return myUserID;
		}
    }
	
	
	
	public static void launchGame(String param) {
		try {
			Process p = Runtime.getRuntime().exec("deploy_win\\Game.exe ");
			System.exit(0);
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


