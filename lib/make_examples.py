# -*- coding: utf-8 -*-

# collects files under examples

import glob
import os

files = glob.glob("example_srcs/*.karuta")

m = {}

def proc(fn):
    desc = ""
    src = ""
    k = os.path.basename(fn)
    index = -1
    doCompile = True
    for line in open(fn):
        if line.startswith("##") or line.startswith("//#"):
            line = line[:-1]
            t = line.find("key:")
            if t > -1:
                k = line[t + 4:]
                continue
            t = line.find("index:")
            if t > -1:
                index = int(line[t + 6:])
                continue
            t = line.find("compile:")
            if t > -1:
                doCompile = bool(int(line[t + 8:]))
                continue
            desc = line
            continue
        src = src + line
    if desc == "":
        return (None, None)
    v = {}
    v['s'] = src
    if desc:
        v['n'] = desc[3:]
    else:
        v['n'] = ''
    if index > -1:
        v['i'] = str(index)
    if doCompile:
        v['c'] = True
    else:
        v['c'] = False
    return (k, v)

index = 100

for fn in files:
    (k, v) = proc(fn)
    if not k:
        continue
    if not 'i' in v:
        v['i'] = str(index)
    m[k] = v
    index = index + 1


print("# built with make_examples.py")
print("EXAMPLES =" + str(m))
