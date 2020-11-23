project('nanograd', 'cpp')

cc = meson.get_compiler('cpp')

cpp_args = ['-std=c++17', '-Wall', '-Wextra']

opencl = dependency('OpenCL')

nanograd_test = ['test/unit_tensor.cpp', 'nanograd/tensor.cpp', 'nanograd/ops.cpp']

nanograd_inc = include_directories('nanograd')

# subdir('utils')
subdir('nanograd')
subdir('examples')
subdir('test')


