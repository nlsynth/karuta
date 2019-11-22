User's guide
============

.. contents::

==============
Run or Compile
==============

For example, you have a design like this and save to a file my_design.karuta

.. code-block:: none

   process thr() {
     // Possibly communicate with main() and other threads.
   }
   
   @Soft
   process testThr() {
     // Code to generate stimulus to other threads.
     // (NOTE: a thread with @Soft will not be synthesized)
   }
   
   func f() {
     // Code which can be called from other methods or processes.
   }
   
   process main() {
     // Does interesting computation.
   }

Karuta generates synthesizable Verilog file, if *--compile* flag is specified.

.. code-block:: none

   $ karuta my_design.karuta --compile
   ... karuta will output my_design.v


This is equivalent to call compile() and writeHdl("my_design.v") at the end of the code.

To run the threads described in the code, *--run* option can be used. The example above has 3 thread entries *thr()*, *testThr()* and *main()*, so it will make 3 threads and wait for them to finish (or timeout).

.. code-block:: none

   $ karuta my_design.karuta --run
   ... thr(), testThr() and main() will run

This is equivalent to call *run()* at the end of the code.

=============================
Prototype-based object system
=============================

Karuta adopts prototype-base object oriented programming style. So, a new object can be created by cloning a base object and User's design is described by modifying object(s).

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

   process self.main() {
     // Accesses a member of a member.
     o.v++
   }

   process self.o.f() {
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

------------
Array images
------------

Array images can be written to a file or read from a file.

.. code-block:: none

   shared arr int[16]

   arr.saveImage("arr.image")
   arr.loadImage("arr.image")

=======
Threads
=======

Method can be declared as a thread entry. A thread will be created when the code is executed or synthesized.

.. code-block:: none

   func f() {
     // Just a method.
   }

   func main() {
     // main() is automatically treated as a thread entry.
   }

   process m1() {
     // This method will run as a thread.
   }

   @ThreadEntry
   func m2() {
     // @ThreadEntry annotation starts the method as a thread entry.
   }

============
Thread local
============

Karuta can create multiple threads from one @ThreadEntry() by specifying num= parameter.

.. code-block:: none

   @ThreadLocal()
   shared M.x int

   @ThreadEntry(num=2)
   func M.thr(idx int) {
     // 2 copies of this thread runs and the index is given as the method
     // argument. idx = 0, 1.

     // x is a per thread variable.
     x = x + idx
   }

=========================
Communication to external
=========================

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

---------------------
AXI interface support
---------------------

Karuta supports AXI master/slave interface. Karuta attaches a DMA controller to an SRAM to use an AXI interface.

^^^^^^^^^^
AXI master
^^^^^^^^^^

.. code-block:: none

   // @AxiMaster(addrWidth = 64) // or 32 (default) to specify the width.
   // @AxiMaster(sramConnection = "shared") // or "exclusive" (default).
   @AxiMaster()
   shared m int[16]

   def f() {
     m.load(mem_addr, count, array_addr)
     m.store(mem_addr, count, array_addr)
   }

^^^^^^^^^
AXI slave
^^^^^^^^^

.. code-block:: none

   @AxiSlave()
   shared s int[16]

   func f() {
     while true {
       s.waitAccess()
     }
   }

`notifyAccess()` method can be used for testing.

----------------
Method interface
----------------

Karuta supports the Method Interface <https://gist.github.com/ikwzm/bab67c180f2f1f3291998fc7dbb5fbf0> to communicate with external circuits.

.. code-block:: none

   // f() will be callable outside of the design.
   @ExtEntry(name="e")
   def f(x int) (int) {
     return 0
   }

   // Actual implementation of f() will be outside of the design.
   @ExtStub(name="e")
   def f(x int) (int) {
     return 0
   }

----------------------------
Embedded combinational logic
----------------------------

A combinational logic in a Verilog module can be embedded in a function of Karuta by spcifying the file name and module name by @ExtCombinational annotation.

.. code-block:: none

   @ExtCombinational(resource = "a", verilog = "resource.v", file="copy", module="my_logic")
   func f(x #32) (#32) {
     // This code is used by the interpreter, but Verilog module in resource.v
     // is used in synthesized code.
     return x + 1
   }

Embedded Verilog module has input arguments arg_0, arg_1,, arg_N and output arguments ret_0, ret_1,, ret_N. The number of inputs and outputs should match with the original function.

.. code-block:: none

   module my_logic(input clk, input rst, input [31:0] arg_0, output [31:0] ret_0);
     assign ret_0 = arg_0 + 1;
   endmodule

===================
Channel and mailbox
===================

Communication between threads is really important for circuit design.
While one simple way of communication is just to use shared registers or arrrays, Karuta also supports channel and mailbox to communicate between threads.

This example this just write values and read them from other threads.

.. code-block:: none

   channel ch int

   process th1() {
     ch.write(1)
     ch.write(1)
   }

   process th2() {
     ch.read()
   }

   // channel can be written or read by arbitrary number of threads.
   process th3() {
     ch.read()
   }

A mailbox is just a channel with one value.

.. code-block:: none

   mailbox mb int

   process th1() {
     mb.put(1)
   }

   process th2() {
     mb.get()
   }

But it can notify waiting threads.

.. code-block:: none

   mailbox mb int

   process th1() {
     mb.notify(10)
   }

   process th2() {
     print(mb.wait())
   }

===========
Method call
===========


.. code-block:: none

   shared m object = new()
   func m.f() {
   }

   func g() {
   }

   process th1() {
     // Does handshake and arbitration
     m.f()
     // Inlined for this thread.
     g()
   }

   process th2() {
     // Does handshake and arbitration
     m.f()
     // Different inlined instance for this thread.
     g()
   }

===========
Type object
===========

.. code-block:: none

   shared Numerics.Int32 object = Object.clone()
   func Numerics.Int32.Build(arg #32) (#32) {
     return arg
   }

   func Numerics.Int32.Add(lhs, rhs #32) (#32) {
     return lhs + rhs
   }

   // Type class can't be accessed from top level environment.
   func f() {
     var x #Int32
     x = Numerics.Int32.Build(1)
     print(x + x)
   }

   // Add a method for the type.
   func Numerics.Int32.IsZero(arg #32) (bool) {
     return arg == 0
   }

   func g() {
     var x #Int32
     x = Numerics.Int32.Build(1)
     print(x.IsZero())
     x + x
   }		

-----------------------------
Custom data type with Verilog
-----------------------------

Type object and embedded combinational logic can be used to build a custom type with staged operations (e.g. FP16, complex num, RGB and so on).

.. code-block:: none

   func Numerics.MyType.Add(lhs, rhs #32) (#32) {
     // 3 stage (clocks) operation.
     return add_st3(add_st2(add_st1(lhs, rhs)))
   }

   @ExtCombinational(resource = "my_type", verilog = "my_type.v", file="copy", module="my_logic_st1")
   func add_st1(lhs, rhs #32) (#32, #32) {
     return rhs, lhs
   }
   // add_st2 and add_st3 here.


=========================
Building object hierarchy
=========================

The basic way to build an object hierarcy is to declare member

.. code-block:: none

   shared x object = new()
   shared x.y object = new()
   func x.f() {
     y.g()
   }
   func x.y.g() {
     print(1)
   }
   func main() {
     x.f()
   }

This structure can be a more cleanly described with `with` block.

.. code-block:: none

   shared x object = new()
   shared x.y object = new()
   with x {
     with y {
       func g() {
         print(1)
       }
     }
     func f() {
       y.g()
     }
   }
   func main() {
     x.f()
   }

When `with` block is used, the member object can access its enclosing object by `parent` keyword.

.. code-block:: none

   shared x object = new()
   with x {
     func f() {
       parent.g()
     }
   }
   func g() {
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

===============
Object distance
===============

Elements of designs are placed onto the physical area of FPGAs and there are distances between them. So Karuta has a feature to specify number of clocks to propagete signals for communication.

.. code-block:: none

   // Object distance between `self` and `m` is 10 clocks.
   @_(distance=10)
   shared self.m object = new()
   shared self.m.v int

   func self.m.f() {
     v = v + 1
   }

   func self.f() {
     m.v = 1
     m.f()
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

=================
Visualize designs
=================

Karuta can visualize following 3 aspects of input designs.

(1) Structure of objects in Karuta.
(2) Structure of modules and FSMs.
(3) Details of each FSM.

Output can be either in HTML or DOT (format for Graphviz <https://www.graphviz.org/>)

============================= ====== ===============================
Type                          Format Usage
============================= ====== ===============================
Structure of objects          DOT    --dot option and call synth()
Structure of modules and FSMs DOT    writeHdl() with file name .dot
Details of each FSM           HTML   writeHdl() with file name .html
============================= ====== ===============================

(1) Structure of objects is generated when the script calls synth() method if command line option '--dot' is specified.

.. code-block:: none

   # synth() is called in design.karuta
   $ karuta design.karuta --dot
   # karuta generates design.0.dot file. Use 'dot' command to generate a png image file.
   $ dot -Tpng design.0.dot -o design.png

(2) Structure of modules and FSMs and (3) Details of each FSM can be generated by specifying appropriate file name suffix.

.. code-block:: none

   // Outputs Verilog.
   writeHdl("design.v")
   // Outputs (2) Structure of modules and FSMs in DOT format.
   writeHdl("design.dot")
   // Outputs (3) Details of each FSM in HTML format.
   writeHdl("design.html")

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
