mpn_src = []

arch = get_option('host-arch')

if arch == 'auto'
    arch = host_machine.cpu_family()
endif

# The values here are not ordered, but the order of subdir commands does 
# define a selection order on the sources.
arch_map = {
    'generic': [],
    'x86_64': ['x86_64'],
    'netburst': ['x86_64', 'netburst'],
    'k8': ['x86_64', 'k8'],
    'k10': ['x86_64', 'k8', 'k10'],
    'k102': ['x86_64', 'k8', 'k10', 'k102'],
    'bulldozer': ['x86_64', 'bulldozer', 'k8', 'k10', 'k102'],
    'piledriver': ['x86_64', 'bulldozer', 'piledriver', 'k8', 'k10', 'k102'],
    'bobcat': ['x86_64', 'bobcat'],
    'core2': ['x86_64', 'core2'],
    'penryn': ['x86_64', 'core2', 'penryn'],
    'nehalem': ['x86_64', 'nehalem'],
    'westmere': ['x86_64', 'nehalem', 'westmere'],
    'sandybridge': ['x86_64', 'sandybridge'],
    'ivybridge': ['x86_64', 'sandybridge', 'ivybridge'],
    'haswell': ['x86_64', 'sandybridge', 'haswell'],
    'haswellavx': ['x86_64', 'sandybridge', 'haswell', 'haswellavx'],
    'broadwell': ['x86_64', 'sandybridge', 'haswell', 'haswellavx'],
    'skylake': ['x86_64', 'sandybridge', 'skylake'],
    'skylakeavx': ['x86_64', 'sandybridge', 'haswell', 'skylake', 'skylakeavx'],
    'atom': ['x86_64', 'atom'],
    'nano': ['x86_64', 'k8'],
}

arch_set = arch_map[arch]
message('Enabling native implementations for:')
message(' + '.join(arch_set))

subdir('generic')

if arch != 'generic'
    if windows
        subdir('x86_64w')
    else
        subdir('x86_64')
    endif
endif
