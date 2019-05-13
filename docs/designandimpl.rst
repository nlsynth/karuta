Design and Implementation
=========================

.. contents::

==================
Overview of Karuta
==================

As readers might know, there have been a good amount of efforts to improve efficiency to design digital circuits. One of the most significant achievement in this area is the introduction of RTL and languages which can describe in RTL. The introduction of RTL was so successful and most of recent designs are done in RTL.

Karuta is one of the efforts to make some of circuit designs more efficient. Karuta is a new programming designed for this purpose and its compiler. The language introduces higher level abstraction than RTL (so called HLS).

While most of other attempts to introduce higher level abstraction adopt existing programming languages for software, Karuta project designs a new language. This is because I believe following things:

1. Different assumptions on underlying hardware.

   * Most of languages for software have some assumptions that they run on CPUs with an instruction pointer, one global address space and so on.
2. Reuse is not easy.

   * Reusing an existing language still requires to get familiar with different semantics from that for software, while is said to save efforts to learn a new language.
   * Anyway many of users have to learn a new language because there is no lingua franca nowadays.
3. Own language will make it easy to experiment new ideas and features.

   * It is also fun!

With above hypotheses, Karuta's design took following considerations.

* Concurrency and communication

Use of concurrency is an essential issue in hardware designs. A whole design is placed over the area of an FPGA and computation can happen anywhare on it. So Karuta aims to make it easy to describe such a behavior by threads.

A thread on software is typically a natural unit of computation from its beginning to the end and can be assigned to a CPU when it is available. This also means any thread with any computation can be assigned to a CPU.

On the other hand, Karuta assumes a thread is a piece of computation and corresponds to an FSM instance on an FPGA. So a whole design will consist of threads and their communications.


* Object system

To choose features to support object oriented programming, language designers usually have to consider two issues; (1) Users' convenience and (2) Runtime efficiency. So we have to be careful about the differences of these conditions from software design.

Most of software languages uses class based object oriented programming. It works really well by assigning each class to code and each instance to data. On the other hand, Karuta's hypothesis is prototype based object oriented programming seems to fit better for hardware design.
Karuta assumes it is more intuitive to place code as an FSM and make member variables as registers or RAMs.


* Arrays

Efficient use of RAM is also crucial for programs on FPGAs. While most of software runtime assumes a shared memory between threads, FPGAs allow to put RAMs near the place where the actual computation is done. This is important to achieve higher performance and energy efficiency.

Karuta allows to add arrays as member of an object and maps them to RAMs at synthesis.


* Data types

CPUs, GPUs and most of accelerators have fixed set of data types and operators for them. It can be inefficient if narrow data type is enough for the purpose.
So Karuta is designed to allow arbitrary data width.

In addition to allow arbitrary width, Karuta allows to define custom operators to variables. This makes it easy to implement data types like narrower/wider precision floating/fixed points or vector-ish data types like complex numbers, RGB or so on.

* Interface to outside of the design

Every design has some kinds of I/Os like master or slave interface of a certain bus protocol, GPIO, handshake or so on. Karuta supports them by annotations to a method or an array.

------------------------
Compiler and interpreter
------------------------

Once the behavior of a design is written in Karuta language, `karuta` command can execute it as an interpreter or generate the RTL description of the behavior.
So, users can simulate and test the behavior on Karuta's interpreter first before implementing it on real FPGAs.

--------------------------
Simple and familiar syntax
--------------------------

Karuta adopts syntax similar to recently popular programming languages. For example, declaring a variable is like `var x int = 123`.
Karuta also takes some syntax from HDLs so bits can be sliced like `x[15:8]` and concatenated like `x :: y`.

---------
Use of IR
---------

Karuta adopts Iroha (Intermediate Representation Of Hardware Abstraction) as its IR and backend which borrowed concepts from LLVM. Karuta generates Iroha based IR and Iroha takes it as its input, optimize and write out HDL files.

======================================
Architecture and source code structure
======================================

Karuta parses an input source code file, builds an AST (fe::Method), then compiles (by compiler::Compiler) into a bytecode sequence (vm::Method). A bytecode sequence can be executed (by vm::Executor) or synthesized to HDL.

To synthesize HDL from a bytecode sequence, Karuta uses Iroha library. Karuta builds Iroha's data structure (iroha::IDesign) and dumps the results into a file, then it invokes iroha command to perform some optimizations and conversion to HDL.


* src/

  * Command and common utilities.
* src/base

  * Common code for other components.
* src/compiler

  * Karuta Script to bytecode.
* src/fe

  * Karuta Script parser.
* src/synth

  * Bytecode to Iroha IR.
* src/vm

  * Bytecode executor.
* iroha/

  * Iroha backend.
