tensor = executable('unit', 'unit_tensor.cpp',
                    cpp_args: cpp_args,
                    include_directories: nanograd_inc,
                    link_with: nanograd_lib)

test('Tensor unit tests', tensor)
