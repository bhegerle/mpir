project('mpir', ['c', 'cpp'], version : '1.11')

fs = import('fs')

c = meson.get_compiler('c')
cpp = meson.get_compiler('cpp')
windows = host_machine.system() == 'windows'

if windows 
    yasm = find_program([get_option('with-yasm'), 'vsyasm.exe'], 
        dirs : ['C:\\Program Files\\yasm\\'], 
        required : false)
else
    yasm = find_program(
        [get_option('with-yasm'), 'yasm'], 
        required : false)
endif

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

alloca = get_option('enable-alloca')
if alloca == 'yes'
    alloca = 'alloca'
elif alloca == 'no'
    alloca = 'malloc-reentrant'
elif alloca == 'reentrant'
    alloca = have_alloca ? 'alloca' : 'malloc-reentrant'
elif alloca == 'notreentrant'
    alloca = have_alloca ? 'alloca' : 'malloc-notreentrant'
endif

# other feature tests
nix_prefix = '''
    #include <unistd.h>
    #include <sys/time.h>
    #include <sys/resource.h>
'''

header_conf_map = {
    'HAVE_FCNTL_H': c.has_header('fcntl.h'),
    'HAVE_FENV_H': c.has_header('fenv.h'),
    'HAVE_FLOAT_H': c.has_header('float.h'),
    'HAVE_INTTYPES_H': c.has_header('inttypes.h'),
    'HAVE_LANGINFO_H': c.has_header('langinfo.h'),
    'HAVE_LOCALE_H': c.has_header('locale.h'),
    'HAVE_MEMORY_H': c.has_header('memory.h'),
    'HAVE_SSTREAM': cpp.has_header('sstream'),
    'HAVE_STDARG': c.has_header('stdarg.h'),
    'HAVE_STDINT_H': c.has_header('stdint.h'),
    'HAVE_STDLIB_H': c.has_header('stdlib.h'),
    'HAVE_STRINGS_H': c.has_header('strings.h'),
    'HAVE_STRING_H': c.has_header('string.h'),
    'HAVE_SYS_MMAN_H': c.has_header('sys/mman.h'),
    'HAVE_SYS_PARAM_H': c.has_header('sys/param.h'),
    'HAVE_SYS_PROCESSOR_H': c.has_header('sys/processor.h'),
    'HAVE_SYS_PSTAT_H': c.has_header('sys/pstat.h'),
    'HAVE_SYS_RESOURCE_H': c.has_header('sys/resource.h'),
    'HAVE_SYS_STAT_H': c.has_header('sys/stat.h'),
    'HAVE_SYS_SYSCTL_H': c.has_header('sys/sysctl.h'),
    'HAVE_SYS_SYSINFO_H': c.has_header('sys/sysinfo.h'),
    'HAVE_SYS_SYSTEMCFG_H': c.has_header('sys/systemcfg.h'),
    'HAVE_SYS_TIMES_H': c.has_header('sys/times.h'),
    'HAVE_SYS_TIME_H': c.has_header('sys/time.h'),
    'HAVE_SYS_TYPES_H': c.has_header('sys/types.h'),
    'HAVE_UNISTD_H': c.has_header('unistd.h'),
    # 'TIME_WITH_SYS_TIME': c.has_header('time.h'),
    'HAVE_ALLOCA_H': c.has_header('alloca.h')
}

