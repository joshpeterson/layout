project('layout', 'cpp')
add_global_arguments('-std=c++14', language : 'cpp')

includes = include_directories('/usr/lib/llvm-3.8/include')
linker_args = ['-L/usr/lib/llvm-3.8/lib', '-lclang']

sources = ['src/translation_unit.cpp']
#executable('layout', sources: ['hello-cpp-world.cc', sources],
#            include_directories: includes, link_args: linker_args)

test_sources = ['test/main.cpp',
                'test/libclang_test_double.cpp',
                'test/test_translation_unit.cpp']
executable('layout_test', sources: [sources, test_sources],
            include_directories: includes, link_args: linker_args)
