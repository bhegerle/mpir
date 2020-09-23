arch = get_option('host-arch')

if arch == 'auto'
    arch = host_machine.cpu_family()
endif

mpn_conf_data = configuration_data()

mpn_conf_data.set('TEXT_SECTION', '.text')
mpn_conf_data.set('DATA_SECTION', '.data')
mpn_conf_data.set('LABEL_SUFFIX', ':')
mpn_conf_data.set('GLOBL_SECTION', '.globl')
mpn_conf_data.set('GLOBL_ATTR', '')
mpn_conf_data.set('LSYM_PREFIX', '.L')
mpn_conf_data.set('W32', '.long')
mpn_conf_data.set('SQR_KARATSUBA_THRESHOLD', '24')
mpn_conf_data.set('SIZEOF_UNSIGNED', '4')
mpn_conf_data.set10('WANT_ASSERT', get_option('enable-assert'))
mpn_conf_data.set('ALIGN_FILL', 'yes')

subdir('generic')

if arch != 'generic'
    # The values here are not ordered, but the order of subdir commands does 
    # define a selection order on the sources.
    arch_map = {
        'generic': [],
        'x86_64': ['x86_64'],
        'netburst': ['x86_64', 'netburst'],
        'k8': ['x86_64', 'k8'],
        'k10': ['x86_64', 'k8', 'k10'],
        'k102': ['x86_64', 'k8', 'k10', 'k102'],
        'bulldozer': ['x86_64', 'bulldozer', 'k8', 'k10', 'k102'],
        'piledriver': ['x86_64', 'bulldozer', 'piledriver', 'k8', 'k10', 'k102'],
        'bobcat': ['x86_64', 'bobcat'],
        'core2': ['x86_64', 'core2'],
        'penryn': ['x86_64', 'core2', 'penryn'],
        'nehalem': ['x86_64', 'nehalem'],
        'westmere': ['x86_64', 'nehalem', 'westmere'],
        'sandybridge': ['x86_64', 'sandybridge'],
        'ivybridge': ['x86_64', 'sandybridge', 'ivybridge'],
        'haswell': ['x86_64', 'sandybridge', 'haswell'],
        'haswellavx': ['x86_64', 'sandybridge', 'haswell', 'haswellavx'],
        'broadwell': ['x86_64', 'sandybridge', 'haswell', 'haswellavx'],
        'skylake': ['x86_64', 'sandybridge', 'skylake'],
        'skylakeavx': ['x86_64', 'sandybridge', 'haswell', 'skylake', 'skylakeavx'],
        'atom': ['x86_64', 'atom'],
        'nano': ['x86_64', 'k8'],
    }

    arch_set = arch_map[arch]
    message('Enabling native implementations for:')
    message(' + '.join(arch_set))

    sym_prefix = c.symbols_have_underscore_prefix()

    # Go into each subdir, which will overwrite entries in mpn_src_map with native implementations.
    # This might adjust mpn_conf_data as well.
    if windows
        yasm_format = 'win'

        subdir('x86_64w')
    else
#        asm_test = custom_target('asm_test',
#            output : 'asm_test.s',
#            input : 'asm_test.c',
#            command : c.cmd_array() + ['-S', '-o', '@OUTPUT@', '@INPUT@'])

#        run_command('test.py', asm_test.full_path())

        mpn_conf_data.set('WANT_PROFILING', '`no\'')
        
        # Map the OS to the binary format; build files for 64-bit arch will append 64 to these.
        if host_machine.system() == 'darwin'
            yasm_format = 'macho' 
        elif host_machine.system() == 'linux'
            yasm_format = 'elf' 
        endif

        subdir('x86_64')
    endif
endif

mpn_src = []
yasm_src = []
asm_src = []
native_functions = []
foreach f, src : mpn_src_map
    if src.endswith('.c')
        mpn_src += src
    else
        mpn_conf_data.set('HAVE_NATIVE_mpn_' + f, 1)
        
        if src.endswith('.asm')
            if windows 
                yasm_src += src
            else 
                asm_src += src
            endif
        elif src.endswith('.as')
            yasm_src += src
        elif not src.endswith('.dummy')
            warning('unexpected extension ' + src)
        endif
    endif
endforeach

pic_asm = get_option('b_staticpic') or get_option('default_library') != 'static'
if asm_src.length() != 0
    if not m4.found()
        error('M4 is required for this host-arch')
    endif

    m4_args = ['@INPUT@', '-o@OUTPUT@', '-I', 'mpn']
    if pic_asm
       m4_args += ['-DPIC']
    endif

    message('configuring m4/assembler')
    asm_pregen = generator(m4,
        output : '@BASENAME@.s',
        arguments : m4_args,
        capture : true)
endif

if yasm_src.length() > 0
    if not yasm.found()
        error('YASM is required for this host-arch')
    endif

    yasm_args = ['-f', yasm_format, '-I', '.', '@INPUT@', '-o', '@OUTPUT@']
    if pic_asm
       yasm_args += ['-D', 'PIC']
    endif

    message('configuring yasm to output ' + yasm_obj_ext + ' files in ' + yasm_format + ' format')
    yasm_gen = generator(yasm,
        output : '@BASENAME@' + yasm_obj_ext,
        arguments : yasm_args)
endif
