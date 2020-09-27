import argparse
import re
import subprocess
import os


def run(cmd):
    print(' '.join(cmd))
    subprocess.run(cmd, check=True)


def redirect(cmd, out):
    print(' '.join(cmd) + ' > ' + out)
    r = subprocess.run(cmd, check=True, capture_output=True, text=True)
    with open(out, 'w') as f:
        f.write(r.stdout)


def includes(suffix):
    s = ''
    for d in args.incdirs:
        for f in os.listdir(d):
            if f.endswith(suffix):
                s = f'{s} {os.path.join(d, f)}'
    return s


ap = argparse.ArgumentParser()
ap.add_argument('--input', required=True)
ap.add_argument('--output', required=True)
ap.add_argument('--depfile', required=True)
ap.add_argument('--cc', required=True)
ap.add_argument('--m4', required=True)
ap.add_argument('--yasm', required=True)
ap.add_argument('--objfmt', required=True)
ap.add_argument('--incdirs', nargs='*')
ap.add_argument('--defs', nargs='*')

args = ap.parse_args()

with open(args.input) as f:
    asm = f.read()

incdirs = [a for i in args.incdirs for a in ['-I', i]]
defs = args.defs or []


if re.search(r'^dnl\b', asm, re.M):
    m4_defs = ['-D' + d for d in defs]
    s = args.output + '.s'

    redirect([args.m4] + incdirs + m4_defs + [args.input], s)
    run([args.cc, '-c', s, '-o', args.output])

    with open(args.depfile, 'w') as d:
        d.write(f'{s}: {args.input}\n')
        d.write(f'{args.output}: {s}')
        d.write(includes('.m4'))
        d.write('\n')
else:
    yasm_defs = [a for d in defs for a in ['-D', d]]
    
    run([args.yasm, '-f', args.objfmt] + incdirs + [args.input, '-o', args.output])

    with open(args.depfile, 'w') as d:
        d.write(f'{args.output}: {args.input}')
        d.write(includes('.inc'))
        d.write('\n')
