package oasis.graphics;

public enum PrimitiveType {
    POINT_LIST(1), 
    LINE_LIST(2), 
    LINE_STRIP(2), 
    TRIANGLE_LIST(3), 
    TRIANGLE_STRIP(3), 
    TRIANGLE_FAN(3); 
    
    private final int points; 
    
    private PrimitiveType(int points) { 
        this.points = points; 
    }
    
    public int getPointCount() { 
        return points; 
    }
}
