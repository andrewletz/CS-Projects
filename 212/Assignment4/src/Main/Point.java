package Main;

import java.awt.Color;
import java.awt.Graphics;

public class Point {

	private int x;
	private int y;
	private Color color;
	private int size;
	
	public Point(int x, int y, Color color, int size) {
		this.x = x;
		this.y = y;
		this.color = color;
		this.size = size;
	}
	
	public int getX() {
		return this.x;
	}
	
	public int getY() {
		return this.y;
	}
	
	public Color getColor() {
		return this.color;
	}
	
	public int getSize() {
		return this.size;
	}
	
    public void draw(Graphics g) {
        g.setColor(color);
        g.fillOval(x, y, size, size);
    }
    
}
