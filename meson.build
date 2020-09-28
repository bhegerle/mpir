project('mpir', ['c', 'cpp'], version : '3.0')

fs = import('fs')

c = meson.get_compiler('c')
cpp = meson.get_compiler('cpp')
python = find_program('python3')
windows = host_machine.system() == 'windows'

assert(not (windows and get_option('default_library') == 'both'),
    'windows build must be static or shared, but not both')

c_args = []

if windows 
    yasm = find_program([get_option('with_yasm'), 'vsyasm.exe'], 
        dirs : ['C:\\Program Files\\yasm\\'], 
        required : false)

    c_args += ['/DYNAMICBASE:NO']
else
    yasm = find_program(
        [get_option('with_yasm'), 'yasm'], 
        required : false)
endif

m4 = find_program('m4', required : false)

subdir('mpn')
subdir('fft')
subdir('mpz')
subdir('mpq')
subdir('mpf')
subdir('printf')
subdir('scanf')
subdir('cxx')

# select allocator
have_alloca = (
    c.has_function('__builtin_alloca')
    or c.compiles('''
        #include <malloc.h>
        void f(size_t n) { _alloca(n); }''', name : '_alloca')
    or c.has_function('alloca', prefix : '#include <alloca.h>')
)

allocator = get_option('allocator')

# configure
conf_data = configuration_data()
conf_data.merge_from(mpn_conf_data)

# other feature tests
nix_prefix = '''
    #include <unistd.h>
    #include <sys/time.h>
    #include <sys/resource.h>
'''

conf_data.set10('HAVE_FCNTL_H', c.has_header('fcntl.h'))
conf_data.set10('HAVE_FENV_H', c.has_header('fenv.h'))
conf_data.set10('HAVE_FLOAT_H', c.has_header('float.h'))
conf_data.set10('HAVE_INTTYPES_H', c.has_header('inttypes.h'))
conf_data.set10('HAVE_LANGINFO_H', c.has_header('langinfo.h'))
conf_data.set10('HAVE_LOCALE_H', c.has_header('locale.h'))
conf_data.set10('HAVE_MEMORY_H', c.has_header('memory.h'))
conf_data.set10('HAVE_SSTREAM', cpp.has_header('sstream'))
conf_data.set10('HAVE_STDARG', c.has_header('stdarg.h'))
conf_data.set10('HAVE_STDINT_H', c.has_header('stdint.h'))
conf_data.set10('HAVE_STDLIB_H', c.has_header('stdlib.h'))
conf_data.set10('HAVE_STRINGS_H', c.has_header('strings.h'))
conf_data.set10('HAVE_STRING_H', c.has_header('string.h'))
conf_data.set10('HAVE_SYS_MMAN_H', c.has_header('sys/mman.h'))
conf_data.set10('HAVE_SYS_PARAM_H', c.has_header('sys/param.h'))
conf_data.set10('HAVE_SYS_PROCESSOR_H', c.has_header('sys/processor.h'))
conf_data.set10('HAVE_SYS_PSTAT_H', c.has_header('sys/pstat.h'))
conf_data.set10('HAVE_SYS_RESOURCE_H', c.has_header('sys/resource.h'))
conf_data.set10('HAVE_SYS_STAT_H', c.has_header('sys/stat.h'))
conf_data.set10('HAVE_SYS_SYSCTL_H', c.has_header('sys/sysctl.h'))
conf_data.set10('HAVE_SYS_SYSINFO_H', c.has_header('sys/sysinfo.h'))
conf_data.set10('HAVE_SYS_SYSTEMCFG_H', c.has_header('sys/systemcfg.h'))
conf_data.set10('HAVE_SYS_TIMES_H', c.has_header('sys/times.h'))
conf_data.set10('HAVE_SYS_TIME_H', c.has_header('sys/time.h'))
conf_data.set10('HAVE_SYS_TYPES_H', c.has_header('sys/types.h'))
conf_data.set10('HAVE_UNISTD_H', c.has_header('unistd.h'))
    # 'TIME_WITH_SYS_TIME', c.has_header('time.h'))
conf_data.set10('HAVE_ALLOCA_H', c.has_header('alloca.h'))

