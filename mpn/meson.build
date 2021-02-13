mpn_conf_data = configuration_data()

mpn_conf_data.set('SQR_KARATSUBA_THRESHOLD', '24')
mpn_conf_data.set('SIZEOF_UNSIGNED', c.sizeof('unsigned'))
mpn_conf_data.set10('WANT_ASSERT', get_option('enable_assert'))
mpn_conf_data.set('ALIGN_FILL', 'yes')
mpn_conf_data.set('JUMPTABSECT', '')

sizeof_size_t = c.sizeof('size_t')
if sizeof_size_t == 4
    bits = 32
elif sizeof_size_t == 8
    bits = 64
else   
    warning('could not determine host machine bitness -- defaulting to 32')
    bits = 32
endif

mpn_hdr_map += {
    'asm-defs.m4': files('asm-defs.m4')
}

subdir('generic')

arch = get_option('host_arch')

if host_machine.cpu_family() == 'aarch64' and arch == 'auto'
    arch = 'generic'
endif

if arch != 'generic'
    top_level_arch_dir = host_machine.cpu_family()

    if windows
        yasm_format = 'win'
        top_level_arch_dir += 'w'
    else
        mpn_conf_data.set('WANT_PROFILING', '`no\'')

        # Map the OS to the binary format; build files for 64-bit arch will append 64 to these.
        if host_machine.system() == 'darwin'
            yasm_format = 'macho' 
            mpn_conf_data.set('JUMPTABSECT', 'define(`JUMPTABSECT\',`    .text\')')
        elif host_machine.system() == 'linux'
            yasm_format = 'elf' 
        endif
    endif

    subdir(top_level_arch_dir)
endif

# mpn_src_map will now have functions as keys and sources as values,
# but the sources could be duplicated, so split mpn_src_map into yasm 
# and m4/asm maps which will naturally de-duplicate the sources.
mpnc_src_map = {}
asm_src_map = {}
native_functions = []
foreach func, src_files : mpn_src_map
    foreach sf : src_files
        src = '@0@'.format(sf)

        if src.endswith('.c')
            mpnc_src_map += { src: src_files }
        else
            mpn_conf_data.set('HAVE_NATIVE_mpn_' + func, 1)
            asm_src_map += { src: src_files }
        endif
    endforeach
endforeach

foreach _, s : mpnc_src_map
    mpn_src += [s]
endforeach

asm_src = []
foreach _, s : asm_src_map
    asm_src += [s]
endforeach

if asm_src.length() != 0
    pic_asm = get_option('b_staticpic') or get_option('default_library') != 'static'

    # required m4...
    asm_defs = []
    if pic_asm
       asm_defs = ['PIC']
    endif

    asm_gen = generator(python,
        output : '@BASENAME@' + yasm_obj_ext,
        depfile : '@BASENAME@.d',
        arguments : [
            '@CURRENT_SOURCE_DIR@' / 'mpn' / 'asm.py',
            '--input', '@INPUT@',
            '--output', '@OUTPUT@',
            '--depfile', '@DEPFILE@',
            '--cc', c.cmd_array()[0],
            '--m4', m4.found() ? m4.full_path() : 'm4_not_found',
            '--yasm', yasm.found() ? yasm.full_path() : 'yasm_not_found',
            '--objfmt', yasm_format,
            '--incdirs', '@BUILD_DIR@' / '..', '@BUILD_DIR@' / '..' / 'mpn',
            '--defs'
        ] + asm_defs)
endif

