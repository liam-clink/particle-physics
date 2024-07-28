#include <text_utils.hpp>

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
    if (file.read(buffer.data(), size))
        std::cerr << "Failed to read the file: " << filepath << std::endl;

    file.close();
    return buffer;
}
