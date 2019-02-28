package Main;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;

public class Window implements ActionListener{
	
	private JFrame frame = new JFrame("Paint XXL-DELUXE");
	private JPanel panel = new JPanel(new BorderLayout());
	private PaintPanel paintPanel = new PaintPanel();
	private JButton color1 = new JButton("Red");
	private JButton color2 = new JButton("Green");
	private JButton color3 = new JButton("Blue");
	private JButton color4 = new JButton("Black");
	private JButton small = new JButton("Small");
	private JButton medium = new JButton("Medium");
	private JButton large = new JButton("Large");
	private JButton clear = new JButton("Clear");
	
	public Window() {
		prepareGUI();
	}

	public static void main(String[] args) {
		@SuppressWarnings("unused")
		Window window = new Window();
	}
	
	private void prepareGUI() {
		Dimension dim = Toolkit.getDefaultToolkit().getScreenSize();
		frame.setSize(800, 600);
		frame.setLocation(dim.width/2-frame.getSize().width/2, dim.height/2-frame.getSize().height/2);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		panel.add(paintPanel, BorderLayout.CENTER);
		initializeButtons();
		frame.add(panel);
		
		frame.setVisible(true);
	}
	
	private void initializeButtons() {
		color1.addActionListener(this);
		color2.addActionListener(this);
		color3.addActionListener(this);
		color4.addActionListener(this);
		small.addActionListener(this);
		medium.addActionListener(this);
		large.addActionListener(this);
		clear.addActionListener(this);
		
		JPanel colorSelect = new JPanel(new GridLayout(4,1));
		colorSelect.add(color1);
		colorSelect.add(color2);
		colorSelect.add(color3);
		colorSelect.add(color4);
		panel.add(colorSelect, BorderLayout.WEST);
		
		JPanel sizeSelect = new JPanel(new GridLayout(4,1));
		sizeSelect.add(small);
		sizeSelect.add(medium);
		sizeSelect.add(large);
		sizeSelect.add(clear);
		panel.add(sizeSelect, BorderLayout.EAST);
	}
	
    public void actionPerformed(ActionEvent e)
    {
        JButton source = (JButton)e.getSource();
		switch (source.getText()) {
			case ("Red"):
				paintPanel.setColor(Color.RED);
				break;
			case ("Green"):
				paintPanel.setColor(Color.GREEN);
				break;
			case ("Blue"):
				paintPanel.setColor(Color.BLUE);
			    break;
			case ("Black"):
				paintPanel.setColor(Color.BLACK);
				break;
			case ("Small"):
				paintPanel.setSize(5);
				break;
			case ("Medium"):
				paintPanel.setSize(7);
				break;
			case ("Large"):
				paintPanel.setSize(9);
				break;
			case ("Clear"):
				paintPanel.clear();
				break;
		}
    }
	
}
