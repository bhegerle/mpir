mpn_conf_data = configuration_data()

mpn_conf_data.set('SQR_KARATSUBA_THRESHOLD', '24')
mpn_conf_data.set('SIZEOF_UNSIGNED', c.sizeof('unsigned'))
mpn_conf_data.set10('WANT_ASSERT', get_option('enable-assert'))
mpn_conf_data.set('ALIGN_FILL', 'yes')

subdir('generic')

arch = get_option('host-arch')

if arch == 'auto'
    auto_run = c.run('#define ' + host_machine.cpu_family() + '''
        #include <stdio.h>

        #ifdef x86_64
        #include <cpuid.h>

          char *get_arch() {
              int a, x, family, model;
              if (!__get_cpuid (1, &a, &x, &x, &x))
                  return NULL;
              family = ((a >> 20) & 0xff) + ((a >> 8) & 0xf);
              model = ((a >> 12) & 0xf0) + ((a >> 4) & 0xf);
              switch(family) {
              case  0xf:
                  return "netburst";
              case 0x6:
                  switch(model) {
                  case 0x0f: case 0x16: return "core2";
                  case 0x17: case 0x1d: return "penryn";
                  case 0x1a: case 0x1e: case 0x1f: case 0x2e: return "nehalem";
                  case 0x25: case 0x2c: case 0x2f: return "westmere";
                  case 0x2a: case 0x2d: return "sandybridge";
                  case 0x3a: case 0x3e: return "ivybridge";
                  case 0x3c: case 0x3f: case 0x45: case 0x46: return "haswell";
                  case 0x3d: case 0x47: case 0x4f: case 0x56: return "broadwell";
                  default: if(model > 0x4e) return "skylake";
                  }
              }
              printf("could not id processor with family 0x%x / model 0x%x\n", family, model);
              return NULL;
          }

          char *get_avx() {
              int c, x;
              if (!__get_cpuid (1, &x, &x, &c, &x))
                  return "";
              return c & 0x10000000 ? "avx" : "";
          }
          #endif

          int main() {
              char *arch = get_arch();
              if(arch) printf("%s%s", arch, get_avx());
              return !arch;
          }''', name : 'cpuid')

    if auto_run.returncode() == 0
        arch = auto_run.stdout().strip()
        message('detected ' + arch)
    elif
        arch = host_machine.cpu_family()
        message('architecture detection failed - using ' + arch)
    endif
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
yasm_src_map = {}
asm_src_map = {}
native_functions = []
foreach f, src : mpn_src_map
    if src.endswith('.c')
        mpnc_src_map += { src: src }
    else
        mpn_conf_data.set('HAVE_NATIVE_mpn_' + f, 1)
        
        if src.endswith('.asm')
            if use_yasm_for_asm_files
                yasm_src_map += { src: src }
            else 
                asm_src_map += { src: src }
            endif
        elif src.endswith('.as')
            yasm_src_map += { src: src }
        else
            warning('unexpected extension ' + src)
        endif
    endif
endforeach

foreach s, _ : mpnc_src_map
    mpn_src += [s]
endforeach

asm_src = []
foreach s, _ : asm_src_map
    asm_src += [s]
endforeach

yasm_src = []
foreach s, _ : yasm_src_map
    yasm_src += [s]
endforeach

if asm_src.length() != 0
    pic_asm = get_option('b_staticpic') or get_option('default_library') != 'static'

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
    pic_asm = get_option('b_staticpic') or get_option('default_library') != 'static'

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

message(asm_src)
message(yasm_src)