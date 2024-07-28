#include <gl_utils.hpp>

GLuint load_shader(const std::filesystem::path& filepath, GLenum shader_type)
{
    auto shader_source = load_text_file(filepath);
    if (!shader_source)
        throw std::runtime_error("Failed to read GLSL source file.");

    GLuint shader_id = glCreateShader(shader_type);
    if (!shader_id)
        throw std::runtime_error("Failed to generate shader ID.");

    // This is two lines because
    const char* source = shader_source->c_str();
    std::cout << "Shader source: \n";
    std::cout << source;
    glShaderSource(shader_id, 1, &source, NULL);

    glCompileShader(shader_id);
    return shader_id;
}