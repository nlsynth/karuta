#! /usr/bin/python3

# Playground server for Karuta

from http.server import CGIHTTPRequestHandler
from http.server import HTTPServer
import os
import os.path
from socketserver import ThreadingMixIn
import sys
import tempfile
import urllib


import karuta_wrapper

workdir = '/tmp'
karuta_version = 'karuta-0.0.0-unknown'
karuta_interpreter = '../karuta'
log_fn = workdir + '/karuta.log'

if sys.version_info[0] == 2:
    print("please use python3")
    exit()


def scrape_version():
    tf = tempfile.mktemp()
    if os.system(karuta_interpreter + ' --version | head -n 1 > ' + tf):
        return karuta_version
    rf = open(tf, 'r')
    karuta_version = rf.readline()
    rf.close()
    karuta_version = karuta_version[:-1]
    os.unlink(tf)
    return karuta_version


def log_message(msg):
    log_fh = open(log_fn, 'a')
    log_fh.write(msg)
    log_fh.close()


class KarutaServerHandler(CGIHTTPRequestHandler):
    def do_GET(self):
        if self.path.startswith('/o/'):
            return self.ServeOutput()
        if os.path.basename(self.path) == "nl.jpg":
            return self.ServeLogo()
        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.end_headers()

        w = karuta_wrapper.KarutaWrapper(False, self.wfile)
        qs = urllib.parse.parse_qs(urllib.parse.urlparse(self.path).query)
        w.Render(qs)

    def do_POST(self):
        # DIR, PATH
        self.cgi_info = '', 'karuta_wrapper.py'
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

    def ServeLogo(self):
        self.send_response(200)
        self.send_header('Content-type', 'image/jpeg')
        self.end_headers()
        self.wfile.write(bytes(open('nl.jpg', 'rb').read()))

    def log_message(self, format, *args):
        super().log_message(format, *args)
        log_message("%s - - [%s] %s\n" %
                    (self.address_string(),
                     self.log_date_time_string(),
                     format%args))

class ThreadingServer(ThreadingMixIn, HTTPServer):
    pass

if __name__ == '__main__':
    os.environ['KARUTA_VERSION'] = scrape_version()
    os.environ['KARUTA_BINARY'] = karuta_interpreter
    os.environ['KARUTA_WORK'] = workdir
    print(os.getenv('KARUTA_VERSION'))
    httpd = ThreadingServer(("0.0.0.0", 8000), KarutaServerHandler)
    httpd.serve_forever()
