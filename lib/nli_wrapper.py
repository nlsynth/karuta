#! /usr/bin/python

import cgi
import os
import sys
import tempfile

def RunNLI(src):
    bin = os.getenv("NLI_BINARY")

    tf = tempfile.mktemp()
    ofh = open(tf, 'w')
    ofh.write(src)
    ofh.close()

    cmd = bin + " --vanilla " + tf + " > output"
    os.system(cmd)
    os.unlink(tf)

    print "OUTPUT:<br>"
    ifh = open("output", "r")
    for line in ifh:
        line = line.replace("\n", "<br>")
        print line


def Render(is_post):
    if is_post:
        form = cgi.FieldStorage()
    else:
        form = {}
    if 's' in form:
        src = form['s'].value
    else:
        src = """print("Hello World!");"""

    version = os.getenv("NLI_VERSION")

    print \
"""<html>%s<form id=\"nli\" method=\"POST\" action=\"\">
<textarea name=\"s\" cols=100 rows=10>
%s
</textarea>
<input type=\"submit\" value=\"run\">
</form>
""" % (version, src)

    if is_post:
        RunNLI(src)
    print "</html>"

    sys.stdout.flush()


if len(sys.argv) > 1 and sys.argv[1] == "get":
    Render(False)
else:
    # For POST method.
    print "Content-type: text/html\n\n"
    Render(True)
