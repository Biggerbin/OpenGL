//
//  VertexBuffer.hpp
//  OpenGL
//
//  Created by 赵赵安安 on 2022/4/13.
//

#pragma once


class VertexBuffer{
private:
    unsigned int m_RendererID;
public:
    VertexBuffer(const void* data, unsigned int size);
    ~VertexBuffer();
    
    void Bind() const;
    void unBind() const;
};
