project('nanograd', 'cpp')


cc = meson.get_compiler('cpp')
cpp_args = ['-std=c++17', '-Wall', '-Wextra']

base_dir = meson.current_source_dir()
add_global_arguments('-Dbase_dir="@0@"'.format(base_dir),
                     language: 'cpp')

opencl = dependency('OpenCL')

nanograd_test = ['test/unit_tensor.cpp', 'nanograd/tensor.cpp', 'nanograd/ops.cpp']

nanograd_inc = include_directories('nanograd')
utils_inc = include_directories('utils')

subdir('utils')
subdir('nanograd')
subdir('examples')
subdir('test')


