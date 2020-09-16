mpn_src = []

arch = get_option('host-arch')

if arch == 'auto'
    arch = host_machine.cpu_family()
endif

subdir('generic')

mpn_src = []
foreach _, src : mpn_src_map
    mpn_src += src
endforeach
