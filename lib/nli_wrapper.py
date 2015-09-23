#! /usr/bin/python

import cgi
import os
import sys
import tempfile

bin = os.getenv("NLI_BINARY")
form = cgi.FieldStorage()
if 's' in form:
    src = form['s'].value
else:
    src = """print("Hello World\n");"""

version = os.getenv("NLI_VERSION")

print "Content-type: text/html\n\n"
print \
"""<html>%s<form id=\"nli\" method=\"POST\" action=\"run\">
<textarea name=\"s\" cols=100 rows=10>
%s
</textarea>
<input type=\"submit\" value=\"run\">
</form></html>
""" % (version, src)

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

sys.stdout.flush()
