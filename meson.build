project('nanograd', 'cpp')

cc = meson.get_compiler('cpp')
opencl = dependency('OpenCL')

src = ['src/main.cpp', 'src/tensor.cpp']
inc_dir = include_directories('src')

executable('main', src, cpp_args: '--std=c++17', include_directories: inc_dir,
dependencies: opencl)

