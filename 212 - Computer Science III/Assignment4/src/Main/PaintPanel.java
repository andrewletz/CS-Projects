package Main;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;
import java.util.ArrayList;

import javax.swing.JPanel;

@SuppressWarnings("serial")
public class PaintPanel extends JPanel implements MouseListener, MouseMotionListener{
	
	private ArrayList<Point> points = new ArrayList<Point>();
	private Point currentPoint;
	private int currentSize = 5;
	private Color currentColor = Color.BLACK;
	private boolean dragging = false;
	
	PaintPanel() {
		addMouseListener(this);
		addMouseMotionListener(this);
		
		setBackground(Color.WHITE);
	}
	
	public void paintComponent(Graphics g) {
		super.paintComponent(g);
		
		for (int i = points.size() - 1; i >= 0; i--)
			points.get(i).draw(g);
		
		if (currentPoint != null)
			currentPoint.draw(g);
	}
	
	@Override
	public void mousePressed(MouseEvent e) {
		currentPoint = new Point(e.getX(), e.getY(), currentColor, currentSize);
	}

	@Override
	public void mouseReleased(MouseEvent e) {
		if (!dragging) {
		points.add(currentPoint);
		}
		
		currentPoint = null;
		dragging = false;
		repaint();
	}
	
	@Override
	public void mouseDragged(MouseEvent e) {
		dragging = true;
		currentPoint = new Point(e.getX(), e.getY(), currentColor, currentSize);
		points.add(currentPoint);
		repaint();
		
	}
	
	public void setColor(Color color) {
		currentColor = color;
	}
	
	public void setSize(int size) {
		currentSize = size;
	}
	
	public void clear() {
		points.clear();
		repaint();
	}

	@Override
	public void mouseMoved(MouseEvent arg0) {}

	@Override
	public void mouseClicked(MouseEvent arg0) {}

	@Override
	public void mouseEntered(MouseEvent arg0) {}

	@Override
	public void mouseExited(MouseEvent arg0) {}

}
