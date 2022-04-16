//
//  IndexBuffer.hpp
//  OpenGL
//
//  Created by 赵赵安安 on 2022/4/13.
//

#pragma once


class IndexBuffer{
private:
    unsigned int m_RendererID;
    unsigned int m_Count;
public:
    IndexBuffer(const unsigned int* data, unsigned int count);
    ~IndexBuffer();
    
    void Bind() const;
    void unBind() const;
    
    inline unsigned int GetCount() const {return m_Count;}
};