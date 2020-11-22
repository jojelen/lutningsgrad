project('nanograd', 'cpp')

cc = meson.get_compiler('cpp')
opencl = dependency('OpenCL')

src = ['src/main.cpp', 'src/tensor.cpp', 'src/ops.cpp']
src_test = ['test/unit_tensor.cpp', 'src/tensor.cpp', 'src/ops.cpp']

inc_dir = include_directories('src')

executable('main', src, cpp_args: '--std=c++17', include_directories: inc_dir,
dependencies: opencl)

e = executable('unit', src_test, cpp_args: '--std=c++17', include_directories: inc_dir,
dependencies: opencl)
test('Tensor unit tests', e)

