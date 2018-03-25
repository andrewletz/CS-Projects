package Main;

public class Rectangle implements Measurable {
	
	private double width;
	private double height;

	public Rectangle(double width, double height) {
		this.width = width;
		this.height = height;
		
	}
	
	@Override
	public double getArea() {
		return width * height;
	}
	
	protected double getWidth() {
		return width;
	}
	
	protected double getHeight() {
		return height;
	}

}
