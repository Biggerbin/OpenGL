//
//  Texture.hpp
//  OpenGL
//
//  Created by 赵赵安安 on 2022/4/20.
//

#pragma once

#include "Renderer.hpp"

class Texture{
private:
    unsigned int m_RendererID;
    std::string m_FilePath;
    unsigned char* m_localBuffer;
    int m_Width, m_Height, m_BPP;
public:
    Texture(const std::string& path);
    ~Texture();
    
    void Bind(unsigned int slot = 0) const;
    void unBind() const;
    
    inline int GetWight() const { return m_Width; }
    inline int GetHeigt() const { return m_Height; }
};
