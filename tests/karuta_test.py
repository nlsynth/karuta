import os
import re
import tempfile

import synth_test

# Set from external.
iroha_binary=""
with_synth_test=False

karuta_binary="../karuta-bin"
tmp_prefix = "/tmp"
default_tb="test_tb.v"
verilog_compiler="iverilog"


def FileBase(fn):
    bn = os.path.basename(fn)
    # assumes .karuta
    return bn[:-7]


def CheckLog(fn, exp):
    num_fails = 0
    done_stat = 0
    has_exp = False
    ifh = open(fn, "r")
    for line in ifh:
        if re.search("ASSERTION FAILURE", line):
            num_fails = num_fails + 1
        if re.search("ASSERTION UNDEFINED", line):
            num_fails = num_fails + 1
        if re.search("KARUTA DONE", line):
            done_stat = 1
            if re.search("error", line):
                num_fails = num_fails + 1
        if exp and re.search(exp, line):
            has_exp = True
    if exp and not has_exp:
        num_fails = num_fails + 1
    return {"num_fails":num_fails,
            "done_stat":done_stat}


def ReadTestInfo(fn):
    test_info = {"exp_fails":0,
                 "vl_exp_fails":0,
                 "karuta_ignore_errors":0,
                 "exp_abort":0}
    dn = os.path.dirname(fn)
    if dn != "":
        dn = dn + "/"
    test_info["dirname"] = dn
    ifh = open(fn, "r")
    for line in ifh:
        m = re.search("KARUTA_EXPECTED_ERRORS: (\d+)", line)
        if m:
            test_info["exp_fails"] = int(m.group(1))
        m = re.search("VERILOG_EXPECTED_ERRORS: (\d+)", line)
        if m:
            test_info["vl_exp_fails"] = int(m.group(1))
        m = re.search("VERILOG_EXPECTED_OUTPUT: (\S+)", line)
        if m:
            test_info["vl_exp_output"] = m.group(1)
        m = re.search("VERILOG_OUTPUT: (\S+)", line)
        if m:
            test_info["verilog"] = m.group(1)
        m = re.search("VERILOG_TB: (\S+)", line)
        if m:
            test_info["verilog_tb"] = m.group(1)
        m = re.search("KARUTA_IGNORE_ERRORS:", line)
        if m:
            test_info["karuta_ignore_errors"] = 1
        m = re.search("KARUTA_TIMEOUT: (\d+)", line)
        if m:
            test_info["karuta_timeout"] = int(m.group(1))
        m = re.search("KARUTA_EXPECT_ABORT:", line)
        if m:
            test_info["exp_abort"] = 1
        m = re.search("KARUTA_SPLIT_TEST: (\S+)", line)
        if m:
            test_info["split_info"] = m.group(1)
        m = re.search("SELF_SHELL:", line)
        if m:
            test_info["self_shell"] = 1
            test_info["verilog"] = FileBase(fn) + ".v"
    return test_info


def GetVerilogCompileCommand(dut_fn, tb_fn, test_bin_fn):
    cmd = (verilog_compiler + " -o " + test_bin_fn + " " +
           dut_fn + " " + tb_fn + " -I../lib")
    return cmd


def CheckVerilog(dut_fn, source_fn, summary, test_info):
    test_bin_fn = tempfile.mktemp()
    test_log_fn = tempfile.mktemp()
    if "self_shell" in test_info:
        tb_fn = ""
    elif "verilog_tb" in test_info:
        tb_fn = test_info["dirname"] + test_info["verilog_tb"]
    else:
        tb_fn = default_tb
    cmd = GetVerilogCompileCommand(dut_fn, tb_fn, test_bin_fn)
    print("  compiling " + dut_fn + "(" + cmd + ")")
    os.system(cmd)
    if not os.path.isfile(test_bin_fn):
        summary.AddVerilogCompileFailure(source_fn)
        return
    test_cmd = test_bin_fn + ">" + test_log_fn
    print ("  running verilog executable " + test_bin_fn +
           "(" + test_cmd + ")")
    os.system(test_cmd)
    exp = None
    if "vl_exp_output" in test_info:
        exp = test_info["vl_exp_output"]
    res = CheckLog(test_log_fn, exp)
    if with_synth_test:
        print("  testing synthesizability " + dut_fn)
        sr = synth_test.Process(dut_fn)
        if not sr:
            print("Failed!")
            e = 0
            if "num_fails" in res:
                e = res["num_fails"]
            res["num_fails"] = e + 1
    num_fails = res["num_fails"]
    exp_fails = test_info["vl_exp_fails"]
    summary.AddVerilogResult(source_fn, num_fails,
                             test_info["karuta_ignore_errors"],
                             exp_fails)
    try:
        os.unlink(test_bin_fn)
        os.unlink(test_log_fn)
    except:
        pass


def GetKarutaCommand(source_fn, tf, test_info):
    vanilla = "--vanilla"
    if "verilog" in test_info:
        # verilog tests requires imported modules.
        vanilla = ""
    timeout = "1000"
    if "karuta_timeout" in test_info:
        timeout = str(test_info["karuta_timeout"])
    cmd = "KARUTA_DIR=../lib "
    cmd += karuta_binary + " " + source_fn + " " + vanilla
    if iroha_binary != "":
        cmd += " --iroha_binary " + iroha_binary
    cmd += " --root " + tmp_prefix
    cmd += " --timeout " + timeout + " "
    cmd += " --print_exit_status "
    if "self_shell" in test_info:
        cmd += " --compile --with_shell "
    else:
        cmd += " --module_prefix=mod "
    cmd += " > " + tf
    return cmd


class KarutaTest():
    def __init__(self, source_fn):
        self.source_fn = source_fn

    def RunTest(self, summary):
        test_info = ReadTestInfo(self.source_fn)
        tf = tempfile.mktemp()
        cmd = GetKarutaCommand(self.source_fn, tf, test_info)
        if "verilog" in test_info:
            try:
                os.unlink(tmp_prefix + "/" + test_info["verilog"])
            except:
                pass
        print("executing test " + self.source_fn)
        if "split_info" in test_info:
            print(" split: " + str(test_info["split_info"]))
        print(" command line=" + cmd)
        rv = os.system(cmd)
        if rv:
            summary.AddAbort(rv)
        if rv == 0 and "verilog" in test_info:
            CheckVerilog(tmp_prefix + "/" + test_info["verilog"],
                         self.source_fn,
                         summary, test_info)
        res = CheckLog(tf, None)
        num_fails = res["num_fails"]
        done_stat = res["done_stat"]
        exp_fails = test_info["exp_fails"]
        exp_abort = test_info["exp_abort"]
        summary.AddResult(self.source_fn,
                          num_fails,
                          test_info["karuta_ignore_errors"],
                          done_stat, exp_abort, exp_fails)
        os.unlink(tf)
