//
//  Renderer.hpp
//  OpenGL
//
//  Created by 赵赵安安 on 2022/4/13.
//

#pragma once

#include <GL/glew.h>
#include <iostream>
#include "Shader.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"

#define ASSERT(x) if(!(x)) asm int 3;
#define GLCaLL(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, const int line);

class Renderer{
public:
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
    void Clear() const;
};

