=========
Reference
=========

.. contents::

Command line flags
==================

$ karuta <command> [Files]

* Commands(optional)

  * run - starts runnable threads (same as --run)
  * compile - compiles objects for specified files (same as --compile)
  * sim - same as ``sim`` and also with self contained shell (same as --compile and --with_shell)

* Debug options

  * -db debug byte code compiler
  * -dp debug parser
  * -ds debug scanner
  * -dt debug types

* -l

  * Enables info logging.
  * Comma separated list of modules to enable for specific files.

* --compile

  * Compiles the file object and writes to a Verilog file.
  * Calls compile() and writeHdl(name.v) at the end of execution.

* --duration

  * Maximum duration of the simulation.

* --iroha_binary [binary]

  * Specifies an alternative iroha binary.

* --module_prefix=[mod]

  * Module name prefix.
  * File name without suffix ("a" for "a.v") will be used if this is not specified.
  * This can be used to get fixed module name for testing.

* --output_marker=[marker]

  * Marker string to be output before output file name.
  * Karuta server uses this to generate links from output log.

* --flavor=[flavor]

  * Sets a specific flavor to the generated HDL files.
  * e.g. --flavor=vivado-axi

* --print_exit_status

  * Shows exit status at the end of execution.
  * Test uses this to check if karuta isn't aborted.

* --root

  * Prefix for file output name.
  * Karuta server uses this to isolate each run.

* --run

  * Runs every runnable threads in the source file.
  * Calls run() at the end of execution.

* --timeout

  * Timeout of karuta command execution.
  * Avoid infinite loop to run forever for test or Karuta server.

* --vanilla

  * Doesn't read lib/default-isynth.karuta.

* --vcd

  * Generates vcd from generated verilog file.

* --version

  * Print version number.

* --with_shell

  * Generates a top level module to feed clock and reset.

Program structure
=================

A program is comprised of top level environment and method environment.
Methods and various things can be declared only in top level environment.

.. code-block:: none

   // * Top level environment
   // Modifying objects by declaring member variables.
   //
   func f() {
     // * Method environment
     // Object modification is not allowed (hence synthesizable).
   }

Methods
-------

A method is declared as a member of an object.
If no object name is given in the declaration, the method will belong to the current file object.

.. code-block:: none

   // This method belong to the current file object.
   func f() {
   }

   @Annotation(key1="value1", key2="value2")
   func mod.f(x, y #32) (#16, #16) {
     return (0, 0)
   }

A declaration can have an argument list and return value list.
A declaration begin with a keyword either *func* or *process*.

Variable declaration
--------------------

Syntax to declare a variable is:
  [variable type] [name] [data type]
  e.g. ram a int[16]

============= ================ ========================
Variable type Data type        Note
============= ================ ========================
shared        scalar or array  Equivalent to ram or reg
ram           array            BRAM/SRAM
reg           scalar           reg
mailbox       scalar           mailbox
channel       scalar           channel
var           scalar           Local variable
============= ================ ========================

Data types of a scalar variable are:

* int - 32 bits
* #0  - boolean
* #10 - 10 bits
* #T - User define type T
* object, module - Object

A vector type is declared by [scalar type][length] like int[16].

.. code-block:: none

   // top level local variable.
   var x int
   // member variable.
   reg y int
   reg self.z int

   func f() {
     // method local variable
     var a int
     a = y + z
   }

Basic Syntax
------------

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
   //
   var s string = "abc"
   // var for an array is not allowed
   shared a int[32]
   shared m.a #16[4] = {1,2,3,4}

Expressions

.. code-block:: none

   //
   name
   __name // reserved for the implementation
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

Operators

.. code-block:: none
   
   a + b
   a - b
   a * b
   // TODO: Describe the limitations
   a / b
   // shift amount should be constant
   a >> b
   a << b
   // bit concat
   a :: b
   // range should be constant
   a[l:r]

Statements

.. code-block:: none

   if a > b {
   } else {
   }

   for var x = 0; x < 10; ++x {
   }

Control

.. code-block:: none

   if cond {
   }

   for init; cond; update {
   }

TODO: switch/case statement

module block

.. code-block:: none

   module {
     shared obj object = new()
     func bar() {
       obj.x[0] = 0
       obj.foo()
     }
   }

   module obj {
     // same as obj.foo()
     func foo() {
     }
     // same as obj.x
     shared x int[16]
   }


Built in objects and methods
============================

Objects
-------

* Object

  * Array - Internal SRAM
  * Env - Profiling
  * Global - Placeholder for global variables
  * Kernel - Base object for user's design
  * Memory - External SRAM
  * Numerics - Registry for user defined types.


Built in methods
----------------

* Object.clone()
* Object.dump()
* Object.run()
* Object.bool
* Object.false
* Object.true
* Object.Object

* Kernel.assert()
* Kernel.abort()
* Kernel.compile()
* Kernel.exit()
* Kernel.new()
* Kernel.print()
* Kernel.runIroha()
* Kernel.setDump()
* Kernel.setIROutput()
* Kernel.setIrohaPath()
* Kernel.setSynthParam()
* Kernel.synth()
* Kernel.wait()
* Kernel.widthof()
* Kernel.writeHdl()
* Kernel.yield()

* Kernel.Kernel\_
* Kernel.Object
* Kernel.Module
* Kernel.parent
* Kernel.self

* Kernel.Array
* Kernel.Env
* Kernel.Global
* Kernel.Memory
* Kernel.Numerics

* Env.gc()
* Env.clearProfile()
* Env.disableProfile()
* Env.enableProfile()
* Env.isMain()

* Array axiLoad, axiStore, waitAccess, notifyAccess, saveImage, loadImage, read, write
* Memory setWidth
* Channel write, writeFast, read
* Mailbox width, put, notify, get, wait

* .$compiled_module
* .$dump_file_name

* setIrohaPath(p string)
* setIROuput(p string)
* runIroha(opts string)

  * e.g. runIroha("-v -S -o x.v")

Synthesis parameters
====================

When compilation is requested by calling compile() method, the synthesizer takes a snapshot of the object and generates IR from the structure and computation.

.. code-block:: none

   setSynthParam("resetPolarity", 0) // set negative reset (e.g. rst_n).
   setSynthParam("maxDelayPs", 10000) // 10ns
   setSynthParam("platformFamily", "generic-platform")
   setSynthParam("platformName", "generic")

Annotations
===========

.. code-block:: none

   // Annotation for a method
   @ThreadEntry() @ProcessEntry() @Process()
   @SoftThreadEntry() @SoftProcess() @Soft()
   @ExtEntry()
   @ExtStub()
   @ExtIO()
   @ExtCombinational()
   @DataFlowEntry()  // Might be removed
   @ExtFlowStub()  // Might be removed
   // Annotation for an array
   @AxiMaster() @AxiMaster64() @AxiMaster32()
   @AxiSlave() @AxiSlave64() @AxiSlave32()
   @ThreadLocal() @ProcessLocal() @Local()
   // channel parameters
   depth=
   // object parameters
   distance=
   // thread number
   num=

========
Glossary
========

* DFG

  * Data Flow Graph to represent internal RTL

* Bytecode

  * Compiled from Karuta Light Script and can be executed or synthesized

* Iroha

  * Intermediate Representation Of Hardware Abstraction
  * https://github.com/nlsynth/iroha

* Karuta

  * Name of Japanese playing cards.
  * This package.

* Soft thread

  * Threads which will not be synthesized (used for tests).
