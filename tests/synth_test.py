import os
import os.path
import sys

def GenerateScript(vfn, ys, ofn):
    ofh = open(ys, 'w')
    ofh.write("verilog_defines -DSTRIP_SHELL=1\n")
    ofh.write("read_verilog %s\n" % vfn)
    ofh.write("hierarchy; proc; opt; techmap; opt\n")
    ofh.write("write_verilog %s; clean\n" % ofn)
    ofh.close()

def CheckLog(ofn, ylog):
    if os.path.isfile(ofn) and os.path.isfile(ylog):
        return True
    return False

def Process(vfn):
    ys = vfn + ".ys"
    ofn = "/tmp/a-synth.v"
    ylog = "/tmp/ylog"
    try:
        os.unlink(ylog)
        os.unlink(ofn)
    except:
        pass
    GenerateScript(vfn, ys, ofn)
    os.system("yosys " + ys + " > " + ylog)
    return CheckLog(ofn, ylog)


if __name__ == '__main__':
    if len(sys.argv) > 1:
        r = Process(sys.argv[1])
        if r:
            print("Success")
        else:
            print("Failed")
