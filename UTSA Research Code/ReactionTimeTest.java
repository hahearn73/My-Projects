import java.awt.Color;
import java.awt.Dimension;
import java.awt.Toolkit;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.util.concurrent.ThreadLocalRandom;
import javax.swing.*;

public class ReactionTimeTest extends JFrame implements KeyListener{
	
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	public static void main(String[] args) throws InterruptedException
	{
		new ReactionTimeTest(5,15);
	}

	static JPanel panel;
	static JTextArea text;
	static int phase = 0; // alerts keyPressed to stop notifying if phase isnt 0
	
	/**
	 * Java swing application that tests reaction time
	 * @param min minimum time between trials in seconds
	 * @param max maximum time between trials in seconds
	 * @throws InterruptedException
	 */
	public ReactionTimeTest(int min, int max) throws InterruptedException
	{
		// Basic Java Swing stuff
		this.setSize(450, 400);
	    Toolkit tk = Toolkit.getDefaultToolkit();
	    Dimension dim = tk.getScreenSize();
	    int xPos = (dim.width / 2) - (this.getWidth() / 2);
	    int yPos = (dim.height / 2) - (this.getHeight() / 2);
	    this.setLocation(xPos, yPos);
	    this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	    this.setTitle("Square Test");
	    
	    // Creating panel and setting background to black
	    panel = new JPanel();
	    panel.setBackground(Color.BLACK);
	    text = new JTextArea(5,20);
	    text.setEditable(false);
	    
	    this.add(panel);
	    this.setVisible(true);
	    addKeyListener(this); // Adding KeyListener
	    setFocusable(true);
	    
	    // sum amounts of time
	    double timeToPress = 0;
	    double timeToRelease = 0;
	    
	    // Actual application
	    String str = ""; // output string
	    for(int i = 0; i < 5; i++) {
	    	str = addIterationCountStr(str,i);
	    	phase = 0;
	    	
	    	// mouse press	
	    	double timeToAdd = (timeEvent(min, max));
	    	timeToPress += timeToAdd; // add delta(time)
	    	str = addTimeDataToStr(false,str,timeToAdd); // output string edit
	    	
	    	// mouse release
	    	timeToAdd = (timeEvent(min, max));
	    	timeToRelease += timeToAdd; // add delta(time)
	    	str = addTimeDataToStr(true,str,timeToAdd); // output string edit
	    	System.out.println(str);
	    	
	    }
	    
	    // Output
	    output(str,timeToPress,timeToRelease);
	    
	}
	
	/**
	 * Adds a text box and outputs reaction data to it
	 * @param str output string
	 * @param timeToPress total time taken to react by pressing
	 * @param timeToRelease total time taken to react by releasing
	 */
	public static void output(String str, double timeToPress, double timeToRelease) {
		 panel.add(text);
		 text.append(str);
		    
		 timeToPress /= 5;
		 timeToRelease /= 5;
		 
		 String press = String.valueOf(timeToPress);
		 text.append("\naverage press time: " + press + " ms");
		   
		 
		 String release = String.valueOf(timeToRelease);
		 text.append("\naverage release time: " + release + " ms");  
		    
	}
	
	/**
	 * Adds iteration count to each section of the string
	 * @param str the string to be edited
	 * @param i the iteration
	 * @return str
	 */
	public String addIterationCountStr(String str, int i) {
		if(i > 0)
			str = str + "\n" + "iteration: " + (i+1);
		else
			str = "iteration: " + (i+1);
		return str;
	}
	
	/**
	 * Adds data to output string that includes the phase (press or release) and time it took for that trial
	 * @param c false for press, true for release
	 * @param str string to be output
	 * @param timeToAdd time interval to add to output string
	 * @return str which is the output string
	 */
	public String addTimeDataToStr(boolean c, String str, double timeToAdd) {
		if(c == true)
			return str + "\n" + ("release:" + (timeToAdd));// output delta(time)	
		return str + "\n" + ("press:" + (timeToAdd)); // output delta(time)
	}
	
	/**
	 * Times user reaction time, is interrupted by a keyListener event
	 * @param min minimum time in seconds
	 * @param max maximum time in seconds
	 * @return a double value that is the time it took for the user to react
	 * @throws InterruptedException
	 */
	public double timeEvent(int min, int max) throws InterruptedException {
		long start,finish;
		int r = ThreadLocalRandom.current().nextInt(min, max + 1); // Random sleep time between min and max
    	Thread.sleep(r*1000); // Sleep
    	start = System.currentTimeMillis(); // initial time value
    	if(panel.getBackground().equals(Color.red) || panel.getBackground().equals(Color.black))
    		panel.setBackground(Color.green);
    	else
    		panel.setBackground(Color.red);
    	
    	// wait for interrupt
    	synchronized(this) {
    	    try {
    	        this.wait();
    	    } catch (InterruptedException e) {}
    	}
    	
    	finish = System.currentTimeMillis(); // end time value	
	    
		return (finish-start);
	}
	
	@Override
	public void keyTyped(KeyEvent e) {}
	
	public void keyPressed(KeyEvent e) {
		if (e.getKeyCode() == KeyEvent.VK_ENTER && panel.getBackground().equals(Color.green) && phase == 0) {
			phase = 1; // sets phase to 1 so that it cannot spam notify
			synchronized(this) {
			    this.notify();
			}
		}
	}


	@Override
	public void keyReleased(KeyEvent e) {
		if (e.getKeyCode() == KeyEvent.VK_ENTER && panel.getBackground().equals(Color.red)) { 
			synchronized(this) {
				this.notify();
			}
		}
	}
}
