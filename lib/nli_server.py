#! /usr/bin/python2

# HTTP server for Neon Light (This assumes Python2 for now)

import CGIHTTPServer
import BaseHTTPServer
import os
import shutil
import sys
import urllib
import urlparse
import tempfile

import nli_wrapper

tmpdir = '/tmp'
nli_version = 'nli-0.0.0-unknown'
nli_interpreter = '../nli'


def scrape_version():
    tf = tempfile.mktemp()
    if os.system(nli_interpreter + ' --version | head -n 1 > ' + tf):
        return nli_version
    rf = open(tf, 'r')
    nli_version = rf.readline()
    rf.close()
    nli_version = nli_version[:-1]
    os.unlink(tf)
    return nli_version


class NliServerHandler(CGIHTTPServer.CGIHTTPRequestHandler):
    def do_GET(self):
        if self.path.startswith('/o/'):
            return self.ServeOutput()
        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.end_headers()

        qs = urlparse.parse_qs(urlparse.urlparse(self.path).query)
        tf = tempfile.mktemp()
        tfh = open(tf, 'w')
        nli_wrapper.Render(tfh, False, qs)
        tfh.close()

        rf = open(tf, 'r')
        for line in rf:
            self.wfile.write(line)
        os.unlink(tf)

    def do_POST(self):
        # DIR, PATH
        self.cgi_info = '', 'nli_wrapper.py'
        self.run_cgi()

    def ServeOutput(self):
        p = self.path[3:]
        fn = tmpdir + '/' + p
        self.send_response(200)
        if fn[-5:] == '.html':
            self.send_header('Content-type', 'text/html')
        else:
            self.send_header('Content-type', 'text/plain')
        self.end_headers()

        for line in open(fn, 'r'):
            self.wfile.write(line)

if __name__ == '__main__':
    os.environ['NLI_VERSION'] = scrape_version()
    os.environ['NLI_BINARY'] = nli_interpreter
    os.environ['NLI_TEMP'] = tmpdir
    print(os.getenv('NLI_VERSION'))
    httpd = BaseHTTPServer.HTTPServer(('0.0.0.0', 8000), NliServerHandler)
    httpd.serve_forever()
