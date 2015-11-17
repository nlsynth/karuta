#! /usr/bin/python

# extracts document annotated in the source files.
# TO BE IMPLEMENTED

import glob

sections = {}

def process_file(fn):
    section = ""
    section_name = ""
    in_section = False
    for line in open(fn, 'r'):
        if line[0:2] != "//" or line[0:3] == "///":
            # end of a section (and possibly new section)
            if section:
                sections[section_name] = section
                section = ""
            in_section = False
        if line[0:3] == "///":
            in_section = True
            section_name = line[3:]
        if in_section:
            line = line[3:]
            section += line


files=glob.glob("src/*.cpp") + glob.glob("src/*/*.cpp")

for fn in files:
    process_file(fn)

for section in sections:
    print sections[section]

