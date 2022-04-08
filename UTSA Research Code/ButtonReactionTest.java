import java.awt.Color;
import java.awt.Dimension;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.util.ArrayList;
import java.util.concurrent.ThreadLocalRandom;
import javax.swing.*;

public class ButtonReactionTest extends JFrame implements KeyListener {

	private static final long serialVersionUID = 1L;

	// calls frame object to be created
	public static void main(String[] args) throws InterruptedException {
		new ButtonReactionTest();
	}
	
	// global variables
	static JPanel panel;
	static JTextArea text;
	static ArrayList<Integer> enterPressTimes;
	static ArrayList<Integer> enterReleaseTimes;
	static ArrayList<Integer> mouseClickTimes;
	static long mouseFinish;
	static int mousePhase = 0;
	static int enterPhase = 0;
	static long finish;
	static long keyFinish;
	static int r;
	static ArrayList<JButton> buttons;
	static int rPrev;
	static ListenForButton buttonListener;
	static long start;
	
	/**
	 * Creates button reaction test
	 * @throws InterruptedException
	 */
	public ButtonReactionTest() throws InterruptedException {
		// Basic Java Swing stuff
		ListenForButton buttonListener = new ListenForButton();
		this.setSize(1000, 1000);
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
		
		// initializing panel
		this.add(panel);
		this.setVisible(true);
		addKeyListener(this); // Adding KeyListener
		setFocusable(true);
		
		// add buttons 
		buttons = new ArrayList<JButton>();
		buttons = createButtons(8);
		this.addButtons(buttons); // add buttons
		
		
		// initialize data storage
		enterPressTimes = new ArrayList<Integer>();
		enterReleaseTimes = new ArrayList<Integer>();
		mouseClickTimes = new ArrayList<Integer>();
		
		// actual application process
		rPrev = -1;
		for(int i = 0; i < 2; i++) {
			
			// test greens
			int numGreens = ThreadLocalRandom.current().nextInt(5, 11);
			for(int j = 0; j < numGreens; j++) {
				do {
					r = ThreadLocalRandom.current().nextInt(0, buttons.size());
				}while(rPrev == r);
				
				// modify button and track time
				buttons.get(r).addActionListener(buttonListener);
				buttons.get(r).setBackground(Color.green);
				start = System.currentTimeMillis();
				
				synchronized(panel) {
		    	    try {
		    	        panel.wait();
		    	    } catch (InterruptedException e) {}
		    	}
				System.out.println("here3");
				mouseClickTimes.add((int) (finish-start));
				
				System.out.println(mouseClickTimes + "\n" + enterPressTimes);
				
				// reset test
				buttons.get(r).setBackground(Color.white);
				buttons.get(r).removeActionListener(buttonListener);
				rPrev = r;
				Thread.sleep(1000);
				mousePhase = 0;
			}
			
			
			// reds test
			int numReds = ThreadLocalRandom.current().nextInt(2, 6);
			enterPhase = 2;
			for(int j = 0; j < numReds; j++) {
				r = ThreadLocalRandom.current().nextInt(0, buttons.size());
				buttons.get(r).setBackground(Color.red);
				long start = System.currentTimeMillis();
				int randTime = ThreadLocalRandom.current().nextInt(2, 5) * 1000; // * 1000 to convert s to ms
				Thread.sleep(randTime);
				if(j == 0)
					enterReleaseTimes.add((int) (keyFinish-start));
				
				buttons.get(r).setBackground(Color.white);
			}
			
			// initialize test
			enterPhase = 0;
			mousePhase = 0;
		}
		
		// Output
		JTextArea output = new JTextArea();
		panel.add(output);
		output.setVisible(true);
		output.append("mouse time in ms: " + mouseClickTimes + "\n" + "enter press times in ms: " + enterPressTimes + "\nenter release times: " + enterReleaseTimes);
	}
	
	// button listener
	private class ListenForButton implements ActionListener {
		@Override
		public void actionPerformed(ActionEvent e) {
			if(e.getSource() == buttons.get(r) && mousePhase == 0) {
				finish = System.currentTimeMillis();
				mousePhase = 1;
				
				synchronized(panel) {
					panel.notify();
				}
			}
		}
	}

	@Override
	public void keyPressed(KeyEvent e) {
		if (e.getKeyCode() == KeyEvent.VK_ENTER && enterPhase == 0){
			keyFinish = System.currentTimeMillis();
			System.out.println(keyFinish);
			enterPhase = 1;
			enterPressTimes.add((int) (keyFinish-start));
		}
	}
	
	/**
	 * Creates a button arraylist
	 * @param n integer amount of buttons
	 * @return button arraylist
	 */
	public static ArrayList<JButton> createButtons(int n) {
		ArrayList<JButton> buttons = new ArrayList<JButton>();
		for(int i = 0; i < n; i++) {
			buttons.add(new JButton("Button " + (i+1)));
		}
		return buttons;
	}
	
	/**
	 * adds an arraylist of buttons to a panel
	 * @param buttons the arraylist of buttons to be added
	 */
	public void addButtons(ArrayList<JButton> buttons) {
		for(JButton button: buttons) {
			panel.add(button);
			button.setFocusable(false); // stops buttons from stealing focus
		}
	}		
	
	@Override
	public void keyReleased(KeyEvent e) {
		if (e.getKeyCode() == KeyEvent.VK_ENTER && enterPhase == 2){
			keyFinish = System.currentTimeMillis();
			enterPhase = 1;
		}
	}
	
	@Override
	public void keyTyped(KeyEvent e) {}
}
