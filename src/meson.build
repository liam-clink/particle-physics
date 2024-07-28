src_files = ['main.cpp', 'gl_utils.cpp', 'text_utils.cpp']

executable('hello_triangle',
'main.cpp',
install: true,
include_directories: inc,
sources: src_files,
dependencies: [
    dependency('glew'),
    dependency('glfw3'),
    dependency('GL')],
)
