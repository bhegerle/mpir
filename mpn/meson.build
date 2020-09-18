mpn_conf_map = {}

arch = get_option('host-arch')

if arch == 'auto'
    arch = host_machine.cpu_family()
endif

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

    # Go into each subdir, which will overwrite entries in mpn_src_map with native implementations.
    # This might overwrite mpn_conf_map as well.
    if windows
        yasm_format = 'win'

        subdir('x86_64w')
    else
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
        mpn_conf_map += { 'HAVE_NATIVE_mpn_' + f: true }
        
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

if asm_src.length() != 0
    if not m4.found()
        error('M4 is required for this host-arch')
    endif

    message('configuring m4/assembler')
    asm_pregen = generator(m4,
        output : '@BASENAME@.s',
        arguments : ['@INPUT@', '-o@OUTPUT@', '-I', 'mpn'],
        capture : true)
endif

if yasm_src.length() > 0
    if not yasm.found()
        error('YASM is required for this host-arch')
    endif

    message('configuring yasm to output ' + yasm_obj_ext + ' files in ' + yasm_format + ' format')
    yasm_gen = generator(yasm,
        output : '@BASENAME@' + yasm_obj_ext,
        arguments : ['-f', yasm_format, '-I', '.', '@INPUT@', '-o', '@OUTPUT@'])
endif
