//
//  Renderer.cpp
//  OpenGL
//
//  Created by 赵赵安安 on 2022/4/13.
//

#include "Renderer.hpp"

void GLClearError(){
    while(glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, const int line){
    while(GLenum error = glGetError()){
        std::cout << "[OpenGL Error] (" << error << ")" << function << " " << file << " " << line << std::endl;
        return false;
    }
    return true;
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const {
    
    
    shader.Bind();
    va.Bind();
    ib.Bind();
    //glDrawArrays(GL_TRIANGLES, 0, 6);
    GLCaLL(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, NULL));
}

void Renderer::Clear() const { 
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);;
}