func_conf_map = {
    'HAVE_ALARM': c.has_function('alarm', prefix : '#include <unistd.h>'),
    'HAVE_ATTR_GET': c.has_function('attr_get'),
    'HAVE_CLOCK_GETTIME': c.has_function('clock_gettime'),
    'HAVE_CLOCK': c.has_function('clock'),
    'HAVE_GETPAGESIZE': c.has_function('getpagesize', prefix : nix_prefix),
    'HAVE_GETRUSAGE': c.has_function('getrusage', prefix : nix_prefix),
    'HAVE_GETTIMEOFDAY': c.has_function('gettimeofday', prefix : nix_prefix),
    'HAVE_LOCALECONV': c.has_function('localeconv', prefix : '#include <locale.h>'),
    'HAVE_MMAP': c.has_function('mmap', prefix : '#include <sys/mman.h>'),
    'HAVE_MPROTECT': c.has_function('mprotect', prefix : '#include <sys/mman.h>'),
    'HAVE_NL_LANGINFO': c.has_function('nl_langinfo', prefix : '#include <langinfo.h>'),
    'HAVE_OBSTACK_VPRINTF': c.has_function('obstack_vprintf', prefix : '#include <stdio.h>'),
    'HAVE_POPEN': c.has_function('popen', prefix : '#include <stdio.h>'),
    'HAVE_PROCESSOR_INFO': c.has_function('processor_info', prefix : '#include <mach/processor_info.h>'),
    'HAVE_PSTAT_GETPROCESSOR': c.has_function('pstat_getprocessor', prefix : '''
        #include <sys/param.h>
        #include <sys/pstat.h>'''),
    'HAVE_RAISE': c.has_function('raise', prefix : '#include <signal.h>'),
    'HAVE_READ_REAL_TIME': c.has_function('read_real_time', prefix : '''
        #include <sys/time.h>
        #include <sys/systemcfg.h>'''),
    'HAVE_STRERROR': c.has_function('strerror', prefix : '#include <string.h>'),
    'HAVE_STRNLEN': c.has_function('strnlen', prefix : '#include <string.h>'),
    'HAVE_STRTOL': c.has_function('strtol', prefix : '#include <string.h>'),
    'HAVE_STRTOUL': c.has_function('strtoul', prefix : '#include <string.h>'),
    'HAVE_SYSCONF': c.has_function('sysconf', prefix : nix_prefix),
    'HAVE_SYSCTL': c.has_function('sysctl', prefix : nix_prefix),
    'HAVE_SYSCTLBYNAME': c.has_function('sysctlbyname', prefix : nix_prefix),
    'HAVE_SYSSGI': c.has_function('syssgi', prefix : nix_prefix),
    'HAVE_TIMES': c.has_function('times', prefix : '#include <sys/times.h>'),
    'HAVE_VSNPRINTF': c.has_function('vsnprintf', prefix : '#include <stdio.h>')
}

attr_conf_map = {
    'HAVE_ATTRIBUTE_CONST': c.compiles('int foo (int x) __attribute__ ((const));', 
        name : '__attribute__((const))'),
    'HAVE_ATTRIBUTE_MALLOC': c.compiles('void *foo (int x) __attribute__ ((malloc));',
        name : '__attribute__ ((malloc))'),
    'HAVE_ATTRIBUTE_MODE': c.compiles('typedef int SItype __attribute__ ((mode (SI)));',
        name : '__attribute__ ((mode (XX)))'),
    'HAVE_ATTRIBUTE_NORETURN': c.compiles('void foo (int x) __attribute__ ((noreturn));',
        name : '__attribute__ ((noreturn))')
}

type_conf_map = {
    'HAVE_INTMAX_T': c.compiles('''#include <inttypes.h>
        intmax_t f();''', name : 'intmax_t test'),
    'HAVE_UINTMAX_T': c.compiles('''#include <inttypes.h>
        uintmax_t f();''', name : 'uintmax_t test'),
    'HAVE_UINT_LEAST32_T': c.compiles('''#include <inttypes.h>
        uint_least32_t f();''', name : 'uint_least32_t test'),
    'HAVE_LONG_DOUBLE': c.compiles('long double f();', name : 'long double test'),
    'HAVE_LONG_LONG': c.compiles('long long f();', name : 'long long test'),
    'HAVE_QUAD_T': c.compiles('''#include <sys/types.h>
        quad_t f();''',  name : 'quad_t test'),
    'HAVE_PSP_ITICKSPERCLKTICK': c.has_member('struct pst_processor', 'psp_iticksperclktick', 
        prefix : '#include<sys/pstat.h>'),
    'HAVE_STD__LOCALE': cpp.compiles('''#include <locale>
        std::locale f();''',  name : 'std::locale test')
}

