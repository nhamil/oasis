package oasis.graphics.light;

import java.util.ArrayList;
import java.util.List;

public class LightList {

    private List<Light> lights = new ArrayList<>(); 
    
    public int getLightCount() {
        return lights.size(); 
    }
    
    public Light get(int index) {
        return lights.get(index); 
    }
    
    public void add(Light light) {
        lights.add(light); 
    }
    
    public void clear() {
        lights.clear(); 
    }
    
}
