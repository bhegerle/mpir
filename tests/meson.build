test_lib_src = [
    'memory.c',
    'misc.c',
    'refmpf.c',
    'refmpn.c',
    'refmpq.c',
    'refmpz.c',
    'spinner.c',
    'trace.c'
]

test_lib = library('test_lib_src', test_lib_src, 
    include_directories : test_inc,
    c_args : '-D__GMP_WITHIN_GMP=1')

subdir('mpn')

test_src = [
    #'t-bswap.c'
]

foreach src : test_src
    name = fs.stem(src)
    exe = executable(name, src, 
        include_directories : test_inc,
        link_with : mpir_lib)
    test(name, exe)
endforeach


