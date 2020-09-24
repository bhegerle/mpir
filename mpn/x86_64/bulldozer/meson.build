if 'bulldozer' in arch_set
    mpn_hdr_map += {
        'gmp-mparam.h': 'mpn/x86_64/bulldozer/gmp-mparam.h.in',
    }

    mpn_src_map += {
        'com_n': 'mpn/x86_64/bulldozer/com_n.asm',
        'copyd': 'mpn/x86_64/bulldozer/copyd.asm',
        'copyi': 'mpn/x86_64/bulldozer/copyi.asm',
        'lshift': 'mpn/x86_64/bulldozer/lshift.asm',
        'mul_basecase': 'mpn/x86_64/bulldozer/mul_basecase.asm',
        'rshift': 'mpn/x86_64/bulldozer/rshift.asm',
    }

    subdir('piledriver')
endif
