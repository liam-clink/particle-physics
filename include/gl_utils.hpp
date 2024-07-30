#include <GL/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>
#include <text_utils.hpp>

void print_gl_info();
GLuint load_shader(const std::filesystem::path& filepath, GLenum shader_type);