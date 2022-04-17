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
#include "Shader.hpp"

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
        
        Shader shader("/Users/zhaozhaoanan/Documents/OpenGL_Object/OpenGL/OpenGL/res/shaders/Basic.shader");
        shader.Bind();
        shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);
        
        va.unBind();
        vb.unBind();
        ib.unBind();
        shader.unBind();

        
        float r = 0.0f;
        float increment = 0.05f;
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            //glDrawArrays(GL_TRIANGLES, 0, 6);
            
            shader.Bind();
            shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);
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
    }
    glfwTerminate();
    return 0;
}
