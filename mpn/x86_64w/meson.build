if 'x86_64' in arch_set
    mpn_hdr_map += {
        'gmp-mparam.h': 'mpn/x86_64w/gmp-mparam.h.in',
        'longlong_inc.h': 'mpn/x86_64w/longlong_inc.h.in'
    }

    mpn_src_map += {
        'add_err1_n': 'mpn/x86_64w/add_err1_n.asm',
        'add_err2_n': 'mpn/x86_64w/add_err2_n.asm',
        'addmul_2': 'mpn/x86_64w/addmul_2.asm',
        'divexact_1': 'mpn/x86_64w/divexact_1.asm',
        'divexact_by3c': 'mpn/x86_64w/divexact_by3c.asm',
        'divexact_byfobm1': 'mpn/x86_64w/divexact_byfobm1.asm',
        'divrem_2': 'mpn/x86_64w/divrem_2.asm',
        'divrem_euclidean_qr_1': 'mpn/x86_64w/divrem_euclidean_qr_1.asm',
        'divrem_euclidean_qr_2': 'mpn/x86_64w/divrem_euclidean_qr_2.asm',
        'modexact_1c_odd': 'mpn/x86_64w/modexact_1c_odd.asm',
        'mul_2': 'mpn/x86_64w/mul_2.asm',
        'mullow_n_basecase': 'mpn/x86_64w/mullow_n_basecase.asm',
        'mulmid_basecase': 'mpn/x86_64w/mulmid_basecase.asm',
        'sqr_basecase': 'mpn/x86_64w/sqr_basecase.asm',
        'sub_err1_n': 'mpn/x86_64w/sub_err1_n.asm',
        'sub_err2_n': 'mpn/x86_64w/sub_err2_n.asm',
        'udiv_qrnnd': 'mpn/x86_64w/udiv_qrnnd.asm',
        'umul_ppmm': 'mpn/x86_64w/umul_ppmm.asm'
    }
    
    subdir('netburst')
    subdir('k8')
    subdir('bulldozer')
    subdir('bobcat')
    subdir('core2')
    subdir('nehalem')
    subdir('sandybridge')
    subdir('haswell')
    subdir('skylake')
    subdir('atom')
    
    yasm_gen = generator(yasm,
        output: '@BASENAME@.obj',
        arguments: ['-fwin64', '-o', '@OUTPUT@', '-I', 'mpn/x86_64w', '@INPUT@'])

    configure_file(input : 'yasm_mac.inc', output : 'yasm_mac.inc', copy : true)
endif