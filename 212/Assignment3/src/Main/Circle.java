package Main;

public class Circle implements Measurable{
	
	private double radius;

	public Circle(double radius) {
		this.radius = radius;
	}
	
	@Override
	public double getArea() {
		return 3.14 * (radius * radius);
	}
	
	protected double getRadius(){
		return radius;
	}

}
