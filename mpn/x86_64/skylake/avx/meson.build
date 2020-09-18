if 'avx' in arch_set
    mpn_hdr_map += {
        'gmp-mparam.h': 'mpn/x86_64/skylake/avx/gmp-mparam.h.in',
    }

    mpn_src_map += {
        'mul_1': 'mpn/x86_64/skylake/avx/mul_1.as',
        'sqr_basecase': 'mpn/x86_64/skylake/avx/sqr_basecase.asm',
        'addmul_1': 'mpn/x86_64/skylake/avx/addmul_1.asm',
        'sub_err1_n': 'mpn/x86_64/skylake/avx/sub_err1_n.as',
        'mul_basecase': 'mpn/x86_64/skylake/avx/mul_basecase.asm',
        'add_err1_n': 'mpn/x86_64/skylake/avx/add_err1_n.as',
    }

endif
