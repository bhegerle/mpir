if 'x86_64' in arch_set
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
        mpn_hdr_map += {
            'longlong_inc.h': 'mpn/x86_64/longlong_inc.h.in',
            'gmp-mparam.h': 'mpn/x86_64/gmp-mparam.h.in',
            'yasm_mac.inc': 'yasm_mac.inc.nofat',
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
endif