public class User
{
  private final String ip;
  private String name;

  public User(String ip, String name)
  {
    this.ip = ip;
    this.name = name;
  }

  public String getIp()
  {
    return this.ip;
  }

  public String getName()
  {
    return this.name;
  }

  public void setName(String name)
  {
    this.name = name;
  }
  
  public String toString()
  {
    return this.getName();
  }
}


