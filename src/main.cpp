#include <gl_utils.hpp>
#include <iostream>
#include <shapes.hpp>

using std::cout;

int main()
{
    // start GL context and OS window using GLFW
    if (!glfwInit())
    {
        throw std::runtime_error("ERROR: could not start GLFW\n");
        return 1;
    }

    // Disable window resizing
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    GLFWwindow* window = glfwCreateWindow(1920, 1080, "Hello Triangle", NULL, NULL);
    if (!window)
    {
        throw std::runtime_error("ERROR: could not open window with GLFW3\n");
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);

    // start GLEW
    glewExperimental = GL_TRUE;
    glewInit();

    // get version info
    print_gl_info();

    // tell GL to only draw onto a pixel if the shape is closer to the viewer
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Actually drawing stuff now
    std::array points = {0.0f, 0.5f, 0.0f, 0.5f, -0.5f, 0.0f, -0.5f, -0.5f, 0.0f};
    std::array colors = {1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f};

    auto vao = triangle(points, colors);

    // Compile the shaders
    GLuint vs = load_shader("../share/Particle Physics/test_vertex_shader.glsl", GL_VERTEX_SHADER);
    GLuint fs = load_shader("../share/Particle Physics/test_fragment_shader.glsl", GL_FRAGMENT_SHADER);

    // Link the shaders together
    GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, vs);
    glAttachShader(shader_program, fs);
    glLinkProgram(shader_program);

    glfwSwapInterval(1); // Enable vsync

    // Cull faces with CCW winding order
    glEnable(GL_CULL_FACE); // cull face
    glCullFace(GL_BACK);    // cull back face
    glFrontFace(GL_CW);     // GL_CCW for counter clock-wise

    // Draw loop
    while (!glfwWindowShouldClose(window))
    {
        // wipe the drawing surface clear
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shader_program);
        glBindVertexArray(vao);
        // draw points 0-3 from the currently bound VAO with current in-use
        // shader
        glDrawArrays(GL_TRIANGLES, 0, 3);
        // update other events like input handling
        glfwPollEvents();
        // put the stuff we've been drawing onto the display
        glfwSwapBuffers(window);

        // Update Triangle
        // glBindBuffer(GL_ARRAY_BUFFER, positions_vbo);
        // points[6] += 0.01;
        // if (points[6] >= 1.)
        //     points[6] -= 2.;
        // glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points);
    }

    // close GL context
    glfwTerminate();
    return 0;
}