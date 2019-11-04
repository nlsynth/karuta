#
LIB_FILES = ["karuta.in", "default-isynth.karuta", "karuta_wait.v", "karuta_exit.v", "karuta_server.py", "karuta_wrapper.py", "karuta_examples.py","fp/fp16raddsub.v",  "fp/fp16rmul.v", "fp/fp16r.karuta", "fp/fp16b.karuta", "fp/fp16baddsub.v",  "fp/fp16bmul.v"]

def GetFiles(base_dir):
    files = []
    for fn in LIB_FILES:
        files.append(base_dir + fn)
    return files
