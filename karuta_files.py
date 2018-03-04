import sys
sys.path.append("iroha/")
import iroha_files
sys.path.append("tests/")
import test_files

VERSION = "0.3.0wip"

EXTRA = ["README.md", "NEWS", "configure", "Makefile", "config.mk", "karuta", "src/karuta.gyp", "iroha/src/iroha.gyp", "src/fe/parser.ypp", "genparser.py", "karuta_files.py", "docs/LRM.md", "examples/top.karuta"]

LIB_FILES = ["lib/karuta.in", "lib/default-isynth.n", "lib/nli_wait.v", "lib/nli_exit.v", "lib/nli_server.py", "lib/nli_wrapper.py", "lib/nli_examples.py"]

ifiles = iroha_files.GetGypFileList("iroha/src/iroha.gyp")
iextras = iroha_files.GetExtraFileList("iroha/")
nfiles = iroha_files.GetGypFileList("src/karuta.gyp")

tfiles = test_files.GetFiles("tests/")

files = nfiles + EXTRA + LIB_FILES + ifiles + iextras + tfiles

iroha_files.MakeTarBall("karuta-" + VERSION, files)