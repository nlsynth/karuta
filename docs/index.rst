Welcome to Karuta's documentation! (WIP)
========================================

.. toctree::
   :maxdepth: 2
   :caption: Contents:

NOTE: There may be mistakes or glitches in this document due to my English skill. Please feel free to point out (or ignore...) them.

NOTE: The word Karuta means Japanese playing cards.

I am just adding various topics of Karuta to this document for now and will start to organize topics later.

Author: Yusuke Tabata (tabata.yusuke@gmail.com)

Source of this projects: <https://github.com/nlsynth/karuta> (see its docs/ directory for this document)

Karuta is an object-oriented scripting language and its compiler to design logic circuits. The main objective of Karuta is to improve the productivity of logic circuit design. This kind of software is usually known as HLS (High Level Synthesis).

Karuta has various features to support hardware design.

.. contents::


==============
Quick tutorial
==============

This section describes Karuta's features using Xorshift32 method.
Simplest Xorshift32 in Karuta is like this:

.. code-block:: none

   func main() {
     var y int = 1
     for (var i int = 0; i < 10; ++i) {
       y = y ^ (y << 13)
       y = y ^ (y >> 17)
       y = y ^ (y << 15)
       print(y)
     }
   }

   main()

Save this to a file named xorshift32.karuta, then you can run this program like

.. code-block:: none

   $ karuta xorshift32.karuta
   print: default-isynth.karuta loaded
   print: 268476417
   print: 1157628417
   print: 1158709409
    ...

I guess this looks pretty mundane to you, so let's start hardware design.

.. code-block:: none

   func main() {
     var y int = 1
     for (var i int = 0; i < 10; ++i) {
       y = y ^ (y << 13); y = y ^ (y >> 17); y = y ^ (y << 15)
       print(y)
     }
   }
   
   // Instead of calling main()
   compile()
   writeHdl("xorshift32.v")

So you can the run same karuta command again and will get xorshift32.v! The content should look like this.

.. code-block:: none

   ... 100~ lines of code in Verilog here. ...

   module xorshift32(clk, rst);
     input clk;
     input rst;
     xorshift32_main xorshift32_main_inst(.clk(clk), .rst(rst));
   endmodule

Then you can run this on a Verilog simulator with a test bench file to feed the clock and reset.

.. code-block:: none

   $ iverilog tb.v xorshift32.v
   $ ./a.out
    268476417
   1157628417
   1158709409
    269814307
   ...

OK. Looks good? But there is a big problem. The code uses $display() which is useless on real FPGAs. The next step is to generate an output port from this design.
With Karuta, you can annotate a method to make it an output port. The output value is updated when the method is called. For example,

.. code-block:: none

   @ExtIO(output = "o")
   func output(v int) {
     print(v)
   }

   func main() {
     var y int = 1
     for (var i int = 0; i < 10; ++i) {
       y = y ^ (y << 13); y = y ^ (y >> 17); y = y ^ (y << 15)
       output(y)
     }
   }

   compile()
   writeHdl("xorshift32.v")

The code above will generate a Verilog file like as follows. The top module xorshift32 has an output port 'o', so you can connect the port to other parts of your design.

.. code-block:: none

   ... 100~ lines of code in Verilog here. ...

   module xorshift32(clk, rst, o);
     input clk;
     input rst;
     output [31:0] o;
     mod_main mod_main_inst(.clk(clk), .rst(rst), .o(o));
   endmodule

This can be tidied up a bit by factoring out update formulas.

.. code-block:: none

   // Member variable of the default object for this file.
   var y int

   @ExtIO(output = "o")
   func output(v int) {
     print(v)
   }

   // Gets an argument t and returns an update value.
   func update(t int) (int) {
     t = t ^ (t << 13); t = t ^ (t >> 17); t = t ^ (t << 15)
     return t
   }

   func main() {
     y = 1
     while true {
       y = update(y)
       output(y)
     }
   }

The last example here illustrates some of the most important features of Karuta such as multiple threads and channels.

.. code-block:: none

   // This channels can be accessed like ch.write(v) or v = ch.read()
   channel ch int

   func update(t int) (int) {
     t = t ^ (t << 13); t = t ^ (t >> 17); t = t ^ (t << 15)
     return t
   }

   // main() will be compiled to be an entry point of a thread.
   func main() {
     var y int = 1
     while true {
       y = update(y)
       ch.write(y)
     }
   }

   @ExtIO(output = "o")
   func output(y #0) {
     print(y)
   }

   // @ThreadEntry() annotation makes this method as an entry point of a thread.
   @ThreadEntry()
   func thr() {
     var b #0 = 0
     while true {
       var v int = ch.read()
       // Flip the output on-off value when the generated random number is
       // below this number.
       if v < 1000000 {
         b = ~b
         output(b)
       }
     }
   }

