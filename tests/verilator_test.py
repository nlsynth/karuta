import os

def Process(vfn):
    r = os.system("verilator -cc " + vfn)
    if r:
        return False
    return True
