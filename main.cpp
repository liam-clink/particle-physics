#include <GL/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>

using std::cout;

std::optional<std::string> load_text_file(const std::filesystem::path& filepath)
{
    std::ifstream file(filepath, std::ios::in);
    if (!file.is_open())
    {
        std::cerr << "Failed to open file: " << filepath << std::endl;
        return std::nullopt;
    }

    auto size = std::filesystem::file_size(filepath);

    std::string buffer(size, '\0');
    if (!file.read(buffer.data(), size))
        std::cerr << "Failed to read the file: " << filepath << std::endl;

    file.close();
    return buffer;
}

GLuint load_shader(const std::filesystem::path& filepath, GLenum shader_type)
{
    auto shader_source = load_text_file(filepath);
    if (shader_source)
        throw std::runtime_error("Failed to read GLSL source file.");

    GLuint shader_id = glCreateShader(shader_type);
    if (shader_id == 0)
        throw std::runtime_error("Failed to generate shader ID.");

    // This is two lines because
    const char* source = shader_source->c_str();
    glShaderSource(shader_id, 1, &source, NULL);

    glCompileShader(shader_id);
    return shader_id;
}

int main()
{
    // start GL context and OS window using GLFW
    if (!glfwInit())
    {
        throw std::runtime_error("ERROR: could not start GLFW\n");
        return 1;
    }

    GLFWwindow* window = glfwCreateWindow(1920, 1080, "Hello Triangle", NULL, NULL);
    if (!window)
    {
        throw std::runtime_error("ERROR: could not oopen window with GLFW3\n");
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);

    // start GLEW
    glewExperimental = GL_TRUE;
    glewInit();

    // get version info
    const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
    const GLubyte* version = glGetString(GL_VERSION);   // version as a string
    cout << "Renderer: " << renderer << "\n";
    cout << "OpenGL version supported " << version << "\n";

    // tell GL to only draw onto a pixel if the shape is closer to the viewer
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Actually drawing stuff now
    float points[] = {0.0, 0.5, 0.0, 0.5, -0.5, 0.0, -0.5, -0.5, 0.0};

    // Copy this data into a vertex buffer object on the GPU
    GLuint vbo = 0;
    glGenBuffers(1, &vbo); // generate ID for VBO
    glBindBuffer(GL_ARRAY_BUFFER,
                 vbo); // binds buffer to GL_ARRAY_BUFFER target
    // Allocate memory for the buffer bound to the GL_ARRAY_BUFFER target
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points, GL_STATIC_DRAW);

    // Put the vertex buffer object into a vertex array object
    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    // Compile the shaders
    GLuint vs = load_shader("../test_vertex_shader.glsl", GL_VERTEX_SHADER);
    GLuint fs = load_shader("../test_fragment_shader.glsl", GL_FRAGMENT_SHADER);

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
        // draw points 0-3 from the currently bound VAO with current in-use
        // shader
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