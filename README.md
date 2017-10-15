# Project: Neon Light
Author: Yusuke TABATA (tabata.yusuke@gmail.com)

## What's this?
TL;DR:
    Experimental high level synthesis (HLS) from prototype based object oriented script language to RTL (Verilog) which might become useful for FPGA development...

This software Neon Light (Compiler) takes Neon Light Script language as an input and outputs cirtuits in Verilog RTL.
As of now, this software has too many bugs and unimplemented features. In addition to implementation/documentation quality, many important features are not documented and liable to change.

This software package is under development to explore efficient logic circuit design methodology.

See https://sites.google.com/site/neonlightcompiler/ for some more details.

## Usage

-- Get the code

To check out the code including Iroha submodule.
    > $ git clone --recursive https://github.com/nlsynth/nli
    or
    > $ git submodule update --init
    in nli/ directory.

-- Build

At first, you have to compile the interpreter (nli command).

    > $ ./configure
    > $ make

NOTE: Please make sure you checked out iroha submodule and have iroha/ directory

-- Use

Run tb.n (this example outputs a.v)

    > $ cd examples
    > $ ../nli top.n

Run the output with your Verilog simulator.

    > $ iverilog tb_top.v top.v
    > $ ./a.out # Icarus verilog

(If you do 'make install', nli command will be available at the path you specified)

## Overview
Neon Light Script is an object oriented scripting language. The syntax is similar to JavaScript, Python, Ruby or so on.
Minimum code looks like as follows.

     def Kernel.main() {
       // Do some computation, I/O or call other methods.
     }

This defines a method 'main' of 'Kernel' object. It can be called like this.

     Kernel.main();  // or just main() as 'Kernel' is default.

Now some computation is defined within object 'Kernel', so Neon Light Compiler can take a snapshot of this object and transform it into RTL.

     Kernel.compile();  // A snapshot is taken.
     // "my_module_rtl.cpp" or "my_module_rtl.html" are also possible.
     Kernel.writeHdl("my_module_rtl.v");

### Features (selected)
(Still many of them are just in demo level).

* Prototype based object system
    * Object.clone() to create derivative designs
* Interger with width
    * Declaration like "var x #32"
* Threads
* Channels
* Verilog embedding
* C++, HTML output (in addition to Verilog)
* SSA based optimizers

## Other information

-- Command line options

* Debug options
    * -db debug byte code compiler
    * -dp debug parser
    * -ds debug scanner
    * -dt debug types
* -l
    * Enable info logging.
    * Comma separated list of modules to enable for specific files.
* --module_prefix=[mod]
    * Module name prefix.
    * File name without suffix ("a" for "a.v") will be used if this is not specified.
    * This can be used to get fixed module name for testing.
* --output_marker=[marker]
    * Marker string to be output before output file name.
    * NLI server uses this to generate links from output log.
* --print_exit_status
    * Shows exit status at the end of execution.
    * Test uses this to check if NLI isn't aborted.
* --root
    * Prefix for file output name.
    * NLI server uses this to isolate each run.
* --timeout
    * Timeout of NLI command execution.
    * Avoid infinite loop to run forever for test or NLI server.
* --vanilla
    * Don't read lib/default.n.
* --version
    * Print version number.

-- Source tree

* src/
    * Command and common utilities.
* src/base
    * Common code for other components.
* src/compiler
    * Neon Light Script to bytecode.
* src/fe
    * Neon Light Script parser.
* src/numeric
    * Numeric operations.
* src/synth
    * Bytecode to Iroha IR.
* src/vm
    * Bytecode executor.
* iroha/
    * Iroha backend.

-- Glossary

* DFG
    * Data Flow Graph to represent internal RTL
* Bytecode
    * Compiled fron Neon Light Script and can be executed or synthesized
* Iroha
    * Intermediate Representation Of Hardware Abstraction
    * https://github.com/nlsynth/iroha

-- COPYING

See COPYING file. Feel free to ask me to change to other licenses, if it is inconvenient for you.

NOTE: The license of course doesn't apply to the outputs of Neon Light Compiler executables. It's up to the author of input source code.


-- format this document

$ markdown README.md > README.html
