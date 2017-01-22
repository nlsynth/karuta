#! /usr/bin/python3

# Playground server for Neon Light

from http.server import CGIHTTPRequestHandler
from http.server import HTTPServer
import os
from socketserver import ThreadingMixIn
import tempfile
import urllib


import nli_wrapper

workdir = '/tmp'
nli_version = 'nli-0.0.0-unknown'
nli_interpreter = '../nli'
log_fn = workdir + '/nli.log'


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


def log_message(msg):
    log_fh = open(log_fn, 'w+')
    log_fh.write(msg)
    log_fh.close()


class NliServerHandler(CGIHTTPRequestHandler):
    def do_GET(self):
        if self.path.startswith('/o/'):
            return self.ServeOutput()
        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.end_headers()

        w = nli_wrapper.NliWrapper(False, self.wfile)
        qs = urllib.parse.parse_qs(urllib.parse.urlparse(self.path).query)
        w.Render(qs)

    def do_POST(self):
        # DIR, PATH
        self.cgi_info = '', 'nli_wrapper.py'
        self.run_cgi()

    def ServeOutput(self):
        p = self.path[3:]
        fn = workdir + '/' + p
        if fn[-4:] == '.log':
            self.send_response(404)
            self.end_headers()
            return
        self.send_response(200)
        if fn[-5:] == '.html':
            self.send_header('Content-type', 'text/html')
        else:
            self.send_header('Content-type', 'text/plain')
        self.end_headers()

        for line in open(fn, 'r'):
            self.wfile.write(bytes(line, 'utf-8'))

    def log_message(self, format, *args):
        super().log_message(format, *args)
        log_message("%s - - [%s] %s\n" %
                    (self.address_string(),
                     self.log_date_time_string(),
                     format%args))

class ThreadingServer(ThreadingMixIn, HTTPServer):
    pass

if __name__ == '__main__':
    os.environ['NLI_VERSION'] = scrape_version()
    os.environ['NLI_BINARY'] = nli_interpreter
    os.environ['NLI_WORK'] = workdir
    print(os.getenv('NLI_VERSION'))
    httpd = ThreadingServer(("0.0.0.0", 8000), NliServerHandler)
    httpd.serve_forever()
