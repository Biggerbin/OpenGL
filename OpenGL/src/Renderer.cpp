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

