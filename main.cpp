#include <GL/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>
#include <cstdio>
#include <iostream>

int main()
{
    // start GL context and OS window using GLFW
    if (!glfwInit())
    {
        fprintf(stderr, "ERROR: could not start GLFW\n");
        return 1;
    }

    GLFWwindow *window = glfwCreateWindow(1920, 1080, "Hello Triangle", NULL, NULL);
    if (!window)
    {
        fprintf(stderr, "ERROR: could not oopen window with GLFW3\n");
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);

    // start GLEW
    glewExperimental = GL_TRUE;
    glewInit();

    // get version info
    const GLubyte *renderer = glGetString(GL_RENDERER); // get renderer string
    const GLubyte *version = glGetString(GL_VERSION);   // version as a string
    std::cout << "Renderer: " << renderer << "\n";
    std::cout << "OpenGL version supported " << version << "\n";

    // tell GL to only draw onto a pixel if the shape is closer to the viewer
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // close GL context
    glfwTerminate();
    return 0;
}