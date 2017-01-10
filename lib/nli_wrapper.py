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

# Key: Example key (query parameter 'e')
# Value: Example
#  'n' : title
#  'i' : index for sorting
#  's' : source
EXAMPLES = {
    'h0': {'i' : 0,
           'n' : '00 - Hello World!',
           's' : 'print("Hello World!");'},
    'h1': {'i' : 1,
           'n' : '01 - Function',
           's' : '''def Kernel.main() {
  print("Hello World!");
}

main();
'''},
    'h2': {'i' : 2,
           'n' : '02 - Synth',
           's' : '''def Kernel.main() {
  int i;
  int t = 0;
  for (i = 0; i < 10; i++) {
    print(i);
    t += i;
  }
  print(t);
}

Kernel.main();
Kernel.compile();
Kernel.writeHdl("sum.v");

'''},
    'h3': {'i' : 3,
           'n' : '03 - Memory',
           's' : '''def Kernel.main() {
  int i;
  int t = 0;
  int *p = 0;
  for (i = 0; i < 10; i++) {
    t += i;
  }
  *p = t;
}

int *q = 0;
print(*q);
Kernel.main();
print(*q);

Kernel.compile();
Kernel.writeHdl("sum.v");

'''},
    'h3': {'i' : 3,
           'n' : '03 - Channel',
           's' : '''channel Kernel.in = int #64;
channel Kernel.out = int #64;

def Kernel.main() {
  int #64 arg = *in;
  int i;
  int #64 t = 0;
  for (i = 0; i < arg; i++) {
    t += i;
  }
  *out = t;
}

Kernel.compile();
Kernel.writeHdl("sum.v");

'''},
    'h4': {'i' : 4,
           'n' : '04 - Test',
           's' : '''channel Kernel.in = int;
channel Kernel.out = int;

def Kernel.f(int arg) (int) {
  int i;
  int t = 0;
  for (i = 0; i < arg; i++) {
    t += i;
  }
  return t;
}

def Kernel.main() {
  *out = f(*in);
}

Kernel.compile();
Kernel.writeHdl("sum.v");

object T = Kernel.clone();
def T.main() {
  assert(f(10) == 45);
}

T.main();
T.compile();
T.writeHdl("sum_test.v");

'''},
    'h5': {'i' : 5,
           'n' : '05 - Thread',
           's' : '''channel Kernel.req = int;
channel Kernel.resp = int;

def Kernel.f() {
  *resp = *req + 1;
}

def Kernel.g() {
  *req = 10;
  print(*resp);
}

thread Kernel.t1 = f();
thread Kernel.t2 = g();

Kernel.compile();
Kernel.writeHdl("thr.v");
'''},
    'h6': {'i' : 6,
           'n' : '06 - Member',
           's' : '''object O = Kernel.clone();
object M = Kernel.clone();
object O.M = M;
def M.f(int a) (int) {
  return a + 1;
}

def O.main() {
  print(M.f(10));
}

O.compile();
O.writeHdl("call.v");
'''},
    'h7': {'i' : 7,
           'n' : '07 - External port',
           's' : '''object L = Kernel.clone();

def L.f(bool b) [ output = "led" ] {
  // print(b);
}

def L.main() {
  bool b = false;
  while (true) {
    wait(10000000);
    f(b);
    b = ~b;
  }
}

L.compile();
L.writeHdl("led.v");
'''},
    'h8': {'i' : 8,
           'n' : '08 - Embedded module',
           's' : '''object M = Kernel.clone();

def M.my_wait(int cycles) [
    resource = "wait_cycles",
    verilog = "nli_wait.v",
    ack = "ack",
    file= "copy",
    module= "wait_cycles" ] {
  print(cycles);
}

def M.main() {
  my_wait(10);
}

M.compile();
M.writeHdl("wait.v");
'''},
    'h9': {'i' : 9,
           'n' : '09 - Misc',
           's' : '''object M = Kernel.clone();

def M.main() {
  int i;
  for (i = 0; i < 10; i++) {
  }
}

M.setSynthParam("resetPolarity", "0");
M.setDump("zz");
M.compile();
M.writeHdl("dummy.v");
M.writeHdl("dummy.cpp");
'''},
    'default': {'i' : 999,
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
    for key, value in EXAMPLES.items():
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
