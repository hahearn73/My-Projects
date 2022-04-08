import java.net.*;
import javax.swing.*;
import javax.swing.border.Border;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.io.*;

@SuppressWarnings("serial")
public class Client extends JFrame implements KeyListener
{

  // Variables used for whole class
  JButton sendButton;
  JTextField message;
  static JTextArea board;
  static JTextField name;
  static int verticalScrollBarMaximumValue;
  static JButton ip;
  static String serverIP;
  static JButton changeNameRequest;

  public static void main(String[] args) throws IOException
  {
    new Client();
  }

  public Client()
  {
    // Basic swing elements
    this.setSize(450, 400);
    Toolkit tk = Toolkit.getDefaultToolkit();
    Dimension dim = tk.getScreenSize();
    int xPos = (dim.width / 2) - (this.getWidth() / 2);
    int yPos = (dim.height / 2) - (this.getHeight() / 2);
    this.setLocation(xPos, yPos);
    this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    this.setTitle("HelloWorld");
    
    
    //color & border
    Color gray = new Color(77, 77, 77);
    Border border = BorderFactory.createLineBorder(Color.BLACK);
    
    // Panel
    JPanel panel = new JPanel();
    panel.setBackground(gray);
    // Label
    JLabel nameLabel = new JLabel("Name:");
    nameLabel.setForeground(Color.WHITE);
    // Message Board
    board = new JTextArea(15, 30);
    board.setBackground(gray);
    board.setForeground(Color.WHITE);
    board.setLineWrap(true);
    board.setWrapStyleWord(true);
    board.setEditable(false);
    board.setBorder(BorderFactory.createCompoundBorder(border, BorderFactory.createEmptyBorder(10, 10, 10, 10)));
    // Place to enter message
    name = new JTextField(10);
    message = new JTextField(35);
    
    ip = new JButton("Server Switch");
    ip.addActionListener(new java.awt.event.ActionListener() {
        @Override
        public void actionPerformed(java.awt.event.ActionEvent evt) {
            String newIP = JOptionPane.showInputDialog(panel,
                    "Enter server IP", null);
            serverIP = newIP;
            board.setText("server IP has been changed to: " + serverIP);
        }
    });
    
    name.setBackground(gray);
    message.setBackground(gray);
    
    name.setForeground(Color.WHITE);
    message.setForeground(Color.WHITE);
    
    name.setBorder(BorderFactory.createCompoundBorder(border, BorderFactory.createEmptyBorder(10, 10, 10, 10)));
    message.setBorder(BorderFactory.createCompoundBorder(border, BorderFactory.createEmptyBorder(10, 10, 10, 10)));

    // Scrollbar
    JScrollPane scrolltxt = new JScrollPane(board);
    panel.add(scrolltxt);
    // Button settings
    sendButton = new JButton();
    sendButton.setText("SEND");
    ListenForButton sender = new ListenForButton();
    sendButton.addActionListener(sender);

    // ADD THINGS TO PANEL
    panel.add(message);
    panel.add(nameLabel);
    panel.add(name);
    panel.add(sendButton);
    panel.add(ip);
    
    // AUTOSCROLL DO NOT TOUCH THIS IS LEGACY CODE
    verticalScrollBarMaximumValue = scrolltxt.getVerticalScrollBar()
        .getMaximum();
    scrolltxt.getVerticalScrollBar().addAdjustmentListener(e -> {
      if ((verticalScrollBarMaximumValue - e.getAdjustable().getMaximum()) == 0)
        return;
      e.getAdjustable().setValue(e.getAdjustable().getMaximum());
      verticalScrollBarMaximumValue = scrolltxt.getVerticalScrollBar()
          .getMaximum();
    });

    // Adding KeyListeners to the panel elements
    message.addKeyListener(this);
    name.addKeyListener(this);

    // Final Visibility
    this.add(panel);
    this.setVisible(true);

    // Functionality
    try
    {
      listenForMessages();
    }
    catch (IOException e)
    {
      e.printStackTrace();
    }
  }

  /**
   * Sends message to server
   * 
   * @param message
   *          Message being sent
   * @throws UnknownHostException
   * @throws IOException
   */
  public static void sendMessage(String message)
      throws UnknownHostException, IOException
  {
    Socket s = new Socket(InetAddress.getByName(serverIP), 5000);//change ip based on 
    //where you’re connecting to, get host ip by doing 
    //‘System.out.println(InetAddress.getLocalHost().getHostAddress())’

    PrintWriter pr = new PrintWriter(s.getOutputStream());
    pr.println(InetAddress.getLocalHost().getHostAddress() + "\\\\"
        + name.getText() + ": " + message);
    pr.flush();

    s.close();
  }

  /**
   * Waits for messages from server and updates the board
   * 
   * @throws IOException
   */
  public static void listenForMessages() throws IOException
  {
    while (true)
    {
      ServerSocket ss = new ServerSocket(5001);
      Socket s = ss.accept();
      
      InputStreamReader in = new InputStreamReader(s.getInputStream());
      BufferedReader bf = new BufferedReader(in);

      String str = bf.readLine();

      if (board.getText().equals(""))
        board.append(str);
      else
        board.setText(board.getText() + "\n" + str);
      
      ss.close();
    }
  }

  /**
   * Gives actions to the button, calls send function
   */
  private class ListenForButton implements ActionListener
  {

    public void actionPerformed(ActionEvent e)
    {
      if (message.getText().equals(""))
      {
        JOptionPane.showMessageDialog(Client.this,
            "Please enter text before sending", "Error",
            JOptionPane.ERROR_MESSAGE);
      }
      else if (e.getSource() == sendButton)
      {
        try
        {
          sendMessage(message.getText());
          message.setText("");
        }
        catch (IOException e1)
        {
        }
      }
    }
  }

  @Override
  public void keyPressed(KeyEvent e)
  {
    if (e.getKeyCode() == KeyEvent.VK_ENTER && message.getText().equals(""))
    {
      JOptionPane.showMessageDialog(Client.this,
          "Please enter text before sending", "Error",
          JOptionPane.ERROR_MESSAGE);
    }
    else if (e.getKeyCode() == KeyEvent.VK_ENTER)
    {
      try
      {
        sendMessage(message.getText());
        message.setText("");
      }
      catch (IOException e1)
      {
      }
    }
  }

  @Override
  public void keyReleased(KeyEvent e)
  {
  }

  @Override
  public void keyTyped(KeyEvent e)
  {
  }

}

