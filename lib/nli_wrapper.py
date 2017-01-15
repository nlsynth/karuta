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

class NliWrapper(object):
    def __init__(self, isCgi, ofh):
        self.isCgi = isCgi
        self.ofh = ofh

    def Render(self, qs):
        ofh = self.ofh
        prev_runid = None
        if qs.get('r'):
            prev_runid = qs.get('r')[0]

        if self.isCgi:
            form = cgi.FieldStorage()
        else:
            form = {}
        if 's' in form:
            src = form['s'].value
        elif prev_runid:
            src = self.GetSourceFromRun(prev_runid)
        else:
            src = self.GetExampleSource(qs)

        version = os.getenv('NLI_VERSION')

        self.Write('''
<html><head><title>Neon Light Playground</title></head><body>
<h1>Neon Light Playground</h1>
%s<br>\n
''' % version)

        self.Write(
'''<form id="src" method="POST" action="">
<textarea name="s" cols=100 rows=20>
%s
</textarea>
<input type="submit" value="Run">
</form>
''' % html.escape(src))

        self.Write(
'''<form id="example" method="GET" action="">
<select name="e">''')
        self.RenderExampleOptions(qs)
        self.Write('''
</select>
<input type="submit" value="Load code">
</form>
    ''')
        if prev_runid:
            self.ShowPreviousOutput(prev_runid)

        if self.isCgi:
            self.RunNLI(src)
        self.Write('</body></html>')

        self.ofh.flush()

    def Write(self, s):
        if self.isCgi:
            self.ofh.write(s)
        else:
            # writes to network
            self.ofh.write(bytes(s, 'utf-8'))

    def RunNLI(self, src):
        bin = os.getenv('NLI_BINARY')
        workdir = os.getenv('NLI_TEMP')
        runid = self.GetRunID()
        rundir = self.GetRunDir(runid)
        os.mkdir(rundir)

        srcf = rundir + '/src'
        srcfh = open(srcf, 'w')
        srcfh.write(src)
        srcfh.close()

        marker = self.GetMarker(runid)

        outputfn = rundir + '/output'

        cmd = (bin + ' --root=' + rundir + ' ' +
               '--output_marker=' + marker + ' ' +
               '--timeout=3000 ' +
               srcf +
               ' > ' + outputfn + ' 2>&1')
        os.system(cmd)

        self.Write('<a href="/?r=' + runid +
                  '">Link to this run</a><br><br>')

        self.Write('OUTPUT:<br>\n')
        ifh = open(outputfn, 'r')
        self.CopyOutput(ifh, marker, runid)

    def GetRunID(self):
        return 'run-' + str(time.time()) + '-' + str(os.getpid())

    def GetMarker(self, runid):
        return 'marker:' + runid + ':'

    def GetRunDir(self, runid):
        workdir = os.getenv('NLI_TEMP')
        return workdir + '/' + runid

    def GetSourceFromRun(self, runid):
        rundir = self.GetRunDir(runid)
        srcfn = rundir + '/src'
        src = ''
        for line in open(srcfn, 'r'):
            src += line
        return src

    def CopyOutput(self, ifh, marker, runid):
        for line in ifh:
            if line.find(marker) == 0:
                line = line[len(marker):-1]
                line = html.escape(line)
                line = ('<a href="/o/' + runid + '/' + line + '">' +
                        line + '</a><br>')
            else:
                line = html.escape(line)
                line = line.replace('\n', '<br>')
            self.Write(line + '\n')

    def ShowPreviousOutput(self, runid):
        self.Write('PREVIOUS OUTPUT:<br>\n')
        rundir = self.GetRunDir(runid)
        outputfn = rundir + '/output'
        marker = self.GetMarker(runid)
        ifh = open(outputfn, 'r')
        self.CopyOutput(ifh, marker, runid)

    def RenderExampleOptions(self, qs):
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
            self.Write('''
<option value="%s" %s>%s</option>
        ''' % (key, selected, value['n']))

    def GetExampleSource(self, qs):
        tmpl = (qs.get('e', ['']))[0]
        if not tmpl:
            tmpl = ''
        if tmpl in nli_examples.EXAMPLES:
            e = nli_examples.EXAMPLES[tmpl]
        else:
            e = nli_examples.EXAMPLES['default']
        return e['s']

if __name__ == '__main__':
    # For POST method.
    print("Content-type: text/html\n\n")
    w = NliWrapper(True, sys.stdout)
    w.Render({})