conf_data.set10('HAVE_ALARM', c.has_function('alarm', prefix : '#include <unistd.h>'))
conf_data.set10('HAVE_ATTR_GET', c.has_function('attr_get'))
conf_data.set10('HAVE_CLOCK_GETTIME', c.has_function('clock_gettime'))
conf_data.set10('HAVE_CLOCK', c.has_function('clock'))
conf_data.set10('HAVE_GETPAGESIZE', c.has_function('getpagesize', prefix : nix_prefix))
conf_data.set10('HAVE_GETRUSAGE', c.has_function('getrusage', prefix : nix_prefix))
conf_data.set10('HAVE_GETTIMEOFDAY', c.has_function('gettimeofday', prefix : nix_prefix))
conf_data.set10('HAVE_LOCALECONV', c.has_function('localeconv', prefix : '#include <locale.h>'))
conf_data.set10('HAVE_MMAP', c.has_function('mmap', prefix : '#include <sys/mman.h>'))
conf_data.set10('HAVE_MPROTECT', c.has_function('mprotect', prefix : '#include <sys/mman.h>'))
conf_data.set10('HAVE_NL_LANGINFO', c.has_function('nl_langinfo', prefix : '#include <langinfo.h>'))
conf_data.set10('HAVE_OBSTACK_VPRINTF', c.has_function('obstack_vprintf', prefix : '#include <stdio.h>'))
conf_data.set10('HAVE_POPEN', c.has_function('popen', prefix : '#include <stdio.h>'))
conf_data.set10('HAVE_PROCESSOR_INFO', c.has_function('processor_info', prefix : '#include <mach/processor_info.h>'))
conf_data.set10('HAVE_PSTAT_GETPROCESSOR', c.has_function('pstat_getprocessor', prefix : '''
        #include <sys/param.h>
        #include <sys/pstat.h>'''))
conf_data.set10('HAVE_RAISE', c.has_function('raise', prefix : '#include <signal.h>'))
conf_data.set10('HAVE_READ_REAL_TIME', c.has_function('read_real_time', prefix : '''
        #include <sys/time.h>
        #include <sys/systemcfg.h>'''))
conf_data.set10('HAVE_STRERROR', c.has_function('strerror', prefix : '#include <string.h>'))
conf_data.set10('HAVE_STRNLEN', c.has_function('strnlen', prefix : '#include <string.h>'))
conf_data.set10('HAVE_STRTOL', c.has_function('strtol', prefix : '#include <string.h>'))
conf_data.set10('HAVE_STRTOUL', c.has_function('strtoul', prefix : '#include <string.h>'))
conf_data.set10('HAVE_SYSCONF', c.has_function('sysconf', prefix : nix_prefix))
conf_data.set10('HAVE_SYSCTL', c.has_function('sysctl', prefix : nix_prefix))
conf_data.set10('HAVE_SYSCTLBYNAME', c.has_function('sysctlbyname', prefix : nix_prefix))
conf_data.set10('HAVE_SYSSGI', c.has_function('syssgi', prefix : nix_prefix))
conf_data.set10('HAVE_TIMES', c.has_function('times', prefix : '#include <sys/times.h>'))
conf_data.set10('HAVE_VSNPRINTF', c.has_function('vsnprintf', prefix : '#include <stdio.h>'))

func_attrs = c.get_supported_function_attributes('const', 'malloc', 'noreturn')

conf_data.set10('HAVE_ATTRIBUTE_CONST', 'const' in func_attrs)
conf_data.set10('HAVE_ATTRIBUTE_MALLOC', 'malloc' in func_attrs)
conf_data.set10('HAVE_ATTRIBUTE_MODE', c.compiles('typedef int SItype __attribute__ ((mode (SI)));',
            name : '__attribute__ ((mode (XX)))'))
conf_data.set10('HAVE_ATTRIBUTE_NORETURN', 'noreturn' in func_attrs)

conf_data.set10('HAVE_INTMAX_T', c.compiles('''#include <inttypes.h>
        intmax_t f();''', name : 'intmax_t test'))
conf_data.set10('HAVE_UINTMAX_T', c.compiles('''#include <inttypes.h>
        uintmax_t f();''', name : 'uintmax_t test'))
conf_data.set10('HAVE_UINT_LEAST32_T', c.compiles('''#include <inttypes.h>
        uint_least32_t f();''', name : 'uint_least32_t test'))
conf_data.set10('HAVE_LONG_DOUBLE', c.compiles('long double f();', name : 'long double test'))
conf_data.set10('HAVE_LONG_LONG', c.compiles('long long f();', name : 'long long test'))
conf_data.set10('HAVE_QUAD_T', c.compiles('''#include <sys/types.h>
        quad_t f();''',  name : 'quad_t test'))
conf_data.set10('HAVE_PSP_ITICKSPERCLKTICK', c.has_member('struct pst_processor', 'psp_iticksperclktick', 
        prefix : '#include<sys/pstat.h>'))
conf_data.set10('HAVE_STD__LOCALE', cpp.compiles('''#include <locale>
        std::locale f();''',  name : 'std::locale test'))

