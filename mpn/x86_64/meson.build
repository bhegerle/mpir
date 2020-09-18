if 'x86_64' in arch_set
    mpn_hdr_map += {
        'longlong_inc.h': 'mpn/x86_64/longlong_inc.h.in',
        'gmp-mparam.h': 'mpn/x86_64/gmp-mparam.h.in',
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
    }

    subdir('nehalem')
    subdir('atom')
    subdir('skylake')
    subdir('haswell')
    subdir('core2')
    subdir('netburst')
    subdir('bobcat')
    subdir('k8')
    subdir('sandybridge')
    subdir('bulldozer')
    
    if host_machine.system() == 'darwin'
        yasm_format = 'macho64'
    else
        yasm_format = 'elf64'
    endif
    
    yasm_gen = generator(yasm,
        output: '@BASENAME@.obj',
        arguments: ['-f' + yasm_format, '-o', '@OUTPUT@', '-I', 'mpn/x86_64w', '@INPUT@'])

    configure_file(input : 'yasm_mac.inc', output : 'yasm_mac.inc', copy : true)
endif
