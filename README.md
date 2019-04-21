# Karuta
Author: Yusuke TABATA (tabata.yusuke@gmail.com)

## What's this?
TL;DR:
    High level synthesis (HLS) from scripting language (Karuta) to RTL (Verilog).
    The main objective is to make FPGA development productive.

See docs/LRM.md for some more details.

## Overview
Karuta Script is an object oriented scripting language. The syntax is similar to recent programming languages like JavaScript, Python, Ruby or so on.
Minimum code looks like as follows.

     func main() {
       // Do some computation, I/O or call other methods.
     }

This defines a method 'main' of current object. It can be called like this.

     main() // obj.main() can be used to specify an object.

Now some computation is defined within the object, so Karuta compiler can take a snapshot of this object and transform it into RTL.

     compile()  // A snapshot is taken.
     // "my_module_rtl.html" is also possible.
     writeHdl("my_module_rtl.v")

### Important features

This project designed its own language Karuta just only for RTL design instead of reusing existing languages.
So, some of following features are incorporated in the language constructs to make it easy to use.

* Prototype based object system to model design structures
* Flexible data types
    * Integer with width. Custom operators for defined data types like FP16
* Communication primitives
    * Threads, mailboxes, channels and so on
    * AXI, RPC like handshake, GPIO, embedded verilog and so on
* HDL generators and optimizers
    * Generates Verilog or HTML
    * SSA based optimizers
    * Scheduling and allocation based on device parameters

## Usage

-- Get the code

Check out the code with Iroha submodule.

    > $ git clone --recursive https://github.com/nlsynth/karuta
    or
    > $ git submodule update --init
    in karuta/ directory.

-- Build

At first, you have to compile the interpreter (karuta command).

    > $ ./configure
    > $ make

NOTE: Please make sure you checked out iroha submodule and have iroha/ directory

-- Use

Run top.karuta (this example outputs top.v)

    > $ cd examples
    > $ ../karuta top.karuta

Run the output with your Verilog simulator.

    > $ iverilog tb_top.v top.v
    > $ ./a.out # Icarus verilog

(If you do 'make install', karuta command will be available at the path you specified)

## Command line options

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

## COPYING

See COPYING file. Feel free to ask me to change to other licenses, if it is inconvenient for you.

NOTE: The license of course doesn't apply to the outputs of Karuta compiler executables. It's up to the author of input source code.


-- format this document

$ markdown README.md > README.html
