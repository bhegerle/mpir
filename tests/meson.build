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
subdir('fft')
subdir('mpz')
subdir('mpq')
subdir('mpf')
subdir('rand')
subdir('misc')

test_src = mpn_test_src + fft_test_src + mpz_test_src + mpq_test_src + mpf_test_src + rand_test_src + misc_test_src + [ 
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
    
    exe = executable(exe_name, src, 
        include_directories : test_inc,
        link_with : [mpir_lib, test_lib])
        
    test(name, exe, suite : suite)
endforeach


