//
//  VertexBuffer.cpp
//  OpenGL
//
//  Created by 赵赵安安 on 2022/4/13.
//

#include "VertexBuffer.hpp"
#include "Renderer.hpp"

VertexBuffer::VertexBuffer(const void* data, unsigned int size) {
    GLCaLL(glGenBuffers(1, &m_RendererID));
    GLCaLL(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
    GLCaLL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

void VertexBuffer::Bind() const{
    GLCaLL(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void VertexBuffer::unBind() const{ 
    GLCaLL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

VertexBuffer::~VertexBuffer() { 
    GLCaLL(glDeleteBuffers(1, &m_RendererID));
}


