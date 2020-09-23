import sys
import subprocess
import re

with open('.test.c', 'w') as c:
    c.write('const int C=123; int I=1; const char *s="hi";')

cmd = sys.argv[2:] + ['-S', '.test.c']
run = subprocess.run(cmd)

with open('.test.s', 'r') as s:
    asm = s.read()

def x(arg, pattern, func):
    if sys.argv[1] == arg:
        m = re.search(pattern, asm, re.M)
        if m:
            print(func(m))
    elif sys.argv[1] == 'all':
        m = re.search(pattern, asm, re.M)
        print(f'{arg}: {func(m) if m else "?"}')
    
x('TEXT', r'^\s+(\.text)\b', lambda m: m[1])
x('DATA', r'^\s+(\.data)\b', lambda m: m[1])
x('LABEL_SUFFIX', r'^_?C(:)?', lambda m: m[1])
x('GLOBL', r'^\s+(\.globl)\s+_?I\b', lambda m: m[1]) 
x('GSYM_PREFIX', r'^(_?)C:?', lambda m: m[1])
x('RODATA', r'^\s+(\.section)\b.*(\.rodata|__TEXT,__const)', lambda m: m[1] + ' ' + m[2])
x('TYPE', r'^\s+(\.type)\s+_?I\s*,\s*@\w+', lambda m: m[1] + ' $1,@$2')
x('SIZE', r'^\s+(\.size)\s+_?I\s*,\s*\d+', lambda m: m[1] + ' $1,$2')
x('LSYM_PREFIX', r'^\.?L', lambda m: m[0])

sys.exit(run.returncode)
