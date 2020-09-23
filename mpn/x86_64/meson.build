if 'x86_64' in arch_set
    mpn_conf_data.set('BITS_PER_MP_LIMB', 64)

    alignment = c.run('''
        #include <stdint.h>
        #include <stdio.h>
        int main() {
            int64_t x, y;
            asm(".align 4\nx:\n\t" "jmp y\n\t"
                ".align 4\ny:\n\t" "leaq x(%%rip), %0\n\t" "leaq y(%%rip), %1"
                : "=r"(x), "=r"(y) : : );
            printf("%ld", y - x);
            return 0;
        }''', name : 'alignment test').stdout().strip()
    
    if alignment == '4'
        mpn_conf_data.set('ALIGN_LOGARITHMIC', 'no')
    elif alignment == '16'
        mpn_conf_data.set('ALIGN_LOGARITHMIC', 'yes')
    else
        error('could not interpret .align assembly directive')
    endif

    python3 = find_program('python3')
    foreach k : ['TEXT', 'DATA', 'LABEL_SUFFIX', 'GLOBL', 
                 'GSYM_PREFIX', 'RODATA', 'TYPE', 'SIZE', 'LSYM_PREFIX']
        message('testing for ' + k)
        cmd = run_command(python3, ['asm_test.py', k] + c.cmd_array())
        assert(cmd.returncode() == 0, 'could not determine ' + k)
        mpn_conf_data.set(k, cmd.stdout().strip())
        message('    ' + cmd.stdout().strip())
    endforeach

    mpn_hdr_map += {
        'longlong_inc.h': 'mpn/x86_64/longlong_inc.h.in',
        'gmp-mparam.h': 'mpn/x86_64/gmp-mparam.h.in',
        'yasm_mac.inc': 'yasm_mac.inc.nofat',
        'config.m4': 'config.m4.in',
        'asm-defs.m4': 'mpn/asm-defs.m4',
        'x86_64-defs.m4': 'mpn/x86_64/x86_64-defs.m4'
    }

    mpn_src_map += {
        'divexact_by3c': 'mpn/x86_64/divexact_by3c.as',
        'divrem_euclidean_qr_2': 'mpn/x86_64/divrem_euclidean_qr_2.as',
        'sqr_basecase': 'mpn/x86_64/sqr_basecase.asm',
        'divrem_2': 'mpn/x86_64/divrem_2.as',
        'mulmid_basecase': 'mpn/x86_64/mulmid_basecase.asm',
        'divexact_byfobm1': 'mpn/x86_64/divexact_byfobm1.as',
        'modexact_1c_odd': 'mpn/x86_64/modexact_1c_odd.as',
        'sub_err1_n': 'mpn/x86_64/sub_err1_n.asm',
        'add_err2_n': 'mpn/x86_64/add_err2_n.asm',
        'mullow_n_basecase': 'mpn/x86_64/mullow_n_basecase.asm',
        'sub_err2_n': 'mpn/x86_64/sub_err2_n.asm',
        'divrem_euclidean_qr_1': 'mpn/x86_64/divrem_euclidean_qr_1.as',

        'preinv_divrem_1': '.dummy'
    }

#    subdir('nehalem')
#    subdir('atom')
#    subdir('skylake')
#    subdir('haswell')
#    subdir('core2')
#    subdir('netburst')
#    subdir('bobcat')
#    subdir('k8')
#    subdir('sandybridge')
#    subdir('bulldozer')
    
    yasm_format += '64'
    yasm_obj_ext = '.o'
endif
