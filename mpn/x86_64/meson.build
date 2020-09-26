use_yasm_for_asm_files = false

mpn_conf_data.set('BITS_PER_MP_LIMB', 64)

asm_test_ok = true
foreach k : ['TEXT', 'DATA', 'LABEL_SUFFIX', 'GLOBL', 
             'GSYM_PREFIX', 'RODATA', 'TYPE', 'SIZE', 'LSYM_PREFIX',
             'ALIGN_LOGARITHMIC']
    message('testing for ' + k)
    cmd = run_command(python, ['asm_test.py'] + c.cmd_array() + [k])
    if cmd.returncode() != 0
        warning('failed! disabling assembler implementations')
        asm_test_ok = false
        break
    endif

    mpn_conf_data.set(k, cmd.stdout().strip())
    message('    ' + cmd.stdout().strip())
endforeach

if asm_test_ok
    yasm_format += '64'
    yasm_obj_ext = '.o'

    mpn_hdr_map += {
        'longlong_inc.h': 'mpn/x86_64/longlong_inc.h.in',
        'gmp-mparam.h': 'mpn/x86_64/gmp-mparam.h.in',
        'yasm_mac.inc': 'yasm_mac.inc.in',
        'config.m4': 'config.m4.in',
        'asm-defs.m4': 'mpn/asm-defs.m4',
        'x86_64-defs.m4': 'mpn/x86_64/x86_64-defs.m4'
    }

    mpn_src_map += {
        'add_err1_n': 'mpn/x86_64/add_err1_n.asm',
        'add_err2_n': 'mpn/x86_64/add_err2_n.asm',
        'divexact_by3c': 'mpn/x86_64/divexact_by3c.as',
        'divexact_byfobm1': 'mpn/x86_64/divexact_byfobm1.as',
        'divrem_2': 'mpn/x86_64/divrem_2.as',
        'divrem_euclidean_qr_1': 'mpn/x86_64/divrem_euclidean_qr_1.as',
        'preinv_divrem_1': 'mpn/x86_64/divrem_euclidean_qr_1.as',
        'divrem_euclidean_qr_2': 'mpn/x86_64/divrem_euclidean_qr_2.as',
        'modexact_1_odd': 'mpn/x86_64/modexact_1c_odd.as',
        'modexact_1c_odd': 'mpn/x86_64/modexact_1c_odd.as',
        'mullow_n_basecase': 'mpn/x86_64/mullow_n_basecase.asm',
        'mulmid_basecase': 'mpn/x86_64/mulmid_basecase.asm',
        'sqr_basecase': 'mpn/x86_64/sqr_basecase.asm',
        'sub_err1_n': 'mpn/x86_64/sub_err1_n.asm',
        'sub_err2_n': 'mpn/x86_64/sub_err2_n.asm',
    }

    if arch == 'auto'
        auto_run = c.run('''
            #include <stdio.h>

            #include <cpuid.h>
            int a, b, c, d;
            char *get_arch() {
                int family, model;
                if (!__get_cpuid (1, &a, &b, &c, &d))
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
                fprintf(stderr, "could not id processor with family 0x%x / model 0x%x\n", family, model);
                return NULL;
            }

            char *get_avx() { return c & 0x10000000 ? "avx" : ""; }

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

    arch_map = {
        'netburst': ['netburst'],
        'k8': ['k8', 'k8/k8only'],
        'k10': ['k8', 'k8/k10'],
        'k102': ['k8', 'k8/k10', 'k8/k10/k102'],
        'bulldozer': ['k8', 'k8/k10', 'k8/k10/k102', 'bulldozer'],
        'pilediver': ['k8', 'k8/k10', 'k8/k10/k102', 'bulldozer', 'bulldozer/piledriver'],
        'bobcat': ['bobcat'],
        'core2': ['core2'],
        'penryn': ['core2', 'core2/penryn'],
        'nehalem': ['nehalem'],
        'westmere': ['nehalem', 'nehalem/westmere'],
        'sandybridge': ['nehalem', 'nehalem/westmere', 'sandybridge'],
        'ivybridge': ['nehalem', 'nehalem/westmere', 'sandybridge', 'sandybridge/ivybridge'],
        'haswell': ['sandybridge', 'haswell'],
        'haswellavx': ['sandybridge', 'haswell', 'haswell/avx'],
        'broadwell': ['sandybridge', 'haswell', 'haswell/avx', 'haswell/broadwell'],
        'broadwellavx': ['sandybridge', 'haswell', 'haswell/avx', 'haswell/broadwell'],
        'skylake': ['sandybridge', 'skylake'],
        'skylakeavx': ['sandybridge', 'haswell', 'skylake', 'haswell/avx', 'skylake/avx'],
        'atom': ['atom'],
        'nano': ['k8', 'k8/k8only']
    }

    if arch in arch_map
       foreach arch_dir : arch_map[arch]
           subdir(arch_dir)
       endforeach
    endif
else
    warning('could not configure assembler - using generic c implementation')
endif