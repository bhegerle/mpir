if 'skylake' in arch_set
    mpn_hdr_map += {
        'gmp-mparam.h': 'mpn/x86_64/skylake/gmp-mparam.h.in',
    }

    mpn_src_map += {
        'sub_n': 'mpn/x86_64/skylake/sub_n.as',
        'add_n': 'mpn/x86_64/skylake/add_n.as',
    }

    subdir('avx')
endif
