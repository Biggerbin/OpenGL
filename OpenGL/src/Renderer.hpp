//
//  Renderer.hpp
//  OpenGL
//
//  Created by 赵赵安安 on 2022/4/13.
//

#ifndef Renderer_hpp
#define Renderer_hpp

#include <GL/glew.h>
#include <iostream>

#define ASSERT(x) if(!(x)) asm int 3;
#define GLCaLL(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, const int line);





#endif /* Renderer_hpp */
