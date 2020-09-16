project('mpir', 'c', version : '1.11')

yasm = find_program(get_option('with-yasm'))

c = meson.get_compiler('c')

mpir_src = []

# feature tests
gmp_cv_func_alloca = (
    c.has_function('__builtin_alloca')
    or c.compiles('''
        #include <malloc.h>
        void f(size_t n) { _alloca(n); }''', name : '_alloca')
    or c.has_function('alloca', prefix : '#include <alloca.h>')
)

# select allocator
alloca = get_option('enable-alloca')
if alloca == 'yes'
    alloca = 'alloca'
elif alloca == 'no'
    alloca = 'malloc-reentrant'
elif alloca == 'reentrant'
    alloca = gmp_cv_func_alloca ? 'alloca' : 'malloc-reentrant'
elif alloca == 'notreentrant'
    alloca = gmp_cv_func_alloca ? 'alloca' : 'malloc-notreentrant'
endif

# get os / cpu / arch
os = host_machine.system()
cpu = host_machine.cpu_family()
arch = get_option('host-arch')

nix = (
    os == 'darwin' or 
    os == 'linux' or 
    os.endswith('bsd') or 
    os == 'gnu' or
    os == 'sunos'
)

windows =  os == 'windows'

# configure
conf_data = configuration_data()

conf_data.set10('LIBGMP_DLL', windows and get_option('default_library') != 'static')

conf_data.set10('WANT_ASSERT', get_option('enable-assert'))

conf_data.set10('HAVE_ALLOCA_H', c.has_header('alloca.h'))
conf_data.set10('WANT_TMP_ALLOCA', alloca == 'alloca')
conf_data.set10('WANT_TMP_REENTRANT', alloca == 'malloc-reentrant')
conf_data.set10('WANT_TMP_NOTREENTRANT', alloca == 'malloc-notreentrant')
conf_data.set10('WANT_TMP_DEBUG', alloca == 'debug')

conf_data.set10('WANT_FFT', get_option('enable-fft'))

# profiling
# fat binary

conf_data.set('GMP_NAIL_BITS', 0)

configure_file(input : 'config.h.in', output : 'config.h', configuration : conf_data)
configure_file(input : 'mpir.h.in', output : 'mpir.h', configuration : conf_data)

# subdirs
subdir('mpn')

# select sources
mpir_src = mpn_src + [
    'assert.c', 'compat.c', 'cpuid.c', 'errno.c', 'extract-dbl.c', 'invalid.c', 'memory.c', 'mp_bpl.c', 'mp_clz_tab.c',
    'mp_dv_tab.c', 'mp_get_fns.c', 'mp_minv_tab.c', 'mp_set_fns.c', 'nextprime.c', 'primesieve.c', 'randbui.c', 'randclr.c',
    'randdef.c', 'randiset.c', 'randlc2s.c', 'randlc2x.c', 'randmt.c', 'randmts.c', 'randmui.c', 'rands.c', 'randsd.c',
    'randsdui.c', 'version.c'
] 
mpir_inc = []

# alloc src
if alloca == 'alloca'
    assert(gmp_cv_func_alloca, 'alloca specified, but alloca not available')
elif alloca == 'malloc-reentrant'
    mpir_src += ['tal-reent.c']
elif alloca == 'malloc-notreentrant'
    mpir_src += ['tal-notreent.c'] 
elif alloca == 'debug'
    mpir_src += ['tal-debug.c']
endif

if get_option('enable-fft')
    mpir_src += [
        'fft/adjust_sqrt2.c',
        'fft/butterfly_lshB.c',
        'fft/butterfly_rshB.c',
        'fft/combine_bits.c',
        'fft/div_2expmod_2expp1.c',
        'fft/fermat_to_mpz.c',
        'fft/fft_mfa_trunc_sqrt2.c',
        'fft/fft_mfa_trunc_sqrt2_inner.c',
        'fft/fft_negacyclic.c',
        'fft/fft_radix2.c',
        'fft/fft_trunc.c',
        'fft/fft_trunc_sqrt2.c',
        'fft/ifft_mfa_trunc_sqrt2.c',
        'fft/ifft_negacyclic.c',
        'fft/ifft_radix2.c',
        'fft/ifft_trunc.c',
        'fft/ifft_trunc_sqrt2.c',
        'fft/mul_2expmod_2expp1.c',
        'fft/mul_fft_main.c',
        'fft/mul_mfa_trunc_sqrt2.c',
        'fft/mul_trunc_sqrt2.c',
        'fft/mulmod_2expp1.c',
        'fft/normmod_2expp1.c',
        'fft/revbin.c',
        'fft/split_bits.c',
        'fft/adjust.c'
    ]
endif

lib = library('mpir', mpir_src, 
    c_args : '-D__GMP_WITHIN_GMP=1')

library('mpirxx')
