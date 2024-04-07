#include <OpenGL/OpenGL.h>
#define GL_SILENCE_DEPRECATION
#include <iostream>
#include <GLFW/glfw3.h>
#include <glad/glad.h>
using namespace std;

struct WindowProperties{
    std::string title;
    uint32_t width, height;
};

int main(){

    const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

    if(!glfwInit()){
        printf("GLFWinit errored out!\n");
        return -2;
    }

    WindowProperties properties = {.title = "Simulator", .width = 900, .height = 480};

    GLFWwindow* window = glfwCreateWindow(properties.width, properties.height, properties.title.c_str(), nullptr, nullptr);

    if(!window){
        printf("Window was nullptr'ed!\n");
        return -2;
    }

    glfwMakeContextCurrent(window);

    int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    if(!status){
        printf("Failed to initialize Glad!\n");
        return -2;
    }

    //! @note Set the vsync to be enabled by default
    glfwSwapInterval(1);
    
    float vertices[] = {
        0.5f,  0.5f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f,  0.5f, 0.0f,  // top left 
        // second triangle
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left
    };


    uint32_t verticesBufferRendererID;
    glGenBuffers(GL_ARRAY_BUFFER, &verticesBufferRendererID);
    // glBindBuffer(GL_ARRAY_BUFFER, verticesBufferRendererID);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // float indices[] ={
    //     0, 1, 3, //! @note First Triangle
    //     1, 2, 3 //! @note Second Triangle
    // };

    // uint32_t indicesBufferRendererID;
    // glGenBuffers(GL_ELEMENT_ARRAY_BUFFER, &indicesBufferRendererID);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBufferRendererID);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // glDrawElements(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), GL_UNSIGNED_INT, 0);


    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    return 0;
}