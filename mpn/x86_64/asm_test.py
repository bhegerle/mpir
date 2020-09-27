import sys
import subprocess
import re
import os

if 'MESON_BUILD_ROOT' in os.environ:
    asm_test = os.path.join(os.environ['MESON_BUILD_ROOT'], '.asm_test')
else:
    asm_test = os.path.abspath('.asm_test')


cc = sys.argv[1:-1]
mode = sys.argv[-1]


def test(mode_filter, gen, pattern, match_func):
    if mode == 'all' or mode == mode_filter:
        i = gen()
        m = re.search(pattern, i, re.M)
        r = match_func(m)
        if mode == 'all':
            print(f'{mode_filter}: {r}')
        else:
            print(r)
            

def execute(mode_filter, src, pattern, match_func):
    def gen():
        with open(asm_test + '.c', 'w') as c:
            c.write(src)

        cmd = cc + ['-o', asm_test, asm_test + '.c']
        subprocess.run(cmd, check=True)

        run = subprocess.run(asm_test, check=True, capture_output=True, text=True)
        return run.stdout

    test(mode_filter, gen, pattern, match_func)
            
        
def parse_asm(mode_filter, pattern, match_func):
    def gen():
        with open(asm_test + '.c', 'w') as c:
            c.write('const int C=123; int I=1; const char *s="hi";')

        cmd = cc + ['-S', asm_test + '.c']
        subprocess.run(cmd, check=True)

        with open(asm_test + '.s', 'r') as s:
            asm = s.read()

        return asm

    test(mode_filter, gen, pattern, match_func)
    

def fail():
    raise Exception()


parse_asm('TEXT', r'^\s+(\.text\b|\.section\s+__TEXT.*)', lambda m: m[1])
parse_asm('DATA', r'^\s+(\.data\b|\.section\s+__DATA.*)', lambda m: m[1])
parse_asm('LABEL_SUFFIX', r'^_?C(:)?', lambda m: m[1])
parse_asm('GLOBL', r'^\s+(\.globl)\s+_?I\b', lambda m: m[1]) 
parse_asm('GSYM_PREFIX', r'^(_?)C:?', lambda m: m[1])
parse_asm('RODATA', r'^\s+(\.section)\s.*(\.rodata|__TEXT,__const)', lambda m: m[1] + ' ' + m[2])
parse_asm('TYPE', r'^\s+(\.type)\s+_?I\s*,\s*@\w+', lambda m: m[1] + ' $1,@$2' if m else '')
parse_asm('SIZE', r'^\s+(\.size)\s+_?I\s*,\s*\d+', lambda m: m[1] + ' $1,$2' if m else '')
parse_asm('LSYM_PREFIX', r'^\.?L', lambda m: m[0])
execute('ALIGN_LOGARITHMIC', r'''
        #include <stdint.h>
        #include <stdio.h>
        int main() {
            int64_t x, y;
            asm(".align 4\nx:\n\t" "jmp y\n\t"
                ".align 4\ny:\n\t" "leaq x(%%rip), %0\n\t" "leaq y(%%rip), %1"
                : "=r"(x), "=r"(y) : : );
            printf("%ld", y - x);
            return 0;
        }''',
        r'\d+', lambda m: 'no' if m[0] == '4' else 'yes' if m[0] == '16' else fail())
