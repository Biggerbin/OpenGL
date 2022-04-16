//
//  IndexBuffer.cpp
//  OpenGL
//
//  Created by 赵赵安安 on 2022/4/13.
//

#include "IndexBuffer.hpp"
#include "Renderer.hpp"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count): m_Count(count) {
    
    assert(sizeof(unsigned int) == sizeof(GLuint));
    
    GLCaLL(glGenBuffers(1, &m_RendererID));
    GLCaLL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
    GLCaLL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int ), data, GL_STATIC_DRAW));
}

void IndexBuffer::Bind() const{
    GLCaLL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}

void IndexBuffer::unBind() const{
    GLCaLL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

IndexBuffer::~IndexBuffer() { 
    GLCaLL(glDeleteBuffers(1, &m_RendererID));
}
