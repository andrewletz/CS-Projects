package Main;

public class Box extends Rectangle {

	private double depth;
	
	public Box(double width, double height, double depth) {
		super(width, height);
		this.depth = depth;
	}
	
	@Override
	public double getArea() {
		return 2*(getHeight() * getWidth()) + 2*(getHeight() * depth) + 2*(getWidth() * depth);
	}
	

}
