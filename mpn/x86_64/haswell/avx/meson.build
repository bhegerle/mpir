if 'avx' in arch_set
    mpn_hdr_map += {
        'gmp-mparam.h': 'mpn/x86_64/haswell/avx/gmp-mparam.h.in',
    }

    mpn_src_map += {
        'lshift': 'mpn/x86_64/haswell/avx/lshift.as',
        'mul_1': 'mpn/x86_64/haswell/avx/mul_1.asm',
        'sqr_basecase': 'mpn/x86_64/haswell/avx/sqr_basecase.asm',
        'copyd': 'mpn/x86_64/haswell/avx/copyd.as',
        'rshift': 'mpn/x86_64/haswell/avx/rshift.as',
        'submul_1': 'mpn/x86_64/haswell/avx/submul_1.as',
        'addmul_1': 'mpn/x86_64/haswell/avx/addmul_1.as',
        'com_n': 'mpn/x86_64/haswell/avx/com_n.as',
        'lshift1': 'mpn/x86_64/haswell/avx/lshift1.as',
        'copyi': 'mpn/x86_64/haswell/avx/copyi.as',
        'mul_basecase': 'mpn/x86_64/haswell/avx/mul_basecase.as',
        'rshift1': 'mpn/x86_64/haswell/avx/rshift1.as',
    }

endif
