//
//  Application.cpp
//  OpenGL
//
//  Created by 赵赵安安 on 2022/4/6.
//
#include <string>
#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>
#include "Renderer.hpp"
#include "IndexBuffer.hpp"
#include "VertexBuffer.hpp"
#include "VertexArray.hpp"

struct ShaderProgramSource{
    std::string VertexSource;
    std::string FragmentSource;
};

static ShaderProgramSource ParseShader(const std::string& filepath){
    std::ifstream stream(filepath);
    
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


static unsigned int CompileShader(unsigned int type, const std::string& source){
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

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader){
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

int main(void)
{
    /* Initialize the library */
    if (!glfwInit())
        return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    /* Create a windowed mode window and its OpenGL context */

    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK){
        std::cout << "ERROR" << std::endl;
        return -1;
    }
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    {
        float positions[] = {
             -0.5f, -0.5f,
              0.5f, -0.5f,
              0.5f,  0.5f,
             -0.5f,  0.5f
            
            
        };
        
        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
        };
        
        VertexBufferLayout layout;
        layout.Push<float>(2);
        VertexArray va;
        VertexBuffer vb(positions, 4 * 2 * sizeof(float));
        va.AddBuffer(vb, layout);
        IndexBuffer ib(indices, 6);
        
        ShaderProgramSource source = ParseShader("/Users/zhaozhaoanan/Documents/OpenGL_Object/OpenGL/OpenGL/res/shaders/Basic.shader");
        unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
        glUseProgram(shader);
        
        va.unBind();
        vb.unBind();
        ib.unBind();
        GLCaLL(glUseProgram(0));
        
        
        int location = glGetUniformLocation(shader, "u_Color");
        
        float r = 0.0f;
        float increment = 0.05f;
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            //glDrawArrays(GL_TRIANGLES, 0, 6);
            glUniform4f(location, r, 0.5f, 0.1f, 1.0f);
            
            GLCaLL(glUseProgram(shader));
            va.Bind();
            ib.Bind();
            
            GLCaLL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL));
            
            if(r > 1.0f){
                increment = -0.05f;
            }
            else if(r < 0.0f){
                increment = 0.05f;
            }
            
            r += increment;

            /* Swap front and back buffers */
            glfwSwapBuffers(window);
            /* Poll for and process events */
            glfwPollEvents();
        }

        glDeleteProgram(shader);
    }
    glfwTerminate();
    return 0;
}
