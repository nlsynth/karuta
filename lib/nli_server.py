#! /usr/bin/python

# HTTP server for nli

import CGIHTTPServer
import BaseHTTPServer
import os
import shutil
import sys
import urllib
import tempfile

tmpdir = "/tmp"
nli_version = "nli-0.0.0-unknown"
nli_interpreter = "../nli"


def scrape_version():
    tf = tempfile.mktemp()
    if os.system(nli_interpreter + " --version | head -n 1 > " + tf):
        return nli_version
    rf = open(tf, 'r')
    nli_version = rf.readline()
    rf.close()
    nli_version = nli_version[:-1]
    os.unlink(tf)
    return nli_version


class NliServerHandler(CGIHTTPServer.CGIHTTPRequestHandler):
    def do_GET(self):
        self.send_response(200)
        self.send_header("Content-type", "text/html")
        self.end_headers()
        tf = tempfile.mktemp()
        os.system("./nli_wrapper.py > " + tf)
        rf = open(tf, 'r')
        for line in rf:
            self.wfile.write(line)
        os.unlink(tf)

    def do_POST(self):
        # DIR, PATH
        self.cgi_info = "", "nli_wrapper.py"
        self.run_cgi()

if __name__ == '__main__':
    os.environ["NLI_VERSION"] = scrape_version()
    os.environ["NLI_BINARY"] = nli_interpreter
    print os.getenv("NLI_VERSION")
    HandlerClass = NliServerHandler
    ServerClass = BaseHTTPServer.HTTPServer
    BaseHTTPServer.test(HandlerClass, ServerClass)
