# Project Neon Light
Author: Yusuke TABATA (tabata.yusuke@gmail.com)

## What's this?
This interpreter/compiler takes PhyloScript language (N language was a tentative name) as input and outputs sequential cirtuits in Verilog language.
As of now, the interpreter/compiler has too many bugs and unimplemented
features. In addition to implementation/documentation quality, many important
features are not documented and liable to change.

This software is under development to explore efficient
logic circuit design methodology.

## Usage
At first, you have to compile NLI.
> $ ./configure;make

-- when you want to use PhyloScript language
Compile tb.n
> $ cd examples
> $ ../nli tb.n

Run the output with your Verilog simulator.
> $ iverilog tb_top.v a.v
> $ ./a.out

-- command line options

* -ds debug scanner
* -dp debug parser
* -dt debug types
* -dc debug compiler
* -dg debug graph (after optimization pass)
* -O0 no optimization

-- source tree

Glossary:
* DFG
* Bytecode

* src/
    * Command and common utilities.
* src/compiler
    * PhyloScript to bytecode.
* src/dfg
    * Data flow graph.
* src/fe
    * PhyloScript parser.
* src/opt
    * DFG optimizer.
* src/synth
    * Bytecode to DFG.
* src/vm
    * Bytecode executor.
* src/writer
    * Verilog/C++ writer.

-- format this document
$ markdown README.md > README.html
