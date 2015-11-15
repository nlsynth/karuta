#! /usr/bin/python2

# This file can be invoked either
#  (1) import-ed from nli_server and serve GET method.
#  (2) executed from POST handler in nli_server.

import cgi
import os
import sys
import tempfile
import time


def GetExampleSource(qs):
    tmpl = (qs.get('e', ['']))[0]
    if tmpl == 's':
        return '''def main() {
}

compile();
'''
    else:
        return 'print("Hello World!");'

def GetRunID():
    return 'run-' + str(time.time()) + '-' + str(os.getpid())

def GetMarker(runid):
    return 'marker:' + runid + ':'

def CopyOutput(ifh, marker, runid, ofh):
    for line in ifh:
        if line.find(marker) == 0:
            line = line[len(marker):-1]
            line = ('<a href="/o/' + runid + '/' + line + '">' +
                    line + '</a><br>')
        line = line.replace('\n', '<br>')
        ofh.write(line + '\n')

def RunNLI(ofh, src):
    bin = os.getenv('NLI_BINARY')
    workdir = os.getenv('NLI_TEMP')
    runid = GetRunID()
    rundir = workdir + '/' + runid
    os.mkdir(rundir)

    srcf = tempfile.mktemp()
    srcfh = open(srcf, 'w')
    srcfh.write(src)
    srcfh.close()

    marker = GetMarker(runid)

    output = rundir + '/output'

    cmd = (bin + ' --root=' + rundir + ' ' +
           '--output_marker=' + marker + ' ' +
           '--timeout=3 ' +
           srcf +
           ' > ' + output)
    os.system(cmd)
    os.unlink(srcf)

    ofh.write('OUTPUT:<br>\n')
    ifh = open(output, 'r')
    CopyOutput(ifh, marker, runid, ofh)

def Render(ofh, is_post, qs):
    if is_post:
        form = cgi.FieldStorage()
    else:
        form = {}
    if 's' in form:
        src = form['s'].value
    else:
        src = GetExampleSource(qs)

    version = os.getenv('NLI_VERSION')

    ofh.write(
'''<html><body>%s<br>\n''' % version)

    ofh.write(
'''<form id="src" method="POST" action="">
<textarea name="s" cols=100 rows=10>
%s
</textarea>
<input type="submit" value="run">
</form>
''' % src)

    ofh.write(
'''<form id="example" method="GET" action="">
<select name="e">
<option value="h">hello world</option>
<option value="s">synth</option>
</select>
<input type="submit" value="update">
</form>
''')

    if is_post:
        RunNLI(ofh, src)
    ofh.write('</body></html>')

    ofh.flush()


if __name__ == '__main__':
    # For POST method.
    print "Content-type: text/html\n\n"
    Render(sys.stdout, True, {})
