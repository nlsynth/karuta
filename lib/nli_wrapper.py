#! /usr/bin/python

# This file can be either
#  (1) import-ed from nli_server and serve GET method.
#  (2) executed from POST handler in nli_server.

import cgi
import os
import sys
import tempfile

def RunNLI(ofh, src):
    bin = os.getenv('NLI_BINARY')

    srcf = tempfile.mktemp()
    srcfh = open(srcf, 'w')
    srcfh.write(src)
    srcfh.close()

    cmd = bin + ' --vanilla ' + srcf + ' > output'
    os.system(cmd)
    os.unlink(srcf)

    ofh.write('OUTPUT:<br>\n')
    ifh = open('output', 'r')
    for line in ifh:
        line = line.replace('\n', '<br>')
        ofh.write(line + '\n')


def Render(ofh, is_post, qs):
    if is_post:
        form = cgi.FieldStorage()
    else:
        form = {}
    if 's' in form:
        src = form['s'].value
    else:
        tmpl = qs.get('e', [''])
        if tmpl[0] == 's':
            src = '''def main() {}
compile();
'''
        else:
            src = 'print("Hello World!");'

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
