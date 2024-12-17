#include <array>
#include <gl_utils.hpp>

struct triangle
{
    triangle(const std::array<float, 9>& points, const std::array<float, 9>& colors);
    ~triangle();
    void update_points(const std::array<float, 9>& points);
    void update_colors(const std::array<float, 9>& points);

    GLuint vao = 0;
    GLuint position_vbo = 0;
    GLuint color_vbo = 0;
};
