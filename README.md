# Karuta HLS Compiler
Author: Yusuke TABATA (tabata.yusuke@gmail.com)

## What's this?
TL;DR:
    High level synthesis (HLS) from scripting language (Karuta) to RTL (Verilog).
    The main objective is to make FPGA development productive.

See the document at [https://karuta.readthedocs.io](https://karuta.readthedocs.io/en/latest/) (or [docs/index.rst](docs/index.rst) in this repository) for more details.


If you are using recent Ubuntu, just

     $ sudo snap install karuta

to install the Karuta package. For most of other distributions (including WSL2), your can use following script to install Karuta.

     $ curl -o install-karuta.sh https://raw.githubusercontent.com/nlsynth/karuta/master/install-karuta.sh
     ## Please take a quick look what this script does. You may have to additional software packages to fix errors to build Karuta.
     $ sh install-karuta.sh

Please follow [@karutalang](https://twitter.com/karutalang) on Twitter for updates and tips.

## Quick overview

Karuta's language is an object oriented scripting language. The syntax is similar to recently popular programming languages like JavaScript, Python, Go or so on.
Minimum code looks like as follows.

     output led #1
     process {
       // Do computation, call other methods and do I/O.
       led.write(1)
     }

The code above defines some computation within the default object, so Karuta compiler can take a snapshot of the object and transform it into RTL.

     $ karuta compile mod.karuta
     (karuta writes a synthesizable Verilog file mod.v)
## Important features

This project designed Karuta's language just to describe hardware designs instead of reusing existing languages for software.
So, some of following features are incorporated in the language constructs to make them easy to use.

* Prototype based object system to model design structures
* Communication primitives for processes
    * Shared memory, mailboxe, channel and so on
    * AXI, RPC like handshake, GPIO, embedded Verilog code and so on
* Flexible data types
    * Integer with arbitrary width (not only typical 1, 8, 16, 32, 64 and so on)
    * Custom operators for defined data types like FP16, SIMD and so on
* HDL generators and optimizers
    * Generates Verilog or HTML
    * SSA based optimizers
    * Profile guided optimizer
    * Scheduling and allocation based on device parameters

## How the code looks like

Karuta is designed to describe process networks easily by using processes and communication primitives. Following example code shows some of primitives.

     // I/Os.
     input dipsw #4
     output led #4
     // Primitives for data and communication.
     reg r0 int
     ram a int[32]
     maibox mb int
     channel ch int
     shared subMod object = ...

     // processes can do computation and calculation.
     process {
       dipsw.read()
       led.write(12)
       r0 = 1
       a[123] = 345
       ch.write(234)
       mb.put(345)
     }

     process {
       wait(1000000)  // Waits 1M clocks.
       ch.read()
       mb.get()
       r0 += 1
       a[123] += 1
     }

     process {
       ...
       subMod.f()
     }
