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

-- Install

At first, you have to compile the interpreter (nli command).

    > $ ./configure;make
    > $ make install # optional

-- Use

Run tb.n (this example outputs a.v)

    > $ cd examples
    > $ ../nli tb.n

Run the output with your Verilog simulator.

    > $ iverilog tb_top.v a.v
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
    * Declaration like "int #32 x;"
* Threads
* Channels
* Verilog embedding
* C++, HTML output (in addition to Verilog)
* SSA based optimizers

## Other information

-- Command line options

* -ds debug scanner
* -dp debug parser
* -dt debug types
* -dc debug compiler
* -dg debug graph (after optimization pass)
* -O0 no optimization

-- Source tree

* src/
    * Command and common utilities.
* src/compiler
    * Neon Light Script to bytecode.
* src/dfg
    * Data flow graph.
* src/fe
    * Neon Light Script parser.
* src/opt
    * DFG optimizer.
* src/synth
    * Bytecode to DFG.
* src/vm
    * Bytecode executor.
* src/writer
    * Verilog/C++ writer.

-- Glossary

* DFG
    * Data Flow Graph to represent internal RTL
* Bytecode
    * Compiled fron Neon Light Script and can be executed or synthesized

-- COPYING
See COPYING file. Feel free to change to other licenses.

-- format this document

$ markdown README.md > README.html
