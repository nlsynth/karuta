#! /usr/bin/python3
# -*- coding: utf-8 -*-

# This file can be invoked either
#  (1) import-ed from karuta_server and serve GET method.
#  (2) executed from POST handler in karuta_server.

import cgi
from datetime import datetime
import html
import os
import sys
import tempfile
import time

import karuta_examples

class KarutaWrapper(object):
    def __init__(self, isCgi, ofh):
        self.isCgi = isCgi
        self.ofh = ofh
        self.runid = 'run-' + str(time.time()) + '-' + str(os.getpid())
        self.workdir = os.getenv('KARUTA_WORK')

    def Render(self, qs):
        ofh = self.ofh
        prev_runid = None
        if qs.get('r'):
            prev_runid = qs.get('r')[0]

        if self.isCgi:
            form = cgi.FieldStorage()
        else:
            form = {}
        withShell = 'sh' in form
        noCompile = 'nc' in form
        if 's' in form:
            src = form['s'].value
        elif prev_runid:
            src = self.GetSourceFromRun(prev_runid)
        else:
            src = self.GetExampleSource(qs)

        version = os.getenv('KARUTA_VERSION')

        self.Write('''
<html><head>
<title>Karuta Playground</title>
<style>
  body {
  background: #ddfaba
  }
  .codearea {
  background: #cefaba;
  border-radius: 5px;
  font-weight: bold;
  width: 100%%;
  }
</style>
</head>
<body>
<div>
  <a href="." style="text-decoration: none"><h1 style="color: #888844">Karuta Playground</h1></a>\n
  %s
</div>
<img src="nl.jpg" style="float:right">
''' % version)
        self.Write('''(<a href="https://github.com/nlsynth/karuta">Source code on GitHub</a>. <a href="https://karuta.readthedocs.io/en/latest/">Documents on Read the Docs</a>)<br/><br/>\n''')

        self.Write(
'''<form id="src" method="POST" action="">
<textarea name="s" rows=20 class=codearea>
%s
</textarea><br/>
<input type="submit" value="Run">
(Generates shell module for standalone simulation <input type="checkbox" name="sh">.
Executes karuta without --compile option <input type="checkbox" name="nc">.)
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
            self.RunKaruta(src, withShell, noCompile)
        self.Write('</body></html>')

        self.ofh.flush()

    def Write(self, s):
        if self.isCgi:
            self.ofh.write(s)
        else:
            # writes to network
            self.ofh.write(bytes(s, 'utf-8'))

    def RunKaruta(self, src, withShell, noCompile):
        bin = os.getenv('KARUTA_BINARY')
        runid = self.GetRunID()
        rundir = self.GetRunDir(runid)
        os.mkdir(rundir)

        srcf = self.GetSourceFn(runid)
        srcfh = open(srcf, 'w')
        srcfh.write(src)
        srcfh.close()

        logf = self.GetLogFn(runid)
        logfh = open(logf, 'w')
        logfh.write('Host: ' + str(os.environ['REMOTE_HOST']) + '\n')
        logfh.write('Addr: ' + str(os.environ['REMOTE_ADDR']) + '\n')
        logfh.write('Start: ' + str(datetime.now()) + '\n')

        marker = self.GetMarker(runid)

        outputfn = self.GetOutputFn(runid)

        cmd = (bin + ' --root=' + rundir + ' ' +
               '--output_marker=' + marker + ' ' +
               '--timeout=3000 ' +
               srcf)
        if withShell:
            cmd += (' --with_shell --vcd ')
        if not noCompile:
            cmd += (' --compile ')
        cmd += (' > ' + outputfn + ' 2>&1')
        os.system(cmd)
        logfh.write('Cmd: ' + cmd + '\n')
        logfh.write('End: ' + str(datetime.now()) + '\n')
        logfh.close()

        self.Write('<a href="./?r=' + runid +
                  '">Link to this run</a><br><br>')

        self.Write('OUTPUT:<br>\n')
        ifh = open(outputfn, 'r')
        self.CopyOutput(ifh, marker, runid)

    def GetRunID(self):
        return self.runid

    def GetMarker(self, runid):
        return 'marker:' + runid + ':'

    def GetRunDir(self, runid):
        return self.workdir + '/' + runid

    def GetSourceFromRun(self, runid):
        rundir = self.GetRunDir(runid)
        srcfn = self.GetSourceFn(runid)
        src = ''
        for line in open(srcfn, 'r'):
            src += line
        return src

    def CopyOutput(self, ifh, marker, runid):
        for line in ifh:
            if line.find(marker) == 0:
                line = line[len(marker):-1]
                line = html.escape(line)
                line = ('<a href="./o/' + runid + '/' + line + '">' +
                        line + '</a><br>')
            else:
                line = html.escape(line)
                line = line.replace('\n', '<br>')
            self.Write(line + '\n')

    def ShowPreviousOutput(self, runid):
        self.Write('PREVIOUS OUTPUT:<br>\n')
        outputfn = self.GetOutputFn(runid)
        marker = self.GetMarker(runid)
        ifh = open(outputfn, 'r')
        self.CopyOutput(ifh, marker, runid)

    def GetOutputFn(self, runid):
        # This should be reasonablly hard to predict so that bad program
        # will not overwrite it.
        # ditto for GetSourceFn() and GetLogFn()
        rundir = self.GetRunDir(runid)
        return rundir + '/' + runid + '.output'

    def GetSourceFn(self, runid):
        rundir = self.GetRunDir(runid)
        return rundir + '/my_design.karuta'

    def GetLogFn(self, runid):
        rundir = self.GetRunDir(runid)
        return rundir + '/' + runid + '.log'

    def RenderExampleOptions(self, qs):
        temp = []
        for key, value in karuta_examples.EXAMPLES.items():
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
        if tmpl in karuta_examples.EXAMPLES:
            e = karuta_examples.EXAMPLES[tmpl]
        else:
            e = karuta_examples.EXAMPLES['default']
        return e['s']

if __name__ == '__main__':
    # For POST method.
    print('Content-type: text/html\n\n')
    w = KarutaWrapper(True, sys.stdout)
    w.Render({})
