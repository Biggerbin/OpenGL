//
//  Shader.cpp
//  OpenGL
//
//  Created by 赵赵安安 on 2022/4/18.
//
#include <fstream>
#include <sstream>
#include "Shader.hpp"
#include "Renderer.hpp"



Shader::Shader(const std::string &filename) : m_FilePath(filename), m_RendererID(0) {
    
    ShaderProgramSource source = ParseShader(filename);
    m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
    //CompileShader();
}

Shader::~Shader(){
    GLCaLL(glDeleteProgram(m_RendererID));
}

ShaderProgramSource Shader::ParseShader(const std::string &filename){
    std::ifstream stream(m_FilePath);
    
    enum class ShaderType{
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };
    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while(getline(stream, line)){
        if(line.find("#shader") != std::string::npos){
            if(line.find("vertex") != std::string::npos){
                //set mode to vertex
                type = ShaderType::VERTEX;
            }else if(line.find("fragment") != std::string::npos){
                //set mode to fragment
                type = ShaderType::FRAGMENT;
            }
        }else{
            ss[(int)type] << line << "\n";
        }
    }
    return {ss[0].str(), ss[1].str()};
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source){
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, NULL);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if(result == GL_FALSE){
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Compile ERROR" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }
    return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader){
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);

    glLinkProgram(program);

    //glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

void Shader::Bind() const { 
    GLCaLL(glUseProgram(m_RendererID));
}

void Shader::unBind() const { 
    GLCaLL(glUseProgram(0));;
}

void Shader::SetUniform4f(const std::string &name, float v0, float v1, float v2, float v3) {
    
    GLCaLL(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

unsigned int Shader::GetUniformLocation(const std::string& name) {
    if(m_UniformLocationCache.find(name) != m_UniformLocationCache.end()){
        return m_UniformLocationCache[name];
    }
    GLCaLL(unsigned int location = glGetUniformLocation(m_RendererID, name.c_str()));
    if(location == -1){
        std::cout << "Warning: uniform " << name << "doesn't exits!" << std::endl;
    }
    m_UniformLocationCache[name] = location;
    return location;
}