This code has 2 thread entry points. One generates random numbers and the another reads the numbers via the channel.
When the code is compiled, generated Verilog code will have 2 state machines ('always' blocks).
You can deploy the code to an FPGA board, connect the output to an LED and see it flickers randomly.

==============
Run or Compile
==============

For example, you have a design like this and save to a file my_design.karuta

.. code-block:: none

   @ThreadEntry()
   func thr() {
     // Possibly communicate with main() and other threads.
   }

   @SoftThreadEntry()
   func testThr() {
     // Code to generate stimulus to other threads.
     // (NOTE: a thread with @SoftThreadEntry() will not be synthesized)
   }
   
   func main() {
     // Does interesting computation.
   }

You can get synthesizable Verilog file with --compile flag.

.. code-block:: none

   $ karuta my_design.karuta --compile
   ... karuta will output my_design.v


This is equivalent to call compile() and writeHdl("my_design.v") at the end of the code.

To run the threads described in the code, --run option can be used. The example above has 3 thread entries thr(), testThr() and main(), so it will make 3 threads and wait for them to finish (or timeout).

.. code-block:: none

   $ karuta my_design.karuta --run
   ... thr() and main() will run

This is equivalent to call run() at the end of the code.

===================
Default file object
===================

Karuta allocates an object for each file and the object is used as the default object while executing the code. The default object can be ommitted or explicitly denoted as *self*.

.. code-block:: none

   // All self. are optional in this example.
   var self.m int
   func self.main() {
   }
   self.compile()
   self.writeHdl("my_design.v")

=============
Integer width
=============

(Karuta also has features for user defined types (e.g. bfloat16). Document will be added later.)

Bit width of data is important to use FPGAs efficiently while it is not cared so much for CPUs. Karuta allows arbitrary bit width.

.. code-block:: none

   // Variable declarations.
   var x int  // default width is 32 bits.
   var rgb #24  // specify 24 bits.

   // This function takes a 32 bits argument (arg) and returns a 32 bits argument.
   func bswap32(arg #32) (#32) {
     // [h:l] - bit slice operator
     // ::    - bit concatenation operator
     return arg[7:0] :: arg[15:8] :: arg[23:16] :: arg[31:24]
   }


=================================
Profile Guided Optimization (PGO)
=================================

One of the most important points of opitmization is to know which part of the design is a good target of optimization. Karuta uses a technique called PGO (Profile Guided Optimization) to obtain the information.

Following example illustrates how to enable profiling. Profiling is enabled between the calls of Env.enableProfile() and Env.disableProfile(), so the profile information will be collected while running main().
compile() takes the profile information into account and does optimization.

.. code-block:: none

   func main() {
     // Does some stuff.
   }

   Env.clearProfile()
   Env.enableProfile()

   // Run actual code here.
   main()

   Env.disableProfile()

   compile()
   writeHdl("my_design.v")

=============
Karuta Syntax
=============

Comments

.. code-block:: none

   // Comment
   /* Comment too */
   # is alloed at the beginning of a file. This is for #! for shells.

Literals

.. code-block:: none

   // Just a number.
   123
   0xf00d
   0b1010
   // A number with explicit width
   123#32
   // string
   "abc"

Method definition

.. code-block:: none

   // func name(arguments) (return values) { ... }
   // (return values) can be omitted if there is no arguments.
   func funcName(arg1, arg2 #16, arg3 int) (int, int) {
     return arg1, arg3
   }

Declarations

.. code-block:: none

   //
   var x int
   var x #32
   var x #MyType
   var x object
   //
   var x, y int
   var x int = 0
   //
   channel c int
   mailbox m int

Expressions

.. code-block:: none

   //
   a + b
   a - b
   a * b
   a = b
   a, b
   (a)
   f(x)
   a = f(x,y)
   (a, b) = f(x,y)
   obj.a
   obj.f()

Statements

.. code-block:: none

   if a > b {
   } else {
   }

   for (x = 0; x < 10; ++x) {
   }

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

Indices and tables
==================

* :ref:`genindex`
* :ref:`search`
