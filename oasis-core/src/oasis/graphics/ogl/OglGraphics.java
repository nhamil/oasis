package oasis.graphics.ogl;

import oasis.core.Oasis;
import oasis.core.OasisException;
import oasis.graphics.FrontFace;
import oasis.graphics.Geometry;
import oasis.graphics.GraphicsDevice;
import oasis.graphics.GraphicsState;
import oasis.graphics.IndexBuffer;
import oasis.graphics.Shader;
import oasis.graphics.Texture2D;
import oasis.graphics.VertexBuffer;
import oasis.math.Vector4;

public class OglGraphics implements GraphicsDevice {

    private Ogl ogl; 
    
    private int[] vao = new int[1]; 
    
    private OglShader curShader = null; 
    private GraphicsState curState = null; 
    
    public OglGraphics(Ogl ogl) {
        this.ogl = ogl; 
    }

    @Override
    public void preRender() {
        ogl.glClearColor(0.7f, 0.8f, 1.0f, 0.0f); 
        ogl.glClear(Ogl.GL_COLOR_BUFFER_BIT | Ogl.GL_DEPTH_BUFFER_BIT); 
        
        if (vao[0] == 0) {
            ogl.glGenVertexArrays(1, vao, 0); 
            ogl.glBindVertexArray(vao[0]); 
        }
        
        ogl.glEnable(Ogl.GL_BLEND);
        ogl.glBlendEquation(Ogl.GL_FUNC_ADD); 
        ogl.glDepthFunc(Ogl.GL_LEQUAL); 
        ogl.glCullFace(Ogl.GL_BACK); 
        
        ogl.glViewport(0, 0, Oasis.getDisplay().getWidth(), Oasis.getDisplay().getHeight());
    }

    @Override
    public void postRender() {
        // TODO Auto-generated method stub
        
    }


    @Override
    public void assignNativeResource(VertexBuffer vb) {
        vb.setNativeResource(new OglVertexBuffer(ogl, vb)); 
    }

    @Override
    public void assignNativeResource(IndexBuffer ib) {
        ib.setNativeResource(new OglIndexBuffer(ogl, ib)); 
    }

    @Override
    public void assignNativeResource(Geometry g) {
        g.setNativeResource(new OglGeometry(ogl, g)); 
    }

    @Override
    public void assignNativeResource(Shader s) {
        s.setNativeResource(new OglShader(ogl, s)); 
    }

    @Override
    public void assignNativeResource(Texture2D t) {
        t.setNativeResource(new OglTexture2D(ogl, t)); 
    }

    @Override
    public void setShader(Shader s) {
        if (s == null) {
            curShader = null; 
        }
        else {
            curShader = (OglShader) s.getNativeResource(); 
            curShader.update(); 
        }
    }
    
    @Override
    public void drawGeometry(Geometry g) {
        if (!g.isValid()) {
            throw new OasisException("Geometry is invalid: " + g); 
        }
        if (curShader == null) {
            throw new OasisException("No shader is set"); 
        }
        if (!curShader.isValid()) {
            throw new OasisException("Shader is not valid"); 
        }
        
        OglShader.bind(ogl, curShader); 
        curShader.update(); 
        
        OglGeometry geom = (OglGeometry) g.getNativeResource(); 
        geom.setBuffers(); 
        int prim = OglConvert.getPrimitive(g.getPrimitive()); 
        int size; 
        
        if (g.hasIndexBuffer()) {
            size = g.getIndexBuffer().getIndexCount(); 
            ogl.glDrawElements(prim, size, Ogl.GL_UNSIGNED_SHORT, 0);
        }
        else {
            size = g.getVertexBuffer(0).getVertexCount(); 
            ogl.glDrawArrays(prim, 0, size); 
        }
}

    @Override
    public void clearBuffers(Vector4 color, boolean depth) {
        ogl.glClearColor(color.x, color.y, color.z, color.w);
        
        int flags = Ogl.GL_COLOR_BUFFER_BIT; 
        
        if (depth) flags |= Ogl.GL_DEPTH_BUFFER_BIT; 
        
        ogl.glClear(flags); 
    }

    @Override
    public void setState(GraphicsState state) {
        if (curState == null || curState.getDestBlendMode() != state.getDestBlendMode() || curState.getSourceBlendMode() != state.getSourceBlendMode()) {
            int src = OglConvert.getBlendMode(state.getSourceBlendMode()); 
            int dst = OglConvert.getBlendMode(state.getDestBlendMode()); 
            ogl.glBlendFunc(src, dst); 
        }
        
        if (curState == null || curState.getFillMode() != state.getFillMode()) {
            ogl.glPolygonMode(Ogl.GL_FRONT_AND_BACK, OglConvert.getFillMode(state.getFillMode()));
        }
        
        if (curState == null || curState.getFrontFace() != state.getFrontFace()) {
            if (state.getFrontFace() == FrontFace.BOTH || state.getFrontFace() == null) {
                ogl.glDisable(Ogl.GL_CULL_FACE);
            }
            else {
                ogl.glEnable(Ogl.GL_CULL_FACE);
                ogl.glFrontFace(OglConvert.getFrontFace(state.getFrontFace())); 
            }
        }
        
        if (curState == null || curState.isDepthTestEnabled() != state.isDepthTestEnabled()) {
            if (state.isDepthTestEnabled()) {
                ogl.glEnable(Ogl.GL_DEPTH_TEST); 
            }
            else {
                ogl.glDisable(Ogl.GL_DEPTH_TEST); 
            }
        }
        
        if (curState == null || curState.isDepthWriteEnabled() != state.isDepthWriteEnabled()) {
            ogl.glDepthMask(state.isDepthTestEnabled()); 
        }
        
        curState = new GraphicsState(state); 
    }

}
