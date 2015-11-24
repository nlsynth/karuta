#! /usr/bin/python2

# This file can be invoked either
#  (1) import-ed from nli_server and serve GET method.
#  (2) executed from POST handler in nli_server.

import cgi
import os
import sys
import tempfile
import time
# use html package when I migrate to python 3.x
import xml.sax.saxutils


def GetExampleSource(qs):
    tmpl = (qs.get('e', ['']))[0]
    if tmpl == 'h':
        return 'print("Hello World!");'
    else:
        return '''def main() {
  int i;
  int s = 0;
  for (i = 0; i < 10; ++i) {
    s += i;
  }
  // TODO: Do real I/O.
  print(s);
}

// Synthesize and output.
compile();
writeHdl("a.v");
writeHdl("a.html");

// Run on interpreter mode.
main();
'''

def GetRunDir(runid):
    workdir = os.getenv('NLI_TEMP')
    return workdir + '/' + runid

def GetSourceFromRun(runid):
    rundir = GetRunDir(runid)
    srcfn = rundir + '/src'
    src = ''
    for line in open(srcfn, 'r'):
        src += line
    return src

def GetRunID():
    return 'run-' + str(time.time()) + '-' + str(os.getpid())

def GetMarker(runid):
    return 'marker:' + runid + ':'

def CopyOutput(ifh, marker, runid, ofh):
    for line in ifh:
        if line.find(marker) == 0:
            line = line[len(marker):-1]
            line = xml.sax.saxutils.escape(line)
            line = ('<a href="/o/' + runid + '/' + line + '">' +
                    line + '</a><br>')
        else:
            line = xml.sax.saxutils.escape(line)
            line = line.replace('\n', '<br>')
        ofh.write(line + '\n')

def ShowPreviousOutput(ofh, runid):
    ofh.write('PREVIOUS OUTPUT:<br>\n')
    rundir = GetRunDir(runid)
    outputfn = rundir + '/output'
    marker = GetMarker(runid)
    ifh = open(outputfn, 'r')
    CopyOutput(ifh, marker, runid, ofh)

def RunNLI(ofh, src):
    bin = os.getenv('NLI_BINARY')
    workdir = os.getenv('NLI_TEMP')
    runid = GetRunID()
    rundir = GetRunDir(runid)
    os.mkdir(rundir)

    srcf = rundir + '/src'
    srcfh = open(srcf, 'w')
    srcfh.write(src)
    srcfh.close()

    marker = GetMarker(runid)

    outputfn = rundir + '/output'

    cmd = (bin + ' --root=' + rundir + ' ' +
           '--output_marker=' + marker + ' ' +
           '--timeout=3000 ' +
           srcf +
           ' > ' + outputfn + ' 2>&1')
    os.system(cmd)

    ofh.write('<a href="/?r=' + runid +
              '">Link to this run</a><br><br>')

    ofh.write('OUTPUT:<br>\n')
    ifh = open(outputfn, 'r')
    CopyOutput(ifh, marker, runid, ofh)

def Render(ofh, is_post, qs):
    runid = None
    if qs.get('r'):
        runid = qs.get('r')[0]
    else:
        runid = None

    if is_post:
        form = cgi.FieldStorage()
    else:
        form = {}
    if 's' in form:
        src = form['s'].value
    elif runid:
        src = GetSourceFromRun(runid)
    else:
        src = GetExampleSource(qs)

    version = os.getenv('NLI_VERSION')

    ofh.write(
'''<html><head><title>Neon Light</title></head><body>%s<br>\n''' % version)

    ofh.write(
'''<form id="src" method="POST" action="">
<textarea name="s" cols=100 rows=20>
%s
</textarea>
<input type="submit" value="Run">
</form>
''' % xml.sax.saxutils.escape(src))

    ofh.write(
'''<form id="example" method="GET" action="">
<select name="e">
<option value="h">Hello world</option>
<option value="s">Synth</option>
</select>
<input type="submit" value="Load code">
</form>
''')
    if runid:
        ShowPreviousOutput(ofh, runid)

    if is_post:
        RunNLI(ofh, src)
    ofh.write('</body></html>')

    ofh.flush()


if __name__ == '__main__':
    # For POST method.
    print "Content-type: text/html\n\n"
    Render(sys.stdout, True, {})
