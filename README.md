# Karuta HLS Compiler
Author: Yusuke TABATA (tabata.yusuke@gmail.com)

## What's this?
TL;DR:
    High level synthesis (HLS) from scripting language (Karuta) to RTL (Verilog).
    The main objective is to make FPGA development productive.

See the [document at karuta.readthedocs.io](https://karuta.readthedocs.io/en/latest/) or [docs/index.rst](docs/index.rst) for more details.


If you are using recent Ubuntu, just

     $ sudo snap install karuta

to install the Karuta package.

Please follow [@karutalang on Twitter](https://twitter.com/karutalang) for updates and tips.

## Quick overview
Karuta's language is an object oriented scripting language. The syntax is similar to recently popular programming languages like JavaScript, Python, Go or so on.
Minimum code looks like as follows.

     module {
       process main() {
         // Do computation, call other methods and some I/O.
       }
     }

This defines a method 'main' of current object. It can be called like this.

     main()

Now some computation is defined within the object, so Karuta compiler can take a snapshot of this object and transform it into RTL.

     compile()  // A snapshot of the object is taken.
     writeHdl("my_module_rtl.v")  // Synthesizable verilog file is written.

## Important features

This project designed Karuta's language just to describe hardware designs instead of reusing existing languages for software.
So, some of following features are incorporated in the language constructs to make them easy to use.

* Prototype based object system to model design structures
* Communication primitives for threads
    * Threads, mailboxes, channels and so on
    * AXI, RPC like handshake, GPIO, embedded verilog and so on
* Flexible data types
    * Integer with arbitrary width (not only typical 1, 8, 16, 32, 64 and so on)
    * Custom operators for defined data types like FP16, SIMD and so on
* HDL generators and optimizers
    * Generates Verilog or HTML
    * SSA based optimizers
    * Profile guided optimizer
    * Scheduling and allocation based on device parameters
