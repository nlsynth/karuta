User's guide
============

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
   shared y int

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
       if v < 10000 {
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

=============================
Prototype-based object system
=============================

Karuta adopts prototype-base object oriented programming style.

.. code-block:: none

   // Temporary object.
   var o object = new()

   // Adds 2 method f() and g()
   func o.f() {
     print(g())
   }
   func o.g() (int) {
     return 1
   }

   // Makes 2 clones of the object `o` and set them as member objects of `self`.
   shared self.o1 object = o.clone()
   shared self.o2 object = o.clone()

   // Modifies one of them a bit.
   func o2.g() (int) {
     return 2
   }

   // `self` can access 2 objects and their methods.
   func self.main() {
     o1.f()
     o2.f()
   }

===================
Default file object
===================

Karuta allocates an object for each file and the object is used as the default object while executing the code. The default object can be ommitted or explicitly denoted as *self*.

.. code-block:: none

   // All self. are optional in this example.
   shared self.m int
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

================
Member variables
================

Karuta is an object oriented language, so a design can be described as objects and their members. `shared` keyword is used to declare an member value of an in teger, array or object (other kinds of member has different syntax).


.. code-block:: none

   // `self.` part can be omitted. Just `shared o object` is also ok.
   shared self.o object = new()
   // This declares a member of a member `o`.
   shared self.o.v int

   func self.main() {
     // Accesses a member of a member.
     o.v++
   }

   @ThreadEntry()
   func self.o.f() {
     v = 0
   }

======
Arrays
======

Arrays are really important to utilize FPGA, so Karuta has features to use arrays efficiently.

.. code-block:: none

   shared arr int[16]

   func f(idx int) (int) {
     // This index wraps around by 16.
     return arr[idx - 1] + arr[idx] + arr[idx + 1]
   }

One important diffrence from Karuta and other languages is that an array index wraps around by the length of the array.

=====================
AXI interface support
=====================

----------
AXI master
----------

.. code-block:: none

   @AxiMaster()
   shared m int[16]

   def f() {
     m.load(mem_addr, count, array_addr)
     m.store(mem_addr, count, array_addr)
   }

---------
AXI slave
---------

.. code-block:: none

   @AxiSlave()
   shared s int[16]

   func f() {
     while true {
       s.waitAccess()
     }
   }

=====================
Handshake to external
=====================

--------------------
I/O from/to external
--------------------

.. code-block:: none

   @ExtIO(output = "o")
   func L.f(b bool) {
   }

   @ExtIO(input = "i")
   func L.g() (bool) {
     return true
   }

----------------
Method interface
----------------

Karuta supports the Method Interface <https://gist.github.com/ikwzm/bab67c180f2f1f3291998fc7dbb5fbf0> to communicate with external circuits.

===================
Channel and mailbox
===================

Communication between threads is really important for circuit design.
While one simple way of communication is just to use shared registers or arrrays, Karuta also supports channel and mailbox to communicate between threads.

This example this just write values and read them from other threads.

.. code-block:: none

   channel ch int

   @ThreadEntry()
   func th1() {
     ch.write(1)
     ch.write(1)
   }

   @ThreadEntry()
   func th2() {
     ch.read()
   }

   // channel can be written or read by arbitrary number of threads.
   @ThreadEntry()
   func th3() {
     ch.read()
   }

A mailbox is just a channel with one value.

.. code-block:: none

   mailbox mb int

   @ThreadEntry()
   func th1() {
     mb.put(1)
   }

   @ThreadEntry()
   func th2() {
     mb.get()
   }

But it can notify waiting threads.

.. code-block:: none

   mailbox mb int

   @ThreadEntry()
   func th1() {
     mb.notify(10)
   }

   @ThreadEntry()
   func th2() {
     print(mb.wait())
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

==============
Importing file
==============

.. code-block:: none

   // Just reads and executes the file.
   import "filename_1.karuta"

   // Reads the file and assigns a local variable `m`.
   import "filename_2.karuta" as m

   // Now you can access m.
   m.dump()

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

   for var x = 0; x < 10; ++x {
   }

=======
Testing
=======

Karuta's features for object oriented programming can be used to test designs as well. One key idea is to create an enclosing tester object for the design (There may be other ways).

.. code-block:: none

   // design.karuta
   func f(arg int) (int) {
     return arg + 1
   }

.. code-block:: none

   // test.karuta
   // imports the design file and assigns the object to a local object `d`.
   import "design.karuta" as d

   // assigns to a member object.
   shared design object = d

   func main() {
     assert(design.f(10) == 11)
   }

   run()

====================
Platform description
====================

============
Installation
============

If you are using Ubuntu, just do

.. code-block:: none

   $ sudo snap install karuta

Installing Karuta from its source code requires a C++ compiler (namely g++ or clang++), python, gyp (Makefile generator) and make.

.. code-block:: none

   # Get the source code.
   $ git clone --recursive https://github.com/nlsynth/karuta

   # Do build.
   $ ./configure
   $ make

   # Compile an example.
   $ cd examples
   $ ../karuta top.karuta

   # Test the output from the example.
   $ iverilog tb_top.v top.v
   $ ./a.out
