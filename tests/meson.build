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

test_lib_obj = []
foreach l : libs
    test_lib_obj += [l.extract_all_objects()]
endforeach

test_lib = static_library('test_lib', test_lib_src, 
    objects : test_lib_obj,
    include_directories : test_inc,
    c_args : c_args)

subdir('mpn')
subdir('fft')
subdir('mpz')
subdir('mpq')
subdir('mpf')
subdir('rand')
subdir('misc')
subdir('cxx')

test_src = mpn_test_src + fft_test_src + mpz_test_src + mpq_test_src + mpf_test_src + rand_test_src + cxx_test_src + misc_test_src + [ 
    't-bswap.c',
    't-constants.c',
    't-count_zeros.c',
    't-gmpmax.c',
    't-hightomask.c',
    't-modlinv.c',
    't-parity.c',
    't-popc.c',
    't-sub.c'
]

foreach src : test_src
    name = fs.stem(src)
    suite = fs.parent(src)
    exe_name = fs.replace_suffix(src, '').underscorify()
    
    exe = executable(exe_name, 
        [src], 
        include_directories : test_inc,
        link_with : test_lib,
        c_args : c_args, 
        cpp_args : c_args)
        
    test(name, exe, suite : suite, timeout : 90)
endforeach


