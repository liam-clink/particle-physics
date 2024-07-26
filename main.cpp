#include <GL/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>
#include <cstdio>
#include <iostream>

using std::cout;

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
    cout << "Renderer: " << renderer << "\n";
    cout << "OpenGL version supported " << version << "\n";

    // tell GL to only draw onto a pixel if the shape is closer to the viewer
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Actually drawing stuff now
    float points[] = {
        0.0, 0.5, 0.0,
        0.5, -0.5, 0.0,
        -0.5, -0.5, 0.0};

    // Copy this data into a vertex buffer object on the GPU
    GLuint vbo = 0;
    glGenBuffers(1, &vbo);              // generate ID for VBO
    glBindBuffer(GL_ARRAY_BUFFER, vbo); // binds buffer to GL_ARRAY_BUFFER target
    // Allocate memory for the buffer bound to the GL_ARRAY_BUFFER target
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points, GL_STATIC_DRAW);

    // Put the vertex buffer object into a vertex array object
    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    // Define the shaders (later load these from text file)
    const char *vertex_shader =
        "#version 400\n"
        "in vec3 vp;"
        "void main() {"
        "  gl_Position = vec4(vp, 1.0);" // The 1.0 at the end means to not calculate perspective
        "}";

    const char *fragment_shader =
        "#version 400\n"
        "out vec4 frag_colour;"
        "void main() {"
        "  frag_colour = vec4(0.5, 0.0, 0.5, 1.0);"
        "}";

    // Compile the shaders
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertex_shader, NULL);
    glCompileShader(vs);
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragment_shader, NULL);
    glCompileShader(fs);

    // Link the shaders together
    GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, fs);
    glAttachShader(shader_program, vs);
    glLinkProgram(shader_program);

    // Draw loop
    while (!glfwWindowShouldClose(window))
    {
        // wipe the drawing surface clear
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shader_program);
        glBindVertexArray(vao);
        // draw points 0-3 from the currently bound VAO with current in-use shader
        glDrawArrays(GL_TRIANGLES, 0, 3);
        // update other events like input handling
        glfwPollEvents();
        // put the stuff we've been drawing onto the display
        glfwSwapBuffers(window);
    }

    // close GL context
    glfwTerminate();
    return 0;
}