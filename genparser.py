#! /usr/bin/python3

# This is basically ylwrap.
import filecmp
import os
import shutil
import tempfile

# -d produces header file
cmd = "bison -d src/fe/parser.ypp"
print("running: " + cmd)
r = os.system(cmd)
if r != 0:
    print("...failed.")
    exit(r)

def Copy(sfn, ofn, skipCopy):
    tf = tempfile.mkstemp()
    tfd = tf[0]
    tfn = tf[1]
    sfh = open(sfn, 'r')
    for line in sfh:
        line = line.replace("YY_YY_PARSER_TAB_HPP_INCLUDED", "YY_SRC_FE_PARSER_H")
        line = line.replace("parser.tab.cpp", "src/fe/parser.cpp")
        # kludge not to replace an occurence in the comment.
        if not line.startswith(' '):
            line = line.replace("parser.tab.hpp", "src/fe/parser.h")
        os.write(tf[0], line.encode('utf-8'))
    os.close(tfd)
    if not skipCopy or not os.path.exists(ofn) or not filecmp.cmp(tfn, ofn):
        shutil.copy(tfn, ofn)
    else:
        print("skipping copy to " + ofn)
    os.unlink(sfn)

        
Copy("parser.tab.cpp", "src/fe/parser.cpp", False)
Copy("parser.tab.hpp", "src/fe/parser.h", True)
