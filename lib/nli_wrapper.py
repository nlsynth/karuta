#! /usr/bin/python3
# -*- coding: utf-8 -*-

# This file can be invoked either
#  (1) import-ed from nli_server and serve GET method.
#  (2) executed from POST handler in nli_server.

import cgi
import html
import os
import sys
import tempfile
import time

import nli_examples

def GetExampleSource(qs):
    tmpl = (qs.get('e', ['']))[0]
    if not tmpl:
        tmpl = ''
    if tmpl in nli_examples.EXAMPLES:
        e = nli_examples.EXAMPLES[tmpl]
    else:
        e = nli_examples.EXAMPLES['default']
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

def Write(ofh, s):
    if __name__ == '__main__':
        ofh.write(s)
    else:
        ofh.write(bytes(s, 'utf-8'))

def CopyOutput(ifh, marker, runid, ofh):
    for line in ifh:
        if line.find(marker) == 0:
            line = line[len(marker):-1]
            line = html.escape(line)
            line = ('<a href="/o/' + runid + '/' + line + '">' +
                    line + '</a><br>')
        else:
            line = html.escape(line)
            line = line.replace('\n', '<br>')
        Write(ofh, line + '\n')

def ShowPreviousOutput(ofh, runid):
    Write(ofh, 'PREVIOUS OUTPUT:<br>\n')
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
    for key, value in nli_examples.EXAMPLES.items():
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
        Write(ofh, ('''
<option value="%s" %s>%s</option>
        ''' % (key, selected, value['n'])))

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

    s = '''<html><head><title>Neon Light</title></head><body>%s<br>\n''' % version
    Write(ofh, s)

    Write(ofh,
'''<form id="src" method="POST" action="">
<textarea name="s" cols=100 rows=20>
%s
</textarea>
<input type="submit" value="Run">
</form>
''' % html.escape(src))

    Write(ofh,
'''<form id="example" method="GET" action="">
<select name="e">''')
    RenderExampleOptions(ofh, qs)
    Write(ofh, '''
</select>
<input type="submit" value="Load code">
</form>
    ''')
    if prev_runid:
        ShowPreviousOutput(ofh, prev_runid)

    if is_post:
        RunNLI(ofh, src)
    Write(ofh, '</body></html>')

    ofh.flush()


if __name__ == '__main__':
    # For POST method.
    print("Content-type: text/html\n\n")
    Render(sys.stdout, True, {})
