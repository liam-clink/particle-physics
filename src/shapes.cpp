#include <shapes.hpp>

GLuint triangle(const std::array<float, 9>& points, const std::array<float, 9>& colors)
{

    // Copy this data into a vertex buffer object on the GPU
    GLuint positions_vbo = 0;
    glGenBuffers(1, &positions_vbo); // generate ID for VBO
    glBindBuffer(GL_ARRAY_BUFFER,
                 positions_vbo); // binds buffer to GL_ARRAY_BUFFER target
    // Allocate memory for the buffer bound to the GL_ARRAY_BUFFER target
    glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(float), points.data(), GL_STREAM_DRAW);

    GLuint colors_vbo = 0;
    glGenBuffers(1, &colors_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
    glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(float), colors.data(), GL_STATIC_DRAW);

    // Put the vertex buffer object into a vertex array object
    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, positions_vbo);
    // GLuint layout index, GLint size, GLenum type, GLboolean normalize, GLsizei stride, const void * pointer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    // The vertex attribute arrays are disabled by default
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    // Unbind VAO and VBOs
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return vao;
}
