//
//  VertexArray.cpp
//  OpenGL
//
//  Created by 赵赵安安 on 2022/4/17.
//

#include "VertexArray.hpp"
#include "Renderer.hpp"
#include "VertexBufferLayout.hpp"

void VertexArray::AddBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout) {
    Bind();
    const auto& elements = layout.GetElements();
    unsigned int offset = 0;
    for(unsigned int i = 0; i < elements.size(); ++i){
        const auto& element = elements[i];
        GLCaLL(glEnableVertexAttribArray(i));
        GLCaLL(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void *)offset));
        offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
    }
}

VertexArray::VertexArray() { 
    GLCaLL(glGenVertexArrays(1, &m_RendererID));
}

VertexArray::~VertexArray() { 
    GLCaLL(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::Bind() const {
    GLCaLL(glBindVertexArray(m_RendererID));
}

void VertexArray::unBind() const {
    GLCaLL(glBindVertexArray(0));
}


