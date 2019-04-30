import os
import sys
import subprocess

BIN = os.getenv("KARUTA_BIN")

sys.stdout.flush()

args = [BIN]

while True:
    s = sys.stdin.readline()
    s = s.rstrip()
    if s == "":
        break
    args.append(s)

subprocess.run(args)

sys.stdout.flush()

