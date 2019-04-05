(WIP) Welcome to Karuta's documentation! (WIP)
==============================================

.. toctree::
   :maxdepth: 2
   :caption: Contents:


NOTE: There may be mistakes or glitches in this document due to my English skill. Please feel free to point out (or ignore...) them.

NOTE: The word Karuta means Japanese playing cards.

Author: Yusuke Tabata (tabata.yusuke@gmail.com)

Source of this projects: <https://github.com/nlsynth/karuta> (see its docs/ directory for this document)

Karuta is an object-oriented scripting language and its compiler to design logic circuits. The main objective of Karuta is to improve the productivity of logic circuit design. This kind of software is usually known as HLS (High Level Synthesis).

Karuta has various features to support hardware design.

==============
Quick tutorial
==============

This section describes Karuta's features using Xorshift32 method.
Simplest Xorshift32 in Karuta is like this:

.. code-block:: none

    def main() {
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

   def main() {
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
   def output(v int) {
      print(v)
   }

   def main() {
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
   def output(v int) {
      print(v)
   }

   // Gets an argument t and returns an update value.
   def update(t int) (int) {
     t = t ^ (t << 13); t = t ^ (t >> 17); t = t ^ (t << 15)
     return t
   }

   def main() {
     y = 1
     while true {
       y = update(y)
       output(y)
     }
   }

=================
Program structure
=================

======================
External communication
======================

======
Values
======

=======
Objects
=======

=====================
Source code structure
=====================

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
* :ref:`modindex`
* :ref:`search`
