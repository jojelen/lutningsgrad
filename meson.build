project('nanograd', 'cpp')

cc = meson.get_compiler('cpp')
opencl = dependency('OpenCL')

nanograd = ['nanograd/main.cpp', 'nanograd/tensor.cpp', 'nanograd/ops.cpp']
nanograd_test = ['test/unit_tensor.cpp', 'nanograd/tensor.cpp', 'nanograd/ops.cpp']

inc_dir = include_directories('nanograd')

executable('main', nanograd, cpp_args: '--std=c++17', include_directories: inc_dir,
dependencies: opencl)

e = executable('unit', nanograd_test, cpp_args: '--std=c++17', include_directories: inc_dir,
dependencies: opencl)
test('Tensor unit tests', e)

