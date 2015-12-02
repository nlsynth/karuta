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

# Key: Example key (query parameter 'e')
# Value: Example
#  'n' : title
#  'i' : index for sorting
#  's' : source
EXAMPLES = {
    'h': {'i' : 0,
          'n' : 'Hello World!',
          's' : 'print("Hello World!");'},
    'default': {'i' : 1,
                'n' : 'Synth example',
         's' : '''def main() {
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
'''}
}

def GetExampleSource(qs):
    tmpl = (qs.get('e', ['']))[0]
    if not tmpl:
        tmpl = ''
    if tmpl in EXAMPLES:
        e = EXAMPLES[tmpl]
    else:
        e = EXAMPLES['default']
    return e['s']

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

def RenderExampleOptions(ofh, qs):
    temp = []
    for key, value in EXAMPLES.iteritems():
        temp.append([key, value])
    s = sorted(temp, key=lambda k: (k[1])['i'])
    for v in s:
        key = v[0]
        value = v[1]
        tmpl = (qs.get('e', ['']))[0]
        if tmpl == key:
            selected = 'selected'
        else:
            selected = ''
        ofh.write('''
<option value="%s" %s>%s</option>
        ''' % (key, selected, value['n']))

def Render(ofh, is_post, qs):
    prev_runid = None
    if qs.get('r'):
        prev_runid = qs.get('r')[0]

    if is_post:
        form = cgi.FieldStorage()
    else:
        form = {}
    if 's' in form:
        src = form['s'].value
    elif prev_runid:
        src = GetSourceFromRun(prev_runid)
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
<select name="e">''')
    RenderExampleOptions(ofh, qs)
    ofh.write('''
</select>
<input type="submit" value="Load code">
</form>
''')
    if prev_runid:
        ShowPreviousOutput(ofh, prev_runid)

    if is_post:
        RunNLI(ofh, src)
    ofh.write('</body></html>')

    ofh.flush()


if __name__ == '__main__':
    # For POST method.
    print "Content-type: text/html\n\n"
    Render(sys.stdout, True, {})
