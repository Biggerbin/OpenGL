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
#include "VertexBufferLayout.hpp"
#include "Texture.hpp"
#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"

#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_glfw.h"
#include "vendor/imgui/imgui_impl_opengl3.h"

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
             -0.5f, -0.5f, 0.0f, 0.0f,
              0.5f, -0.5f, 1.0f, 0.0f,
              0.5f,  0.5f, 1.0f, 1.0f,
             -0.5f,  0.5f, 0.0f, 1.0f
        };
        
        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
        };
        
        GLCaLL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        GLCaLL(glEnable(GL_BLEND));
        
        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        VertexArray va;
        VertexBuffer vb(positions, 4 * 4 * sizeof(float));
        va.AddBuffer(vb, layout);
        IndexBuffer ib(indices, 6);
        
        glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);
        
        Shader shader("/Users/zhaozhaoanan/Documents/OpenGL_Object/OpenGL/OpenGL/res/shaders/Basic.shader");
        shader.Bind();
        //shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);
        Texture texture("/Users/zhaozhaoanan/Desktop/img.jpg");
        texture.Bind();
        shader.SetUniform1i("u_Texture", 0);
        
        
        va.unBind();
        vb.unBind();
        ib.unBind();
        shader.unBind();

        Renderer renderer;
        float r = 0.0f;
        float increment = 0.05f;
        
        glm::vec3 translation(0,0,0);
        
        ImGui::CreateContext();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init();
        ImGui::StyleColorsDark();

        
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            renderer.Clear();
            
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
            
            glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);
            glm::mat4 view = glm::translate(glm::mat4(1.0f), translation);
            glm::mat4 mvp = proj * view * model;
            
            shader.Bind();
            //shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);
            renderer.Draw(va, ib, shader);
            
            shader.SetUniformMat4f("u_MVP", mvp);
            if(r > 1.0f){
                increment = -0.05f;
            }
            else if(r < 0.0f){
                increment = 0.05f;
            }
            
            r += increment;
            
            {
                ImGui::SliderFloat3("translation", &translation.x, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            }
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            /* Swap front and back buffers */
            glfwSwapBuffers(window);
            /* Poll for and process events */
            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}
