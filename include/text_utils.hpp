#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>

std::optional<std::string> load_text_file(const std::filesystem::path& filepath);
