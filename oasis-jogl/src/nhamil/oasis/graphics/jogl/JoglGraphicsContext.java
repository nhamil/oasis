package nhamil.oasis.graphics.jogl;

import com.jogamp.opengl.GL;

import nhamil.oasis.core.GameLogger;
import nhamil.oasis.graphics.ColorRgba;
import nhamil.oasis.graphics.FrameBuffer;
import nhamil.oasis.graphics.GraphicsContext;
import nhamil.oasis.graphics.Mesh;
import nhamil.oasis.graphics.Renderer;
import nhamil.oasis.graphics.ShaderProgram;
import nhamil.oasis.graphics.Texture;
import nhamil.oasis.graphics.VertexDefinition;

public class JoglGraphicsContext implements GraphicsContext {

    private static final GameLogger log = new GameLogger(JoglGraphicsContext.class);
    
    private JoglDisplay display;
    private JoglGlWrapper gl;
    
    private JoglShaderProgram defaultShader;
    
    public JoglGraphicsContext(JoglDisplay display, JoglGlWrapper gl) {
        this.display = display;
        this.gl = gl;
        gl.setContext(this);
    }
    
    public JoglShaderProgram getDefaultShader() {
        return defaultShader;
    }
    
    public void init() {
        
    }
    
    public void newFrame() {
        
    }
    
    @Override
    public int getWidth() {
        return display.getWidth();
    }

    @Override
    public int getHeight() {
        return display.getHeight();
    }

    @Override
    public void setScreenClearColor(ColorRgba color) {
        gl.clearColor(color.getRed(), color.getGreen(), color.getBlue(), color.getAlpha());
    }

    @Override
    public void clearScreen() {
        gl.clear(GL.GL_COLOR_BUFFER_BIT | GL.GL_DEPTH_BUFFER_BIT | GL.GL_STENCIL_BUFFER_BIT);
    }

    @Override
    public FrameBuffer createFrameBuffer(int width, int height) {
        JoglFrameBuffer2 fb = new JoglFrameBuffer2(width, height, gl);
        return fb;
    }

    @Override
    public ShaderProgram createShaderProgram(String vSource, String fSource) {
        return new JoglShaderProgram(vSource, fSource, gl);
    }

    @Override
    public Texture createTexture(int width, int height) {
        return new JoglTexture(width, height, gl);
    }

    @Override
    public Mesh createMesh(VertexDefinition def) {
        // TODO FINISH
        return null;
    }

    @Override
    public Renderer createRenderer() {
        // TODO FINISH
        return null;
    }

}
