//
//  VertexArray.hpp
//  OpenGL
//
//  Created by 赵赵安安 on 2022/4/17.
//

#pragma once

#include "VertexBuffer.hpp"

class VertexBufferLayout;

class VertexArray{
private:
    unsigned int m_RendererID;
public:
    VertexArray();
    ~VertexArray();
    
    void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
    void Bind() const;
    void unBind() const;
};
