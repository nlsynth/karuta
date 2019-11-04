#
BASE_FILES = ["karuta.in", "default-isynth.karuta", "karuta_wait.v", "karuta_exit.v"]

FP_LIB_FILES = ["fp/fp16raddsub.v", "fp/fp16rmul.v", "fp/fp16r.karuta", "fp/fp16b.karuta", "fp/fp16baddsub.v", "fp/fp16bmul.v"]

PLAY_GROUND_SERVER = ["karuta_server.py", "karuta_wrapper.py", "karuta_examples.py", "make_examples.py"]

LIB_FILES = BASE_FILES + FP_LIB_FILES + PLAY_GROUND_SERVER

def GetFiles(base_dir):
    files = []
    for fn in LIB_FILES:
        files.append(base_dir + fn)
    return files
