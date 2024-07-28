#include <GL/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>
#include <text_utils.hpp>

GLuint load_shader(const std::filesystem::path& filepath, GLenum shader_type);