#! /usr/bin/python

# This is basically ylwrap.
import filecmp
import os
import shutil
import tempfile

r = os.system("bison -y -d -g -p z_yy src/fe/parser.ypp")
if r != 0:
    exit(r)

def Copy(sfn, ofn, skipCopy):
    tf = tempfile.mkstemp()
    tfd = tf[0]
    tfn = tf[1]
    sfh = open(sfn, 'r')
    for line in sfh:
        line = line.replace("YY_Y_TAB_H", "YY_SRC_FE_LIBPARSE_LA_PARSER_HPP")
        line = line.replace("y.tab.c", "src/fe/libparse_la-parser.cpp")
        # kludge not to replace an occurence in the comment.
        if not line.startswith(' '):
            line = line.replace("y.tab.h", "src/fe/libparse_la-parser.hpp")
        os.write(tf[0], line)
    os.close(tfd)
    if not skipCopy or not os.path.exists(ofn) or not filecmp.cmp(tfn, ofn):
        shutil.copy(tfn, ofn)
    else:
        print "skipping copy to " + ofn
    os.unlink(sfn)

        
Copy("y.tab.c", "src/fe/libparse_la-parser.cpp", False)
Copy("y.tab.h", "src/fe/libparse_la-parser.hpp", True)