conf_data.set10('LIBGMP_DLL', windows and get_option('default_library') != 'static')
conf_data.set10('HAVE_STRINGIZE', c.compiles('''#define f(x) #x
        char *c = f(0);''', name : 'stringize test'))
conf_data.set10('HAVE_ALLOCA', have_alloca)
conf_data.set10('WANT_ASSERT', get_option('enable_assert'))
conf_data.set10('WANT_TMP_ALLOCA', allocator == 'alloca')
conf_data.set10('WANT_TMP_REENTRANT', allocator == 'malloc-reentrant')
conf_data.set10('WANT_TMP_NOTREENTRANT', allocator == 'malloc-notreentrant')
conf_data.set10('WANT_TMP_DEBUG', allocator == 'debug')
conf_data.set10('WANT_FFT', get_option('enable_fft'))
conf_data.set10('WANT_PROFILING', false)

conf_data.set_quoted('VERSION', meson.project_version())
conf_data.set('BITS_PER_MP_LIMB', bits)
if bits == 64
    conf_data.set('_LONG_LONG_LIMB', 1)
endif
conf_data.set('GMP_NAIL_BITS', 0)

conf_data.set('SIZEOF_MP_LIMB_T', bits / 8)
conf_data.set('SIZEOF_UINTMAX_T', c.sizeof('uintmax_t', prefix : '#include <stdint.h>'))
conf_data.set('SIZEOF_UNSIGNED', c.sizeof('unsigned'))
conf_data.set('SIZEOF_UNSIGNED_LONG', c.sizeof('unsigned long'))
conf_data.set('SIZEOF_UNSIGNED_LONG_LONG', c.sizeof('unsigned long long'))
conf_data.set('SIZEOF_UNSIGNED_SHORT', c.sizeof('unsigned short'))

# select sources
configure_file(input : 'config.h.in', output : 'config.h', configuration : conf_data)
configure_file(input : 'mpir.h.in', output : 'mpir.h', configuration : conf_data, install_dir : '.')
configure_file(input : 'mpirxx.h', output : 'mpirxx.h', copy : true, install_dir : '.')

foreach out_hdr, in_hdr : mpn_hdr_map
    message(in_hdr + ' -> ' + out_hdr)
    configure_file(input : in_hdr, output : out_hdr, configuration : mpn_conf_data)
endforeach

mpir_src = mpn_src + mpz_src + fft_src + mpq_src + mpf_src + printf_src + scanf_src + [
    'assert.c', 
    # 'compat.c', 'cpuid.c',  
    'errno.c', 'extract-dbl.c', 'invalid.c', 'memory.c', 'mp_bpl.c', 'mp_clz_tab.c',
    'mp_dv_tab.c', 'mp_get_fns.c', 'mp_minv_tab.c', 'mp_set_fns.c', 'nextprime.c', 'primesieve.c', 'randbui.c',
    'randclr.c', 'randdef.c', 'randiset.c', 'randlc2s.c', 'randlc2x.c', 'randmt.c', 'randmts.c', 'randmui.c',
    'rands.c', 'randsd.c', 'randsdui.c', 'version.c'
]
mpir_inc = []

# alloc src
if allocator == 'alloca'
    assert(have_alloca, 'alloca specified, but alloca not available')
    mpir_src += 'tal-reent.c'
elif allocator == 'malloc-reentrant'
    mpir_src += 'tal-reent.c'
elif allocator == 'malloc-notreentrant'
    mpir_src += 'tal-notreent.c'
elif allocator == 'debug'
    mpir_src += 'tal-debug.c'
endif

# Build the libraries.
if asm_src.length() > 0
    mpir_src += [asm_gen.process(asm_src)]
endif

c_args += ['-D__GMP_WITHIN_GMP=1', '-D__GMP_WITHIN_GMPXX=1']
if windows and get_option('default_library') == 'shared'
    mpir_lib = library('mpir', 
        mpir_src + mpirxx_src, 
        c_args : c_args, 
        cpp_args : c_args)
        
    libs = [mpir_lib]
else 
    mpir_lib = library('mpir', 
        mpir_src, 
        c_args : c_args)

    mpirxx_lib = library('mpirxx', 
        mpirxx_src, 
        link_with : mpir_lib, 
        cpp_args : c_args)

    libs = [mpir_lib, mpirxx_lib]
endif

if not meson.is_subproject()
    test_inc = include_directories('.', 'tests')
    subdir('tests')
endif

libmpir_dep = declare_dependency(
    link_with : libs,
    include_directories : '.')
