package oasis.sample;

import oasis.core.Application;
import oasis.core.Config;
import oasis.core.GameLogger;
import oasis.core.Oasis;
import oasis.core.jogl.Jogl3Engine;
import oasis.graphics.ColorRgba;
import oasis.graphics.Shader;
import oasis.graphics.model.Material;
import oasis.graphics.model.Mesh;
import oasis.graphics.model.Model;
import oasis.graphics.model.ModelRenderer;
import oasis.graphics.model.PerspectiveCamera;
import oasis.graphics.model.RenderQueue;
import oasis.math.Mathf;
import oasis.math.Quaternionf;
import oasis.math.Vector3f;
import oasis.math.Vector4f;

public class SampleApp extends Application {

    private static final GameLogger log = new GameLogger(SampleApp.class);
    
    private PerspectiveCamera camera; 
    private ModelRenderer renderer; 
    
    private Shader shader;
    private Mesh heightmap, water; 
    
    private Model terrainModel; 
    
    private float angle = 0.0f; 
    
    private float freq = 1 / 6.0f; 
    private float pers = 0.45f; 
    private int octs = 10; 
    private long res = 512; 
    
    private float height = 3f; 
    
    private Heightmap htmap; 
    
    private String vSource = ""
    + "#version 120\n "
    + ""
    + "attribute vec3 aPosition; "
    + "attribute vec3 aNormal; "
    + "attribute vec4 aColor; "
    + "attribute vec2 aTexCoord0; "
    + ""
    + "uniform mat4 Model; "
    + "uniform mat3 NormalMat; "
    + "uniform mat4 View; "
    + "uniform mat4 Projection; "
    + ""
    + "varying vec4 vColor; "
    + "varying vec3 vNormal; "
    + "varying vec3 vModelPos; "
    + "" 
    + "void main() "
    + "{ "
    + "  vColor = aColor; "
    + "  vNormal = normalize(NormalMat * aNormal); "
    + "  gl_Position = Projection * View * Model * vec4(aPosition, 1.0); "
    + "  "
    + "  vec4 tmp = Model * vec4(aPosition, 1.0); "
    + "  vModelPos = tmp.xyz / tmp.w; "
    + "}";
    
    private String fSource = ""
    + "#version 120\n "
    + ""
    + "varying vec4 vColor; "
    + "varying vec3 vNormal; "
    + "varying vec3 vModelPos; "
    + ""
    + "uniform vec3 LightDirection = vec3(-1, -1, 0); "
    + "uniform vec3 ViewPos; "
    + "uniform float SpecularPower; "
    + "uniform vec4 SpecularColor; "
    + ""
    + "float Diffuse(vec3 normal, vec3 lightDir) "
    + "{"
    + "  normal = normalize(normal); "
    + "  lightDir = normalize(lightDir); "
    + "  "
    + "  float diffuse = clamp(dot(lightDir, normal), 0.0, 1.0); "
    + "  return diffuse; "
    + "}"
    + ""
    + "float Specular(vec3 normal, vec3 lightDir, vec3 camDir, float power) "
    + "{"
    + "  normal = normalize(normal); "
    + "  lightDir = normalize(lightDir); "
    + "  camDir = normalize(camDir); "
    + "  vec3 halfVec = normalize(camDir + lightDir); "
    + "  "
    + "  float specular = pow(abs(dot(-halfVec, normal)), power); "
    + "  return specular; "
    + "}"
    + ""
    + "void main() "
    + "{ "
    + "  vec3 camDir = normalize(vModelPos - ViewPos); "
    + "  vec3 normal = normalize(vNormal); "
    + "  vec3 lightDir = normalize(LightDirection); "
    + "  "
    + "  float diffuse = Diffuse(normal, lightDir); "
    + "  vec4 specular = SpecularColor * Specular(normal, lightDir, camDir, SpecularPower); "
    + "  "
    + "  gl_FragColor = vec4(vec3(0.2 + 0.8 * diffuse) + specular.rgb, 1.0) * vColor;\n "
    + "}";
    
    @Override
    public void onInit() {
        display.setResizable(true);
        display.setSize(800, 400);
        
        renderer = new ModelRenderer(graphics); 
        camera = new PerspectiveCamera(800, 600, 70.0f, 0.1f, 1000.0f); 
        
        shader = graphics.createShader(vSource, fSource);  
        
        float offset = 0.015f; 
        
        htmap = new Heightmap();
        htmap.setFlat(true);
        water = new Mesh(graphics); 
        htmap.genMeshData(new Vector3f(-10, height * 0.65f - offset, 10), new Vector3f(10, height * 0.65f + offset, -10), (int) res, (int) res, 5, freq * 10, 0.9f).apply(water);
        
        heightmap = new Mesh(graphics); 
        htmap.setFlat(false);
        htmap.genMeshData(new Vector3f(-10, 0, 10), new Vector3f(10, height, -10), (int) res, (int) res, octs, freq, pers).apply(heightmap);
        
        Material waterMaterial = new Material(); 
        waterMaterial.renderQueue = RenderQueue.TRANSLUCENT; 
        waterMaterial.specularPower = 100.0f; 
        waterMaterial.specularColor = new Vector4f(1); 
        waterMaterial.shader = shader; 
        
        Material heightmapMaterial = new Material(); 
        heightmapMaterial.renderQueue = RenderQueue.OPAQUE;
        heightmapMaterial.specularPower = 200.0f; 
        heightmapMaterial.specularColor = new Vector4f(0); 
        heightmapMaterial.shader = shader; 
        
        terrainModel = new Model(); 
        terrainModel.add(water, waterMaterial);
        terrainModel.add(heightmap, heightmapMaterial);
    }

    @Override
    public void onUpdate(float dt) {
        if (display.shouldClose()) {
            stop();
        }

        angle += 2f / 60.0f; 
    }

    @Override
    public void onRender() {
        graphics.clearScreen(new ColorRgba(0.9f, 0.9f, 0.9f, 1.0f));
        
        camera.setPosition(new Vector3f(-10, 6, 0));
        camera.setRotation(-Mathf.PI * 0.5f, -Mathf.toRadians(40));
        
        renderer.begin(camera);
        renderer.draw(terrainModel, new Vector3f(), Quaternionf.axisAngle(new Vector3f(0, 1, 0), angle * 0.1f));
        renderer.end(); 
    }
    
    @Override
    public void onExit() {
        
    }
    
    public static void main(String[] args) {
        log.info(Oasis.getEngineInfo());
        
        Config cfg = new Config();
        cfg.engine = Jogl3Engine.class;
        cfg.fps = 60.0f;
        cfg.ups = 60.0f;
        
        Application app = new SampleApp();
        app.start(cfg);
    }

}
