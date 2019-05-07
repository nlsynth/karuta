Reference
=========

==================
Command line flags
==================

* Debug options

  * -db debug byte code compiler
  * -dp debug parser
  * -ds debug scanner
  * -dt debug types

* -l

  * Enable info logging.
  * Comma separated list of modules to enable for specific files.

* --compile

  * Compiles the file object and writes to a Verilog file.
  * Calls compile() and writeHdl(name.v) at the end of execution.

* --module_prefix=[mod]

  * Module name prefix.
  * File name without suffix ("a" for "a.v") will be used if this is not specified.
  * This can be used to get fixed module name for testing.

* --output_marker=[marker]

  * Marker string to be output before output file name.
  * Karuta server uses this to generate links from output log.

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

  * Don't read lib/default-isynth.karuta.

* --version

  * Print version number.

=================
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

-------
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

A method declaration can have an argument list and return value list.

--------------------
Variable declaration
--------------------

================
Built in methods
================

* Object

  * Kernel

    * Module

* Object.clone()
* Object.dump()
* Object.setDump()
* Object.assert()
* Object.Kernel()

* Kernel.abort()
* Kernel.compile()
* Kernel.exit()
* Kernel.print()
* Kernel.writeHdl()
* Kernel.bool()
* Kernel.Object()
* Kernel.Module ()

* .$compiled_module
* .$dump_file_name

===========
Annotations
===========

.. code-block:: none

   // Annotation for a method
   @ThreadEntry()
   @SoftThreadEntry()
   @ExtEntry()
   @ExtStub()
   @ExtIO()
   @ExtCombinational()
   @DataFlowEntry()  // Might be removed
   @ExtFlowStub()  // Might be removed
   // Annotation for an array
   @AxiMaster()
   @AxiSlave()
   @ThreadLocal()
   // channel parameters
   depth=
   // object parameters
   distance=

========
Glossary
========

* DFG

  * Data Flow Graph to represent internal RTL

* Bytecode

  * Compiled fron Karuta Light Script and can be executed or synthesized

* Iroha

  * Intermediate Representation Of Hardware Abstraction
  * https://github.com/nlsynth/iroha

* Karuta

  * Name of Japanese playing cards.
  * This package.

* Soft thread

  * Threads which will not be synthesized (used for tests).