config_map = header_conf_map + func_conf_map + attr_conf_map + type_conf_map + mpn_conf_map + {
    'LIBGMP_DLL': windows and get_option('default_library') != 'static',
    'HAVE_STRINGIZE': c.compiles('''#define f(x) #x
        char *c = f(0);''', name : 'stringize test'),
    'HAVE_ALLOCA': have_alloca,   
    'WANT_ASSERT': get_option('enable-assert'),
    'WANT_TMP_ALLOCA': alloca == 'alloca',
    'WANT_TMP_REENTRANT': alloca == 'malloc-reentrant',
    'WANT_TMP_NOTREENTRANT': alloca == 'malloc-notreentrant',
    'WANT_TMP_DEBUG': alloca == 'debug',
    'WANT_FFT': get_option('enable-fft')
}

# configure
conf_data = configuration_data()

foreach symbol, flag : config_map
    conf_data.set10(symbol, flag)
endforeach

conf_data.set_quoted('VERSION', meson.project_version())
conf_data.set('BITS_PER_MP_LIMB', '(8 * SIZEOF_MP_LIMB_T)')
conf_data.set('GMP_NAIL_BITS', 0)
conf_data.set('SIZEOF_UINTMAX_T', c.sizeof('uintmax_t', prefix : '#include <stdint.h>'))
conf_data.set('SIZEOF_UNSIGNED', c.sizeof('unsigned'))
conf_data.set('SIZEOF_UNSIGNED_LONG', c.sizeof('unsigned long'))
conf_data.set('SIZEOF_UNSIGNED_LONG_LONG', c.sizeof('unsigned long long'))
conf_data.set('SIZEOF_UNSIGNED_SHORT', c.sizeof('unsigned short'))

# select sources
configure_file(input : 'config.h.in', output : 'config.h', configuration : conf_data)
configure_file(input : 'mpir.h.in', output : 'mpir.h', configuration : conf_data)

foreach out_hdr, in_hdr : mpn_hdr_map
    message(in_hdr + ' -> ' + out_hdr)
    configure_file(input : in_hdr, output : out_hdr, copy : true)
endforeach

mpir_src = mpn_src + mpz_src + fft_src + mpq_src + mpf_src + printf_src + scanf_src + [
    'assert.c', 'compat.c', 
    # 'cpuid.c', 
    'errno.c', 'extract-dbl.c', 'invalid.c', 'memory.c', 'mp_bpl.c', 'mp_clz_tab.c',
    'mp_dv_tab.c', 'mp_get_fns.c', 'mp_minv_tab.c', 'mp_set_fns.c', 'nextprime.c', 'primesieve.c', 'randbui.c', 'randclr.c',
    'randdef.c', 'randiset.c', 'randlc2s.c', 'randlc2x.c', 'randmt.c', 'randmts.c', 'randmui.c', 'rands.c', 'randsd.c',
    'randsdui.c', 'version.c'
]
mpir_inc = []

# alloc src
if alloca == 'alloca'
    assert(have_alloca, 'alloca specified, but alloca not available')
    mpir_src += 'tal-reent.c'
elif alloca == 'malloc-reentrant'
    mpir_src += 'tal-reent.c'
elif alloca == 'malloc-notreentrant'
    mpir_src += 'tal-notreent.c'
elif alloca == 'debug'
    mpir_src += 'tal-debug.c'
endif

# Build the libraries.
if yasm_src.length() > 0
    mpir_src += [yasm_gen.process(yasm_src)]
endif

mpir_lib = library('mpir', mpir_src, 
    c_args : '-D__GMP_WITHIN_GMP=1')

mpirxx_lib = library('mpirxx', mpirxx_src, 
    cpp_args : '-D__GMP_WITHIN_GMP=1')

# Setup tests.
test_inc = include_directories('.', 'tests')
subdir('tests')