if 'haswell' in arch_set
    mpn_hdr_map += {
        'gmp-mparam.h': 'mpn/x86_64/haswell/gmp-mparam.h.in',
    }

    mpn_src_map += {
        'sub_n': 'mpn/x86_64/haswell/sub_n.as',
        'addlsh1_n': 'mpn/x86_64/haswell/addlsh1_n.as',
        'karasub': 'mpn/x86_64/haswell/karasub.as',
        'sublsh1_n': 'mpn/x86_64/haswell/sublsh1_n.as',
        'karaadd': 'mpn/x86_64/haswell/karaadd.asm',
        'add_n': 'mpn/x86_64/haswell/add_n.as',
        'sumdiff_n': 'mpn/x86_64/haswell/sumdiff_n.as',
        'nsumdiff_n': 'mpn/x86_64/haswell/nsumdiff_n.as',
    }

    subdir('avx')
    subdir('broadwell')
endif
