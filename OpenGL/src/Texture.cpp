//
//  Texture.cpp
//  OpenGL
//
//  Created by 赵赵安安 on 2022/4/20.
//

#include "Texture.hpp"
#include "vendor/stb_image/stb_image.h"

Texture::Texture(const std::string& path)
    : m_RendererID(0), m_FilePath(path), m_localBuffer(nullptr), m_Width(0), m_Height(0), m_BPP(0)
{
    stbi_set_flip_vertically_on_load(1);
    m_localBuffer = stbi_load(m_FilePath.c_str(), &m_Width, &m_Height, &m_BPP, 4);
    
    GLCaLL(glGenTextures(1, &m_RendererID));
    GLCaLL(glBindTexture(GL_TEXTURE_2D, m_RendererID));
    
    GLCaLL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCaLL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCaLL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCaLL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
    
    GLCaLL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_localBuffer));
    
    GLCaLL(glBindTexture(GL_TEXTURE_2D, 0));
    
    if(m_localBuffer){
        stbi_image_free(m_localBuffer);
    }
}

Texture::~Texture(){
    GLCaLL(glDeleteTextures(1, &m_RendererID));
}

void Texture::Bind(unsigned int slot) const{
    GLCaLL(glActiveTexture(GL_TEXTURE0 + slot));
    GLCaLL(glBindTexture(GL_TEXTURE_2D, m_RendererID));
};

void Texture::unBind() const{
    GLCaLL(glBindTexture(GL_TEXTURE_2D, 0));
};

