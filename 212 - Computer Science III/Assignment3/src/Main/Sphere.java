package Main;

public class Sphere extends Circle{

	public Sphere(double radius) {
		super(radius);
	}
	
	@Override
	public double getArea() {
		return 4*3.14*(getRadius() * getRadius());
	}

	
}
