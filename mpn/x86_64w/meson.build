assert(bits == 64)

yasm_format += '64'
yasm_obj_ext = '.obj'

mpn_hdr_map += {
    'gmp-mparam.h': files('gmp-mparam.h.in'),
    'longlong_inc.h': files('longlong_inc.h.in'),
    'yasm_mac.inc': files('yasm_mac.inc')
}

mpn_src_map += {
    'add_err1_n': files('add_err1_n.asm'),
    'add_err2_n': files('add_err2_n.asm'),
    'addmul_2': files('addmul_2.asm'),
    'divexact_1': files('divexact_1.asm'),
    'divexact_by3c': files('divexact_by3c.asm'),
    'divexact_by3': files('divexact_by3c.asm'),
    'divexact_byfobm1': files('divexact_byfobm1.asm'),
    'divrem_2': files('divrem_2.asm'),
    'divrem_euclidean_qr_1': files('divrem_euclidean_qr_1.asm'),
    'preinv_divrem_1': files('divrem_euclidean_qr_1.asm'),
    'divrem_euclidean_qr_2': files('divrem_euclidean_qr_2.asm'),
    'modexact_1_odd': files('modexact_1c_odd.asm'),
    'modexact_1c_odd': files('modexact_1c_odd.asm'),
    'mul_2': files('mul_2.asm'),
    'mullow_n_basecase': files('mullow_n_basecase.asm'),
    'mulmid_basecase': files('mulmid_basecase.asm'),
    'sqr_basecase': files('sqr_basecase.asm'),
    'sub_err1_n': files('sub_err1_n.asm'),
    'sub_err2_n': files('sub_err2_n.asm'),
    'udiv_qrnnd': files('udiv_qrnnd.asm'),
    'umul_ppmm': files('umul_ppmm.asm')
}

if arch == 'auto'
    auto_run = c.run('''
        #include <stdio.h>
        #include <intrin.h>

        int c[4];
        char* get_arch() {
            int family, model;
            __cpuid(c, 1);
            family = ((c[0] >> 20) & 0xff) + ((c[0] >> 8) & 0xf);
            model = ((c[0] >> 12) & 0xf0) + ((c[0] >> 4) & 0xf);
            switch (family) {
            case  0xf:
                return "netburst";
            case 0x6:
                switch (model) {
                case 0x0f: case 0x16: return "core2";
                case 0x17: case 0x1d: return "penryn";
                case 0x1a: case 0x1e: case 0x1f: case 0x2e: return "nehalem";
                case 0x25: case 0x2c: case 0x2f: return "westmere";
                case 0x2a: case 0x2d: return "sandybridge";
                case 0x3a: case 0x3e: return "ivybridge";
                case 0x3c: case 0x3f: case 0x45: case 0x46: return "haswell";
                case 0x3d: case 0x47: case 0x4f: case 0x56: return "broadwell";
                default: if (model >= 0x4e) return "skylake";
                }
            }
            fprintf(stderr, "could not id processor with family 0x%x / model 0x%x\n", family, model);
            return NULL;
        }

        char* get_avx() { return c[3] & 0x10000000 ? "avx" : ""; }

        int main() {
            char* arch = get_arch();
            if (arch) printf("%s%s", arch, get_avx());
            return !arch;
        }''', name : 'cpuid')

    if auto_run.returncode() == 0
        arch = auto_run.stdout().strip()
        message('detected ' + arch)
    else
        arch = host_machine.cpu_family()
        message('architecture detection failed - using ' + arch)
    endif
endif

arch_map = {
    'netburst': ['netburst'],
    'k8': ['k8'],
    'k10': ['k8', 'k8/k10'],
    'k102': ['k8', 'k8/k10', 'k8/k10/k102'],
    'bulldozer': ['k8', 'k8/k10', 'k8/k10/k102', 'bulldozer'],
    'pilediver': ['k8', 'k8/k10', 'k8/k10/k102', 'bulldozer', 'bulldozer/piledriver'],
    'bobcat': ['bobcat'],
    'core2': ['core2'],
    'penryn': ['core2', 'core2/penryn'],
    'nehalem': ['nehalem'],
    'westmere': ['nehalem', 'nehalem/westmere'],
    'sandybridge': ['sandybridge'],
    'ivybridge': ['sandybridge', 'sandybridge/ivybridge'],
    'haswell': ['sandybridge', 'haswell'],
    'haswellavx': ['sandybridge', 'haswell', 'haswell/avx'],
    'broadwell': ['sandybridge', 'haswell', 'haswell/avx'],
    'broadwellavx': ['sandybridge', 'haswell', 'haswell/avx'],
    'skylake': ['sandybridge', 'skylake'],
    'skylakeavx': ['sandybridge', 'haswell', 'skylake', 'haswell/avx', 'skylake/avx'],
    'atom': ['atom'],
    'nano': ['k8']
}

if arch in arch_map
    foreach arch_dir : arch_map[arch]
        subdir(arch_dir)
    endforeach
endif