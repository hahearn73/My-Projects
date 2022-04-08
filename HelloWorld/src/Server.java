import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.ArrayList;

public class Server
{
  private static ArrayList<User> userList = new ArrayList<User>();

  public static void main(String[] args) throws IOException
  {
	System.out.println(InetAddress.getByName("localhost"));
	ServerSocket ss = new ServerSocket(5000);
    acceptMessages(ss);
    ss.close();
    System.out.println("Server Closed");
  }
  
  
  /**
   * Accepts messages from clients and calls other methods
   * A
   * @param ss
   *          The ServerSocket being used
   * @throws IOException
   */
  public static void acceptMessages(ServerSocket ss) throws IOException
  {

    String str = "";

    while (true)
    {
      try
      {
        Socket s = ss.accept();

        InputStreamReader in = new InputStreamReader(s.getInputStream());
        BufferedReader bf = new BufferedReader(in);

        str = bf.readLine();

        System.out.println(str);

        sendMessage(messageToSend(str));
        System.out.println(getUserList());
      }
      catch (IOException e)
      {
        System.out.println(e);
      }
    }
  }

  /**
   * Sends message to all clients
   * 
   * @param message
   *          The message being sent
   * @throws UnknownHostException
   * @throws IOException
   */
  public static void sendMessage(String message)
      throws UnknownHostException, IOException
  {
    for (User u : getUserList())
    {
      Socket s = new Socket(u.getIp(), 5001);

      PrintWriter pr = new PrintWriter(s.getOutputStream());
      pr.println(message);
      pr.flush();

      s.close();
    }
  }

  /**
   * Formats the message
   * 
   * @param str
   *          The message being sent
   * @return
   */
  public static String messageToSend(String str)
  {
    return findUser(str) + str.substring(str.indexOf(":"));
  }

  /**
   * Returns the username of client
   * 
   * @param str
   *          The String their name/Ip is contained in
   * @return
   */
  public static String findUser(String str)
  {
    for (User u : getUserList())
    {
      if (u.getIp().equals(str.substring(0, str.indexOf("\\"))))
      {
        return u.getName();
      }
    }

    userList.add(new User((str.substring(0, str.indexOf("\\"))),
        str.substring(str.indexOf("\\\\") + 1, str.indexOf(":"))));
    return getUserList().get(getUserList().size() - 1).getName();
  }

  /**
   * Returns userList
   * 
   * @return UserList
   */
  public static ArrayList<User> getUserList()
  {
    return userList;
  }
}
