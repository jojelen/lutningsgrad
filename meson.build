project('lutningsgrad', 'cpp')


cc = meson.get_compiler('cpp')
cpp_args = ['-std=c++17', '-Wall', '-Wextra']

base_dir = meson.current_source_dir()
add_global_arguments('-DBASE_DIR="@0@"'.format(base_dir),
                     language: 'cpp')

opencl = dependency('OpenCL')

lutningsgrad = ['test/unit_tensor.cpp',
                'lutningsgrad/tensor.cpp',
                'lutningsgrad/ops.cpp']

lutningsgrad = include_directories('lutningsgrad')
utils_inc = include_directories('utils')

subdir('utils')
subdir('lutningsgrad')
subdir('examples')
subdir('test')


