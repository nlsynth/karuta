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
